//
//  StudentFileReader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//


#include <g3log/g3log.hpp>

#include <OHARStudentLayer/StudentFileReader.h>
#include <OHARStudentLayer/StudentDataItem.h>


namespace OHARStudent {

	
   StudentFileReader::StudentFileReader(OHARBase::DataReaderObserver & obs)
   : OHARBase::DataFileReader(obs), TAG("SFileReader ") {
      
   }

   StudentFileReader::~StudentFileReader() {
      
   }
    
   /**
    Parses a string containing student data.
    @param str The line of string to parse, assuming to have student data items.
    @param contentType Which kind of student data the line contains.
    @returns The new student data item, or null if creation fails.
    */
   OHARBase::DataItem * StudentFileReader::parse(const std::string & str, const std::string & contentType) {
      std::unique_ptr<StudentDataItem> itemPtr(new StudentDataItem());
      if (str.length() > 0) {
         LOG(INFO) << TAG << "Parsing string " << str.substr(0,15) << "...";
         if (!itemPtr->parse(str, contentType)) {
            LOG(WARNING) << TAG << "StudentDataItem failed to parse string!";
            return nullptr;
         }
      }
      return itemPtr.release();
   }


} //namespace
