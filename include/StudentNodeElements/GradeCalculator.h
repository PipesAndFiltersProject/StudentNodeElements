//
//  GradeCalculator.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef PipesAndFiltersFramework_GradeCalculator_h
#define PipesAndFiltersFramework_GradeCalculator_h

namespace OHARStudent {

	
   class StudentDataItem;

   /**
    An interface for grade calculator implementations.
    */
   class GradeCalculator {
   public:
      /** The method to call when one wants to calculate the grade for a student.
       Impementors can implement various different methods for grading the student.
       @param source The student for whom the grade is calculated. 
       @returns The grade for the student. 
       */
      virtual int calculate(const StudentDataItem & source) = 0;
      virtual ~GradeCalculator() {};
   };
      
	
} //namespace
#endif
