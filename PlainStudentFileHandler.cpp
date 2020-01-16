//
//  PlainStudentFileHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//


#include <sstream>

#include <g3log/g3log.hpp>

#include <OHARBaseLayer/ProcessorNode.h>
#include <OHARBaseLayer/Package.h>

#include <OHARStudentLayer/PlainStudentFileHandler.h>
#include <OHARStudentLayer/StudentDataItem.h>
#include <OHARStudentLayer/StudentFileReader.h>


namespace OHARStudent {
   
   const std::string PlainStudentFileHandler::TAG{"SPlainFileHandler "};
   
   PlainStudentFileHandler::PlainStudentFileHandler(OHARBase::ProcessorNode & myNode)
   : node(myNode)
   {
   }
   
   PlainStudentFileHandler::~PlainStudentFileHandler() {
      
   }
   
   /** Uses a StudentFileReader for reading student data from a file.
    File name is acquired from the ProcessorNode configuration. */
   void PlainStudentFileHandler::readFile() {
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
    Checks if the package contains a control message indicating that
    a data file should be read. If yes, reads the data using readFile().
    @param data The package message indicating what to do.
    @returns Returns always false, pass the package to next handler.
    */
   bool PlainStudentFileHandler::consume(OHARBase::Package & data) {
      if (data.getType() == OHARBase::Package::Control) {
         if (data.getPayloadString() == "readfile") {
            readFile();
         }
      }
      return false; // false: pass to next handler. true: do not pass to next handler.
   }
   
   /** This method is called by the StudentFileReader when the new data item has
    been read from the data file. The student object is then placed in a Package
    and passed on to the next DataHandler in the ProcessorNode.
    @param item The new student data item read from the file.
    */
   void PlainStudentFileHandler::handleNewItem(std::unique_ptr<OHARBase::DataItem> item) {
      // Check if the item is already in the container.
      LOG(INFO) << TAG << "One new file data item received";
      StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item.get());
      if (newStudent) {
         LOG(INFO) << TAG << "Creating a package...";
         OHARBase::Package package;
         package.setType(OHARBase::Package::Data);
         package.setPayload(std::move(item));
         LOG(INFO) << TAG << "... to pass to next handler.";
         node.passToNextHandlers(this, package);
      }
   }
   
   
} //namespace

