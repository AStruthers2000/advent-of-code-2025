module;

#include <span>
#include <string>
#include <string_view>
#include <vector>

export module aoc.parse;

import :impl;

export namespace AoC::Parse
{

    auto read_lines(std::string_view path) -> std::vector<std::string>;
    auto split_line_by_token(std::string_view str, std::string_view token) -> std::vector<std::string_view>;
    auto split_lines(std::string_view input) -> std::vector<std::string_view>;

//    template <typename T = char>
//    auto parse_grid(std::span<std::string_view const> lines) -> AoC::Types::Grid<T>;

} // namespace AoC::Parse
