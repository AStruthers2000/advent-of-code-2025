////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <CppUTest/TestHarness.h>

#include "../support/answer_comparator.h"
#include "../../src/problems/day01/problem_01.h"

using namespace AoC;

TEST_GROUP(Problem01Tests)
{
    Problem01* dut;
    void setup() override
    {
        dut = new Problem01("../../src/problems/day01/test.txt");
        dut->load_problem();
    }

    void teardown() override
    {
        delete dut;
    }

protected:
    void extra_test(std::string_view file, Answer* expected)
    {
        std::string filename = "../../test/extra_tests/day01/" + std::string(file);
        Problem01* extra = new Problem01(filename);
        extra->load_problem();

        auto result = extra->solve_part_2();

        COMPARE_ANSWER(expected, result.get());
        delete extra;
    }
};

TEST(Problem01Tests, Part1TestData)
{
    auto result = dut->solve_part_1();
    auto expected = std::make_unique<NumericAnswer>(3);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem01Tests, Part2TestData)
{
    auto result = dut->solve_part_2();
    auto expected = std::make_unique<NumericAnswer>(6);

    COMPARE_ANSWER(expected.get(), result.get());
}

TEST(Problem01Tests, Part2ExtraTest1)
{
    auto expected = std::make_unique<NumericAnswer>(1);

    extra_test("extra_test_1.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest2)
{
    auto expected = std::make_unique<NumericAnswer>(1);

    extra_test("extra_test_2.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest3)
{
    auto expected = std::make_unique<NumericAnswer>(1);

    extra_test("extra_test_3.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest4)
{
    auto expected = std::make_unique<NumericAnswer>(1);

    extra_test("extra_test_4.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest5)
{
    auto expected = std::make_unique<NumericAnswer>(1);

    extra_test("extra_test_5.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest6)
{
    auto expected = std::make_unique<NumericAnswer>(1);

    extra_test("extra_test_6.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest7)
{
    auto expected = std::make_unique<NumericAnswer>(2);

    extra_test("extra_test_7.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest8)
{
    auto expected = std::make_unique<NumericAnswer>(2);

    extra_test("extra_test_8.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest9)
{
    auto expected = std::make_unique<NumericAnswer>(2);

    extra_test("extra_test_9.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest10)
{
    auto expected = std::make_unique<NumericAnswer>(2);

    extra_test("extra_test_10.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest11)
{
    auto expected = std::make_unique<NumericAnswer>(2);

    extra_test("extra_test_11.txt", expected.get());
}

TEST(Problem01Tests, Part2ExtraTest12)
{
    auto expected = std::make_unique<NumericAnswer>(2);

    extra_test("extra_test_12.txt", expected.get());
}

