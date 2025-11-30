////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "solver.h"
#include "problems/day01/problem_01.h"
#include "problems/day02/problem_02.h"
#include "problems/day03/problem_03.h"
#include "problems/day04/problem_04.h"
#include "problems/day05/problem_05.h"
#include "problems/day06/problem_06.h"
#include "problems/day07/problem_07.h"
#include "problems/day08/problem_08.h"
#include "problems/day09/problem_09.h"
#include "problems/day10/problem_10.h"
#include "problems/day11/problem_11.h"
#include "problems/day12/problem_12.h"

#include <chrono>
#include <format>
#include <optional>
#include <print>

import aoc.math;

//----------------------------------------------------------------------------------------------------------------------
namespace AoC
{

//----------------------------------------------------------------------------------------------------------------------
Solver::Solver()
{
    m_problems[0] = std::make_unique<Problem_01>("../src/problems/day01/input.txt");
    m_problems[1] = std::make_unique<Problem_02>("../src/problems/day02/input.txt");
    m_problems[2] = std::make_unique<Problem_03>("../src/problems/day03/input.txt");
    m_problems[3] = std::make_unique<Problem_04>("../src/problems/day04/input.txt");
    m_problems[4] = std::make_unique<Problem_05>("../src/problems/day05/input.txt");
    m_problems[5] = std::make_unique<Problem_06>("../src/problems/day06/input.txt");
    m_problems[6] = std::make_unique<Problem_07>("../src/problems/day07/input.txt");
    m_problems[7] = std::make_unique<Problem_08>("../src/problems/day08/input.txt");
    m_problems[8] = std::make_unique<Problem_09>("../src/problems/day09/input.txt");
    m_problems[9] = std::make_unique<Problem_10>("../src/problems/day10/input.txt");
    m_problems[10] = std::make_unique<Problem_11>("../src/problems/day11/input.txt");
    m_problems[11] = std::make_unique<Problem_12>("../src/problems/day12/input.txt");
}

//----------------------------------------------------------------------------------------------------------------------
Solver& Solver::instance()
{
    static Solver inst;
    return inst;
}

//----------------------------------------------------------------------------------------------------------------------
void Solver::solve_all_problems()
{
    for(std::size_t i = 0; i < m_problems.size(); ++i)
    {
        solve_problem(static_cast<Day>(i));
    }
}

//----------------------------------------------------------------------------------------------------------------------
void Solver::solve_problem(Day day)
{
    std::uint8_t day_index = static_cast<std::uint8_t>(day);
    std::uint8_t day_num = day_index + 1;

    // std::printf("Solving problem %d\n", day_num);

    // take ownership of the unique pointer from the array
    std::unique_ptr<Problem> problem = std::move(m_problems[day_index]);

    auto [load_success, load_time] = time_function_call<bool>([&]() {
        return problem->load_problem();
    });
    auto [part_1_answer, part_1_time] = time_function_call<std::unique_ptr<Answer>>([&]() {
        return problem->solve_part_1();
    });
    auto [part_2_answer, part_2_time] = time_function_call<std::unique_ptr<Answer>>([&]() {
        return problem->solve_part_2();
    });

    // return ownership of the unique pointer back to the array
    m_problems[day_index] = std::move(problem);

    // print status
    std::optional<Answer*> p1_answer = part_1_answer ? std::make_optional(part_1_answer.get()) : std::nullopt;
    std::optional<Answer*> p2_answer = part_2_answer ? std::make_optional(part_2_answer.get()) : std::nullopt;
    print_problem_answers(day_num, p1_answer, p2_answer, load_time, part_1_time, part_2_time);
}

//----------------------------------------------------------------------------------------------------------------------
void Solver::print_problem_answers(std::uint8_t day, std::optional<Answer*> part_1_answer, std::optional<Answer*> part_2_answer, double load_time, double part_1_time, double part_2_time)
{
    double total_time = load_time + part_1_time + part_2_time;

    std::unique_ptr<Answer> null_answer = std::make_unique<NumericAnswer>(0);

    std::println("//==============================================\\\\");
    std::println("||  Problem {:02d} \t\t|  Answer\t\t||", day);
    std::println("||----------------------+-----------------------||");
    std::println("||  Part 1        \t|  {:<20} ||", part_1_answer.value_or(null_answer.get())->to_string());
    std::println("||  Part 2        \t|  {:<20} ||", part_2_answer.value_or(null_answer.get())->to_string());
    std::println("\\\\==============================================//\n");

    std::println("//======================================================================\\\\");
    std::println("||  Stage\t\t|  Runtime (seconds)\t|  Percent of runtime   ||");
    std::println("||----------------------+-----------------------+-----------------------||");
    std::print("||  Loading/parsing\t|  {:011.9f}\t\t|  {:06.3f}%\t\t||\n", load_time, (AoC::Math::safe_divide<double>(load_time, total_time)) * 100.0);
    std::print("||  Part 1         \t|  {:011.9f}\t\t|  {:06.3f}%\t\t||\n", part_1_time, (AoC::Math::safe_divide<double>(part_1_time, total_time)) * 100.0);
    std::print("||  Part 2         \t|  {:011.9f}\t\t|  {:06.3f}%\t\t||\n", part_2_time, (AoC::Math::safe_divide<double>(part_2_time, total_time)) * 100.0);
    std::println("||----------------------+-----------------------+-----------------------||");
    std::println("||  Total time     \t|  {:011.9f}\t\t|=======================||", total_time);
    std::println("\\\\======================================================================//");
}

//----------------------------------------------------------------------------------------------------------------------
template<typename T>
std::pair<T, double> Solver::time_function_call(std::function<T()> func)
{
    auto start = std::chrono::high_resolution_clock::now();
    T ret = func();
    auto end = std::chrono::high_resolution_clock::now();

    auto time_count = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    auto time = static_cast<double>(time_count) / 1e+6;

    return std::make_pair(std::move(ret), time);
}

} // namespace AoC
