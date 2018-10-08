//
//  TheUsualGrader.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__TheUsualGrader__
#define __PipesAndFiltersFramework__TheUsualGrader__

#include <OHARStudentLayer/GradeCalculator.h>

namespace OHARStudent {

   /** One implementation for grading students */
   class TheUsualGrader : public GradeCalculator {
   public:
      int calculate(const StudentDataItem & source);
   };

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__TheUsualGrader__) */
