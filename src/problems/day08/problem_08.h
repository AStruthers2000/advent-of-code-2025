////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Header for problem 08 implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ADVENT_OF_CODE_PROBLEM_08_H
#define ADVENT_OF_CODE_PROBLEM_08_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Includes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem.h"

#include <map>
import aoc.math;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AoC
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Problem 08 concrete implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Problem08 : public Problem
{

public:
    /**
     * @brief Constructor that passes and automatically loads file data
     * @param [in] input_data_path Path to this problem's data file
     */
    explicit Problem08(std::string_view input_data_path) : Problem(input_data_path, true)
    {}

    /**
     * @brief Loads the problem data into a problem-specific format
     * @return True if loading was successful, false otherwise
     */
     bool load_problem() override;

    /**
     * @brief Solves part 1 of day 08
     * @return Returns an Answer, or nullptr if no answer is computed yet
     */
    std::unique_ptr<Answer> solve_part_1() override;

    /**
     * @brief Solves part 2 of day 08
     * @return Returns an Answer, or nullptr if no answer is computed yet
     */
    std::unique_ptr<Answer> solve_part_2() override;

    void set_num_connections(std::size_t new_connections)
    {
        m_num_connections = new_connections;
    }

private:
    std::vector<AoC::Math::Point3D> m_points{};

    using Group = std::pair<Math::Point3D, Math::Point3D>;
    struct GroupCmp
    {
        bool operator()(Group const& left, Group const& right) const
        {
            double left_dist = AoC::Math::euclidean_distance(left.first, left.second);
            double right_dist = AoC::Math::euclidean_distance(right.first, right.second);

            return left_dist < right_dist;
        }
    };
    std::map<Group, double, GroupCmp> m_distances;

    Group connect_groups(std::vector<std::pair<Math::Point3D, int>>& connections, std::optional<std::size_t> early_stop_on_connection = std::nullopt) const;

    static inline std::size_t m_num_connections{ 1000 };
};

} // namespace AoC

#endif // ADVENT_OF_CODE_PROBLEM_08_H
