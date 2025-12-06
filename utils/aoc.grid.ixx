////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2025 AStruthers2000 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Grid utilities
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
module;

#include <algorithm>
#include <cstdint>
#include <functional>
#include <set>
#include <string_view>
#include <utility>
#include <vector>


//----------------------------------------------------------------------------------------------------------------------
export module aoc.grid;

//----------------------------------------------------------------------------------------------------------------------
export namespace AoC::Grid
{

//----------------------------------------------------------------------------------------------------------------------
enum class GridDirection : std::uint8_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
};

//----------------------------------------------------------------------------------------------------------------------
struct GridPosition
{
    int row = 0;
    int column = 0;

    friend bool operator<(GridPosition const& lhs, GridPosition const& rhs)
    {
        auto l = std::tie(lhs.row, lhs.column);
        auto r = std::tie(rhs.row, rhs.column);

        return l < r;
    }
};

//----------------------------------------------------------------------------------------------------------------------
template <class GridType>
class Grid2D
{
public:
    /**
     *
     */
    Grid2D() : Grid2D(0)
    {}

    /**
     *
     * @param size
     */
    explicit Grid2D(int size) : Grid2D(size, size)
    {}

    /**
     *
     * @param rows
     * @param cols
     */
    Grid2D(int rows, int cols) : Grid2D(rows, cols, GridType{})
    {}

    /**
     *
     * @param rows
     * @param cols
     * @param default_val
     */
    Grid2D(int rows, int cols, GridType default_val)
    {
        m_grid.resize(rows);
        for (auto &row: m_grid)
        {
            row.resize(cols);
            std::fill(row.begin(), row.end(), default_val);
        }
    }

    /**
     *
     * @param lines
     */
    explicit Grid2D(const std::vector<std::string_view>& lines) : Grid2D(lines, [](char element) { return static_cast<GridType>(element); })
    {}

    /**
     *
     * @param lines
     * @param translation_function
     */
    Grid2D(std::vector<std::string_view> const& lines, std::function<GridType(char)> translation_function)
    {
        std::size_t rows = lines.size();
        m_grid.resize(rows);
        for (std::size_t i = 0; i < rows; ++i)
        {
            std::size_t cols = lines[i].size();
            m_grid[i].resize(cols);
            for (std::size_t j = 0; j < cols; ++j)
            {
                m_grid[i][j] = translation_function(lines[i][j]);
            }
        }
    }

    explicit Grid2D(std::vector<std::vector<GridType>> const& defaults)
    {
        m_grid = std::move(defaults);
    }

    void for_each_element(std::function<void(GridType&, GridPosition)> process_element)
    {
        for (std::size_t row = 0; row < m_grid.size(); ++row)
        {
            for (std::size_t col = 0; col < m_grid[row].size(); ++col)
            {
                process_element(m_grid[row][col], GridPosition{static_cast<int>(row), static_cast<int>(col)});
            }
        }
    }

    void for_each_element(std::function<void(GridType const&, GridPosition)> process_element) const
    {
        for_each_element(process_element);
    }
    /**
     *
     * @param position
     * @param include_diagonals
     * @return
     */
    std::set<std::tuple<GridType, GridPosition, GridDirection>> get_neighbors(GridPosition position, bool include_diagonals) const
    {
        auto [row, col] = position;

        if (row < 0 || row >= m_grid.size())
        {
            if (col < 0 || col >= m_grid[row].size())
            {
                return {};
            }
        }

        std::vector<std::pair<GridPosition, GridDirection>> neighbor_offsets = {
                {{-1, 0},  GridDirection::UP},
                {{1,  0},  GridDirection::DOWN},
                {{0,  -1}, GridDirection::LEFT},
                {{0,  1},  GridDirection::RIGHT},
        };
        if (include_diagonals)
        {
            neighbor_offsets.push_back({{-1, -1}, GridDirection::UP_LEFT});
            neighbor_offsets.push_back({{-1,  1}, GridDirection::UP_RIGHT});
            neighbor_offsets.push_back({{1,  -1}, GridDirection::DOWN_LEFT});
            neighbor_offsets.push_back({{1,   1}, GridDirection::DOWN_RIGHT});
        }

        std::set<std::tuple<GridType, GridPosition, GridDirection>> neighbors{};
        for (auto const& [offset, direction] : neighbor_offsets)
        {
            GridPosition pos = { row + offset.row, col + offset.column };
            std::optional<GridType> element = get_element(pos);

            if (element.has_value())
            {
                neighbors.insert(std::make_tuple(element.value(), pos, direction));
            }
        }

        return neighbors;
    }

    std::optional<std::vector<GridType>> get_row(std::size_t row_num) const
    {
        if (row_num < m_grid.size())
        {
            return m_grid[row_num];
        }

        return std::nullopt;
    }

    std::optional<std::vector<GridType>> get_col(std::size_t col_num)
    {
        if (col_num < m_grid[0].size())
        {
            std::vector<GridType> column{};
            for (auto const& row : m_grid)
            {
                column.push_back(row[col_num]);
            }

            return column;
        }

        return std::nullopt;
    }

    [[nodiscard]] std::size_t get_row_count() const
    {
        return m_grid.size();
    }

    [[nodiscard]] std::size_t get_col_count() const
    {
        return m_grid[0].size();
    }

private:
    std::optional<GridType> get_element(GridPosition position) const
    {
        auto [row, col] = position;

        std::optional<GridType> element = std::nullopt;
        if (row >= 0 && row < m_grid.size())
        {
            if (col >= 0 && col < m_grid[row].size())
            {
                element = m_grid[row][col];
            }
        }

        return element;
    }

    /// @brief
    std::vector<std::vector<GridType>> m_grid{};
};

} // namespace AoC::Grid
