////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_05.h"

#include <algorithm>
#include <ranges>
import aoc.parse;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem05::load_problem()
{
    bool parsing_ranges = true;
    for (auto const& line : get_lines())
    {
        if (line.empty())
        {
            parsing_ranges = false;
            continue;
        }

        if (parsing_ranges)
        {
            auto range = AoC::Parse::split_line_by_token(line, "-");
            auto low = AoC::Parse::sv_to_int<std::uint64_t>(range[0]);
            auto high = AoC::Parse::sv_to_int<std::uint64_t>(range[1]);

            if (low.has_value() && high.has_value())
            {
                m_ranges.push_back({low.value(), high.value()});
            }
        }
        else
        {
            auto id = AoC::Parse::sv_to_int<std::uint64_t>(line);
            if (id.has_value())
            {
                m_ids.push_back(id.value());
            }
        }
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem05::solve_part_1()
{
    std::uint64_t fresh_count{ 0 };

    for (auto const& id : m_ids)
    {
        for (auto const& range : m_ranges)
        {
            if (range.low <= id && id <= range.high)
            {
                fresh_count++;
                break;
            }
        }
    }

    return std::make_unique<BigNumericAnswer>(fresh_count);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem05::solve_part_2()
{
    std::uint64_t fresh_count{ 0 };

    std::vector<Range> merged = merge_all_ranges(m_ranges);

    for (auto const& range : merged)
    {
        fresh_count += ((range.high - range.low) + 1);
    }

    return std::make_unique<BigNumericAnswer>(fresh_count);
}

std::optional<Problem05::Range> Problem05::merge_ranges_if_overlap(const Problem05::Range &r1, const Problem05::Range &r2)
{
    if (r1.low <= r2.high && r2. low <= r1.high)
    {
        return Range{
                .low = std::min(r1.low, r2. low),
                .high = std::max(r1.high, r2.high)
        };
    }

    return std::nullopt;
}

std::vector<Problem05::Range> Problem05::merge_all_ranges(std::vector<Problem05::Range> all_ranges)
{
    if (all_ranges.empty())
    {
        return {};
    }

    // Sort ranges by their low value
    std::ranges::sort(all_ranges, {}, &Range::low);

    std::vector<Range> merged;
    merged.reserve(all_ranges.size());

    Range current = all_ranges[0];

    for (std::size_t i = 1; i < all_ranges.size(); ++i)
    {
        auto const& next = all_ranges[i];

        // Check if current and next can be merged
        if (auto merged_range = merge_ranges_if_overlap(current, next))
        {
            current = *merged_range;
        }
        else
        {
            // No overlap/adjacency, save current and move to next
            merged.push_back(current);
            current = next;
        }
    }

    // Don't forget the last range
    merged.push_back(current);

    return merged;
}

} // namespace AoC
