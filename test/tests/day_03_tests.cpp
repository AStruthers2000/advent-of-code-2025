////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day03/problem_03.h"

using namespace AoC;

TEST_GROUP(Problem03Tests)
{
    Problem03* dut;
    void setup() override
    {
        dut = new Problem03("../../src/problems/day03/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem03Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique<NumericAnswer>(357);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem03Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique<BigNumericAnswer>(3121910778619);

    COMPARE_ANSWER(expected.get(), result.get());
}
