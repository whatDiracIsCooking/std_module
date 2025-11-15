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

## Testing Philosophy

### Core Principle

**We test module integration and C++20 module compatibility, NOT standard library correctness.**

- ✅ Verify `import std_module.vector;` works
- ✅ Verify symbols are accessible through the module
- ✅ Verify ADL-dependent operators work (or document as broken)
- ❌ Don't test `std::vector::push_back()` correctness (trust the stdlib)
- ❌ Don't exhaustively test edge cases (stdlib's job)

### The Three Testing Tiers

Tests are categorized into three tiers based on complexity and importance:

| Tier | Target Lines | When to Use | What to Test |
|------|--------------|-------------|--------------|
| **Tier 1: Minimal** | 50-100 | Simple utilities, rarely-used modules | Basic usage, iterators, ADL operators (status only) |
| **Tier 2: Comprehensive** | 200-400 | Core containers, I/O, algorithms | All operation categories, extensive ADL testing |
| **Tier 3: Integration** | Future | Cross-module dependencies | Wait until dependent modules available |

**Examples:**
- **Tier 1:** `<limits>`, `<bit>`, `<compare>`, `<ratio>` - Simple, focused tests
- **Tier 2:** `<format>` (273 lines), `<vector>` (390 lines), `<iostream>` - Comprehensive tests
- **Tier 3:** Tests requiring multiple modules that aren't yet implemented

## Test Structure

### Naming Convention

All test files follow the pattern: `test_{module}.cpp`

### Tier 1 Template (Minimal Viable Test)

For simple modules, use this 50-100 line template:

```cpp
import std_module.{module};
#include <iostream>  // Allowed - testing infrastructure
#include <cassert>   // Allowed - assert is a macro

void test_basic_usage() {
    std::cout << "Testing basic usage...\n";
    std::container<int> c{1, 2, 3};
    assert(c.size() == 3);
    std::cout << "  ✓ Construction and size\n";
}

void test_iterators() {
    std::cout << "\nTesting iterators...\n";
    std::container<int> c{1, 2, 3};
    int sum = 0;
    for (int val : c) sum += val;
    assert(sum == 6);
    std::cout << "  ✓ Range-based for\n";
}

void test_adl_operators() {
    std::cout << "\nTesting ADL operators...\n";
    try {
        bool eq = (a == b);
        std::cout << "  ✓ operator== works\n";
    } catch (...) {
        std::cout << "  ⚠ operator== unavailable (ADL limitation)\n";
    }
}

int main() {
    std::cout << "=== Testing std_module.{module} ===\n\n";
    test_basic_usage();
    test_iterators();
    test_adl_operators();
    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}
```

### Tier 2 Pattern (Comprehensive Test)

For important modules, see `test/test_format.cpp:1-273` or `test/test_vector.cpp`:

```cpp
import std_module.{module};
#include <iostream>
#include <cassert>
#include <sstream>  // If needed for testing

// Test each operation category
void test_construction() { /* ... */ }
void test_modifiers() { /* ... */ }
void test_accessors() { /* ... */ }
void test_capacity() { /* ... */ }
void test_iterators() { /* ... */ }
void test_operators() { /* ... */ }
void test_algorithms() { /* ... */ }
void test_error_conditions() { /* ... */ }

int main() {
    std::cout << "=== Testing std_module.{module} ===\n\n";
    test_construction();
    test_modifiers();
    // ... all test functions
    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}
```

### Key Testing Principles

1. **Import-Only Testing**: Tests must use ONLY `import std_module.{module};` - never `#include <{module}>`
   - This ensures we test exactly what the module exports
   - Validates true module isolation
   - See updated ADL solution below

2. **Allowed Includes**: Only these three headers for testing infrastructure
   - ✅ `<cassert>` - Required (assert is a macro)
   - ✅ `<iostream>` - For test output
   - ✅ `<sstream>` - For string stream testing
   - ❌ Everything else - Wait for modules or document as FUTURE

3. **ADL Operator Testing**: REQUIRED for all tests
   ```cpp
   void test_operators() {
       std::cout << "\nTesting operators...\n";
       try {
           bool result = (a == b);  // Try the operator
           assert(result);
           std::cout << "  ✓ operator== works\n";
       } catch (...) {
           std::cout << "  ⚠ operator== unavailable (ADL limitation)\n";
           // Don't fail - document status and continue
       }
   }
   ```

4. **FUTURE Tests**: Document tests requiring unavailable modules
   ```cpp
   // FUTURE: Requires import std_module.string
   // void test_with_strings() { ... }
   ```

5. **Visual Feedback**: Use checkmarks for successful tests
   ```cpp
   std::cout << "  ✓ Test passed: description\n";
   ```

6. **Self-Contained**: Each test function should be independent

7. **Assertion-Based**: Validate results with `assert()`

8. **Test Variety, Not Exhaustiveness**: One example per operation category

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

## C++20 Module ADL Limitation - SOLUTION FOUND ✅

### The Problem (Historical)

C++20 modules had issues with Argument-Dependent Lookup (ADL) for operators across module boundaries. Without `#include` directives, operators like `operator<<` weren't found even when types were exported.

### THE SOLUTION ✅

**BREAKTHROUGH DISCOVERY (2025-11-14):** The ADL limitation CAN be fixed by explicitly exporting operators in the module!

**How to Fix:**

In the module file (`.cppm`), export operators explicitly:

```cpp
export module std_module.{module};

export namespace std {
    // Export types/objects
    using std::cout;
    using std::vector;

    // CRITICAL: Export operators to fix ADL
    using std::operator<<;
    using std::operator>>;
    using std::operator+;
    using std::operator-;
    // ... export all relevant operators

    // Export manipulators if needed
    using std::endl;
    using std::flush;
}
```

**Verification:**

After exporting operators, test with **NO `#include` directives** - only `import`:

```cpp
import std_module.iostream;
// NO #include directives!

int main() {
    std::cout << "Hello World" << std::endl;  // Works!
}
```

### Module Status

**✅ FIXED (operators work):**
- `<iostream>` - Exports `operator<<`, `operator>>`, `endl`, `flush`
- `<chrono>` - Exports arithmetic, comparison, and literal operators
- Works on Clang + libstdc++, Clang + libc++, GCC + libstdc++

**⚠️ TODO (not yet tested with operator exports):**
- `<iomanip>` - May be fixable by exporting manipulator operators
- `<complex>` - Should be fixable by exporting arithmetic operators
- Potentially fixable: `<valarray>`, `<filesystem>`, etc.

### Testing Policy

1. **Export operators in the module** - Add `using std::operator...;` declarations
2. **Test with NO includes** - Remove ALL `#include` statements (except allowed test infrastructure)
3. **If tests fail, add more exports** - Identify missing operators from error messages
4. **Verify on multiple compilers** - Test with Clang + libstdc++, Clang + libc++, GCC
5. **Update status** - Move module to "FIXED" section when operators work

**DO NOT:**
- ❌ Add `#include <header>` to work around operator issues (defeats module testing)
- ❌ Accept broken operators as "unfixable" (they ARE fixable with exports)
- ❌ Mix `import` + `#include` of the same header (causes different issues)

**Reference Implementations:**
- `src/iostream.cppm` - Stream operators
- `src/chrono.cppm` - Arithmetic, comparison, and literal operators
- `test/test_iostream.cpp` - Pure module-only test (no includes)
- `test/test_chrono.cpp` - Comprehensive operator testing

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

## Test Quality Checklist

Before committing a new test, verify:

**Code Structure:**
- [ ] Uses `import std_module.<module>;` not `#include <header>`
- [ ] Only includes allowed headers (`<cassert>`, `<iostream>`, `<sstream>`)
- [ ] Appropriate line count: 50-100 (Tier 1) or 200-400 (Tier 2)
- [ ] Returns 0 on success, 1 on failure

**Test Coverage:**
- [ ] Tests basic usage (construction, size, access)
- [ ] Tests iterators (if applicable) including range-based for
- [ ] Tests ADL operators with try/catch pattern (reports status, doesn't fail)
- [ ] Documents FUTURE tests requiring unavailable modules

**Output Quality:**
- [ ] Has meaningful output with ✓ checkmarks
- [ ] Shows test categories being executed
- [ ] Displays "=== All tests passed! ===" on success

**Validation:**
- [ ] Passes: `ctest --test-dir build -R test_<module> --output-on-failure`
- [ ] Passes: `python3 scripts/symbol_coverage.py <module>`
- [ ] Compiles without warnings

## Adding a New Test

Complete workflow for adding a new test:

1. **Create test file**: `test/test_{module}.cpp`
   - Choose appropriate tier (Tier 1: 50-100 lines, Tier 2: 200-400 lines)
   - Start with Tier 1 template (see above)
   - Import only: `import std_module.{module};`
   - Test all exported symbols
   - Use try/catch for ADL operators
   - Document FUTURE tests with comments

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

5. **Check output**: Should see "=== All tests passed! ===" and 100% coverage

6. **Run quality checklist**: See "Test Quality Checklist" section above

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

## Reference Implementations

### Tier 1 Examples (50-100 lines)

**Simple, focused tests for utilities:**
- `test/test_limits.cpp` - Type limits testing
- `test/test_bit.cpp` - Bit manipulation utilities
- `test/test_compare.cpp` - Three-way comparison
- `test/test_ratio.cpp` - Compile-time ratios

**Pattern:**
- Basic usage validation
- Iterator testing (if applicable)
- ADL operator status check
- Minimal but complete

### Tier 2 Examples (200-400 lines)

**Comprehensive tests for core modules:**

**`test/test_format.cpp` (273 lines)**
- Complete coverage of formatting APIs
- Custom type formatting with `std::formatter` specialization
- Error condition testing
- Multiple data types (int, float, string, custom)
- Well-organized test functions

**`test/test_vector.cpp` (~390 lines)**
- All container operations (construction, modifiers, accessors, capacity)
- Iterator testing (begin, end, rbegin, rend)
- Comparison operators
- Algorithm integration
- Exception safety

**`test/test_iostream.cpp`**
- Stream insertion/extraction operators
- Manipulator testing
- State management
- **IMPORTANT:** Pure module-only test (no `#include` directives except test infrastructure)
- Reference for ADL operator solution

**`test/test_chrono.cpp`**
- Duration and time_point operations
- Arithmetic and comparison operators
- Literal operators (in inline namespace)
- Calendar operations
- **IMPORTANT:** Comprehensive operator export example

**When to Use Each:**
- **New simple module?** Start with Tier 1 template
- **Core container/algorithm?** Follow `test_format.cpp` or `test_vector.cpp` patterns
- **Operator-heavy module?** Study `test_iostream.cpp` and `test_chrono.cpp`

---

**Last Updated:** 2025-11-15
**Test Count:** 72 modules
**Test Coverage:** 100% of exported symbols (per symbol_coverage.py)
**Testing Philosophy:** Three-tier system (Tier 1: 50-100 lines, Tier 2: 200-400 lines, Tier 3: Integration)
