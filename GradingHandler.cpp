//
//  GradingHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <g3log/g3log.hpp>

#include <ProcessorNode/ProcessorNode.h>
#include <ProcessorNode/Package.h>

#include <StudentNodeElements/GraderFactory.h>
#include <StudentNodeElements/GradingHandler.h>
#include <StudentNodeElements/StudentDataItem.h>

namespace OHARStudent {

   const std::string GradingHandler::TAG{"GradingHandler"};
   
	/**
    Initializes the grading handler by creating a suitable grade calculator,
    using the help of the GraderFactory class.
    @param myNode The ProcessorNode where the handler is located in.
    */
   GradingHandler::GradingHandler(OHARBase::ProcessorNode & myNode)
   {
      // Uses the static student member variable and setter so that all students
      // use the same grade calculator. Equal grading for all students, eh?!
      StudentDataItem::setGradeCalculator(GraderFactory::makeGrader());
   }

   GradingHandler::~GradingHandler() {
      StudentDataItem::setGradeCalculator(nullptr);
   }

   /** Grades the student based on the various course passing aspects, using the 
    selected grader algorithm.
    @param data The Package containing the student data.
    @returns Returns false, giving other handlers the opportunity to handle the package too.
    */
   bool GradingHandler::consume(OHARBase::Package & data) {
      if (data.getType() == OHARBase::Package::Data) {
         OHARBase::DataItem * item = data.getPayloadObject();
         if (item) {
            StudentDataItem * student = dynamic_cast<StudentDataItem*>(item);
            if (student) {
               LOG(INFO) << TAG << "Calculating a grade for the student " << student->getName();
               student->calculateGrade();
            }
         }
      }
      return false; // Always let others handle this data package too.
   }


} //namespace
