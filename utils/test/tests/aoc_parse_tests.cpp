#include <CppUTest/TestHarness.h>
#include <string>
#include <vector>

import aoc.parse;

TEST_GROUP(ParseUtilTests) {};

TEST(ParseUtilTests, SplitString)
{
    std::vector<std::string> expected = {"Hello", "world"};
    std::vector<std::string_view> result = AoC::Parse::split_line_by_token("Hello world", " ");

    for (std::size_t i = 0; i < expected.size(); ++i)
    {
        STRCMP_EQUAL(expected[i].c_str(), std::string(result[i]).c_str());
    }
}