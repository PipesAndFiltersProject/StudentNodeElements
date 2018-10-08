//
//  StudentWriterHandler.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <sstream>

#include <OHARBaseLayer/ProcessorNode.h>
#include <OHARBaseLayer/Log.h>
#include <OHARBaseLayer/Package.h>

#include <OHARStudentLayer/StudentDataItem.h>
#include <OHARStudentLayer/StudentWriterHandler.h>
#include <OHARStudentLayer/StudentFileWriter.h>


namespace OHARStudent {


   /** Initializes the writer handler by creating the writer object. The file name
    used to write the student data into, is gotten from the ProcessorNode configuration.
    @param myNode The node where the handler is.
    */
   StudentWriterHandler::StudentWriterHandler(OHARBase::ProcessorNode & myNode)
   : node(myNode), TAG("StudentWriterHandler")
   {
      writer = new StudentFileWriter(node.getOutputFileName());
   }

   /** Deletes the writer, thus closing the file. */
   StudentWriterHandler::~StudentWriterHandler() {
      delete writer;
   }

   /**
    Consumes the data package containing the student data. Writes the student data into a file.
    @param data The package containing the student data to write.
    @returns Returns false, since there is no need to further manipulate the data. It is
    assumed that writing the finished data into a file is the final step in student data processing
    and further processing is not needed.
    */
   bool StudentWriterHandler::consume(OHARBase::Package & data) {
      OHARBase::Log::get().entry(TAG, "Starting to write a package");
      if (data.getType() == OHARBase::Package::Data) {
         OHARBase::DataItem * item = data.getDataItem();
         if (item) {
            const StudentDataItem * student = dynamic_cast<const StudentDataItem*>(item);
            if (student) {
               writer->write(student);
            }
         }
      }
      return false; // Don't let others handle this data package since it is now finally handled.
   }


} //namespace
