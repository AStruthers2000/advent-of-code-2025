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
//    auto answer = dut->solve_part_1();
//    if (answer)
//    {
//        NumericAnswer& expected = *std::make_unique<NumericAnswer>(2);
//        NumericAnswer& result = dynamic_cast<NumericAnswer&>(*answer);
//
//        CHECK_EQUAL(expected, result);
//    }
//    else
//    {
//        CHECK_TRUE(false);
//    }
}

TEST(Problem_01_Tests, Part2TestData)
{
    auto answer = dut->solve_part_2();
    if (answer)
    {
        BigNumericAnswer& expected = *std::make_unique<BigNumericAnswer>(5);
        BigNumericAnswer& result = dynamic_cast<BigNumericAnswer&>(*answer);

        CHECK_EQUAL(expected, result);
    }
    else
    {
        CHECK_TRUE(false);
    }
}
