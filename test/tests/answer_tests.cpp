#include <CppUTest/TestHarness.h>

#include "../../public/answer.h"

using namespace AoC::Answer;

TEST_GROUP(Answer_Tests)
{

};

TEST(Answer_Tests, SolveProblem)
{
    CHECK_EQUAL(2, solve_problem(1));
    CHECK_EQUAL(1, solve_problem(0));
    CHECK_EQUAL(8, solve_problem(7));
}