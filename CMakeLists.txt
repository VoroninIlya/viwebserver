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
#add_subdirectory(${GMOCK_ROOT_PATH} ${${EXECUTABLE}_BINARY_DIR}/modules/gtest/googlemock)
endif()

add_executable(tst_viwebserver)
enable_testing()

# Add key executable block
target_sources(tst_viwebserver PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tests/main/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/tst_viwebserver.cpp
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
target_compile_options(tst_viwebserver PRIVATE
    -g
    --coverage
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(
  tst_viwebserver viwebserver -g -coverage -lgcov)

add_test(NAME VIWEBSRV_Init COMMAND tst_viwebserver "--gtest_filter=VIWEBSRV_Init.*")
