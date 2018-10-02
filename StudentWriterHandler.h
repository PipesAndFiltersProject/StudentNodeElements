//
//  StudentWriterHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__StudentWriterHandler__
#define __PipesAndFiltersFramework__StudentWriterHandler__

#include "DataHandler.h"

namespace OHARBase {
	class ProcessorNode;
	class Package;
}

namespace OHARStudent {
	
class StudentFileWriter;

class StudentWriterHandler : public OHARBase::DataHandler {
public:
   StudentWriterHandler(OHARBase::ProcessorNode & myNode);
   virtual ~StudentWriterHandler();
   
   bool consume(OHARBase::Package & data);
   
private:
   OHARBase::ProcessorNode & node;
   StudentFileWriter * writer;
   const std::string TAG;
};


} //namespace
#endif /* defined(__PipesAndFiltersFramework__StudentWriterHandler__) */
