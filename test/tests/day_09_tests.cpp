////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day09/problem_09.h"

using namespace AoC;

TEST_GROUP(Problem09Tests)
{
    Problem09* dut;
    void setup() override
    {
        dut = new Problem09("../../src/problems/day09/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem09Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique<BigNumericAnswer>(50);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem09Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique<BigNumericAnswer>(24);

    COMPARE_ANSWER(expected.get(), result.get());
}
