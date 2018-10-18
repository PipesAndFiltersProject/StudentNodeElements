//
//  StudentDataItem.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <vector>
#include <boost/algorithm/string.hpp>

#include <g3log/g3log.hpp>

#include <OHARStudentLayer/StudentDataItem.h>
#include <OHARStudentLayer/GradeCalculator.h>

#include <nlohmann/json.hpp>

namespace OHARStudent {

   void to_json(nlohmann::json & j, const StudentDataItem & student) {
      // Only id is required, all other elements are optional.
      j = nlohmann::json{{"id", student.getId()}};
      
      // Default values are empty strings and -1, so if the default values are there,
      // put nothing to json for that data element.
      if (student.getName().length() > 0) {
         j["name"] = student.getName();
      }
      if (student.getStudyProgram().length() > 0) {
         j["studyprogram"] = student.getStudyProgram();
      }
      if (student.getExamPoints() >= 0) {
         j["exampoints"] = student.getExamPoints();
      }
      if (student.getExercisePoints() >= 0) {
         j["exercisepoints"] = student.getExercisePoints();
      }
      if (student.getCourseProjectPoints() >= 0) {
         j["courseprojectpoints"] = student.getCourseProjectPoints();
      }
      if (student.getGrade() >= 0) {
         j["grade"] = student.getGrade();
      }
   }
   
   void from_json(const nlohmann::json & j, StudentDataItem & student) {
      student.setId(j.at("id"));
      if (j.find("name") != j.end()) {
         student.setName(j.at("name"));
      }
      if (j.find("studyprogram") != j.end()) {
         student.setStudyProgram(j.at("studyprogram"));
      }
      if (j.find("exampoints") != j.end()) {
         student.setExamPoints(j.at("exampoints"));
      }
      if (j.find("exercisepoints") != j.end()) {
         student.setExamPoints(j.at("exercisepoints"));
      }
      if (j.find("courseprojectpoints") != j.end()) {
         student.setCourseProjectPoints(j.at("courseprojectpoints"));
      }
      if (j.find("grade") != j.end()) {
         student.setGrade(j.at("grade"));
      }
   }
   
GradeCalculator * StudentDataItem::calculator = 0;

StudentDataItem::StudentDataItem()
: examPoints(-1), exercisePoints(-1), courseProjectPoints(-1),
  grade(-1), TAG("SDataItem ")
{
}

StudentDataItem::StudentDataItem(const StudentDataItem & another)
: OHARBase::DataItem(another), name(another.name), department(another.department),
  examPoints(another.examPoints), exercisePoints(another.exercisePoints),
  courseProjectPoints(another.courseProjectPoints), grade(another.grade),
  TAG("SDataItem ")
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

const std::string & StudentDataItem::getStudyProgram() const {
   return department;
}

int StudentDataItem::getExamPoints() const {
   return examPoints;
}

int StudentDataItem::getExercisePoints() const {
   return exercisePoints;
}

int StudentDataItem::getCourseProjectPoints() const {
   return courseProjectPoints;
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

void StudentDataItem::setStudyProgram(const std::string & theDept) {
   department = theDept;
}

void StudentDataItem::setExamPoints(int pts) {
   examPoints = pts;
}

void StudentDataItem::setExercisePoints(int pts) {
   exercisePoints = pts;
}

void StudentDataItem::setCourseProjectPoints(int pts) {
   courseProjectPoints = pts;
}
   
void StudentDataItem::setGrade(int g) {
   grade = g;
}

void StudentDataItem::calculateGrade() {
   if (calculator) {
      grade = calculator->calculate(*this);
      LOG(INFO) << TAG << "Calculated grade for the student: " << grade;
   } else {
      LOG(WARNING) << TAG << "No calculator provided for grading!!";
   }
}


bool StudentDataItem::parse(const std::string & fromString, const std::string & contentType) {
   // TODO: change logs to use macros LOG_INFO etc when reimplementing using json.
   std::vector<std::string> strings;
   boost::split(strings, fromString, boost::is_any_of("\t"));
   LOG(INFO) << TAG << "Parsing student string; item count: " << strings.size();
   if (contentType == "summarydata") {
      setId(strings.at(0));
      setName(strings.at(1));
      setStudyProgram(strings.at(2));
      setExamPoints(std::stoi(strings.at(3)));
      setExercisePoints(std::stoi(strings.at(4)));
      setCourseProjectPoints(std::stoi(strings.at(5)));
      return true;
   } else if (contentType == "studentdata") {
      setId(strings.at(0));
      setName(strings.at(1));
      setStudyProgram(strings.at(2));
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
      setCourseProjectPoints(std::stoi(strings.at(1)));
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
         if (this->courseProjectPoints < 0) {
            this->courseProjectPoints = item->courseProjectPoints;
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
   ostr << item.getId() << "\t" << item.getName() << "\t" << item.getStudyProgram()
      << "\t" << item.getExamPoints() << "\t" << item.getExercisePoints()
      << "\t" << item.getCourseProjectPoints() << "\t" << item.getGrade() << std::endl;
   return ostr;
}
	
	
	
} //namespace
