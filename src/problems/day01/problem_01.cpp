////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_01.h"

import aoc.math;
import aoc.parse;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem01::load_problem()
{
    for (auto const& line : get_lines())
    {
        char const direction_char = line[0];
        std::string_view count_slice{ line.begin() + 1, line.end() };

        Direction direction = direction_char == 'L' ? Direction::Left : Direction::Right;
        auto const count = AoC::Parse::sv_to_int<int>(count_slice);

        if (count.has_value())
        {
            m_turns.push_back(std::make_pair(direction, count.value()));
        }
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem01::solve_part_1()
{
    int current{ 50 };
    int zero_count{ 0 };

    for (auto const& turn : m_turns)
    {
        auto [direction, offset] = turn;
        offset = direction == Direction::Left ? offset * -1 : offset;

        AoC::Math::clamp_with_wrap(current + offset, 0, 99, current);

        if (current == 0)
        {
            ++zero_count;
        }
    }

    return std::make_unique<NumericAnswer>(zero_count);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem01::solve_part_2()
{
    int current{ 50 };
    int zero_count{ 0 };

    for (auto const& turn : m_turns)
    {
        auto const start = current;
        auto [direction, offset] = turn;
        offset = direction == Direction::Left ? offset * -1 : offset;

        int wrap_count = AoC::Math::clamp_with_wrap(current + offset, 0, 99, current);

        // if we start on zero and rotate to the left, we don't actually get a new zero crossing (because we are already
        // at 0), even though clamp_with_wrap() will say that we had a crossing (0 -> 99 is counted as a zero crossing),
        // so we subtract one from the wrap count
        if (start == 0 && direction == Direction::Left)
        {
            --wrap_count;
        }

        // if we are rotating left and end on 0, clamp_with_wrap() will not count the ending 0 as a zero crossing, so we
        // manually add one to the wrap count
        if (current == 0 && direction == Direction::Left)
        {
            ++wrap_count;
        }

        zero_count += wrap_count;
    }

    return std::make_unique<BigNumericAnswer>(zero_count);
}

} // namespace AoC
