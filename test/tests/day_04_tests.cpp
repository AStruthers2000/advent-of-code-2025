////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day04/problem_04.h"

using namespace AoC;

TEST_GROUP(Problem04Tests)
{
    Problem04* dut;
    void setup() override
    {
        dut = new Problem04("../../src/problems/day04/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem04Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique<NumericAnswer>(13);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem04Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique<NumericAnswer>(0);

//    COMPARE_ANSWER(expected.get(), result.get());
}
