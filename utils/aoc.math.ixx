////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2025.
////////////////////////////////////////////////////////////////////////////////////////////////////

module;

#include <cmath>
#include <limits>
#include <optional>
#include <type_traits>

export module aoc.math;

export namespace AoC::Math
{

template <typename T, typename = typename std::enable_if_t <std::is_arithmetic_v<T>>>
T safe_divide(T numerator, T denominator, std::optional<T> tolerance = std::numeric_limits<T>::epsilon() * 2)
{
    if (abs(denominator) < tolerance)
    {
        return T{0};
    }
    else
    {
        return numerator / denominator;
    }
}

}