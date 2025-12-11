////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Header for problem 10 implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ADVENT_OF_CODE_PROBLEM_10_H
#define ADVENT_OF_CODE_PROBLEM_10_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Includes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem.h"

#include <bitset>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AoC
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Problem 10 concrete implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Problem10 : public Problem
{
using LightPanel = std::bitset<16>;
struct LightPanelHash
{
    std::size_t operator()(LightPanel const& panel) const noexcept
    {
        return std::hash<unsigned long>{}(panel.to_ulong());
    }
};

using Joltages = std::vector<int>;
struct JoltageHash {
    size_t operator()(std::vector<int> const& vec) const {
        size_t seed = 0;
        for (const auto& val : vec) {
            seed ^= std::hash<int>{}(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

struct Button
{
    LightPanel light_toggles{};
};

struct JoltageMachine
{
    LightPanel target_indicator_lights{};
    LightPanel current_indicator_lights{};
    std::vector<Button> buttons{};
    Joltages target_joltages{};
    Joltages current_joltages{};
};

public:
    /**
     * @brief Constructor that passes and automatically loads file data
     * @param [in] input_data_path Path to this problem's data file
     */
    explicit Problem10(std::string_view input_data_path) : Problem(input_data_path)
    {}

    /**
     * @brief Loads the problem data into a problem-specific format
     * @return True if loading was successful, false otherwise
     */
     bool load_problem() override;

    /**
     * @brief Solves part 1 of day 10
     * @return Returns an Answer, or nullptr if no answer is computed yet
     */
    std::unique_ptr<Answer> solve_part_1() override;

    /**
     * @brief Solves part 2 of day 10
     * @return Returns an Answer, or nullptr if no answer is computed yet
     */
    std::unique_ptr<Answer> solve_part_2() override;

private:
    std::vector<JoltageMachine> m_machines{};

    int lights_bfs(JoltageMachine const& machine) const;
    int joltages_bfs_bidirectional(JoltageMachine const& machine) const;
};

} // namespace AoC

#endif // ADVENT_OF_CODE_PROBLEM_10_H
