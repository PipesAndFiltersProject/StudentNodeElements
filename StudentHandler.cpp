//
//  ExerciseMergerHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include <g3log/g3log.hpp>

#include <OHARBaseLayer/ProcessorNode.h>
#include <OHARBaseLayer/Package.h>

#include <OHARStudentLayer/StudentHandler.h>
#include <OHARStudentLayer/StudentDataItem.h>
#include <OHARStudentLayer/StudentFileReader.h>


namespace OHARStudent {

	
   StudentHandler::StudentHandler(OHARBase::ProcessorNode & myNode)
   : node(myNode), TAG("StudentHandler ")
   {
   }

   StudentHandler::~StudentHandler() {
   }

   /** Reads student data from an input file, using StudentFileReader.
    The file name to read data from is gotten from the ProcessorNode, which
    has the input file name as a configuration item. That file is then read.
    */
   void StudentHandler::readFile() {
      StudentFileReader reader(*this);
      reader.read(node.getDataFileName());
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
    @param data The Package containin the student data to handle.
    @returns Returns true if the data was handled and further processing of the package should
    not be done. Returns false if package should be handled by following DataHandlers.
    */
   bool StudentHandler::consume(OHARBase::Package & data) {
      bool retval = false; // didn't consume, pass to next handler.
      if (data.getType() == OHARBase::Package::Data) {
         OHARBase::DataItem * item = data.getDataItem();
         if (item) {
            StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item);
            if (newStudent) {
               node.showUIMessage("Got student data for " + newStudent->getName());
               LOG(INFO) << TAG << "Consuming data from network";
               StudentDataItem * containerStudent = findStudent(*newStudent);
               if (containerStudent) {
                  LOG(INFO) << TAG << "Student data from file & net merged now. " << containerStudent->getName();
                  node.showUIMessage("Found local student data, merging with received data.");
                  newStudent->addFrom(*containerStudent);
                  dataItems.remove(containerStudent);
                  delete containerStudent;
                  node.passToNextHandlers(this, data);
               } else {
                  LOG(INFO) << TAG << "No matching student data from file yet, hold it in container.";
                  node.showUIMessage("No local data for this student, waiting for it");
                  dataItems.push_back(newStudent->copy());
                  retval = true; // consumed the item and keeping it until additional data found.
               }
            }
         }
      } else if (data.getType() == OHARBase::Package::Control) {
         if (data.getData() == "readfile") {
            readFile();
         }
      }
      return retval; // false: pass to next handler. true: do not pass to next handler.
   }

   /**
    Handles new student data read from a file.
    If the same student data is already in the handler's container, data is combined and
    can now be forwarded to following DataHandlers. If not, student object is placed in
    the container and it waits there for further data (from the previous Node in the network).
    @param item The data item read from the file.
    */
   void StudentHandler::handleNewItem(OHARBase::DataItem * item) {
      // Check if the item is already in the container.
      LOG(INFO) << TAG << "One new data item from file";
      StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item);
      node.showUIMessage("Student data read from file for " + newStudent->getName());
      StudentDataItem * containerStudent = findStudent(*newStudent);
      if (containerStudent) {
         node.showUIMessage("Had received same student data from previous node, combining.");
         LOG(INFO) << TAG << "Student already in container, combine and pass on! " << containerStudent->getName();
         newStudent->addFrom(*containerStudent);
         OHARBase::Package p;
         p.setType(OHARBase::Package::Data);
         p.setDataItem(newStudent);
         dataItems.remove(containerStudent);
         delete containerStudent;
         node.passToNextHandlers(this, p);
      } else {
         node.showUIMessage("Have not yet got data for this student from previous node, holding data.");
         LOG(INFO) << TAG << "No matching student data from network, hold it in container. " << containerStudent->getName();
         dataItems.push_back(newStudent);
      }
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
