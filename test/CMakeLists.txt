cmake_minimum_required(VERSION 3.28)

project(advent-of-code-tests)

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
add_executable(advent-of-code-tests)

target_include_directories(advent-of-code-tests
    PUBLIC
        ${PROJECT_SOURCE_DIR}/../public/
)

# Test source files
target_sources(advent-of-code-tests
    PRIVATE
        # test runner
        ${PROJECT_SOURCE_DIR}/main.cpp

        # tests
        ${PROJECT_SOURCE_DIR}/tests/answer_tests.cpp

        # source
        ${PROJECT_SOURCE_DIR}/../src/answer.cpp
)

# Link CppUTest
target_link_libraries(advent-of-code-tests
    PRIVATE
        CppUTest
        CppUTestExt
)

# Enable test discovery with CTest (optional)
enable_testing()
add_test(NAME advent-of-code-tests COMMAND advent-of-code-tests)