////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief StringFrom support for unit tests
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ADVENT_OF_CODE_STRING_FROM_H
#define ADVENT_OF_CODE_STRING_FROM_H

#include <CppUTest/TestHarness.h>

#include "../../public/problem.h"

SimpleString StringFrom(AoC::NumericAnswer const& inst);
SimpleString StringFrom(AoC::BigNumericAnswer const& inst);
SimpleString StringFrom(AoC::StringAnswer const& inst);
SimpleString StringFrom(AoC::NumericAnswer* inst);
SimpleString StringFrom(AoC::BigNumericAnswer* inst);
SimpleString StringFrom(AoC::StringAnswer* inst);

#endif //ADVENT_OF_CODE_STRING_FROM_H
