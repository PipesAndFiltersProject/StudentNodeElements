//
//  NetOutputHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include "StudentNetOutputHandler.h"
#include "StudentDataItem.h"
#include "ProcessorNode.h"
#include "Log.h"
#include "Package.h"


namespace OHARStudent {
	
	
	StudentNetOutputHandler::StudentNetOutputHandler(OHARBase::ProcessorNode & myNode)
	: node(myNode), TAG("NetOutputHandler")
	{
	}
	
	StudentNetOutputHandler::~StudentNetOutputHandler() {
		
	}
	
	bool StudentNetOutputHandler::consume(OHARBase::Package & data) {
		OHARBase::Log::getInstance().entry(TAG, "Starting to send a package");
		if (data.getType() == OHARBase::Package::Data) {
			OHARBase::DataItem * item = data.getDataItem();
			if (item) {
				const StudentDataItem * student = dynamic_cast<const StudentDataItem*>(item);
				if (student) {
					OHARBase::Log::getInstance().entry(TAG, "It is a student so creating payload");
					std::stringstream stream;
					std::string payload;
					stream << *(student);
					payload = stream.str();
					data.setData(payload);
					data.setDataItem(0);
					OHARBase::Log::getInstance().entry(TAG, "And telling the processornode to send.");
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
