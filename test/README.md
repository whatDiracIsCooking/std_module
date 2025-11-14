# std_module Test Suite

Comprehensive test suite for the std_module C++20 module wrapper library.

## Overview

This directory contains **72 test files** that validate all implemented standard library modules. Each test thoroughly exercises the exported APIs from its corresponding module to ensure correct functionality and comprehensive symbol coverage.

**Test Infrastructure:**
- CMake-based test system with CTest integration
- Automated symbol coverage analysis
- Macro-driven test registration (one line per test)

## Quick Start

### Running All Tests

```bash
# From project root
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++
cmake --build build
ctest --test-dir build --output-on-failure
```

### Running Specific Tests

```bash
# Run a single test
ctest --test-dir build -R test_format --output-on-failure

# Run tests matching a pattern
ctest --test-dir build -R "test_(format|vector)" --verbose

# List all available tests
ctest --test-dir build -N
```

## Test Files

The test suite includes tests for all 72 implemented modules. Each test file follows the pattern `test_{module}.cpp` and corresponds to a module in `src/{module}.cppm`.

**Examples:**
- `test_algorithm.cpp` - Sorting, searching, algorithms
- `test_format.cpp` - Text formatting (comprehensive reference test)
- `test_vector.cpp` - Dynamic array container
- `test_iostream.cpp` - Standard I/O streams
- ⋮ (68 more test files)

**To see all available tests:**
```bash
ls test/test_*.cpp
# Or list tests registered with CTest
ctest --test-dir build -N
```

## Test Structure

### Naming Convention

All test files follow the pattern: `test_{module}.cpp`

### Test Implementation Pattern

Each test follows the structure established in `test_format.cpp:1-273`:

```cpp
import std_module.{module};     // Import the module under test
#include <iostream>              // For output
#include <cassert>               // For assertions

// Test functions
void test_basic_functionality() {
    // Arrange
    auto input = /* ... */;

    // Act
    auto result = std::some_function(input);

    // Assert
    assert(result == expected);
    std::cout << "  ✓ Test description: " << result << "\n";
}

int main() {
    std::cout << "Testing std_module.{module}...\n";

    test_basic_functionality();
    test_edge_cases();
    test_error_conditions();
    // ... more test functions

    std::cout << "All tests passed!\n";
    return 0;
}
```

### Key Testing Principles

1. **Import-Only Testing**: Tests must use ONLY `import std_module.{module};` - never `#include <{module}>`
   - This ensures we test exactly what the module exports
   - If functionality doesn't work, mark with `// FIXME:` rather than working around it

2. **Comprehensive Coverage**: Test ALL exported symbols
   - Functions, classes, type aliases, constants
   - Multiple argument types and edge cases
   - Error conditions and exceptions

3. **Visual Feedback**: Use checkmarks for successful tests
   ```cpp
   std::cout << "  ✓ Test passed: description\n";
   ```

4. **Self-Contained**: Each test function should be independent

5. **Assertion-Based**: Validate results with `assert()`

## Symbol Coverage Analysis

The test suite includes automated symbol coverage analysis via `scripts/symbol_coverage.py`.

### Running Coverage Analysis

```bash
# Check a specific module
python3 scripts/symbol_coverage.py format

# Check all modules
python3 scripts/symbol_coverage.py --all

# Coverage runs automatically with ctest
ctest --test-dir build
```

### Coverage Output

```
Module: format
  Exported symbols: 25
  Tested symbols: 25
  Untested symbols: 0
  Coverage: 100.0%
```

**Purpose:** Ensures no exported symbols are accidentally left untested.

## Export Validation

The test suite includes authoritative validation via `scripts/validate_exports.py` which uses Clang's AST dump to verify module exports.

### Running Export Validation

```bash
# Validate all modules (compares regex extraction vs Clang AST)
python3 scripts/validate_exports.py

# Validate a specific module
python3 scripts/validate_exports.py src/format.cppm

# List exports without validation
python3 scripts/validate_exports.py src/format.cppm --list-only
```

### Validation Output

```
Module: format.cppm
  Clang AST: 25 exports
  Regex:     25 exports

✓ VALIDATION PASSED
  Regex extraction matches Clang AST 100% (25 symbols)
```

**Purpose:** Provides authoritative proof that:
- Our module exports are correct (Clang compiler sees them)
- Symbol coverage analysis is accurate (regex matches compiler view)
- No exports are missing or incorrectly parsed

**How it works:** Uses `clang++ -Xclang -ast-dump` to get the compiler's actual view of module exports, then compares with the regex-based extraction used by `symbol_coverage.py`.

**Results:** 45/49 modules show 100% match. The 4 mismatches are expected (conditional compilation with `#ifdef`).

## CMake Test Infrastructure

### Adding a New Test

Tests are registered using the `std_module_add_test()` macro in `CMakeLists.txt`:

```cmake
# In test/CMakeLists.txt
std_module_add_test(newmodule)
```

This single line:
1. Creates executable target `test_newmodule`
2. Links against `std_module::newmodule`
3. Sets C++20 requirement
4. Registers with CTest

### Build Options

Tests respect the same build options as modules:

```bash
# Build only specific tests
cmake -B build -G Ninja \
  -DSTD_MODULE_BUILD_ALL_MODULES=OFF \
  -DSTD_MODULE_BUILD_FORMAT=ON \
  -DSTD_MODULE_BUILD_VECTOR=ON

# Disable all tests
cmake -B build -G Ninja -DSTD_MODULE_BUILD_TESTS=OFF
```

## Known Limitations

### C++20 Module ADL Issues

Some modules have limited functionality due to C++20 module Argument-Dependent Lookup (ADL) limitations with non-member operators:

**Affected Modules:**
- `<iomanip>` - Manipulators don't work (operator<< not found)
- `<complex>` - Arithmetic operators don't work (operator+, operator*, etc.)

**Details:** See CLAUDE.md section "Testing Conventions" subsection 3 for full explanation.

**Testing Policy:**
- Tests mark broken functionality with `// FIXME: C++20 module ADL limitation`
- Do NOT add `#include <header>` as a workaround
- Keep test coverage high for working functionality
- Document what doesn't work in comments

## Troubleshooting

### Test Compilation Fails

**Problem:** "Module 'std_module.X' not found"
- **Solution:** Ensure the module is built: `cmake --build build`
- **Check:** Module option is enabled (e.g., `-DSTD_MODULE_BUILD_X=ON`)

### Test Crashes at Runtime

**Problem:** Assertion failures or segfaults
- **Solution:** Verify all used symbols are exported in `src/{module}.cppm`
- **Check:** Module and test use matching C++20 standard

### Coverage Analysis Fails

**Problem:** Python script can't find symbols
- **Solution:** Ensure test file and module file follow naming conventions
- **Check:** Python 3 is available: `python3 --version`

## Adding a New Test

Complete checklist for adding a new test:

1. **Create test file**: `test/test_{module}.cpp`
   - Follow the pattern in `test_format.cpp`
   - Import only: `import std_module.{module};`
   - Test all exported symbols
   - Use assertions and visual feedback

2. **Register with CMake**: Add one line to `test/CMakeLists.txt`
   ```cmake
   std_module_add_test({module})
   ```

3. **Build and run**:
   ```bash
   cmake --build build
   ctest --test-dir build -R test_{module} --output-on-failure
   ```

4. **Verify coverage**:
   ```bash
   python3 scripts/symbol_coverage.py {module}
   ```

5. **Check output**: Should see "All tests passed!" and 100% coverage

## Test Execution Order

CTest executes tests in parallel by default for performance. Each test is independent and can run concurrently.

**Sequential execution** (for debugging):
```bash
ctest --test-dir build -j1 --verbose
```

**Parallel execution** (default):
```bash
ctest --test-dir build -j$(nproc)
```

## Continuous Integration

Tests are designed to run in CI environments:

```yaml
# Example CI configuration
- name: Build and Test
  run: |
    cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++
    cmake --build build
    ctest --test-dir build --output-on-failure
```

**Exit codes:**
- `0` - All tests passed
- Non-zero - One or more tests failed

## Reference Implementation

**Best Test Example:** `test/test_format.cpp` (273 lines)
- Comprehensive coverage of all format APIs
- Custom type formatting with `std::formatter` specialization
- Error condition testing
- Multiple data types (int, float, string, custom)
- Clear output with checkmarks
- Well-organized test functions

Use this as a template when writing new tests.

---

**Last Updated:** 2025-11-14
**Test Count:** 72 modules
**Test Coverage:** 100% of exported symbols (per symbol_coverage.py)
