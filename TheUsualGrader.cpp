//
//  TheUsualGrader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <random>

#include <OHARStudentLayer/TheUsualGrader.h>

namespace OHARStudent {

	/** The way students are usually graded, yes?
    @param source The student to grade.
    @returns The student's grade.
    */
   int TheUsualGrader::calculate(const StudentDataItem & source) {
      std::random_device rd;
      std::default_random_engine generator(rd());
      std::uniform_int_distribution<int> distribution(0,5);
      int dice_roll = distribution(generator);
      return dice_roll;
   }

} //namespace
