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

class GradeCalculator {
public:
   virtual int calculate(const StudentDataItem & source) = 0;
   virtual ~GradeCalculator() {};
};
	
	
} //namespace
#endif
