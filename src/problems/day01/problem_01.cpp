////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Problem_01.h"

#include <algorithm>

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem_01::load_problem()
{
    std::uint64_t sum = 0;
    for (std::size_t i = 0; i < get_lines().size(); ++i)
    {
        std::string_view line = get_lines()[i];
        if (line.empty())
        {
            m_sums.push_back(sum);
            sum = 0;
        }
        else
        {
            auto val = AoC::Parse::sv_to_int<std::uint32_t>(line);
            sum += static_cast<std::uint64_t>(val.value_or(0));
        }
    }

    std::ranges::sort(m_sums, std::ranges::greater());
    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem_01::solve_part_1()
{
    return std::make_unique<BigNumericAnswer>(m_sums[0]);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem_01::solve_part_2()
{
    return std::make_unique<BigNumericAnswer>(m_sums[0] + m_sums[1] + m_sums[2]);
}

} // namespace AoC
