////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Solver that encapsulates the process of solving a Problem
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ADVENT_OF_CODE_SOLVER_H
#define ADVENT_OF_CODE_SOLVER_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Includes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "problem.h"

#include <array>
#include <functional>
#include <memory>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AoC
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Enum representing each day of problems this year
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class Day : std::uint8_t
{
    DAY_01 = 0,
    DAY_02,
    DAY_03,
    DAY_04,
    DAY_05,
    DAY_06,
    DAY_07,
    DAY_08,
    DAY_09,
    DAY_10,
    DAY_11,
    DAY_12,
    NUM_DAYS /// @brief placeholder for automatically gathering number of days. Not a valid Day
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Singleton Solver class that owns all Problem instances
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Solver
{
public:
    /**
     * @brief Gets Solver singleton instance
     * @return The static instance of Solver
     */
    static Solver &instance();

    /**
     * @brief Solves all problems in the m_problems array
     */
    void solve_all_problems();

    /**
     * @brief Solves an individual problem specified by the day parameter
     * @param [in] day The problem associated with this day will be solved individually
     */
    void solve_problem(Day day);

    Solver(const Solver &) = delete;
    Solver(Solver &&) = delete;
    Solver &operator=(const Solver) = delete;
    Solver &operator=(Solver &&) = delete;

private:
    /**
     * @brief Constructs each of the problems in the m_problems array
     */
    Solver();

    /**
     * @brief Default destructor (smart pointers are automatically released)
     */
    ~Solver() = default;

    /**
     * @brief Prints out problem solutions and timing statistics in a nice format
     * @param [in] day The human-readable day number (not the index into the m_problems array)
     * @param [in] part_1_answer The answer to this problem's first part
     * @param [in] part_2_answer The answer to this problem's second part
     * @param [in] load_time The time it took for this problem to load its data
     * @param [in] part_1_time The time it took for this problem to solve part 1
     * @param [in] part_2_time The time it took for this problem to solve part 2
     */
    void print_problem_answers(std::uint8_t day,
                               std::optional<Answer*> part_1_answer,
                               std::optional<Answer*> part_2_answer,
                               double load_time,
                               double part_1_time,
                               double part_2_time);

    /**
     * @brief Generic wrapper for timing another function call
     * @tparam T Timed function return type. The std::function passed to this function must have the same return type
     * @param [in] func A std::function to be timed
     * @return A pair containing the timed function return value, and the time in seconds that the provided function
     *         took to run
     */
    template<typename T>
    std::pair<T, double> time_function_call(std::function<T()> func);

    /// @brief Number of days in the Day enum class as a constexpr
    static constexpr std::size_t NUM_DAYS = static_cast<std::size_t>(Day::NUM_DAYS);

    /// @brief Array holding each problem. Day::DAY_01 maps to index 0
    std::array<std::unique_ptr<Problem>, NUM_DAYS> m_problems{};
};

}

#endif //ADVENT_OF_CODE_SOLVER_H
