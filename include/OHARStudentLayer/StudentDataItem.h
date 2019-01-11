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

#include <nlohmann/json.hpp>

#include <OHARBaseLayer/DataItem.h>


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
      
      OHARBase::DataItem * copy() const override;
      
      virtual bool parse(const std::string & fromString, const std::string & contentType) override;
      bool addFrom(const OHARBase::DataItem & another) override;

      const std::string & getName() const;
      const std::string & getStudyProgram() const;
      int getExamPoints() const;
      int getExercisePointsTotal() const;
      const std::vector<int> & getExercisePoints() const;
      int getCourseProjectPoints() const;
      int getGrade() const;
      
      void setName(const std::string & theName);
      void setStudyProgram(const std::string & theDept);
      void setExamPoints(int pts);
      void addToExercisePoints(int pts);
      void setExercisePoints(const std::vector<int> & newPoints);
      void setCourseProjectPoints(int pts);
      /**
       Grade is calculated so use calculateGrade to determine it and use this method only for externalizing (to/from file or network using json).
       @param g The grade value, from 0-5 (zero being failed).
       */
      void setGrade(int g);
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
      std::vector<int> exercisePoints;
      /** The points student got from the exercise work. */
      int         courseProjectPoints;
      /** The final grade student gets from the course. */
      int         grade;
      
      /** A calculator object to calculate the final grade for the student. */
      static GradeCalculator * calculator;
      
      const std::string TAG;
   };

   std::ostream & operator << (std::ostream & ostr, const StudentDataItem & item);


   void to_json(nlohmann::json & j, const StudentDataItem & student);
   void from_json(const nlohmann::json & j, StudentDataItem & student);
   
   
} //namespace
#endif /* defined(__PipesAndFiltersFramework__StudentDataItem__) */
