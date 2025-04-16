# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands
- Build: `mkdir -p build && cd build && cmake .. && make`
- Build with tests: `mkdir -p build && cd build && cmake -DBUILD_TESTS=ON .. && make`
- Run tests: `cd build && ctest --output-on-failure`
- Run single test: `cd build && ./tests/test_st3215_servo_reader` or `./tests/test_position_scaling`
- Build with stack traces: `mkdir -p build && cd build && cmake -DENABLE_BACKWARD=ON .. && make`

## Code Style
- C++ Standard: C++20
- Formatting: Use 4-space indentation
- Naming:
  - Member variables: snake_case with underscore prefix (_variable_name)
  - Functions: camelCase for parameters
  - Classes/Namespaces: PascalCase for class names, lowercase for namespaces (perseus::servo)
- Error handling: Use exceptions with descriptive messages, catch and handle appropriately
- Imports: Group standard library imports first, then project-specific includes
- Type safety: Prefer explicit types, avoid raw pointers
- Constants: Use typed enums in appropriate namespaces (timing::, protocol::, etc.)