//
//  NetOutputHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__NetOutputHandler__
#define __PipesAndFiltersFramework__NetOutputHandler__

#include "DataHandler.h"

namespace OHARBase {
	class ProcessorNode;
	class Package;
}

namespace OHARStudent {
	
	
	class StudentNetOutputHandler : public OHARBase::DataHandler {
	public:
		StudentNetOutputHandler(OHARBase::ProcessorNode & myNode);
		virtual ~StudentNetOutputHandler();
		
		bool consume(OHARBase::Package & data);
		
	private:
		OHARBase::ProcessorNode & node;
		const std::string TAG;
	};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__NetOutputHandler__) */
