cmake_minimum_required(VERSION 3.28)
project(advent-of-code)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

target_sources(advent-of-code
    PUBLIC
        FILE_SET utils TYPE CXX_MODULES FILES
        utils/math/math_utils.cppm
        utils/math/math_utils.simple.cppm
        utils/math/math_utils.combinatorics.cppm
        utils/math/math_utils.linear_algebra.cppm
)

add_subdirectory(utils)
add_subdirectory(test)
set_target_properties(utils-tests PROPERTIES FOLDER "tests")
set_target_properties(advent-of-code PROPERTIES FOLDER "main")
set_target_properties(advent-of-code-tests PROPERTIES FOLDER "main")