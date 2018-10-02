//
//  GradingHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include "GradingHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "Log.h"
#include "Package.h"
#include "GraderFactory.h"

namespace OHARStudent {

	
GradingHandler::GradingHandler(OHARBase::ProcessorNode & myNode)
: node(myNode), TAG("GradingHandler")
{
   StudentDataItem::setGradeCalculator(GraderFactory::makeGrader());
}

GradingHandler::~GradingHandler() {
   StudentDataItem::setGradeCalculator(0);
}

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