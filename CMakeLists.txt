cmake_minimum_required(VERSION 3.28)

project(advent-of-code LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/experimental:module)
    add_compile_options(/std:c++latest)
endif()

# Add utils library CMakeLists
add_subdirectory(utils)

# Main executable
add_executable(advent-of-code
    src/main.cpp
)

target_sources(advent-of-code
    PUBLIC
        public/answer.h
        public/problem.h
        public/solver.h
    PRIVATE
        src/solver.cpp
        src/problems/day01/problem_01.h
        src/problems/day01/problem_01.cpp
        src/problems/day02/problem_02.h
        src/problems/day02/problem_02.cpp
        src/problems/day03/problem_03.h
        src/problems/day03/problem_03.cpp
        src/problems/day04/problem_04.h
        src/problems/day04/problem_04.cpp
        src/problems/day05/problem_05.h
        src/problems/day05/problem_05.cpp
        src/problems/day06/problem_06.h
        src/problems/day06/problem_06.cpp
        src/problems/day07/problem_07.h
        src/problems/day07/problem_07.cpp
        src/problems/day08/problem_08.h
        src/problems/day08/problem_08.cpp
        src/problems/day09/problem_09.h
        src/problems/day09/problem_09.cpp
        src/problems/day10/problem_10.h
        src/problems/day10/problem_10.cpp
        src/problems/day11/problem_11.h
        src/problems/day11/problem_11.cpp
        src/problems/day12/problem_12.h
        src/problems/day12/problem_12.cpp
)

# Link modules to executable
target_link_libraries(advent-of-code PRIVATE aoc_modules)

# Include directories
target_include_directories(advent-of-code PRIVATE
        ${CMAKE_SOURCE_DIR}/public
        ${CMAKE_SOURCE_DIR}/src
)

# Add tests subdirectory
add_subdirectory(test)
