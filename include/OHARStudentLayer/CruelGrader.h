//
//  CruelGrader.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__CruelGrader__
#define __PipesAndFiltersFramework__CruelGrader__

#include <OHARStudentLayer/GradeCalculator.h>

namespace OHARStudent {

	/** One implementation for grading students */
   class CruelGrader : public GradeCalculator {
   public:
      int calculate(const StudentDataItem & source) override;
   };
      
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__CruelGrader__) */
