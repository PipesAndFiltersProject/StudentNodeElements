//
//  GraderFactory.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <random>

#include <OHARBaseLayer/Log.h>

#include <OHARStudentLayer/GraderFactory.h>
#include <OHARStudentLayer/TheUsualGrader.h>
#include <OHARStudentLayer/CruelGrader.h>


namespace OHARStudent {

   /** Creates a grade calculator algorithm object based on 
    current needs and student wellbeing needs.
    @returns a GradeCalculator implementation.
    */
   GradeCalculator * GraderFactory::makeGrader() {
      std::default_random_engine generator(time(0));
      std::uniform_int_distribution<int> distribution(0,1);
      int dice_roll = distribution(generator);
      
      if (dice_roll == 0) {
         OHARBase::Log::get().entry("GradeFactory", "Created the usual grader.");
         return new TheUsualGrader();
      }
      OHARBase::Log::get().entry("GradeFactory", "Created the cruel grader :/");
      return new CruelGrader();
   }


} //namespace
