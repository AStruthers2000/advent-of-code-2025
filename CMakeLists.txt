cmake_minimum_required(VERSION 3.28)

project(advent-of-code LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main application
add_executable(advent-of-code)

target_include_directories(advent-of-code
    PUBLIC
        public/
)

target_sources(advent-of-code
    PUBLIC
        public/answer.h
    PRIVATE
        src/main.cpp
        src/answer.cpp
)

# AoC utils
target_sources(advent-of-code PRIVATE
    FILE_SET CXX_MODULES FILES
        utils/parse/aoc.parse.cppm
        utils/parse/aoc.parse.impl.cppm
)

 add_subdirectory(utils)
 add_subdirectory(test)
