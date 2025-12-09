////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day08/problem_08.h"

using namespace AoC;

TEST_GROUP(Problem08Tests)
{
    Problem08* dut;
    void setup() override
    {
        dut = new Problem08("../../src/problems/day08/test.txt");
        dut->load_problem();
        dut->set_num_connections(10);
    }

    void teardown() override
    {
        delete dut;
    }
};

TEST(Problem08Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique<BigNumericAnswer>(40);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem08Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique<BigNumericAnswer>(25272);

    COMPARE_ANSWER(expected.get(), result.get());
}
