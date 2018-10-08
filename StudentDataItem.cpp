//
//  StudentDataItem.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <vector>
#include <boost/algorithm/string.hpp>

#include <OHARBaseLayer/Log.h>

#include <OHARStudentLayer/StudentDataItem.h>
#include <OHARStudentLayer/GradeCalculator.h>


namespace OHARStudent {

	
GradeCalculator * StudentDataItem::calculator = 0;

StudentDataItem::StudentDataItem()
: examPoints(-1), exercisePoints(-1), exerciseWorkPoints(-1),
  grade(-1), TAG("SDataItem")
{
}

StudentDataItem::StudentDataItem(const StudentDataItem & another)
: OHARBase::DataItem(another), name(another.name), department(another.department),
  examPoints(another.examPoints), exercisePoints(another.exercisePoints),
  exerciseWorkPoints(another.exerciseWorkPoints), grade(another.grade),
  TAG("SDataItem")
{
   
}

OHARBase::DataItem * StudentDataItem::copy() const {
   return new StudentDataItem(*this);
}

StudentDataItem::~StudentDataItem() {
}

const std::string & StudentDataItem::getName() const {
   return name;
}

const std::string & StudentDataItem::getDept() const {
   return department;
}

int StudentDataItem::getExamPoints() const {
   return examPoints;
}

int StudentDataItem::getExercisePoints() const {
   return exercisePoints;
}

int StudentDataItem::getExerciseWorkPoints() const {
   return exerciseWorkPoints;
}

void StudentDataItem::setGradeCalculator(GradeCalculator * calc) {
   delete calculator;
   calculator = 0;
   calculator = calc;
}

int StudentDataItem::getGrade() const {
   return grade;
}

void StudentDataItem::setName(const std::string & theName) {
   name = theName;
}

void StudentDataItem::setDept(const std::string & theDept) {
   department = theDept;
}

void StudentDataItem::setExamPoints(int pts) {
   examPoints = pts;
}

void StudentDataItem::setExercisePoints(int pts) {
   exercisePoints = pts;
}

void StudentDataItem::setExerciseWorkPoints(int pts) {
   exerciseWorkPoints = pts;
}

void StudentDataItem::calculateGrade() {
   if (calculator) {
      grade = calculator->calculate(*this);
      OHARBase::Log::get().entry(TAG, "Calculated grade %d for the student", grade);
   } else {
      OHARBase::Log::get().entry(TAG, "No calculator to grade!!");
   }
}


bool StudentDataItem::parse(const std::string & fromString, const std::string & contentType) {
   std::vector<std::string> strings;
   boost::split(strings, fromString, boost::is_any_of("\t"));
   OHARBase::Log::get().entry(TAG, "String item count: %d", strings.size());
   if (contentType == "summarydata") {
      setId(strings.at(0));
      setName(strings.at(1));
      setDept(strings.at(2));
      setExamPoints(std::stoi(strings.at(3)));
      setExercisePoints(std::stoi(strings.at(4)));
      setExerciseWorkPoints(std::stoi(strings.at(5)));
      return true;
   } else if (contentType == "studentdata") {
      setId(strings.at(0));
      setName(strings.at(1));
      setDept(strings.at(2));
      return true;
   } else if (contentType == "exercisedata") {
      setId(strings.at(0));
      for (int count = 1; count < strings.size(); count++) {
         if (strings.at(count) == "1")
            this->exercisePoints++;
      }
      return true;
   } else if (contentType == "exerciseworkdata") {
      setId(strings.at(0));
      setExerciseWorkPoints(std::stoi(strings.at(1)));
      return true;
   } else if (contentType == "examdata") {
      setId(strings.at(0));
      setExamPoints(std::stoi(strings.at(1)));
      return true;
   } else {
      // UNKNOWN DATA TYPE
   }
   return false;
}

bool StudentDataItem::addFrom(const OHARBase::DataItem & another) {
   const StudentDataItem * item = dynamic_cast<const StudentDataItem*>(&another);
   if (item) {
      if (item->id == id) {
         if (this->name.length() == 0) {
            this->name = item->name;
         }
         if (this->department.length() == 0) {
            this->department = item->department;
         }
         if (this->examPoints < 0) {
            this->examPoints = item->examPoints;
         }
         if (this->exercisePoints < 0) {
            this->exercisePoints = item->exercisePoints;
         }
         if (this->exerciseWorkPoints < 0) {
            this->exerciseWorkPoints = item->exerciseWorkPoints;
         }
         if (this->grade < 0) {
            this->grade = item->grade;
         }
         return true;
      }
   }
   return false;
}

bool StudentDataItem::operator == (const StudentDataItem & item) const {
   return id == item.id;
}

bool StudentDataItem::operator != (const StudentDataItem & item) const {
   return id != item.id;
}


std::ostream & operator << (std::ostream & ostr, const StudentDataItem & item) {
   ostr << item.getId() << "\t" << item.getName() << "\t" << item.getDept()
      << "\t" << item.getExamPoints() << "\t" << item.getExercisePoints()
      << "\t" << item.getExerciseWorkPoints() << "\t" << item.getGrade() << std::endl;
   return ostr;
}
	
	
	
} //namespace
