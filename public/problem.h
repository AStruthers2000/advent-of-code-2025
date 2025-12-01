////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Abstract Problem class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ADVENT_OF_CODE_PROBLEM_H
#define ADVENT_OF_CODE_PROBLEM_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Includes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "answer.h"

#include <memory>
#include <string>
#include <string_view>
#include <optional>
#include <vector>

import aoc.parse;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AoC
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Abstract Problem
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Problem
{
public:
    /**
     * @brief Constructor that automatically loads the given file into a vector of strings
     * @param [in] filepath Path to the given input file. Paths can be relative, but they'll be relative to the exe
     *                      location, not the current project structure
     */
    Problem(std::string_view filepath, bool strip_empty = false)
    {
        auto lines = AoC::Parse::read_lines_from_file(filepath);
        if (lines.empty())
        {
            std::printf("Reading input file: %s resulted in empty vector of lines.\n", std::string(filepath).c_str());
        }

        if (strip_empty)
        {
            for (auto const& line : lines)
            {
                if (!line.empty())
                {
                    m_lines.push_back(line);
                }
            }
        }
        else
        {
            m_lines = lines;
        }
    }
    virtual ~Problem() = default;

    /**
     * @brief Virtual method implemented by concrete classes for special parsing/handling of the input data
     * @return Concrete implementations should return true if loading was successful, false otherwise
     */
    virtual bool load_problem() = 0;

    /**
     * @brief Virtual method implemented by concrete classes for solving the first part of the problem
     * @return An AoC::Answer if the solution is implemented, std::nullopt otherwise
     */
    virtual std::unique_ptr<Answer> solve_part_1() = 0;

    /**
     * @brief Virtual method implemented by concrete classes for solving the second part of the problem
     * @return An AoC::Answer if the solution is implemented, std::nullopt otherwise
     */
    virtual std::unique_ptr<Answer> solve_part_2() = 0;

protected:
    /**
     * @brief Gets all of the lines in the input gathered during object construction
     * @return A vector of string_views, where each element is one line from the input file
     */
    std::vector<std::string_view> get_lines()
    {
        std::vector<std::string_view> lines(m_lines.begin(), m_lines.end());
        return lines;
    }

private:
    /// @brief The owning container of each of the lines from the input file
    std::vector<std::string> m_lines{};
};

}

#endif //ADVENT_OF_CODE_PROBLEM_H
