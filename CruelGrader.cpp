//
//  CruelGrader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include "CruelGrader.h"
#include "StudentDataItem.h"

namespace OHARStudent {

	
int CruelGrader::calculate(const StudentDataItem & source) {
   int grade = 0;
   int examPoints = source.getExamPoints();
   int exercisePoints = source.getExercisePoints();
   int exerciseWorkPoints = source.getExerciseWorkPoints();
   if (examPoints < 12) {
      return grade; // failed
   }
   if (examPoints >= 12 && examPoints <18) {
      grade = 1;
   } else {
      grade = 2;
   }
   grade += ((exercisePoints / 2) + exerciseWorkPoints)/10;
   if (grade > 5) {
      grade = 4;
   }
   return grade;
}


} //namespace