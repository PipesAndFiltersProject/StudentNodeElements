//
//  PlainStudentFileHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//


#include <sstream>

#include "PlainStudentFileHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "StudentFileReader.h"
#include "Package.h"
#include "Log.h"


namespace OHARStudent {

	
   PlainStudentFileHandler::PlainStudentFileHandler(OHARBase::ProcessorNode & myNode)
   : node(myNode), TAG("PlainFileHandler")
   {
   }

   PlainStudentFileHandler::~PlainStudentFileHandler() {
      
   }

   /** Uses a StudentFileReader for reading student data from a file.
    File name is acquired from the ProcessorNode configuration. */
   void PlainStudentFileHandler::readFile() {
      StudentFileReader reader(*this);
      reader.read(node.getDataFileName());
   }

   /**
    Checks if the package contains a control message indicating that
    a data file should be read. If yes, reads the data using readFile().
    @param data The package message indicating what to do. 
    @returns Returns always false, pass the package to next handler.
    */
   bool PlainStudentFileHandler::consume(OHARBase::Package & data) {
      if (data.getType() == OHARBase::Package::Control) {
         if (data.getData() == "readfile") {
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
   void PlainStudentFileHandler::handleNewItem(OHARBase::DataItem * item) {
      // Check if the item is already in the container.
      OHARBase::Log::getInstance().entry(TAG, "One new file data item received");
      StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item);
      if (newStudent) {
         OHARBase::Log::getInstance().entry(TAG, "Creating a package to send ahead...");
         OHARBase::Package p;
         p.setType(OHARBase::Package::Data);
         p.setDataItem(newStudent);
         delete newStudent;
         OHARBase::Log::getInstance().entry(TAG, "Pass to next handler.");
         node.passToNextHandlers(this, p);
      }
   }
      
	
} //namespace

