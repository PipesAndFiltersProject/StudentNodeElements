cmake_minimum_required(VERSION 3.15)

project(StudentNodeElementsProject)

set(LIB_NAME StudentNodeElements)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(Boost 1.70.0 REQUIRED COMPONENTS system)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(g3logger CONFIG REQUIRED)
find_package(ProcessorNode REQUIRED)

# Add a "doc" target to generate API documentation with Doxygen.
# Doxygen is _not_ a component that ProcessorNode uses, but a _tool_
# used in library document generation as part of the build process.
# After "cmake ..", execute "make doc" to create docs.
# When using Ninja, do "cmake -GNinja .." and "ninja doc" to create the docs.
# There will be a docs directory in the build dir, containing the docs.
find_package(Doxygen)
if (DOXYGEN_FOUND)
   configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxyfile @ONLY)
   add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
   )
endif(DOXYGEN_FOUND)

if (Boost_FOUND AND ProcessorNode_FOUND AND nlohmann_json_FOUND)
   add_library(${LIB_NAME} STATIC CruelGrader.cpp PlainStudentFileHandler.cpp StudentFileWriter.cpp StudentNetOutputHandler.cpp GraderFactory.cpp StudentDataItem.cpp StudentHandler.cpp StudentWriterHandler.cpp GradingHandler.cpp StudentFileReader.cpp StudentInputHandler.cpp TheUsualGrader.cpp include/${LIB_NAME}/CruelGrader.h include/${LIB_NAME}/GradeCalculator.h
      include/${LIB_NAME}/GraderFactory.h include/${LIB_NAME}/GradingHandler.h include/${LIB_NAME}/PlainStudentFileHandler.h
      include/${LIB_NAME}/StudentDataItem.h include/${LIB_NAME}/StudentFileReader.h include/${LIB_NAME}/StudentFileWriter.h
      include/${LIB_NAME}/StudentHandler.h include/${LIB_NAME}/StudentInputHandler.h include/${LIB_NAME}/StudentNetOutputHandler.h
      include/${LIB_NAME}/StudentWriterHandler.h include/${LIB_NAME}/TheUsualGrader.h)

   set_target_properties(${LIB_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
   set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 17)

   target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/> $<INSTALL_INTERFACE:include/${LIB_NAME}> ${Boost_INCLUDE_DIRS} ${G3LOGGER_INCLUDE_DIRS} ${ProcessorNode_INCLUDE_DIRS})

   target_link_libraries(${LIB_NAME} PUBLIC Boost::system g3logger ProcessorNode::ProcessorNode nlohmann_json::nlohmann_json)

   set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "include/${LIB_NAME}/CruelGrader.h;include/${LIB_NAME}/PlainStudentFileHandler.h;include/${LIB_NAME}/StudentHandler.h;include/${LIB_NAME}/TheUsualGrader.h;include/${LIB_NAME}/GradeCalculator.h;include/${LIB_NAME}/StudentDataItem.h;include/${LIB_NAME}/StudentInputHandler.h;include/${LIB_NAME}/GraderFactory.h;include/${LIB_NAME}/StudentFileReader.h;include/${LIB_NAME}/StudentNetOutputHandler.h;include/${LIB_NAME}/GradingHandler.h;include/${LIB_NAME}/StudentFileWriter.h;include/${LIB_NAME}/StudentWriterHandler.h")

   install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME})
   install(EXPORT ${LIB_NAME}Targets FILE ${LIB_NAME}Targets.cmake NAMESPACE StudentNodeElements:: DESTINATION lib/cmake/${LIB_NAME})
   install(FILES ${LIB_NAME}Config.cmake DESTINATION lib/cmake/${LIB_NAME})

   export(TARGETS ${LIB_NAME} FILE ${LIB_NAME}Targets.cmake)
endif()
