//
//  NetOutputHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 28.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include <g3log/g3log.hpp>

#include <ProcessorNode/Package.h>

#include <StudentNodeElements/StudentNetOutputHandler.h>
#include <StudentNodeElements/StudentDataItem.h>


namespace OHARStudent {
    
   const std::string StudentNetOutputHandler::TAG{"SNetOutputHandler "};
   
    StudentNetOutputHandler::StudentNetOutputHandler()
    {
    }
    
    StudentNetOutputHandler::~StudentNetOutputHandler() {
        
    }
    
    /**
     Consumes the data, assuming it contains the student data object in Node
     internal format (object). Then formats the data to the format needed when sending
     it to the next Node over the network (JSON).
     @param data The Package which contains the student data in binary (internal) format.
     @return Returns false to indicate that the package can be further handled by (possible) other handlers.
     */
    bool StudentNetOutputHandler::consume(OHARBase::Package & data) {
        LOG(INFO) << TAG << "Converting the payload from object to JSON";
        if (data.getType() == OHARBase::Package::Data) {
            OHARBase::DataItem * item = data.getPayloadObject();
            // If the package contains the binary data object...
            if (item) {
                const StudentDataItem * student = dynamic_cast<const StudentDataItem*>(item);
                // ...and it was a student data item object...
                if (student) {
                    // ...put the data into a JSON string payload...
                    LOG(INFO) << TAG << "Student is converted to JSON... " << student->getName();
                    nlohmann::json j = *student;
                    std::string payload = j.dump();
                    // ... set it as the data for the Package...
                    data.setPayload(payload);
                }
            }
        }
        return false;
    }
    
    
} //namespace
