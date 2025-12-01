#include <CppUTest/TestHarness.h>

#include "../../src/problems/day01/problem_01.h"
#include "../support/string_from.h"

using namespace AoC;

TEST_GROUP(Problem_01_Tests)
{
    Problem_01* dut;
    void setup() override
    {
        dut = new Problem_01("../../src/problems/day01/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem_01_Tests, Part1TestData)
{

}

TEST(Problem_01_Tests, Part2TestData)
{

}
