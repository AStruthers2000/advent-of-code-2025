#include <iostream>
#include "answer.h"

import math_utils;

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << "|-5| = " << abs_val(-5) << std::endl;
    std::cout << "Answer: " << AoC::Answer::solve_problem(1) << std::endl;
    return 0;
}
