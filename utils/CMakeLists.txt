cmake_minimum_required(VERSION 3.28)

project(utils-tests)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(CppUTest)

# Define the test executable
add_executable(utils-tests)

# Test source files
target_sources(utils-tests
    PRIVATE
        test/main.cpp
        test/tests/aoc_parse_tests.cpp
)

# Import the same modules used by the main program
target_sources(utils-tests
    PUBLIC
        FILE_SET utils TYPE CXX_MODULES FILES
        parse/aoc.parse.cppm
        parse/aoc.parse.impl.cppm
)

# Link CppUTest
target_link_libraries(utils-tests
    PRIVATE
        CppUTest
        CppUTestExt
)

# Enable test discovery with CTest (optional)
enable_testing()
add_test(NAME AllUtilsTests COMMAND utils-tests)