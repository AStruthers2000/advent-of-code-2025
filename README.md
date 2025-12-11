
# Advent of Code 2025

Welcome to my [**Advent of Code 2025**](https://adventofcode.com/2025) repository! This project showcases my solutions to the daily programming challenges presented in Advent of Code 2025. Each solution is written in **C++23**, adhering to modern object-oriented programming practices and leveraging the latest language features.

## ⭐ Stats
|                                           Day                                            | Stars |  Parse  |  Part 1  |  Part 2  |                       Problem                       |
|:----------------------------------------------------------------------------------------:|:------|:-------:|:--------:|:--------:|:---------------------------------------------------:|
| [1](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day01)  | ⭐⭐    |  989μs  |   59μs   |   61μs   | [Open on AoC](https://adventofcode.com/2025/day/1)  |
| [2](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day02)  | ⭐⭐    |  160μs  |  1.687s  |  4.719s  | [Open on AoC](https://adventofcode.com/2025/day/2)  |
| [3](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day03)  | ⭐⭐    |  394μs  |  253μs   |  409μs   | [Open on AoC](https://adventofcode.com/2025/day/3)  |
| [4](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day04)  | ⭐⭐    |  476μs  |  146ms   |  3.001s  | [Open on AoC](https://adventofcode.com/2025/day/4)  |
| [5](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day05)  | ⭐⭐    |  640μs  |  155μs   |   84μs   | [Open on AoC](https://adventofcode.com/2025/day/5)  |
| [6](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day06)  | ⭐⭐    |  973μs  | 2.607ms  | 17.646ms | [Open on AoC](https://adventofcode.com/2025/day/6)  |
| [7](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day07)  | ⭐⭐    |  559μs  | 93.951ms |   7μs    | [Open on AoC](https://adventofcode.com/2025/day/7)  |
| [8](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day08)  | ⭐⭐    | 5.133s  | 28.68ms  | 205.8ms  | [Open on AoC](https://adventofcode.com/2025/day/8)  |
| [9](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day09)  | ⭐     | 1.529s  |   5μs    |          | [Open on AoC](https://adventofcode.com/2025/day/9)  |
| [10](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day10) | ⭐     | 4.155ms | 16.265ms |    ∞     | [Open on AoC](https://adventofcode.com/2025/day/10) |
| [11](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day11) |       |         |          |          | [Open on AoC](https://adventofcode.com/2025/day/11) |
| [12](https://github.com/AStruthers2000/advent-of-code-2025/tree/main/src/problems/day12) |       |         |          |          | [Open on AoC](https://adventofcode.com/2025/day/12) |

# TODO
* Fix README
* Get source tests working
* Create module tests

Ignore everything below this

<del>

## 🚀 Project Overview

The project is structured with modularity and maintainability in mind:

- Each day's solution is implemented as a subclass of a base `Problem` class, allowing for:
    - Easy organization of daily challenges.
    - A polymorphic array of `Problem` instances for streamlined execution.
- Utility modules and submodules provide reusable functionality for:
    - Math utilities.
    - String parsing.
    - Algorithms.
    - Data structures.
- The codebase takes full advantage of **C++23 features** such as:
    - `std::optional` for expressive and safe optional values.
    - Template classes and functions for flexibility and type safety.
    - Modules for clean code organization and dependency management.

This repository not only documents my journey through the Advent of Code challenges but also serves as a playground to deepen my understanding of **modern C++ development methodologies**.

## 🛠️ Tools & Environment

- **Language:** C++23
- **IDE:** JetBrains CLion.
- **Compiler:** MSVC with support for C++23 and modules.
- **Build System:** CMake (Version 3.28)
- **Unit Tests:** CppUTest

## 🗂️ File Structure TODO fixme

```
Solution/
├── Problems/
│   ├── Problem.h
│   ├── Problem.cpp
│   ├── Day01/
│   │   ├── Day01.h
│   │   ├── Day01.cpp
│   ├── Day02/
│   │   ├── Day01.h
│   │   ├── Day01.cpp
│   └── ... (more days)
├── Utils/
│   ├── Math/
│   │   └── ... (utils implementation)
│   ├── StringParsing/
│   │   └── ... (utils implementation)
│   └── ... (more utils)
└── AdventOfCode2024.cpp
```

## 🧩 How It Works

1. **Problem Structure:** Each problem is a subclass of `Problem`, implementing specific functionality for the corresponding day. This design ensures that:
    - Code for each problem is modular and encapsulated.
    - A single polymorphic array can store and execute all problems dynamically.

2. **Utilities:** Common utilities like string parsing and math functions are placed in dedicated modules, making them reusable and improving code readability.

3. **Modern C++ Practices:**
    - Use of `std::optional` for optional values.
    - Extensive use of templates for generalized solutions.
    - Modular programming with `import` statements for better organization.

## 📋 Usage

### Adding a New Problem TODO fixme
1. Create a new `DayXX` class and `DayXX` folder in the `Solution/Problems` folder.
2. Inherit from the `Problem` base class.
3. Implement the `LoadProblem()`, `SolvePart1()`, and `SolvePart2()` methods for the problem logic.
4. Add the new problem to the array in `AdventOfCode2024.cpp`.

## 🎯 Goals

This project aims to:
- Solve the Advent of Code 2025 challenges in a clean, efficient, and modular way.
- Embrace and explore modern C++23 features and development methodologies.
- Serve as a learning resource and reference for modular programming in C++.

</del>
---
