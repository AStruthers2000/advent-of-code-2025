////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "answer_comparator.h"

void COMPARE_ANSWER(AoC::Answer* expected, AoC::Answer* result)
{
    if (expected == nullptr && result == nullptr)
    {
        CHECK_TRUE(true);
    }
    else if (expected == nullptr || result == nullptr)
    {
        CHECK_TRUE(false);
    }
    else
    {
        std::string expected_string = expected->to_string();
        std::string result_string = result->to_string();
        STRCMP_EQUAL(expected_string.c_str(), result_string.c_str());
    }
}