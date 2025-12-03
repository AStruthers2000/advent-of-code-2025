////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_03.h"

/* Specific includes/imports go here */

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem03::load_problem()
{
    m_banks = Grid::Grid2D<std::uint8_t>(get_lines(), [](char const& element)
    {
       return static_cast<std::uint8_t>(element - '0');
    });

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem03::solve_part_1()
{
    std::uint32_t sum{ 0 };

    for (int i = 0; i < m_banks.get_row_count(); ++i)
    {
        sum += find_max_sequence(m_banks.get_row(i).value(), 2);
    }

    return std::make_unique<NumericAnswer>(sum);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem03::solve_part_2()
{
    std::uint64_t sum{ 0 };

    for (int i = 0; i < m_banks.get_row_count(); ++i)
    {
        sum += find_max_sequence(m_banks.get_row(i).value(), 12);
    }

    return std::make_unique<BigNumericAnswer>(sum);
}

//----------------------------------------------------------------------------------------------------------------------
std::uint64_t Problem03::find_max_sequence(const std::vector<std::uint8_t> &row, std::size_t sequence_size) const
{
    std::uint64_t max{ 0 };

    std::size_t start_index{ 0 };
    for (std::size_t i = 0; i < sequence_size; ++i)
    {
        std::size_t max_end = sequence_size - i;
        auto [next_max, new_index] = find_next_greedy(row, start_index, max_end);
        max += next_max * pow(10, sequence_size - i - 1);
        start_index = new_index + 1;
    }

    return max;
}

//----------------------------------------------------------------------------------------------------------------------
std::pair<std::uint8_t, std::size_t> Problem03::find_next_greedy(std::vector<std::uint8_t> const& row,
                                         std::size_t start_pos,
                                         std::size_t max_end) const
{
    std::uint8_t max{ 0 };
    std::size_t new_index{ 0 };
    for (std::size_t i = start_pos; i < row.size() - max_end + 1; ++i)
    {
        if (row[i] > max)
        {
            max = row[i];
            new_index = i;
        }
    }
    return std::make_pair(max, new_index);
}

} // namespace AoC
