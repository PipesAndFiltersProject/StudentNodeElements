//
//  GradingHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__GradingHandler__
#define __PipesAndFiltersFramework__GradingHandler__

#include "DataHandler.h"

namespace OHARBase {
	class ProcessorNode;
	class Package;
}


namespace OHARStudent {
	
	
	class GradingHandler : public OHARBase::DataHandler {
	public:
		GradingHandler(OHARBase::ProcessorNode & myNode);
		virtual ~GradingHandler();
		
		bool consume(OHARBase::Package & data);
		
	private:
		OHARBase::ProcessorNode & node;
		const std::string TAG;
	};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__GradingHandler__) */
