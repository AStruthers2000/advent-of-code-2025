////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_04.h"

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem04::load_problem()
{
    m_grid = Grid::Grid2D<Tile>(get_lines(), [](const char& element)
    {
       return element == '@' ? Tile::Paper : Tile::NoPaper;
    });
    return false;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem04::solve_part_1()
{
    auto current = m_grid;
    std::uint64_t count = remove_papers(current);

    return std::make_unique<BigNumericAnswer>(count);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem04::solve_part_2()
{
    std::uint64_t papers_removed{ 0 };
    std::uint64_t removed_this_time{ 0 };

    auto current = m_grid;

    do
    {
        removed_this_time = remove_papers(current);
        papers_removed += removed_this_time;
    }while(removed_this_time != 0);

    return std::make_unique<BigNumericAnswer>(papers_removed);
}

//----------------------------------------------------------------------------------------------------------------------
std::uint64_t Problem04::remove_papers(Grid::Grid2D <Tile>& current)
{
    Grid::Grid2D<Tile> temp = current;

    std::uint64_t new_papers_removed{0};

    temp.for_each_element([&](Tile &element, AoC::Grid::GridPosition position) {
        if (element == Tile::Paper)
        {
            auto neighbors = current.get_neighbors(position, true);
            std::size_t paper_count{0};
            for (auto const &neighbor: neighbors)
            {
                auto [other, pos, dir] = neighbor;
                if (other == Tile::Paper)
                {
                    ++paper_count;
                }
            }
            if (paper_count < 4)
            {
                element = Tile::Removed;
                ++new_papers_removed;
            }
        }
    });

    current = temp;
    return new_papers_removed;
}

} // namespace AoC
