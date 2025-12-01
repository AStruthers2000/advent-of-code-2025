# test/CMakeLists.txt - Unit tests for advent-of-code

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
        ${CMAKE_SOURCE_DIR}/public
        ${CMAKE_SOURCE_DIR}/src/problems
        ${CMAKE_SOURCE_DIR}/utils
)

# Test source files
target_sources(advent-of-code-tests
    PRIVATE
        # test runner
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

        # tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_01_tests.cpp

        # source
        ${CMAKE_SOURCE_DIR}/src/problems/day01/problem_01.cpp
)

# Link CppUTest and aoc_modules (from utils/)
target_link_libraries(advent-of-code-tests
    PRIVATE
        CppUTest
        CppUTestExt
        aoc_modules
)

# Enable test discovery with CTest (optional)
enable_testing()
add_test(NAME advent-of-code-tests COMMAND advent-of-code-tests)