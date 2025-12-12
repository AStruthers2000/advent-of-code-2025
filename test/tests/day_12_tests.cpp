////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day12/problem_12.h"

using namespace AoC;

TEST_GROUP(Problem12Tests)
{
    Problem12* dut;
    void setup() override
    {
        dut = new Problem12("../../src/problems/day12/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem12Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique<BigNumericAnswer>(2);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem12Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique<BigNumericAnswer>(0);

    COMPARE_ANSWER(expected.get(), result.get());
}
