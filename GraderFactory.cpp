//
//  GraderFactory.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <random>

#include <g3log/g3log.hpp>

#include <StudentNodeElements/GraderFactory.h>
#include <StudentNodeElements/TheUsualGrader.h>
#include <StudentNodeElements/CruelGrader.h>


namespace OHARStudent {

   /** Creates a grade calculator algorithm object based on 
    current needs and student wellbeing needs.
    @returns a GradeCalculator implementation.
    */
   GradeCalculator * GraderFactory::makeGrader() {
      std::random_device rd;
      std::default_random_engine generator(rd());
      std::uniform_int_distribution<int> distribution(0,1);
      int dice_roll = distribution(generator);
      
      if (dice_roll == 0) {
         LOG(INFO) << "GradeFactory" << "Created the usual grader.";
         return new TheUsualGrader();
      }
      LOG(INFO) << "GradeFactory" << "Created the cruel grader :/";
      return new CruelGrader();
   }


} //namespace
