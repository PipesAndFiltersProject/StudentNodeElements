//
//  StudentFileReader.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 16.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__StudentFileReader__
#define __PipesAndFiltersFramework__StudentFileReader__

#include <string>

#include <ProcessorNode/DataFileReader.h>
#include <ProcessorNode/DataItem.h>

namespace OHARStudent {

   /**
    The reader class to read student data from a file.
    */
   class StudentFileReader : public OHARBase::DataFileReader {
   public:
      StudentFileReader(OHARBase::DataReaderObserver & obs);
      virtual ~StudentFileReader();
      
   protected:
      std::unique_ptr<OHARBase::DataItem> parse(const std::string & str, const std::string & contentType) override;
      
   private:
      static const std::string TAG;
   };

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__StudentFileReader__) */
