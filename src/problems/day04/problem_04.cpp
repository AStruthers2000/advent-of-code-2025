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
    auto after = remove_papers(m_grid);
    std::uint64_t count = after.count_occurrence(Tile::Removed);

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
        auto after = remove_papers(current);
        removed_this_time = after.count_occurrence(Tile::Removed);
        after.set_elements(Tile::Removed, Tile::NoPaper);
        current = after;
        papers_removed += removed_this_time;
    }while(removed_this_time != 0);

    return std::make_unique<BigNumericAnswer>(papers_removed);
}

//----------------------------------------------------------------------------------------------------------------------
Grid::Grid2D<Problem04::Tile> Problem04::remove_papers(const Grid::Grid2D <Tile> &current)
{
    Grid::Grid2D<Tile> temp = current;

    for (std::size_t row_idx = 0; row_idx < current.get_row_count(); ++row_idx)
    {
        auto row = current.get_row(row_idx).value();
        for (std::size_t col_idx = 0; col_idx < row.size(); ++col_idx)
        {
            auto position = AoC::Grid::GridPosition{static_cast<int>(row_idx), static_cast<int>(col_idx)};
            auto tile = current.get_element(position).value();
            if (tile == Tile::Paper)
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
                    temp.set_element(position, Tile::Removed);
                }
            }
        }
    }

    return std::move(temp);
}

} // namespace AoC
