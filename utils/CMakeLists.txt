#cmake_minimum_required(VERSION 3.28)
#
#project(utils-tests)
#
#set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
#
## Add CppUTest
#include(FetchContent)
#FetchContent_Declare(
#    CppUTest
#        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
#        GIT_TAG        master
#)
#FetchContent_MakeAvailable(CppUTest)
#
## Define the test executable
#add_executable(utils-tests)
#
## Test source files
#target_sources(utils-tests
#    PRIVATE
#        test/main.cpp
#        test/tests/aoc_parse_tests.cpp
#)
#
## Import the same modules used by the main program
#target_sources(utils-tests
#    PUBLIC
#        FILE_SET utils TYPE CXX_MODULES FILES
#        parse/aoc.parse.cppm
#        parse/aoc.parse.impl.cppm
#)
#
## Link CppUTest
#target_link_libraries(utils-tests
#    PRIVATE
#        CppUTest
#        CppUTestExt
#)
#
## Enable test discovery with CTest (optional)
#enable_testing()
#add_test(NAME AllUtilsTests COMMAND utils-tests)

# add_library(utils)
#
#target_sources(utils
#    PUBLIC
#        FILE_SET cxx_modules TYPE CXX_MODULES
#        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
#        FILES
#        ${CMAKE_CURRENT_SOURCE_DIR}/math/aoc.math.cppm
#        ${CMAKE_CURRENT_SOURCE_DIR}/math/aoc.math.impl.cppm
#        ${CMAKE_CURRENT_SOURCE_DIR}/parse/aoc.parse.cppm
#        ${CMAKE_CURRENT_SOURCE_DIR}/parse/aoc.parse.impl.cppm
#)

cmake_minimum_required(VERSION 3.28)
project(aoc_modules CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/experimental:module)
    add_compile_options(/std:c++latest)
endif()

# Define module library
add_library(aoc_modules)
target_sources(aoc_modules
    PUBLIC
        FILE_SET CXX_MODULES FILES
            aoc.grid.ixx
            aoc.math.ixx
            aoc.parse.ixx
)