//
//  GradingHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <OHARBaseLayer/ProcessorNode.h>
#include <OHARBaseLayer/Log.h>
#include <OHARBaseLayer/Package.h>

#include "GraderFactory.h"
#include "GradingHandler.h"
#include "StudentDataItem.h"

namespace OHARStudent {

	/**
    Initializes the grading handler by creating a suitable grade calculator,
    using the help of the GraderFactory class.
    @param myNode The ProcessorNode where the handler is located in.
    */
   GradingHandler::GradingHandler(OHARBase::ProcessorNode & myNode)
   : TAG("GradingHandler")
   {
      // Uses the static student member variable and setter so that all students
      // use the same grade calculator. Equal grading for all students, eh?!
      StudentDataItem::setGradeCalculator(GraderFactory::makeGrader());
   }

   GradingHandler::~GradingHandler() {
      StudentDataItem::setGradeCalculator(0);
   }

   /** Grades the student based on the various course passing aspects, using the 
    selected grader algorithm.
    @param data The Package containing the student data.
    @returns Returns false, giving other handlers the opportunity to handle the package too.
    */
   bool GradingHandler::consume(OHARBase::Package & data) {
      if (data.getType() == OHARBase::Package::Data) {
         OHARBase::DataItem * item = data.getDataItem();
         if (item) {
            StudentDataItem * student = dynamic_cast<StudentDataItem*>(item);
            if (student) {
               OHARBase::Log::getInstance().entry(TAG, "Calculating a grade for the student.");
               student->calculateGrade();
            }
         }
      }
      return false; // Always let others handle this data package too.
   }


} //namespace
