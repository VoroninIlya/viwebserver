cmake_minimum_required(VERSION 3.22)

project(viwebserver)

# Debug message
message("Entering ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")

# Register core library
add_library(viwebserver INTERFACE)
target_sources(viwebserver PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/viwebserver.cpp)
target_include_directories(viwebserver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/inc)

# Debug message
message("Exiting ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")