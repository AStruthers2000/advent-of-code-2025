#include <CppUTest/TestHarness.h>

import math_utils;

TEST_GROUP(MathUtilsSimple) {};

TEST(MathUtilsSimple, AbsValWorks)
{
    CHECK_EQUAL(5, abs_val(-5));
    CHECK_EQUAL(0, abs_val(0));
    CHECK_EQUAL(7, abs_val(7));
}