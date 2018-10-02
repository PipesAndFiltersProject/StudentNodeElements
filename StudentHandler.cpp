//
//  ExerciseMergerHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include "StudentHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "StudentFileReader.h"
#include "Package.h"
#include "Log.h"


namespace OHARStudent {

	
StudentHandler::StudentHandler(OHARBase::ProcessorNode & myNode)
: node(myNode), TAG("StudentHandler")
{
}

StudentHandler::~StudentHandler() {
   
}

void StudentHandler::readFile() {
   StudentFileReader reader(*this);
   reader.read(node.getDataFileName());
}

bool StudentHandler::consume(OHARBase::Package & data) {
   bool retval = false; // didn't consume, pass to next handler.
	if (data.getType() == OHARBase::Package::Data) {
      OHARBase::DataItem * item = data.getDataItem();
      if (item) {
         StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item);
         if (newStudent) {
            OHARBase::Log::getInstance().entry(TAG, "Consuming data from network");
            StudentDataItem * containerStudent = findStudent(*newStudent);
            if (containerStudent) {
               OHARBase::Log::getInstance().entry(TAG, "Student data from file & net merged now.");
               newStudent->addFrom(*containerStudent);
               dataItems.remove(containerStudent);
               delete containerStudent;
					node.passToNextHandlers(this, data);
            } else {
               OHARBase::Log::getInstance().entry(TAG, "No matching student data from file yet, hold it in container.");
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

void StudentHandler::handleNewItem(OHARBase::DataItem * item) {
   // Check if the item is already in the container.
   OHARBase::Log::getInstance().entry(TAG, "One new data item from file");
   StudentDataItem * newStudent = dynamic_cast<StudentDataItem*>(item);
   StudentDataItem * containerStudent = findStudent(*newStudent);
   if (containerStudent) {
      OHARBase::Log::getInstance().entry(TAG, "Student already in container, combine and pass on!");
      newStudent->addFrom(*containerStudent);
      OHARBase::Package p;
		p.setType(OHARBase::Package::Data);
      p.setDataItem(newStudent);
		dataItems.remove(containerStudent);
		delete containerStudent;
      node.passToNextHandlers(this, p);
   } else {
      OHARBase::Log::getInstance().entry(TAG, "No matching student data from network, hold it in container.");
      dataItems.push_back(newStudent);
   }
}

StudentDataItem * StudentHandler::findStudent(const StudentDataItem & which) const {
   for (std::list<OHARBase::DataItem*>::const_iterator iter = dataItems.begin(); iter != dataItems.end(); iter++) {
      StudentDataItem * containerStudent = dynamic_cast<StudentDataItem*>(*iter);
      if (which == *containerStudent) {
         return containerStudent;
      }
   }
   return 0;
}

	
} //namespace
