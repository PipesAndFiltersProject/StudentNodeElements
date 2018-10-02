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
   std::string name;
   std::string department;
   int         examPoints;
   int         exercisePoints;
   int         exerciseWorkPoints;
   int         grade;
   
   static GradeCalculator * calculator;
   
   const std::string TAG;
};

std::ostream & operator << (std::ostream & ostr, const StudentDataItem & item);


} //namespace
#endif /* defined(__PipesAndFiltersFramework__StudentDataItem__) */
