//
//  ExerciseMergerHandler.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__ExerciseMergerHandler__
#define __PipesAndFiltersFramework__ExerciseMergerHandler__

#include <list>

#include "DataHandler.h"
#include "DataReaderObserver.h"

namespace OHARBase {
	class ProcessorNode;
	class Package;
}


/** @brief Namespace supports handling student
 related information in the Pipes & Filters architectural style.<p>
 OHARStudent namespace contains support for handling student
 related information in the Pipes & Filters architectural style.
 This is a higher layer build on top of OHARBase layer. OHARBase
 supports handling any kind of data on Pipes & Filters, as 
 OHARStudent layer adds on top of that, support for handling
 data on student course passing information. OHARStudent is also
 a layer that does not execute anything by itself, but application
 developers use OHARBase and OHARStudent together to implement actual
 applications handling the data.
 */
namespace OHARStudent {

	
class StudentDataItem;

class StudentHandler : public OHARBase::DataHandler, public OHARBase::DataReaderObserver {
public:
   StudentHandler(OHARBase::ProcessorNode & myNode);
   virtual ~StudentHandler();
   
   bool consume(OHARBase::Package & data);

   // From DataReaderObserver
   void handleNewItem(OHARBase::DataItem * item);
   
private:
   void readFile();
   
   StudentDataItem * findStudent(const StudentDataItem & which) const;
   
   OHARBase::ProcessorNode & node;
   const std::string TAG;
   std::list<OHARBase::DataItem*> dataItems;
   
};

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__ExerciseMergerHandler__) */
