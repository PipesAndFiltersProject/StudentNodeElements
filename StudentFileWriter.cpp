//
//  StudentFileWriter.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 30.1.2014.
//  Copyright (c) 2014 Antti Juustila. All rights reserved.
//

#include <chrono>

#include <g3log/g3log.hpp>

#include <OHARStudentLayer/StudentFileWriter.h>
#include <OHARStudentLayer/StudentDataItem.h>


namespace OHARStudent {
    
    
    /** The constructor initializes the object as well as writes the
     header into the file, adding to whatever is already there.
     @param fileName The file name where to write the student data.
     */
    StudentFileWriter::StudentFileWriter(const std::string & fileName) {
        using std::chrono::system_clock;
        if (fileName.length() > 0) {
            LOG(INFO) << "Opening file " << fileName << " for writing.";
            file.open(fileName, std::ofstream::out | std::ofstream::app);
            if (file.is_open()) {
                LOG(INFO) << "Succeeded, start writing";
                system_clock::time_point today = system_clock::now();
                std::time_t tt;
                tt = system_clock::to_time_t ( today );
                file << std::endl << std::endl;
                file << "** Welcome to student register system" << std::endl;
                file << "** (c) Antti Juustila, 2014-2019. University of Oulu, Finland." << std::endl;
                file << "** Today is: " << ctime(&tt) << std::endl;
                file << "** Following grades have been awarded:" << std::endl;
                file << "ID\tName\t\tDept\tExam\tExerc\tWork\tGRADE" << std::endl;
            } else {
                LOG(WARNING) << "Could not open the output file.";
            }
        } else {
           LOG(WARNING) << "No file name set for StudentFileWriter";
        }
    }
    
    /** The destructor writes the ending statements to the file and closes it. */
    StudentFileWriter::~StudentFileWriter() {
        file << std::endl << "**==--> End of batch <--==**" << std::endl;
        if (file.is_open()) {
            file.close();
        }
        LOG(INFO) << "Closing output file.";
    }
    
    /** The method writes the student data into the file using the operator <<().
     @param student The student data to write into the file.
     */
    void StudentFileWriter::write(const StudentDataItem * student) {
        if (file.is_open() && student != nullptr) {
            file << *student;
        }
    }
    
    
} //namespace
