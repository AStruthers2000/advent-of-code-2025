#include "solver.h"

int main()
{
    AoC::Solver& solver{ AoC::Solver::instance() };
//    solver.solve_all_problems();
    solver.solve_problem(AoC::Day::DAY_01);
    return 0;
}
