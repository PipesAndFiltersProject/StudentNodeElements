include(CMakeFindDependencyMacro)

find_dependency(Boost 1.70.0)
find_dependency(ProcessorNode)

include("${CMAKE_CURRENT_LIST_DIR}/StudentNodeElementsTargets.cmake")
