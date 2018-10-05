//
//  NetOutputHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include <OHARBaseLayer/ProcessorNode.h>
#include <OHARBaseLayer/Log.h>
#include <OHARBaseLayer/Package.h>

#include "StudentNetOutputHandler.h"
#include "StudentDataItem.h"


namespace OHARStudent {
	
	
	StudentNetOutputHandler::StudentNetOutputHandler(OHARBase::ProcessorNode & myNode)
	: node(myNode), TAG("NetOutputHandler")
	{
	}
	
	StudentNetOutputHandler::~StudentNetOutputHandler() {
		
	}
	
   /**
    Consumes the data, assuming it contains the student data object in Node
    internal format. Then formats the data to the format needed when sending
    it to the next Node over the network.
    @param data The Package which contains the student data in binary (internal) format.
    @return Returns true if package was handled, otherwise returns false.
    */
	bool StudentNetOutputHandler::consume(OHARBase::Package & data) {
		OHARBase::Log::get().entry(TAG, "Starting to send a package");
		if (data.getType() == OHARBase::Package::Data) {
			OHARBase::DataItem * item = data.getDataItem();
         // If the package contains the binary data object...
			if (item) {
				const StudentDataItem * student = dynamic_cast<const StudentDataItem*>(item);
            // ...and it was a student data item object...
				if (student) {
               // ...stream the data into a string payload...
					OHARBase::Log::get().entry(TAG, "It is a student so creating payload");
					std::stringstream stream;
					std::string payload;
					stream << *(student);
					payload = stream.str();
               // ... set it as the data for the Package...
					data.setData(payload);
               // ... and erase the binary data item from the Package...
					data.setDataItem(0);
					OHARBase::Log::get().entry(TAG, "And telling the processornode to send.");
               // ... and ask the Node to send the data to the next Node.
					node.sendData(data);
				}
			}
			return true; // data consumed, sent away. No need to pass along anymore.
		} else if (data.getType() == OHARBase::Package::Control)  {
			node.sendData(data);
			return true;
		}
		return false;
	}
	
	
} //namespace
