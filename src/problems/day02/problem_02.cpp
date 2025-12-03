////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_02.h"

#include <algorithm>

import aoc.string;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem02::load_problem()
{
    std::string_view line = get_lines()[0];
    std::vector<std::string_view> ranges = AoC::Parse::split_line_by_token(line, ",");
    for (auto const& range : ranges)
    {
        std::vector<std::string_view> split = AoC::Parse::split_line_by_token(range, "-");
        Range range{ std::string(split[0]), std::string(split[1]) };
        m_ids.push_back(range);
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem02::solve_part_1()
{
    std::uint64_t sum{ 0 };

    std::ranges::for_each(m_ids, [&sum](auto const& range)
    {
        std::uint64_t start = AoC::Parse::sv_to_int<std::uint64_t>(range.low).value();
        std::uint64_t end = AoC::Parse::sv_to_int<std::uint64_t>(range.high).value();

        std::uint64_t current{ start };

        while (current <= end)
        {
            std::string current_string = std::to_string(current);

            auto val = AoC::String::split_string_into_even_parts(current_string, 2);
            if (val.has_value() && AoC::String::are_strings_equal(val.value()))
            {
                sum += current;
            }
            current++;
        }
    });

    return std::make_unique<BigNumericAnswer>(sum);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem02::solve_part_2()
{
    std::uint64_t sum{ 0 };

    std::ranges::for_each(m_ids, [&sum](auto const& range)
    {
        std::uint64_t start = AoC::Parse::sv_to_int<std::uint64_t>(range.low).value();
        std::uint64_t end = AoC::Parse::sv_to_int<std::uint64_t>(range.high).value();

        std::uint64_t current{ start };

        while (current <= end)
        {
            std::string current_string = std::to_string(current);

            for (int i = 2; i <= current_string.length(); ++i)
            {
                auto val = AoC::String::split_string_into_even_parts(current_string, i);
                if (val.has_value() && AoC::String::are_strings_equal(val.value()))
                {
                    sum += current;
                    break;
                }
            }

            current++;
        }
    });

    return std::make_unique<BigNumericAnswer>(sum);
}

} // namespace AoC
