////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day11/problem_11.h"

using namespace AoC;

TEST_GROUP(Problem11Tests)
{
    Problem11* dut;
    void setup() override
    {
        dut = new Problem11("../../src/problems/day11/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem11Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique</*Problem type goes here*/>(/*Part 1 test answer goes here*/);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem11Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique</*Problem type goes here*/>(/*Part 2 test answer goes here*/);

    COMPARE_ANSWER(expected.get(), result.get());
}
