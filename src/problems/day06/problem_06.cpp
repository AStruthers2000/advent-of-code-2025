////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_06.h"

#include <algorithm>
#include <ranges>
import aoc.parse;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem06::load_problem()
{
    std::vector<std::vector<int>> math;
    math.resize(get_lines().size());
    for (auto const& [idx, line] : std::views::enumerate(get_lines()))
    {
        auto split = AoC::Parse::split_line_by_token(line, " ");
        for (auto const& number : split)
        {
            int value_to_add{ 0 };

            auto val = AoC::Parse::sv_to_int<int>(number);
            if (val.has_value())
            {
                value_to_add = val.value();
            }
            else
            {
                if (number == "*")
                {
                    value_to_add = -2;
                }
                else if (number == "+")
                {
                    value_to_add = -1;
                }
            }

            math[idx].push_back(value_to_add);
        }
    }

    m_grid = Grid::Grid2D<int>(math);
    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem06::solve_part_1()
{
    std::uint64_t sum{ 0 };
    for (std::size_t i = 0; i < m_grid.get_col_count(); ++i)
    {
        std::uint64_t value{ 0 };
        auto column = m_grid.get_col(i).value();

        char op = *(column.end() - 1) == -1 ? '+' : '*';

        for (auto const& [idx, element] : std::views::enumerate(column))
        {
            if (idx == 0)
            {
                value = element;
            }
            else if (idx < column.size() - 1)
            {
                switch (op){
                    case '+':
                        value += element;
                        break;
                    case '*':
                        value *= element;
                        break;
                    default:
                        std::printf("Something has gone horribly wrong\n");
                }
            }
        }

        sum += value;
    }

    return std::make_unique<BigNumericAnswer>(sum);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem06::solve_part_2()
{
    std::uint64_t sum{ 0 };
    Grid::Grid2D<char> char_grid = Grid::Grid2D<char>(get_lines());

    bool ready_for_next_column = true;
    std::vector<int> problem_digits{};
    char problem_operation{};

    for (std::size_t i = 0; i < char_grid.get_col_count(); ++i)
    {
        std::vector<char> column = char_grid.get_col(i).value();

        if (std::ranges::all_of(column, [](auto const& element){ return element == ' '; }))
        {
            ready_for_next_column = true;
        }
        else
        {
            std::vector<int> digits{};
            char op{};
            for (char const &c: column)
            {
                if (c != ' ')
                {
                    ready_for_next_column = false;
                    auto v = AoC::Parse::sv_to_int<int>(std::string(1, c));
                    if (v.has_value())
                    {
                        digits.push_back(v.value());
                    }

                    if (c == '*' || c == '+')
                    {
                        op = c;
                    }
                }
            }

            int digit{};
            for (auto const [idx, val] : std::views::enumerate(digits))
            {
                digit += val * pow(10, digits.size() - idx - 1);
            }
            problem_digits.push_back(digit);

            if (op == '+' || op == '*')
            {
                problem_operation = op;
            }
        }

        if (ready_for_next_column || i == char_grid.get_col_count() - 1)
        {
            std::uint64_t temp{};
            for (auto const& [idx, element] : std::views::enumerate(problem_digits))
            {
                if (idx == 0)
                {
                    temp = element;
                }
                else
                {
                    switch (problem_operation){
                        case '+':
                            temp += element;
                            break;
                        case '*':
                            temp *= element;
                            break;
                        default:
                            std::printf("Something has gone horribly wrong\n");
                    }
                }
            }
            sum += temp;
            problem_operation = char{};
            problem_digits.clear();
        }
    }
    return std::make_unique<BigNumericAnswer>(sum);
}

} // namespace AoC
