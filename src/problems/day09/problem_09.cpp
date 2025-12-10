////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_09.h"

#include <algorithm>
#include <ranges>
#include <set>

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem09::load_problem()
{
    for (auto const& line : get_lines())
    {
        std::vector<std::string_view> split = AoC::Parse::split_line_by_token(line, ",");
        int x = AoC::Parse::sv_to_int<int>(split[0]).value();
        int y = AoC::Parse::sv_to_int<int>(split[1]).value();
        m_tiles.emplace_back(x, y);
    }

    std::set<Edge> edges{};
    for (std::size_t i = 0; i < m_tiles.size(); ++i)
    {
        std::size_t idx = i;
        std::size_t other_idx = i + 1;
        if (other_idx >= m_tiles.size())
        {
            other_idx = 0;
        }
        Math::Point2D point1 = m_tiles[idx];
        Math::Point2D point2 = m_tiles[other_idx];

        Edge edge{point1, point2};
        edges.insert(edge);
    }

    std::set<Rectangle> rectangles{};
    for (auto const [idx, point] : std::views::enumerate(m_tiles))
    {
        for (auto const [other_idx, other_point] : std::views::enumerate(m_tiles))
        {
            if (idx != other_idx)
            {
                int min_x = std::min({point.x, other_point.x});
                int min_y = std::min({point.y, other_point.y});
                int max_x = std::max({point.x, other_point.x});
                int max_y = std::max({point.y, other_point.y});

                Math::Point2D top_left{min_x, min_y};
                Math::Point2D top_right{max_x, min_y};
                Math::Point2D bottom_left{min_x, max_y};
                Math::Point2D bottom_right{max_x, max_y};

                Rectangle rect{
                        Edge{top_left, bottom_left},     // left edge
                        Edge{top_right, bottom_right},   // right edge
                        Edge{top_left, top_right},       // top edge
                        Edge{bottom_left, bottom_right}, // bottom edge
                };

                rectangles.insert(rect);
            }
        }
    }

    m_edges.resize(edges.size());
    m_rectangles.resize(rectangles.size());

    std::copy(edges.begin(), edges.end(), m_edges.begin());
    std::copy(rectangles.begin(), rectangles.end(), m_rectangles.begin());

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem09::solve_part_1()
{
//    auto calc_area = [](Math::Point2D const& corner1, Math::Point2D const& corner2) -> std::uint64_t
//    {
//        std::uint64_t width = abs(corner1.x - corner2.x) + 1;
//        std::uint64_t height = abs(corner1.y - corner2.y) + 1;
//
//        return width * height;
//    };

    std::uint64_t max_area{ m_rectangles.rbegin()->area };
//    for (auto const [idx, point] : std::views::enumerate(m_tiles))
//    {
//        for (auto const [other_idx, other_point] : std::views::enumerate(m_tiles))
//        {
//            if (idx != other_idx)
//            {
//                std::uint64_t area = calc_area(point, other_point);
//                if (area > max_area)
//                {
//                    max_area = area;
//                }
//            }
//        }
//    }

    return std::make_unique<BigNumericAnswer>(max_area);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem09::solve_part_2()
{

    auto edge_has_any_intersections = [this](Edge const& edge) -> bool
    {
        bool any_intersections = false;

        for (auto const& border : m_edges)
        {
            if (border.orientation != edge.orientation)
            {
                Edge horizontal = edge.orientation == EdgeOrientation::Horizontal ? edge : border;
                Edge vertical = edge.orientation == EdgeOrientation::Vertical ? edge : border;

                any_intersections = Edge::intersects(horizontal, vertical, edge.orientation);
                if (any_intersections)
                {
                    break;
                }
            }
        }

        return any_intersections;
    };

    std::uint64_t max_area{ 0 };
    Rectangle max_rectangle{};
    for (auto it = m_rectangles.rbegin(); it != m_rectangles.rend(); it = std::next(it))
    {
        Rectangle const &rectangle = *it;
        if (rectangle.area > max_area)
        {
            bool left_has_intersection = edge_has_any_intersections(rectangle.left);
            bool right_has_intersection = edge_has_any_intersections(rectangle.right);
            bool top_has_intersection = edge_has_any_intersections(rectangle.top);
            bool bottom_has_intersection = edge_has_any_intersections(rectangle.bottom);

            bool any_intersection = left_has_intersection ||
                                    right_has_intersection ||
                                    top_has_intersection ||
                                    bottom_has_intersection;
            if (!any_intersection)
            {
                max_area = rectangle.area;
                max_rectangle = rectangle;
            }
        }
    }

    return std::make_unique<BigNumericAnswer>(max_area);
}

} // namespace AoC
