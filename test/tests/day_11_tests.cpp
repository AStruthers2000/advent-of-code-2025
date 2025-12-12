////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day11/problem_11.h"

using namespace AoC;

TEST_GROUP(Problem11Tests)
{
    Problem11* dut_p1;
    Problem11* dut_p2;
    void setup() override
    {
        dut_p1 = new Problem11("../../src/problems/day11/test_p1.txt");
        dut_p1->load_problem();

        dut_p2 = new Problem11("../../src/problems/day11/test_p2.txt");
        dut_p2->load_problem();
    }

    void teardown() override
    {
        delete dut_p1;
        delete dut_p2;
    }
};

TEST(Problem11Tests, Part1TestData)
{
    auto result = dut_p1->solve_part_1();
    auto expected = std::make_unique<BigNumericAnswer>(5);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem11Tests, Part2TestData)
{
    auto result = dut_p2->solve_part_2();
    auto expected = std::make_unique<BigNumericAnswer>(2);

    COMPARE_ANSWER(expected.get(), result.get());
}
