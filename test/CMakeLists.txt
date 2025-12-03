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
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_02_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_03_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_04_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_05_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_06_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_07_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_08_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_09_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_10_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_11_tests.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/tests/day_12_tests.cpp

        # source
        ${CMAKE_SOURCE_DIR}/src/problems/day01/problem_01.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day02/problem_02.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day03/problem_03.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day04/problem_04.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day05/problem_05.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day06/problem_06.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day07/problem_07.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day08/problem_08.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day09/problem_09.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day10/problem_10.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day11/problem_11.cpp
        ${CMAKE_SOURCE_DIR}/src/problems/day12/problem_12.cpp

        # support
        ${CMAKE_CURRENT_SOURCE_DIR}/support/answer_comparator.cpp
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