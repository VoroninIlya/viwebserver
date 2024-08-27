cmake_minimum_required(VERSION 3.22)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(tst_viwebserver)

#include(CodeCoverage)
include(CTest)

# Add core subdir
add_subdirectory(core)

if(PROJECT_IS_TOP_LEVEL)
# Set as executable
add_subdirectory(${UNITY_ROOT_PATH} ${${EXECUTABLE}_BINARY_DIR}/modules/unity)
add_subdirectory(${GTEST_ROOT_PATH} ${${EXECUTABLE}_BINARY_DIR}/modules/gtest)
endif()

add_executable(tst_viwebserver)
enable_testing()

# Add key executable block
target_sources(tst_viwebserver PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tests/main/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_viwebserver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_vihtmllabel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_vihtmlinput.cpp
)

# Add key include paths
target_include_directories(tst_viwebserver PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/core/str/inc
    ${UNITY_ROOT_PATH}/src
    ${UNITY_ROOT_PATH}/extras/fixture/src
    ${UNITY_ROOT_PATH}/extras/memory/src
    ${GTEST_ROOT_PATH}/googletest/include/
    ${GTEST_ROOT_PATH}/googlemock/include/
)

# Compilation definition information
target_compile_definitions(tst_viwebserver PUBLIC 
    WIN32
    _DEBUG
    CONSOLE
)

# Compiler options
target_compile_options(tst_viwebserver PUBLIC
    -g
    --coverage
    -fprofile-arcs
    -ftest-coverage
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(
  tst_viwebserver viwebserver gtest gmock -g -coverage -fprofile-arcs -ftest-coverage -lgcov -pthread)

add_test(NAME Test_vihtmllabel COMMAND tst_viwebserver "--gtest_filter=Test_vihtmllabel.*")
add_test(NAME Test_vihtmlinput COMMAND tst_viwebserver "--gtest_filter=Test_vihtmlinput.*")
