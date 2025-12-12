////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_12.h"

/* Specific includes/imports go here */
import aoc.parse;
import aoc.string;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem12::load_problem()
{
    int shape_count = 0;
    bool parsing_shape{ false };
    int tiles_in_shape{ 0 };
    for (auto const& line : get_lines())
    {
        if (line.size() == 2)
        {
            parsing_shape = true;
        }
        else if (line.empty())
        {
            if (parsing_shape)
            {
                m_shapes.push_back(Shape{tiles_in_shape});
            }
            parsing_shape = false;
            tiles_in_shape = 0;
        }
        else if (parsing_shape == true)
        {
            int tiles = AoC::String::count_occurrences_of_char_in_string(line, '#');
            tiles_in_shape += tiles;
        }
        else
        {
            auto split = AoC::Parse::split_line_by_token(AoC::Parse::split_line_by_token(line, ":")[0], "x");

            int row = AoC::Parse::sv_to_int<int>(split[0]).value();
            int col = AoC::Parse::sv_to_int<int>(split[1]).value();

            auto shape_split = AoC::Parse::split_line_by_token(AoC::Parse::split_line_by_token(line, ": ")[1], " ");
            int val1 = AoC::Parse::sv_to_int<int>(shape_split[0]).value();
            int val2 = AoC::Parse::sv_to_int<int>(shape_split[1]).value();
            int val3 = AoC::Parse::sv_to_int<int>(shape_split[2]).value();
            int val4 = AoC::Parse::sv_to_int<int>(shape_split[3]).value();
            int val5 = AoC::Parse::sv_to_int<int>(shape_split[4]).value();
            int val6 = AoC::Parse::sv_to_int<int>(shape_split[5]).value();

            std::array<int, 6> counts = {val1, val2, val3, val4, val5, val6};

            m_boxes.push_back(Box{row, col, counts});
        }
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem12::solve_part_1()
{
    int valid_configs { 0 };

    for (auto const& box : m_boxes)
    {
        int area = box.width * box.height;
        int sum = box.shapes[0] * m_shapes[0].num_tiles_in_shape +
                  box.shapes[1] * m_shapes[1].num_tiles_in_shape +
                  box.shapes[2] * m_shapes[2].num_tiles_in_shape +
                  box.shapes[3] * m_shapes[3].num_tiles_in_shape +
                  box.shapes[4] * m_shapes[4].num_tiles_in_shape +
                  box.shapes[5] * m_shapes[5].num_tiles_in_shape;

        if (area < sum)
            continue;

        valid_configs++;
    }

    return std::make_unique<BigNumericAnswer>(valid_configs);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem12::solve_part_2()
{
    return std::make_unique<BigNumericAnswer>(0);
}

} // namespace AoC
