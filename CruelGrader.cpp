//
//  CruelGrader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <StudentNodeElements/CruelGrader.h>
#include <StudentNodeElements/StudentDataItem.h>

namespace OHARStudent {

	/** Calculates a final course grade for the student.
    @param source The student to grade.
    @returns The grade for the student.
    */
   int CruelGrader::calculate(const StudentDataItem & source) {
      int grade = 0; // Assume failed; cruel eh?
      int examPoints = source.getExamPoints();
      int exercisePoints = source.getExercisePointsTotal();
      int exerciseWorkPoints = source.getCourseProjectPoints();
      if (examPoints < 12) {
         return grade; // failed
      }
      if (examPoints >= 12 && examPoints <18) {
         grade = 1;
      } else {
         grade = 2;
      }
      grade += ((exercisePoints / 2) + exerciseWorkPoints)/10;
      if (grade >= 5) { // Cruel, eh?
         grade = 4;
      }
      return grade;
   }


} //namespace
