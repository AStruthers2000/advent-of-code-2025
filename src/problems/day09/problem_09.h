////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Header for problem 09 implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ADVENT_OF_CODE_PROBLEM_09_H
#define ADVENT_OF_CODE_PROBLEM_09_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Includes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem.h"

import aoc.math;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AoC
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Problem 09 concrete implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Problem09 : public Problem
{
enum EdgeOrientation
{
    Horizontal,
    Vertical
};

struct Edge
{
    Math::Point2D first;
    Math::Point2D second;
    EdgeOrientation orientation;

    Edge() : Edge({0, 0}, {0, 0})
    {
    }

    Edge(Math::Point2D const& node1, Math::Point2D const& node2)
    {
        std::vector<Math::Point2D> points = (node1 < node2) ? std::vector<Math::Point2D>{node1, node2} : std::vector<Math::Point2D>{node2, node1};
        first = points[0];
        second = points[1];

        if (first.x == second.x)
        {
            orientation = EdgeOrientation::Vertical;
        }
        else
        {
            orientation = EdgeOrientation::Horizontal;
        }
    }

    friend bool operator<(Edge const& lhs, Edge const& rhs)
    {
        if (lhs.first != rhs.first)
        {
            return lhs.first < rhs.first;
        }
        return lhs.second < rhs.second;
    }

    static bool intersects(Edge const& horizontal_edge, Edge const& vertical_edge, EdgeOrientation orientation_we_care_about)
    {
        Edge h = horizontal_edge;
        Edge v = vertical_edge;

        if (orientation_we_care_about == EdgeOrientation::Vertical)
        {
            h.first.x -= 1;
            h.second.x += 1;
        }
        else
        {
            v.first.y -= 1;
            v.second.y += 1;
        }
        bool horizontal_overlap = (h.first.x < v.first.x) && (h.second.x > v.second.x);
        bool vertical_overlap = (h.first.y > v.first.y) && (h.second.y < v.second.y);
        return horizontal_overlap && vertical_overlap;
    }
};

struct Rectangle
{
    Edge left;
    Edge right;
    Edge top;
    Edge bottom;
    std::uint64_t area;

    Rectangle() : Rectangle({{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}, {{0, 0}, {0, 0}})
    {
    }

    Rectangle(Edge const& left_edge, Edge const& right_edge, Edge const& top_edge, Edge const& bottom_edge)
        : left(left_edge)
        , right(right_edge)
        , top(top_edge)
        , bottom(bottom_edge)
    {
        std::uint64_t width = std::abs(left.first.x - right.first.x) + 1;
        std::uint64_t height = std::abs(top.first.y - bottom.first.y) + 1;
        area = width * height;
    }

    friend bool operator<(Rectangle const& lhs, Rectangle const& rhs)
    {
        if (lhs.area != rhs.area)
        {
            return lhs.area < rhs.area;
        }
        else
        {
            return lhs.left < rhs.left;
        }
    }
};
public:
    /**
     * @brief Constructor that passes and automatically loads file data
     * @param [in] input_data_path Path to this problem's data file
     */
    explicit Problem09(std::string_view input_data_path) : Problem(input_data_path, true)
    {}

    /**
     * @brief Loads the problem data into a problem-specific format
     * @return True if loading was successful, false otherwise
     */
     bool load_problem() override;

    /**
     * @brief Solves part 1 of day 09
     * @return Returns an Answer, or nullptr if no answer is computed yet
     */
    std::unique_ptr<Answer> solve_part_1() override;

    /**
     * @brief Solves part 2 of day 09
     * @return Returns an Answer, or nullptr if no answer is computed yet
     */
    std::unique_ptr<Answer> solve_part_2() override;

private:
    std::vector<Math::Point2D> m_tiles;
    std::vector<Edge> m_edges{};
    std::vector<Rectangle> m_rectangles{};
};

} // namespace AoC

#endif // ADVENT_OF_CODE_PROBLEM_09_H
