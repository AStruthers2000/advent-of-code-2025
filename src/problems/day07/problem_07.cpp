////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_07.h"

/* Specific includes/imports go here */

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem07::load_problem()
{
    m_grid = Grid::Grid2D<GridSpace>(get_lines(), [](auto const& element)
    {
       switch(element)
       {
           case '.':
               return GridSpace::Empty;
           case 'S':
               return GridSpace::Start;
           case '^':
               return GridSpace::Splitter;
           case '|':
           default:
               return GridSpace::TachyonBeam;
       }
    });

    m_beam_counts = Grid::Grid2D<std::uint64_t>(m_grid.get_row_count(), m_grid.get_col_count(), 0);

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem07::solve_part_1()
{
    std::uint64_t num_splits{0};
    Grid::Grid2D<GridSpace> current = m_grid;
    for (std::size_t i = 0; i < m_grid.get_row_count(); ++i)
    {
        num_splits += update_grid_one_step(current, i, true);
    }

    return std::make_unique<BigNumericAnswer>(num_splits);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem07::solve_part_2()
{
    std::uint64_t num_timelines{0};

    auto last_row = m_beam_counts.get_row(m_beam_counts.get_row_count() - 1).value();
    for (std::size_t i = 0; i < m_grid.get_col_count(); ++i)
    {
        num_timelines += last_row[i];
    }

    return std::make_unique<BigNumericAnswer>(num_timelines);
}

//----------------------------------------------------------------------------------------------------------------------
std::uint64_t Problem07::update_grid_one_step(Grid::Grid2D <GridSpace> &current, int row_to_update, bool update_beam_counts)
{
    auto update_beam_count = [&](Grid::GridPosition current_position, Grid::GridPosition next_position) {
        std::uint64_t starting_count = m_beam_counts.get_element(current_position).value();
        std::uint64_t next_count = m_beam_counts.get_element(next_position).value();
        m_beam_counts.set_element(starting_count + next_count, next_position);
    };

    std::uint64_t splits_this_update{0};
    current.for_each_element([&](auto const &element, Grid::GridPosition const &position) {
        if (row_to_update == position.row)
        {
            Grid::GridPosition next{position.row + 1, position.column};
            switch (element)
            {
                case GridSpace::Start:
                    current.set_element(GridSpace::TachyonBeam, next);
                    if (update_beam_counts)
                    {
                        m_beam_counts.set_element(1, next);
                    }
                    break;
                case GridSpace::TachyonBeam:
                    if (current.get_element(next) == GridSpace::Empty ||
                        current.get_element(next) == GridSpace::TachyonBeam)
                    {
                        current.set_element(GridSpace::TachyonBeam, next);
                        if (update_beam_counts)
                        {
                            update_beam_count(position, next);
                        }
                    }
                    else if (current.get_element(next) == GridSpace::Splitter)
                    {
                        Grid::GridPosition left{position.row + 1, position.column - 1};
                        Grid::GridPosition right{position.row + 1, position.column + 1};
                        current.set_element(GridSpace::TachyonBeam, left);
                        current.set_element(GridSpace::TachyonBeam, right);
                        splits_this_update++;
                        if (update_beam_counts)
                        {
                            update_beam_count(position, left);
                            update_beam_count(position, right);
                        }
                    }
            }
        }
    });

    return splits_this_update;
}

} // namespace AoC
