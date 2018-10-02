//
//  StudentFileReader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//


#include "StudentFileReader.h"
#include "StudentDataItem.h"
#include "Log.h"


namespace OHARStudent {

	
StudentFileReader::StudentFileReader(OHARBase::DataReaderObserver & obs)
: OHARBase::DataFileReader(obs), TAG("SFileReader") {
   
}

StudentFileReader::~StudentFileReader() {
   
}
   
OHARBase::DataItem * StudentFileReader::parse(const std::string & str, const std::string & contentType) {
   StudentDataItem * item = 0;
   if (str.length() > 0) {
		OHARBase::Log::getInstance().entry(TAG, "Parsing line: %s", str.c_str());
      item = new StudentDataItem();
      if (!item->parse(str, contentType)) {
         OHARBase::Log::getInstance().entry(TAG, "SDataItem failed to parse!");
         delete item;
         item = 0;
      }
   }
   return item;
}


} //namespace