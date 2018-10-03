//
//  StudentWriterHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__StudentWriterHandler__
#define __PipesAndFiltersFramework__StudentWriterHandler__

#include <OHARBaseLayer/DataHandler.h>

namespace OHARBase {
	class ProcessorNode;
	class Package;
}

namespace OHARStudent {
	
   class StudentFileWriter;

   /** The DataHandler in the ProcessorNode which handles packages
    containing student data so that the student data is written into a file.
    */
   class StudentWriterHandler : public OHARBase::DataHandler {
   public:
      StudentWriterHandler(OHARBase::ProcessorNode & myNode);
      virtual ~StudentWriterHandler();
      
      bool consume(OHARBase::Package & data);
      
   private:
      /** The ProcessorNode where this handler is residing in. */
      OHARBase::ProcessorNode & node;
      /** The writer to use in writing the data into the file. */
      StudentFileWriter * writer;
      const std::string TAG;
   };


} //namespace
#endif /* defined(__PipesAndFiltersFramework__StudentWriterHandler__) */
