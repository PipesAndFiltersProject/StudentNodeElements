//
//  StudentFileReader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//


#include <g3log/g3log.hpp>

#include <StudentNodeElements/StudentFileReader.h>
#include <StudentNodeElements/StudentDataItem.h>


namespace OHARStudent {

   const std::string StudentFileReader::TAG{"SFileReader "};
   
   StudentFileReader::StudentFileReader(OHARBase::DataReaderObserver & obs)
   : OHARBase::DataFileReader(obs) {
      
   }

   StudentFileReader::~StudentFileReader() {
      
   }
    
   /**
    Parses a string containing student data.
    @param str The line of string to parse, assuming to have student data items.
    @param contentType Which kind of student data the line contains.
    @returns The new student data item, or null if creation fails.
    */
   std::unique_ptr<OHARBase::DataItem> StudentFileReader::parse(const std::string & str, const std::string & contentType) {
      std::unique_ptr<StudentDataItem> itemPtr = std::make_unique<StudentDataItem>();
      if (str.length() > 0) {
         LOG(INFO) << TAG << "Parsing string " << str.substr(0,15) << "...";
         if (!itemPtr->parse(str, contentType)) {
            LOG(WARNING) << TAG << "StudentDataItem failed to parse string!";
            itemPtr.release();
         }
      }
      return itemPtr;
   }


} //namespace
