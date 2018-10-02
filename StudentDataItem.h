//
//  StudentDataItem.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__StudentDataItem__
#define __PipesAndFiltersFramework__StudentDataItem__

#include <ostream>

#include "DataItem.h"


namespace OHARStudent {

	
   class GradeCalculator;

   /**
    A class for handling student data in a ProcessorNode and
    associated classes there (DataHandler, Networker classes etc.).
    */
   class StudentDataItem : public OHARBase::DataItem {
   public:
      StudentDataItem();
      StudentDataItem(const StudentDataItem & another);
      virtual ~StudentDataItem();
      
      OHARBase::DataItem * copy() const;
      
      bool parse(const std::string & fromString, const std::string & contentType);
      bool addFrom(const OHARBase::DataItem & another);

      const std::string & getName() const;
      const std::string & getDept() const;
      int getExamPoints() const;
      int getExercisePoints() const;
      int getExerciseWorkPoints() const;
      int getGrade() const;
      
      void setName(const std::string & theName);
      void setDept(const std::string & theDept);
      void setExamPoints(int pts);
      void setExercisePoints(int pts);
      void setExerciseWorkPoints(int pts);
      
      void calculateGrade();
      
      bool operator == (const StudentDataItem & item) const;
      bool operator != (const StudentDataItem & item) const;
      
      static void setGradeCalculator(GradeCalculator * calc);
      
   protected:
      
   private:
      /** The name of the student. */
      std::string name;
      /** The department or curriculum where the student studies. */
      std::string department;
      /** The points student got from an examination. */
      int         examPoints;
      /** The points student got from participating in exercises. */
      int         exercisePoints;
      /** The points student got from the exercise work. */
      int         exerciseWorkPoints;
      /** The final grade student gets from the course. */
      int         grade;
      
      /** A calculator object to calculate the final grade for the student. */
      static GradeCalculator * calculator;
      
      const std::string TAG;
   };

   std::ostream & operator << (std::ostream & ostr, const StudentDataItem & item);


} //namespace
#endif /* defined(__PipesAndFiltersFramework__StudentDataItem__) */
