//
//  NetOutputHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include <g3log/g3log.hpp>

#include <ProcessorNode/ProcessorNode.h>
#include <ProcessorNode/Package.h>

#include <StudentNodeElements/StudentNetOutputHandler.h>
#include <StudentNodeElements/StudentDataItem.h>


namespace OHARStudent {
    
   const std::string StudentNetOutputHandler::TAG{"SNetOutputHandler "};
   
    StudentNetOutputHandler::StudentNetOutputHandler(OHARBase::ProcessorNode & myNode)
    : node(myNode)
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
        LOG(INFO) << TAG << "Starting to send a package";
        if (data.getType() == OHARBase::Package::Data) {
            OHARBase::DataItem * item = data.getPayloadObject();
            // If the package contains the binary data object...
            if (item) {
                const StudentDataItem * student = dynamic_cast<const StudentDataItem*>(item);
                // ...and it was a student data item object...
                if (student) {
                    // ...put the data into a JSON string payload...
                    LOG(INFO) << TAG << "Student is converted to JSON and sent... " << student->getName();
                    nlohmann::json j = *student;
                    std::string payload = j.dump();
                    // ... set it as the data for the Package...
                    data.setPayload(payload);
                    // ... and ask the Node to send the data to the next Node.
                    node.sendData(data);
                }
            }
            return true; // data consumed, sent away. No need to pass along to any handlers anymore.
        } else if (data.getType() == OHARBase::Package::Control)  {
            LOG(INFO) << TAG << "Forwarding a command: " << data.getPayloadString();
            node.sendData(data);
            return true;
        }
        return false;
    }
    
    
} //namespace
