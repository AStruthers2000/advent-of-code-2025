////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day06/problem_06.h"

using namespace AoC;

TEST_GROUP(Problem06Tests)
{
    Problem06* dut;
    void setup() override
    {
        dut = new Problem06("../../src/problems/day06/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem06Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique</*Problem type goes here*/>(/*Part 1 test answer goes here*/);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem06Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique</*Problem type goes here*/>(/*Part 2 test answer goes here*/);

    COMPARE_ANSWER(expected.get(), result.get());
}
