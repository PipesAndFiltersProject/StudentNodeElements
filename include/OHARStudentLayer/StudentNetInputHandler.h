//
//  ExerciseInfoHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 23.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__ExerciseInfoHandler__
#define __PipesAndFiltersFramework__ExerciseInfoHandler__

#include <OHARBaseLayer/DataHandler.h>

// Forward declaration
namespace OHARBase {
	class Package;
}

namespace OHARStudent {

/** Handles student data input, arriving from the network. 
 Class receives (in consume method) a Package object, which has the received
 data (non-parsed) in a string. This handler then parses the data from
 the string to a StudentDataItem object, which is then stored in the DataItem
 member pointer in the Package and is available to use after this. The data 
 object can now be used to get and set data from/to the student object by
 other handlers (e.g. file readers, graders,...).
 @author Antti Juustila
 */
class StudentNetInputHandler : public OHARBase::DataHandler {
public:
   StudentNetInputHandler();
   virtual ~StudentNetInputHandler();
   
   bool consume(OHARBase::Package & data);
   
private:
   static const std::string TAG;
};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__ExerciseInfoHandler__) */
