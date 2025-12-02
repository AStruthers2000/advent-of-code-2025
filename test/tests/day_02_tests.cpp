////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day02/problem_02.h"

using namespace AoC;

TEST_GROUP(Problem02Tests)
{
    Problem02* dut;
    void setup() override
    {
        dut = new Problem02("../../src/problems/day02/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem02Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique</*Problem type goes here*/>(/*Part 1 test answer goes here*/);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem02Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique</*Problem type goes here*/>(/*Part 2 test answer goes here*/);

    COMPARE_ANSWER(expected.get(), result.get());
}
