//
//  PlainStudentFileHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__PlainStudentFileHandler__
#define __PipesAndFiltersFramework__PlainStudentFileHandler__

#include <ProcessorNode/DataHandler.h>
#include <ProcessorNode/DataReaderObserver.h>
#include <ProcessorNode/DataItem.h>


namespace OHARBase {
	class ProcessorNode;
	class Package;
}


namespace OHARStudent {
	

   /** A DataHandler class which reads student data from a file. */
   class PlainStudentFileHandler : public OHARBase::DataHandler, public OHARBase::DataReaderObserver {
   public:
      PlainStudentFileHandler(OHARBase::ProcessorNode & myNode);
      virtual ~PlainStudentFileHandler();
      
      bool consume(OHARBase::Package & data) override;
      
      // From DataReaderObserver
      void handleNewItem(std::unique_ptr<OHARBase::DataItem> item) override;
      
   private:
      void readFile();
      
      OHARBase::ProcessorNode & node;
      static const std::string TAG;
   };

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__PlainStudentFileHandler__) */
