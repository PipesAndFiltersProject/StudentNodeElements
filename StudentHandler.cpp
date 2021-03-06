//
//  ExerciseMergerHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include <g3log/g3log.hpp>

#include <ProcessorNode/ProcessorNode.h>
#include <ProcessorNode/Package.h>

#include <StudentNodeElements/StudentHandler.h>
#include <StudentNodeElements/StudentDataItem.h>
#include <StudentNodeElements/StudentFileReader.h>


namespace OHARStudent {
   
   const std::string StudentHandler::TAG{"StudentHandler "};
   
   StudentHandler::StudentHandler(OHARBase::ProcessorNode & myNode)
   : node(myNode)
   {
   }
   
   StudentHandler::~StudentHandler() {
   }
   
   /** Reads student data from an input file, using StudentFileReader.
    The file name to read data from is gotten from the ProcessorNode, which
    has the input file name as a configuration item. That file is then read.
    Note that PlainStudentFileHandler has similar functionality. It is used in Nodes
    which do not need StudentHandler (no merging of student object is needed), but
    student data files still need to be read and handled.
    */
   void StudentHandler::readFile() {
      // Why read the file in a thread? When readfile control Package arrives from the previous Node,
      // and this node starts handling the command, the control / command handling is executed
      // in the context of the incomingHandlerThread -- effectively stopping the handling of other
      // packages waiting in the network interface, until file is read. Or, if the command is executed in the context of
      // command handler thread, then other commands cannot be handled until file has been read -- if the
      // file to read is very large, this could take seconds/tens of seconds. So, start a new thread when the file
      // is read, to let the other thread continue the work it needs to do.
      // This would be an issue only with very large files, so if optimization would be required, change the code below
      // so that first, check the size of the file and if it is small then execute file reading without a thread.
      // If it is large, then do as below, read the file in a thread.
      std::thread( [this] {
         StudentFileReader reader(*this);
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(50ms);
         reader.read(node.getDataFileName());
      }).detach();
   }
   
   /**
    Consumes a package holding student data. When the data package is handled,
    first the method checks if a corresponding student object is already in the
    handler's container. If yes, then the data is combined with the arriving data,
    and the object is passed to the next handler. If a correspoding student object
    is not in the container, is is placed there for future handling. The idea is
    thus to combine student data from various sources (previous Node, file) and then
    pass the data to next handlers. Usually this means finally that the last handler
    will send the student data to the next Node.
    @param data The Package containing the student data to handle.
    @returns Returns true if the data was handled and further processing of the package should
    not be done. Returns false if package should be handled by following DataHandlers.
    */
   bool StudentHandler::consume(OHARBase::Package & data) {
      bool retval = false; // didn't consume, or if consumed, still pass to next handler.
      if (data.getType() == OHARBase::Package::Data) {
         OHARBase::DataItem * item = data.getPayloadObject();
         if (item) {
            StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item);
            if (newStudent) {
               node.showUIMessage("Got student data for " + newStudent->getName());
               LOG(INFO) << TAG << "Consuming data from network";
               // Since several threads can call handlers' consume at the
               // same time, must use a mutex to guard multithreaded access to the list.
               // Lock will be released when the guard variable goes out of scope (leaving the if block).
               std::lock_guard<std::mutex> guard(listGuard);
               StudentDataItem * containerStudent = findStudent(*newStudent);
               if (containerStudent) {
                  LOG(INFO) << TAG << "Student data at node merged now with incoming. " << containerStudent->getName();
                  node.showUIMessage("Found local student data, merging with received data.");
                  newStudent->addFrom(*containerStudent);
                  dataItems.remove(containerStudent);
                  delete containerStudent;
               } else {
                  node.showUIMessage("No local data for this student, waiting for it");
                  dataItems.push_back(newStudent->clone().release());
                  LOG(INFO) << TAG << "No matching student data from file yet, hold it in container with " << dataItems.size()+1 << " elements";
                  retval = true; // consumed the item and keeping it until additional data found.
               }
               node.updatePackageCountInQueue("handler", dataItems.size());
            } // guard lock released here.
         }
      } else if (data.getType() == OHARBase::Package::Control) {
         if (data.getPayloadString() == "readfile") {
            readFile();
         }
      }
      return retval; // false: pass to next handler. true: do not pass to next handler.
   }
   
   /**
    Handles new student data.
    If the same student data is already in the handler's container, data is combined and
    can now be forwarded to following DataHandlers. If not, student object is placed in
    the container and it waits there for further data (from the previous Node in the network).
    @param item The data item read from the file.
    */
   void StudentHandler::handleNewItem(std::unique_ptr<OHARBase::DataItem> item) {
      // Check if the item is already in the container.
      LOG(INFO) << TAG << "One new data item from file";
      StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item.get());
      if (newStudent) {
         node.showUIMessage("Student data read from file for " + newStudent->getName());
         // Since several threads can call handlers' consume at the
         // same time, must use a mutex to guard multithreaded access to the list.
         // Lock will be released when the guard variable goes out of scope (leaving the if block).
         std::lock_guard<std::mutex> guard(listGuard);
         StudentDataItem * containerStudent = findStudent(*newStudent);
         if (containerStudent) {
            node.showUIMessage("Had received same student data from previous node, combining.");
            LOG(INFO) << TAG << "Student already in container, combine and pass on! " << containerStudent->getName();
            newStudent->addFrom(*containerStudent);
            OHARBase::Package package;
            package.setType(OHARBase::Package::Data);
            package.setPayload(std::move(item));
            dataItems.remove(containerStudent);
            delete containerStudent;
            LOG(INFO) << "METRICS students in handler: " << dataItems.size();
            node.passToNextHandlers(this, package);
         } else {
            node.showUIMessage("Have not yet got data for this student from previous node, holding data.");
            node.showUIMessage("Holding " + std::to_string(dataItems.size()+1) + " students now.");
            LOG(INFO) << TAG << "No matching student data from network, hold it in container. " << newStudent->getName();
            dataItems.push_back(newStudent);
            item.release();
            LOG(INFO) << "METRICS students in handler: " << dataItems.size();
         }
         node.updatePackageCountInQueue("handler", dataItems.size());
      } // guard lock goes out of scope here and is released.
      LOG(INFO) << TAG << "Container holds " << dataItems.size()+1 << " students.";
      
   }
   
   /** Finds a student from the container, if one exists.
    @param which The student to search for.
    @returns A pointer to the student in the container, null if student was not found.
    */
   StudentDataItem * StudentHandler::findStudent(const StudentDataItem & which) const {
      for (std::list<OHARBase::DataItem*>::const_iterator iter = dataItems.begin(); iter != dataItems.end(); iter++) {
         StudentDataItem * containerStudent = dynamic_cast<StudentDataItem*>(*iter);
         if (which == *containerStudent) {
            return containerStudent;
         }
      }
      return nullptr;
   }
   
   
} //namespace
