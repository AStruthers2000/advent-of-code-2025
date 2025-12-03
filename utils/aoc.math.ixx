////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Math utilities
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module;

#include <cmath>
#include <limits>
#include <optional>
#include <type_traits>

//----------------------------------------------------------------------------------------------------------------------
export module aoc.math;

//----------------------------------------------------------------------------------------------------------------------
export namespace AoC::Math
{

//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
template <typename T, typename = typename std::enable_if_t <std::is_arithmetic_v<T>>>
bool is_same_sign(T left, T right)
{
    if ((left < 0 && right < 0) || (left > 0 && right > 0))
    {
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------
template <typename T, typename = typename std::enable_if_t <std::is_arithmetic_v<T>>>
int clamp_with_wrap(T value, T lower, T upper, T& out_value)
{
    T current{ value };
    T range{ (upper - lower) + 1 };
    int wrap_count{ 0 };

    while (current < lower)
    {
        ++wrap_count;
        current += range;
    }

    while (current > upper)
    {
        ++wrap_count;
        current -= range;
    }

    out_value = current;
    return wrap_count;
}

//----------------------------------------------------------------------------------------------------------------------
template <typename T, typename = typename std::enable_if_t <std::is_arithmetic_v<T>>>
auto round_up_to_nearest_multiple(T value, T multiple) -> T
{
    T remainder = value % multiple;
    T difference = multiple - remainder;

    return T{ value + difference };
}

} // namespace AoC::Math