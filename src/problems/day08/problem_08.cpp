////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_08.h"

/* Specific includes/imports go here */
#include <algorithm>
#include <ranges>
#include <map>
#include <set>

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem08::load_problem()
{
    for (auto const& line : get_lines())
    {
        std::vector<std::string_view> split = AoC::Parse::split_line_by_token(line, ",");
        int x = AoC::Parse::sv_to_int<int>(split[0]).value();
        int y = AoC::Parse::sv_to_int<int>(split[1]).value();
        int z = AoC::Parse::sv_to_int<int>(split[2]).value();
        m_points.emplace_back(x, y, z);
    }

    std::sort(m_points.begin(), m_points.end());

    for (auto const [idx, point] : std::views::enumerate(m_points))
    {
        for (auto const [other_idx, other_point]: std::views::enumerate(m_points))
        {
            if (idx != other_idx)
            {
                Group group =
                        point < other_point ? std::make_pair(point, other_point) : std::make_pair(other_point, point);
                double dist = AoC::Math::euclidean_distance(point, other_point);
                m_distances.emplace(group, dist);
            }
        }
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem08::solve_part_1()
{
    std::vector<std::pair<Math::Point3D, int>> connections{};

    connect_groups(connections, m_num_connections);

    std::sort(connections.begin(), connections.end(), [](std::pair<Math::Point3D, int> const& lhs, std::pair<Math::Point3D, int> const& rhs)
    {
        if (lhs.second != rhs.second)
        {
            return lhs.second < rhs.second;
        }
        else
        {
            return lhs.first < rhs.first;
        }
    });

    std::map<int, std::uint64_t> group_counts;
    for (auto const& element : connections)
    {
        group_counts[element.second]++;
    }

    std::vector<int> counts;
    for (auto const& [key, value] : group_counts)
    {
        counts.push_back(value);
    }

    std::sort(counts.begin(), counts.end(), std::greater<int>());

    std::size_t group_1_size = counts[0];
    std::size_t group_2_size = counts[1];
    std::size_t group_3_size = counts[2];

    return std::make_unique<BigNumericAnswer>(group_1_size * group_2_size * group_3_size);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem08::solve_part_2()
{
    std::vector<std::pair<Math::Point3D, int>> connections{};
    Group last_action = connect_groups(connections);

    Math::Point3D last_left = last_action.first;
    Math::Point3D last_right = last_action.second;
    std::uint64_t length = last_left.x * last_right.x;

    return std::make_unique<BigNumericAnswer>(length);
}

//----------------------------------------------------------------------------------------------------------------------
std::pair<Math::Point3D, Math::Point3D>
Problem08::connect_groups(std::vector<std::pair<Math::Point3D, int>> &connections,
                          std::optional<std::size_t> early_stop_on_connection) const
{
    auto get_element = [&connections](Math::Point3D point) -> std::optional<std::pair<Math::Point3D, int>>
    {
        for (auto const& element : connections)
        {
            if (element.first == point)
                return element;
        }

        return std::nullopt;
    };

    std::pair<Math::Point3D, int> default_element = std::make_pair(Math::Point3D{0, 0, 0}, 0);

    int new_group_number{ 1 };
    Group last_action{};
    int elements_processed{ 0 };
    int nodes_added{ 0 };
    for (auto const& key : std::views::keys(m_distances))
    {
        Math::Point3D left = key.first;
        Math::Point3D right = key.second;

        auto left_optional = get_element(left);
        auto right_optional = get_element(right);
        bool contains_left = left_optional.has_value();
        bool contains_right = right_optional.has_value();
        bool contains_both = contains_left && contains_right;
        auto left_option = left_optional.value_or(default_element);
        auto right_option = right_optional.value_or(default_element);

        if (contains_both)
        {
            // elements are already in the same group
            if (left_option.second == right_option.second)
            {
                // do nothing
            }
            else
            {
                // move the right group to the left group
                for (auto& element : connections)
                {
                    if (element.second == right_option.second)
                    {
                        element.second = left_option.second;
                    }
                }
//                last_action = key;
            }
        }
        else if (contains_left)
        {
            connections.push_back(std::make_pair(right, left_option.second));
            last_action = key;
            ++nodes_added;
        }
        else if (contains_right)
        {
            connections.push_back(std::make_pair(left, right_option.second));
            last_action = key;
            ++nodes_added;
        }
        else
        {
            connections.push_back(std::make_pair(left, new_group_number));
            connections.push_back(std::make_pair(right, new_group_number));
            new_group_number++;
        }

        elements_processed++;
        if (early_stop_on_connection.has_value() && elements_processed >= early_stop_on_connection.value())
        {
            break;
        }
        else if (!early_stop_on_connection.has_value() &&
                 connections.size() == m_points.size() &&
                 std::all_of(connections.begin(), connections.end(), [&connections](auto const& element)
                 {
                    return element.second == connections.begin()->second;
                }))
        {
            break;
        }
    }

    return last_action;
}

} // namespace AoC
