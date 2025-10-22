#include <iostream>
//#include "answer.h"

//import math_utils;
import aoc.parse;

int main()
{
    std::cout << "Hello, World!" << std::endl;
//    std::cout << "|-5| = " << abs_val(-5) << std::endl;
//    std::cout << "Answer: " << AoC::Answer::solve_problem(1) << std::endl;

    auto val = AoC::Parse::split_line_by_token("Hello world", " ");
    auto val2 = AoC::Parse::split_lines("1000\n2000\n3000\n\n4000\n\n5000\n");
    return 0;
}
