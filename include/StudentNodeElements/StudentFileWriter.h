//
//  StudentFileWriter.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__StudentFileWriter__
#define __PipesAndFiltersFramework__StudentFileWriter__

#include <fstream>


namespace OHARStudent {

	
   class StudentDataItem;

   /** A class for writing student data into a file.
    */
   class StudentFileWriter {
   public:
      StudentFileWriter(const std::string & fileName);
      virtual ~StudentFileWriter();
      
      virtual void write(const StudentDataItem * student);
      
   private:
      /** The output file stream to write into. */
      std::ofstream file;
      
   };
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__StudentFileWriter__) */
