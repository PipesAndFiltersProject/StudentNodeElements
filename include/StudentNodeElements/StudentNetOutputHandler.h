//
//  NetOutputHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__NetOutputHandler__
#define __PipesAndFiltersFramework__NetOutputHandler__

#include <ProcessorNode/DataHandler.h>

namespace OHARBase {
	class ProcessorNode;
	class Package;
}

namespace OHARStudent {
	
	/**
    This class converts the data from internal Node format to
    external format to be sent over to network to a following Node.
    */
	class StudentNetOutputHandler : public OHARBase::DataHandler {
	public:
		StudentNetOutputHandler(OHARBase::ProcessorNode & myNode);
		virtual ~StudentNetOutputHandler();
		
		bool consume(OHARBase::Package & data) override;
		
	private:
      /** The Node where this handler is located in. Needed since Node sends the actual data. */
		OHARBase::ProcessorNode & node;
		static const std::string TAG;
	};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__NetOutputHandler__) */
