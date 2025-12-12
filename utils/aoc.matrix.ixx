////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Matrix utilities
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module;

#include <cmath>
#include <optional>
#include <stdexcept>
#include <vector>

//----------------------------------------------------------------------------------------------------------------------
export module aoc.matrix;

//----------------------------------------------------------------------------------------------------------------------
export namespace AoC::Matrix
{

/**
 * @brief Performs Gaussian elimination with partial pivoting and back substitution to solve a system of linear
 *        equations.
 *
 * @param augmented_matrix The augmented matrix [A|b] where Ax = b. Modified in-place to row echelon form.
 * @param epsilon Tolerance for floating-point comparisons (default: 1e-10)
 * @return std::optional<std::vector<double>> Solution vector if system is solvable, std::nullopt if system is singular
 *         or inconsistent.
 */
[[nodiscard]] auto gaussian_elimination(std::vector<std::vector<double>>& augmented_matrix, double epsilon = 1e-10) -> std::optional<std::vector<double>>
{
    if (augmented_matrix.empty())
        return std::nullopt;

    auto const num_rows = augmented_matrix.size();
    auto const num_cols = augmented_matrix[0].size();

    // needs at least one coefficient column and one target column
    if (num_cols < 2)
        return std::nullopt;

    auto const num_variables = num_cols - 1;

    // verify dimensions are consistent
    for (auto const& row : augmented_matrix)
    {
        if (row.size() != num_cols)
            return std::nullopt;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Part 1: Forward Elimination (Row Echelon Form)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for (std::size_t pivot_row = 0; pivot_row < num_rows && pivot_row < num_variables; ++pivot_row)
    {
        // partial pivoting: finds row with greatest absolute value in current column
        std::size_t max_row = pivot_row;
        double max_val = std::abs(augmented_matrix[pivot_row][pivot_row]);

        for (std::size_t row = pivot_row + 1; row < num_rows; ++row)
        {
            if (double const val = std::abs(augmented_matrix[row][pivot_row]); val > max_val)
            {
                max_val = val;
                max_row = row;
            }
        }

        // check for singular matrix
        if (max_val < epsilon)
        {
            continue; // skip this column for now
        }

        // swap rows if necessary
        if (max_row != pivot_row)
        {
            std::swap(augmented_matrix[pivot_row], augmented_matrix[max_row]);
        }

        // eliminate entries below the pivot
        double const pivot_val = augmented_matrix[pivot_row][pivot_row];

        for (std::size_t row = pivot_row + 1; row < num_rows; ++row)
        {
            double const factor = augmented_matrix[row][pivot_row] / pivot_val;

            // subtract factor * pivot_row from current row
            augmented_matrix[row][pivot_row] = 0.0;
            for (std::size_t col = pivot_row + 1; col < num_cols; ++col)
            {
                augmented_matrix[row][col] -= factor * augmented_matrix[pivot_row][col];
            }
        }
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Part 2: Check for inconsistency
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // a row like [0 0 0 ... | non-zero] indicates no solution
    for (std::size_t row = num_variables; row < num_rows; ++row)
    {
        if (std::abs(augmented_matrix[row][num_cols - 1]) > epsilon)
        {
            return std::nullopt;
        }
    }

    // check for rows that are all zeros except the augmented column
    for (std::size_t row = 0; row < std::min(num_rows, num_variables); ++row)
    {
        bool all_coefficients_zero{ true };
        for (std::size_t col = 0; col < num_variables; ++col)
        {
            if (std::abs(augmented_matrix[row][col]) > epsilon)
            {
                all_coefficients_zero = false;
                break;
            }
        }

        if (all_coefficients_zero && std::abs(augmented_matrix[row][num_cols - 1]) > epsilon)
        {
            return std::nullopt; // inconsistent matrix
        }
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Part 3: Back substitution
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::vector<double> solution(num_variables, 0.0);

    for (std::size_t i = num_variables; i-- > 0;)
    {
        if (i >= num_rows)
        {
            // more variables than equations means that this is underdetermined
            continue;
        }

        // check if this pivot is valid
        if (std::abs(augmented_matrix[i][i]) < epsilon)
        {
            // this variable is free; also means that this is underdetermined. in the context of ILP, this typically
            // means no unique solution exists
//            return std::nullopt;
            continue;
        }

        double sum = augmented_matrix[i][num_cols - 1];

        for (std::size_t j = i + 1; j < num_variables; ++j)
        {
            sum -= augmented_matrix[i][j] * solution[j];
        }

        solution[i] = sum / augmented_matrix[i][i];
    }

    return solution;
}

/**
 * @brief Validates that a solution satisfies the original system within tolerance.
 *
 * @param original_matrix The original augmented matrix (unmodified).
 * @param solution The proposed solution vector.
 * @param epsilon Tolerance for validation (default: 1e-9)
 * @return true if solution is valid, false otherwise.
 */
[[nodiscard]] auto validate_solution(std::vector<std::vector<double>> const& original_matrix, std::vector<double> const& solution, double epsilon = 1e-9) -> bool
{
    if (original_matrix.empty())
        return false;

    auto const num_cols = original_matrix[0].size();

    if (solution.size() != num_cols - 1)
        return false;

    for (auto const& row : original_matrix)
    {
        if (row.size() != num_cols)
            return false;

        double computed = 0.0;
        for (std::size_t col = 0; col < solution.size(); ++col)
        {
            computed += row[col] * solution[col];
        }

        double const target = row[num_cols - 1];

        if (std::abs(computed - target) > epsilon)
        {
            return false;
        }
    }

    return true;
}

[[nodiscard]] auto round_to_integer_solution(std::vector<double> const& solution, std::vector<std::vector<double>> const& original_matrix, double epsilon = 1e-9) -> std::optional<std::vector<long long>>
{
    std::vector<long long> int_solution;
    int_solution.reserve(solution.size());

    for (double const val : solution)
    {
        double const rounded = std::round(val);

        // check if value is close enough to an integer
        if (std::abs(val - rounded) > epsilon)
        {
            return std::nullopt; // not an integer solution
        }

        int_solution.push_back(static_cast<long long>(rounded));
    }

    // validate the integer solution against the original system
    std::vector<double> double_solution(int_solution.begin(), int_solution.end());

    if (!validate_solution(original_matrix, double_solution, epsilon))
    {
        return std::nullopt;
    }

    return int_solution;
}

}