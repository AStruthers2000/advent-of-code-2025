////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_11.h"

#include <queue>
import aoc.parse;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem11::load_problem()
{
    for (auto const& line : get_lines())
    {
        std::string node_name{line.begin(), line.begin() + 3};
        auto neighbors = AoC::Parse::split_line_by_token({line.begin() + 5, line.end()}, " ");

        auto& node = m_nodes.try_emplace(node_name, Node{}).first->second;
        for (auto const& neighbor : neighbors)
        {
            node.neighbors.push_back(std::string(neighbor));
            m_nodes.try_emplace(std::string(neighbor), Node{});
        }
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem11::solve_part_1()
{
    int count = device_bfs("you", "out");

    return std::make_unique<BigNumericAnswer>(count);
    return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem11::solve_part_2()
{
    m_path_cache.clear();
    std::uint64_t count1 = static_cast<std::uint64_t>(device_dfs("svr", "fft"));

    m_path_cache.clear();
    std::uint64_t count2 = static_cast<std::uint64_t>(device_dfs("fft", "dac"));

    m_path_cache.clear();
    std::uint64_t count3 = static_cast<std::uint64_t>(device_dfs("dac", "out"));

    std::uint64_t paths = count1 * count2 * count3;
    return std::make_unique<BigNumericAnswer>(paths);
}

//----------------------------------------------------------------------------------------------------------------------
int Problem11::device_bfs(std::string_view start, std::string_view target) const
{
    std::queue<std::string> q;
    q.push(std::string(start));

    int out_counts{ 0 };
    while (!q.empty())
    {
        std::string front = q.front();
        q.pop();

        auto node_it = m_nodes.find(front);
        if (node_it == m_nodes.end())
        {
            continue;
        }

        for (std::string const& neighbor : node_it->second.neighbors)
        {
            if (neighbor == target)
            {
                out_counts++;
            }
            else
            {
                q.push(neighbor);
            }
        }
    }

    return out_counts;
}

//----------------------------------------------------------------------------------------------------------------------
int Problem11::device_dfs(std::string_view current, std::string_view target) const
{
    // base case
    if (target == current)
    {
        return 1;
    }

    // check cache
    auto cache_it = m_path_cache.find(std::string(current));
    if (cache_it != m_path_cache.end())
    {
        return cache_it->second;
    }

    // find current node
    auto node_it = m_nodes.find(std::string(current));
    if (node_it == m_nodes.end())
    {
        return 0;
    }

    // sum paths through all neighbors
    int total_paths = 0;
    for (auto const& neighbor : node_it->second.neighbors)
    {
        total_paths += device_dfs(neighbor, target);
    }

    m_path_cache[std::string(current)] = total_paths;
    return total_paths;
}

} // namespace AoC
