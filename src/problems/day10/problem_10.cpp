////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem_10.h"

#include <execution>
#include <queue>
#include <unordered_map>
import aoc.parse;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
bool Problem10::load_problem()
{
    for (auto const& line : get_lines())
    {
        JoltageMachine machine;
        auto split = AoC::Parse::split_line_by_token(line, " ");
        for (std::string_view const& section : split)
        {
            char brace = section[0];
            std::string_view data{ (section.begin() + 1), (section.end() - 1) };
            switch (brace)
            {
                case '[':
                {
                    for (int i = 0; i < data.size(); ++i)
                    {
                        if (data[i] == '.')
                        {
                            machine.target_indicator_lights[i] = 0;
                        }
                        else
                        {
                            machine.target_indicator_lights[i] = 1;
                        }
                    }
                    break;
                }
                case '(':
                {
                    auto toggles = AoC::Parse::split_line_by_token(data, ",");
                    Button button;
                    for (auto const &b: toggles)
                    {
                        int idx = AoC::Parse::sv_to_int<int>(b).value();
                        button.light_toggles[idx] = 1;
                    }
                    machine.buttons.push_back(button);
                    break;
                }
                case '{':
                {
                    auto joltages = AoC::Parse::split_line_by_token(data, ",");
                    for (auto const &j: joltages)
                    {
                        int idx = AoC::Parse::sv_to_int<int>(j).value();
                        machine.target_joltages.push_back(idx);
                    }
                    machine.current_joltages.resize(machine.target_joltages.size());
                    std::fill(machine.current_joltages.begin(), machine.current_joltages.end(), 0);
                    break;
                }
                default:
                    std::printf("Something went horribly wrong");
            }
        }
        m_machines.push_back(machine);
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem10::solve_part_1()
{
    std::atomic<std::uint64_t> min_operations{ 0 };
    std::for_each(std::execution::par, m_machines.cbegin(), m_machines.cend(), [this, &min_operations](JoltageMachine const& machine)
    {
        int depth = lights_bfs(machine);
        min_operations += depth;
    });

    return std::make_unique<BigNumericAnswer>(min_operations);
}

//----------------------------------------------------------------------------------------------------------------------
std::unique_ptr<Answer> Problem10::solve_part_2()
{
    std::atomic<int> completed{ 0 };
    std::atomic<std::uint64_t> min_operations{ 0 };

    std::for_each(m_machines.cbegin(), m_machines.cend(), [this, &min_operations, &completed](JoltageMachine const& machine)
    {
        int depth = joltages_bfs_bidirectional(machine);

        completed++;
        int completed_val = completed;
        std::printf("Calculated solution for %d out of %zd machines.\n", completed_val, m_machines.size());

        min_operations += depth;
    });

    return std::make_unique<BigNumericAnswer>(min_operations);
}

//----------------------------------------------------------------------------------------------------------------------
int Problem10::lights_bfs(const Problem10::JoltageMachine &machine) const
{
    std::queue<LightPanel> q;
    std::unordered_map<LightPanel, int, LightPanelHash> visited;

    q.push(machine.current_indicator_lights);
    visited[machine.current_indicator_lights] = 0;

    while (!q.empty())
    {
        LightPanel front = q.front();
        q.pop();

        if (front == machine.target_indicator_lights)
        {
            return visited[front];
        }

        int current_depth = visited[front];

        for (Button const& button : machine.buttons)
        {
            LightPanel new_indicator_lights = front ^ button.light_toggles;

            if (!visited.contains(new_indicator_lights))
            {
                q.push(new_indicator_lights);
                visited[new_indicator_lights] = current_depth + 1;
            }
        }
    }

    return -1;
}

//----------------------------------------------------------------------------------------------------------------------
int Problem10::joltages_bfs_bidirectional(const Problem10::JoltageMachine &machine) const
{
    std::queue<Joltages> q_start, q_target;
    std::unordered_map<Joltages , int, JoltageHash> from_start, from_target;

    q_start.push(machine.current_joltages);
    from_start[machine.current_joltages] = 0;

    q_target.push(machine.target_joltages);
    from_target[machine.target_joltages] = 0;

    while (!q_start.empty() || !q_target.empty())
    {
        // Expand from whichever side has fewer unexplored nodes
        if (! q_start.empty() && (q_target.empty() || q_start.size() <= q_target.size()))
        {
            Joltages front = q_start.front();
            q_start.pop();

            int current_depth = from_start[front];

            for (Button const& button : machine.buttons)
            {
                Joltages next{ front.begin(), front.end() };
                for (std::size_t i = 0; i < next.size(); ++i)
                {
                    next[i] += button.light_toggles[i];
                }

                // if we've met in the middle, sum the depths and return
                if (from_target.contains(next))
                {
                    return current_depth + 1 + from_target[next];
                }

                if (!from_start.contains(next))
                {
                    q_start.push(next);
                    from_start[next] = current_depth + 1;
                }
            }
        }
        else if (!q_target.empty())
        {
            Joltages front = q_target.front();
            q_target.pop();

            int current_depth = from_target[front];

            for (Button const& button : machine.buttons)
            {
                Joltages next{ front.begin(), front.end() };
                for (std::size_t i = 0; i < next.size(); ++i)
                {
                    next[i] -= button.light_toggles[i];
                }

                // if we've met in the middle, sum the depths and return
                if (from_start.contains(next))
                {
                    return current_depth + 1 + from_start[next];
                }

                if (!from_target.contains(next))
                {
                    q_target.push(next);
                    from_target[next] = current_depth + 1;
                }
            }
        }
    }

    return -1;
}

} // namespace AoC
