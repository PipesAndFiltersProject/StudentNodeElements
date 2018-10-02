//
//  PlainStudentFileHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__PlainStudentFileHandler__
#define __PipesAndFiltersFramework__PlainStudentFileHandler__

#include <list>

#include "DataHandler.h"
#include "DataReaderObserver.h"


namespace OHARBase {
	class ProcessorNode;
	class Package;
}


namespace OHARStudent {
	

class PlainStudentFileHandler : public OHARBase::DataHandler, public OHARBase::DataReaderObserver {
public:
   PlainStudentFileHandler(OHARBase::ProcessorNode & myNode);
   virtual ~PlainStudentFileHandler();
   
   bool consume(OHARBase::Package & data);
   
   // From DataReaderObserver
   void handleNewItem(OHARBase::DataItem * item);
   
private:
   void readFile();
   
   OHARBase::ProcessorNode & node;
   const std::string TAG;
};

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__PlainStudentFileHandler__) */
