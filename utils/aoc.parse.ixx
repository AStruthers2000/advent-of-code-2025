////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Parsing utilities
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module;

#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

//----------------------------------------------------------------------------------------------------------------------
export module aoc.parse;

//----------------------------------------------------------------------------------------------------------------------
inline std::vector<std::string_view> split_sv(std::string_view str, std::string_view delim, bool keep_empty);

//----------------------------------------------------------------------------------------------------------------------
export namespace AoC::Parse
{

//----------------------------------------------------------------------------------------------------------------------
auto read_lines_from_file(std::string_view path) -> std::vector<std::string>
{
    std::ifstream in(std::string{path});
    std::vector<std::string> lines{};

    if (!in) return lines;

    std::string line;
    bool first = true;
    while (std::getline(in, line))
    {
        lines.push_back(std::move(line));
    }

    return lines;
}

//----------------------------------------------------------------------------------------------------------------------
auto split_line_by_token(std::string_view str, std::string_view token) -> std::vector<std::string_view>
{
    return split_sv(str, token, false);
}

//----------------------------------------------------------------------------------------------------------------------
auto split_lines(std::string_view input) -> std::vector<std::string_view>
{
    return split_sv(input, "\n", true);
}

//----------------------------------------------------------------------------------------------------------------------
template <typename T, typename = typename std::enable_if_t<std::is_integral_v<T>>>
auto sv_to_int(std::string_view sv) -> std::optional<T>
{
    auto first = sv.data();
    auto last = sv.data() + sv.size();

    T value{};
    if (sv.empty()) return std::nullopt;

    auto res = std::from_chars(first, last, value, 10);
    if (res.ec != std::errc{} || res.ptr != last) return std::nullopt;

    return value;
}

} // namespace AoC::Parse

//----------------------------------------------------------------------------------------------------------------------
inline std::vector<std::string_view> split_sv(std::string_view str, std::string_view delim, bool keep_empty)
{
    std::vector<std::string_view> out;
    if (delim.empty()) // ambiguous -> return the whole string as one token
    {
        if (!str.empty()) out.push_back(str);
        return out;
    }

    std::size_t pos = 0;
    while (pos <= str.size())
    {
        auto next = str.find(delim, pos);
        auto take_end = (next == std::string_view::npos) ? str.size() : next;
        auto token = std::string_view{str.data() + pos, take_end - pos};

        // if token is not empty, or if we want to keep emptys anyway, add token to output
        if (!token.empty() || keep_empty) out.push_back(token);
        if (next == std::string_view::npos) break;

        pos = next + delim.size();
    }

    return out;
}
