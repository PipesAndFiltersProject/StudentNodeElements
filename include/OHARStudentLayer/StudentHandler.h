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

#include <OHARBaseLayer/DataHandler.h>
#include <OHARBaseLayer/DataReaderObserver.h>
#include <OHARBaseLayer/DataItem.h>

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

   /** A DataHandler class for handling student data in a ProcessorNode.
    This class handles data arriving from other ProcessorNodes or read from a data file.
    */
   class StudentHandler : public OHARBase::DataHandler, public OHARBase::DataReaderObserver {
   public:
      StudentHandler(OHARBase::ProcessorNode & myNode);
      virtual ~StudentHandler();
      
      bool consume(OHARBase::Package & data) override;

      // From DataReaderObserver
      void handleNewItem(std::unique_ptr<OHARBase::DataItem> item) override;
      
   private:
      void readFile();
      
      StudentDataItem * findStudent(const StudentDataItem & which) const;
      
      /** The ProcessorNode where this handler is residing in. */
      OHARBase::ProcessorNode & node;
      static const std::string TAG;
      /** This list holds the student data handled by this handler. */
      std::list<OHARBase::DataItem*> dataItems;
      
   };

	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__ExerciseMergerHandler__) */
