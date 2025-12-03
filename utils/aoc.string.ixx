////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief String utilities
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module;

#include <algorithm>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

//----------------------------------------------------------------------------------------------------------------------
export module aoc.string;
import aoc.math;

//----------------------------------------------------------------------------------------------------------------------
export namespace AoC::String
{


//----------------------------------------------------------------------------------------------------------------------
auto split_string_into_even_parts(std::string_view candidate,
                                  std::size_t parts,
                                  std::optional<char> padding_character = std::nullopt) -> std::optional<std::vector<std::string>>
{
    std::size_t const candidate_size{ candidate.size() };
    if (candidate_size % parts == 0)
    {
        std::size_t length = candidate_size / parts;
        std::vector<std::string> split{};

        for (std::size_t i = 0; i < candidate_size; i += length)
        {
            std::string_view sub = candidate.substr(i, length);
            split.emplace_back(sub);
        }

        return split;
    }
    else
    {
        if (padding_character == std::nullopt)
        {
            return std::nullopt;
        }
        else
        {
            auto pad_required = Math::round_up_to_nearest_multiple<std::size_t>(candidate_size, parts);
            std::string pad(pad_required, padding_character.value());

            std::string padded_candidate = std::string(candidate) + pad;

            return split_string_into_even_parts(padded_candidate, parts);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
auto are_strings_equal(std::vector<std::string> const& strings) -> bool
{
    if (strings.empty()) return false;

    bool equal{ true };
    std::string_view first{ strings[0] };
    std::ranges::for_each(strings, [&equal, &first](std::string_view str)
    {
        if (first.compare(str) != 0)
        {
            equal = false;
        }
    });

    return equal;
}

} // namespace AoC::String
