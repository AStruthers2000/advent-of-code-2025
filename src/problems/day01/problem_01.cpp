////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_01.h"

/* Specific includes/imports go here */
import aoc.grid;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem_01::load_problem()
{
    return false;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem_01::solve_part_1()
{
    enum class Height : std::uint8_t
    {
        SHORT = 0,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        INVALID
    };
//    Grid::Grid2D<std::string> grid(10, 20, "Hello");
//    Grid::Grid2D<Thing> grid(get_lines());
    Grid::Grid2D<Height> grid(get_lines(), [](char element)
    {
        return static_cast<Height>(element - '0');
    });
    auto neighbors = grid.get_neighbors(Grid::GridPosition{1, 1}, true);
    return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem_01::solve_part_2()
{
    return nullptr;
}

} // namespace AoC
