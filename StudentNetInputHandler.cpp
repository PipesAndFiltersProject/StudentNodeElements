//
//  ExerciseInfoHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 23.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <OHARBaseLayer/ProcessorNode.h>
#include <OHARBaseLayer/Log.h>
#include <OHARBaseLayer/Package.h>

#include "StudentNetInputHandler.h"
#include "StudentDataItem.h"

namespace OHARStudent {
	
	const std::string StudentNetInputHandler::TAG = "NetInputHandler";
	
	/** Default constructor, does nothing. */
	StudentNetInputHandler::StudentNetInputHandler()
	{
	}
	
	/** Destructor, does nothing. */
	StudentNetInputHandler::~StudentNetInputHandler() {
	}
	
	/** Consumes the data in the package. In practise, assumes that
	 the Package::data contains a string containing data elements which
	 need to be parsed. The StudentDataItem knows how to parse the data.
	 Calling StudentDataItem::parse goes through the string and sets
	 the values parsed form the string to the student data item member
	 varibles. This student data item is then stored in the Package::dataItem
	 pointer. Now the Package contains both the raw data from the network as
	 well as the parsed, structured data in the student data object. The latter
	 is more useful in manipulating student data in application classes.
	 @param data The package of data to be parsed.
	 @return Returns false, since data is now parsed (or was something else
	 this object is not interested in) and other handlers should be given the
	 change to use the package also.
	 */
	bool StudentNetInputHandler::consume(OHARBase::Package & data) {
		using namespace OHARBase;
		if (data.getType() == Package::Data && data.getData().length() > 0) {
			Log::get().entry(TAG, "** data received, handling! **");
			// parse data to a student data object
			StudentDataItem * item = new StudentDataItem;
			if (item->parse(data.getData(), "summarydata")) {
				data.setDataItem(item);
				data.setData("");
			} else {
				// could not parse.
				delete item;
			}
		}
		return false; // Always let others handle this data package too.
	}
	
} //namespace
