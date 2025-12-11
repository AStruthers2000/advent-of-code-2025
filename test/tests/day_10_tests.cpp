////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day10/problem_10.h"

using namespace AoC;

TEST_GROUP(Problem10Tests)
{
    Problem10* dut;
    void setup() override
    {
        dut = new Problem10("../../src/problems/day10/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem10Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique<BigNumericAnswer>(7);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem10Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique<BigNumericAnswer>(33);

    COMPARE_ANSWER(expected.get(), result.get());
}
