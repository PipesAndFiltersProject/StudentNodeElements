//
//  GradingHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__GradingHandler__
#define __PipesAndFiltersFramework__GradingHandler__

#include <ProcessorNode/DataHandler.h>

namespace OHARBase {
	class ProcessorNode;
	class Package;
}


namespace OHARStudent {
	
	/** A handler for determining the final grade for the student,
    based on how the student managed the various areas of the course.
    */
	class GradingHandler : public OHARBase::DataHandler {
	public:
		GradingHandler(OHARBase::ProcessorNode & myNode);
		virtual ~GradingHandler();
		
		bool consume(OHARBase::Package & data) override;
		
	private:
      
		static const std::string TAG;
	};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__GradingHandler__) */
