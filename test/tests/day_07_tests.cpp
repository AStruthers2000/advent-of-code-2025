////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day07/problem_07.h"

using namespace AoC;

TEST_GROUP(Problem07Tests)
{
    Problem07* dut;
    void setup() override
    {
        dut = new Problem07("../../src/problems/day07/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem07Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique<BigNumericAnswer>(21);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem07Tests, Part2TestData)
{
    dut->solve_part_1();
    auto result = dut->solve_part_2();
    auto expected = std::make_unique<BigNumericAnswer>(40);

    COMPARE_ANSWER(expected.get(), result.get());
}
