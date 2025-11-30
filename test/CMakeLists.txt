cmake_minimum_required(VERSION 3.28.1)

project(advent-of-code-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/experimental:module)
    add_compile_options(/std:c++latest)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fmodules-ts)
endif()

# Add CppUTest
include(FetchContent)
FetchContent_Declare(
        CppUTest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(CppUTest)

# Define module library
add_library(aoc_modules)
target_sources(aoc_modules
    PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/../utils
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/../utils/aoc.math.ixx
            ${CMAKE_CURRENT_SOURCE_DIR}/../utils/aoc.parse.ixx
)

# Define the test executable
add_executable(advent-of-code-tests)

target_include_directories(advent-of-code-tests
    PUBLIC
        ${PROJECT_SOURCE_DIR}/../public
        ${PROJECT_SOURCE_DIR}/../src/problems
        ${PROJECT_SOURCE_DIR}/../utils
)

# Test source files
target_sources(advent-of-code-tests
    PRIVATE
        # test runner
        ${PROJECT_SOURCE_DIR}/main.cpp

        # tests
        ${PROJECT_SOURCE_DIR}/tests/day_01_tests.cpp

        # source
        ${PROJECT_SOURCE_DIR}/../src/problems/day01/problem_01.cpp
)

# Link CppUTest
target_link_libraries(advent-of-code-tests
    PRIVATE
        CppUTest
        CppUTestExt
)

target_link_libraries(advent-of-code-tests PRIVATE aoc_modules)

#add_subdirectory(../utils ${CMAKE_CURRENT_BINARY_DIR})
#add_subdirectory(../utils)

# Enable test discovery with CTest (optional)
enable_testing()
add_test(NAME advent-of-code-tests COMMAND advent-of-code-tests)