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
            aoc.matrix.ixx
            aoc.parse.ixx
            aoc.regex.ixx
            aoc.string.ixx
)