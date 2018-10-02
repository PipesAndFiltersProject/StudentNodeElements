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

void PlainStudentFileHandler::readFile() {
   StudentFileReader reader(*this);
   reader.read(node.getDataFileName());
}

bool PlainStudentFileHandler::consume(OHARBase::Package & data) {
	if (data.getType() == OHARBase::Package::Control) {
      if (data.getData() == "readfile") {
         readFile();
      }
   }
   return false; // false: pass to next handler. true: do not pass to next handler.
}

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

