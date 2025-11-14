# CLAUDE.md - AI Assistant Guide for std_module

This document provides comprehensive guidance for AI assistants working with the `std_module` repository.

## Project Overview

**std_module** is a C++20 module wrapper library for the C++ standard library. It enables developers to use modern `import` statements instead of traditional `#include` directives.

- **Language:** C++20 with modules
- **Version:** 0.1.0
- **Build System:** CMake 3.28+ with Ninja (required)
- **Status:** Early development - format module complete, more stdlib headers planned

### Core Philosophy

The project prioritizes **flexibility over opinion**:
- No forced dependencies between modules
- Opt-in architecture - build only what you need
- Multiple integration methods (subdirectory, installed, manual)
- Standard library semantics preserved exactly (no modifications)

## Repository Structure

```
/home/user/std_module/
├── CMakeLists.txt              # Root build config (130 lines)
├── README.md                   # User-facing documentation
├── src/                        # Module implementations
│   ├── CMakeLists.txt         # Module build targets (93 lines)
│   ├── format.cppm            # <format> wrapper (47 lines)
│   └── std.cppm               # Aggregate module WIP (10 lines)
├── test/                       # Test suite
│   ├── CMakeLists.txt         # Test build config (33 lines)
│   ├── README.md              # Test documentation
│   ├── build_manual.sh        # Manual build demo script
│   └── test_format.cpp        # Comprehensive format tests (273 lines)
└── cmake/                      # CMake package config
    └── std_module-config.cmake.in
```

### Key Files by Purpose

| File | Lines | Purpose |
|------|-------|---------|
| `src/format.cppm` | 47 | C++20 module wrapping `<format>` header |
| `test/test_format.cpp` | 273 | Comprehensive tests for all format APIs |
| `CMakeLists.txt` (root) | 130 | Build options, compiler detection, installation |
| `src/CMakeLists.txt` | 93 | Module library targets and exports |

## Critical C++20 Module Concepts

### Module File Structure (.cppm)

All module files follow this pattern:

```cpp
module;                          // Global module fragment start
#include <header>                // Include standard library headers
export module std_module.name;   // Module declaration
export namespace std {           // Export namespace
    using std::symbol;           // Re-export symbols
}
```

**Example:** `src/format.cppm:1-47`

### Module Compilation Requirements

1. **Ninja generator is MANDATORY** - Make will not work
2. **CMake 3.28+** - Earlier versions lack proper module support
3. **Modern compiler:**
   - Clang 16+ (recommended)
   - GCC 11+ (experimental support)
   - MSVC 19.30+ (Visual Studio 2022)

### Module Naming Convention

- **Module name:** `std_module.{header}` (e.g., `std_module.format`)
- **CMake target:** `std_module::{header}` (e.g., `std_module::format`)
- **File name:** `{header}.cppm` (e.g., `format.cppm`)
- **Import statement:** `import std_module.{header};`

## Build System Architecture

### CMake Build Options

Configure in `CMakeLists.txt:12-21`:

| Option | Default | Description |
|--------|---------|-------------|
| `STD_MODULE_BUILD_TESTS` | ON | Build test executables |
| `STD_MODULE_BUILD_ALL_MODULES` | ON | Build all available modules |
| `STD_MODULE_INSTALL` | ON | Generate installation targets |
| `STD_MODULE_BUILD_FORMAT` | ON | Build format module |

### Standard Build Workflow

```bash
# 1. Configure (Ninja is required)
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++

# 2. Build all targets
cmake --build build

# 3. Run tests
ctest --test-dir build --output-on-failure

# 4. Optional: Install
cmake --install build --prefix /usr/local
```

### Module Target Pattern

Each module follows this CMake pattern (`src/CMakeLists.txt:1-93`):

```cmake
# 1. Create library target
add_library(std_module_<name>)

# 2. Add module source using FILE_SET
target_sources(std_module_<name>
    PUBLIC FILE_SET CXX_MODULES FILES <name>.cppm)

# 3. Require C++20
target_compile_features(std_module_<name> PUBLIC cxx_std_20)

# 4. Create namespaced alias
add_library(std_module::<name> ALIAS std_module_<name>)

# 5. Export for installation
install(TARGETS std_module_<name> EXPORT std_module-targets)
```

**Critical:** Use `FILE_SET CXX_MODULES` for module files, NOT regular `target_sources()`!

## Development Workflows

### Adding a New Standard Library Module

Follow this checklist when wrapping a new stdlib header:

#### 1. Create Module Implementation File

Create `src/{header}.cppm` following the pattern in `src/format.cppm:1-47`:

```cpp
module;
#include <header>
export module std_module.header;

export namespace std {
    // Export all public APIs from the header
    using std::function_name;
    using std::class_name;
    // ... etc
}
```

**Location:** `src/{header}.cppm`

#### 2. Update Root CMakeLists.txt

Add build option around line 17-21:

```cmake
option(STD_MODULE_BUILD_HEADER "Build std_module.header" ON)
```

Update summary section around line 129 to display the new option.

**Location:** `CMakeLists.txt:17-21, 129`

#### 3. Add Module Target

Add to `src/CMakeLists.txt` following the pattern starting at line 20:

```cmake
# Build std_module.header
if(STD_MODULE_BUILD_HEADER OR STD_MODULE_BUILD_ALL_MODULES)
    add_library(std_module_header)
    target_sources(std_module_header
        PUBLIC FILE_SET CXX_MODULES FILES header.cppm)
    target_compile_features(std_module_header PUBLIC cxx_std_20)
    add_library(std_module::header ALIAS std_module_header)

    list(APPEND ALL_MODULE_TARGETS std_module_header)

    if(STD_MODULE_INSTALL)
        install(TARGETS std_module_header EXPORT std_module-targets)
    endif()
endif()
```

**Location:** `src/CMakeLists.txt:20-93`

#### 4. Create Comprehensive Test

Create `test/test_{header}.cpp` following `test/test_format.cpp:1-273`:

- Import the module: `import std_module.header;`
- Test ALL exported functions and types
- Use assertions for validation
- Print checkmarks (✓) for visual feedback
- Include error handling tests
- Test edge cases and various types

**Key test patterns from test_format.cpp:**
- Basic functionality (lines 31-48)
- Output iterators (lines 50-63)
- Size calculations (lines 83-93)
- Custom types/formatters (lines 154-167)
- Error conditions (lines 120-152)
- Type variations (lines 200-223)

#### 5. Update Test CMakeLists.txt

Add to `test/CMakeLists.txt` around line 15-25:

```cmake
if(STD_MODULE_BUILD_HEADER OR STD_MODULE_BUILD_ALL_MODULES)
    add_executable(test_header test_header.cpp)
    target_link_libraries(test_header PRIVATE std_module::header)
    add_test(NAME test_header COMMAND test_header)
endif()
```

**Location:** `test/CMakeLists.txt:15-32`

#### 6. Update Documentation

Update `README.md` section "Available Modules" (line 94-98):

```markdown
- ✅ `<header>` → `import std_module.header;`
```

Add to library targets section if needed (line 118).

#### 7. Test the Implementation

```bash
# Clean build
rm -rf build

# Configure with only the new module
cmake -B build -G Ninja \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DSTD_MODULE_BUILD_ALL_MODULES=OFF \
  -DSTD_MODULE_BUILD_HEADER=ON

# Build and test
cmake --build build
ctest --test-dir build --output-on-failure
```

### Testing Workflow

**Test infrastructure location:** `test/`

#### Automated Testing (Preferred)

```bash
# Run all tests
ctest --test-dir build --output-on-failure

# Run specific test
ctest --test-dir build -R test_format --output-on-failure

# Verbose output
ctest --test-dir build --verbose
```

#### Manual Testing (For Debugging)

The `test/build_manual.sh` script demonstrates the low-level module compilation:

```bash
cd test
./build_manual.sh
```

This 5-step process shows:
1. Precompile standard headers
2. Compile module interface (.cppm → .pcm)
3. Compile test source (.cpp → .o)
4. Link executable
5. Run test

**Use case:** Understanding module build mechanics, debugging compiler issues

### Testing Conventions

From `test/test_format.cpp:1-273`:

1. **One test function per feature area**
   - Example: `test_basic_format()`, `test_format_to()`, `test_custom_formatter()`

2. **Assertion-based validation**
   ```cpp
   auto result = std::format("Value: {}", 42);
   assert(result == "Value: 42");
   ```

3. **Visual feedback**
   ```cpp
   std::cout << "  ✓ Test description: " << result << "\n";
   ```

4. **Comprehensive coverage**
   - All exported functions
   - Multiple argument types
   - Edge cases (empty strings, large numbers, etc.)
   - Error conditions
   - Custom types/formatters

5. **Exception handling**
   ```cpp
   try {
       // Test code
   } catch (const std::format_error& e) {
       std::cout << "  ✓ Expected error: " << e.what() << "\n";
   }
   ```

### Git Workflow and Commit Conventions

**Current branch:** `claude/claude-md-mhyb6sx50vx0x652-01GvWb1xstPoWREcHQGWk2oB`

#### Commit Message Style

Based on git history:

```
48014f4 - Merge pull request #2 from ...
d4d4e27 - Complete C++20 format module implementation with comprehensive tests
0552509 - Merge pull request #1 from ...
ca8696e - Add flexible CMake build system for C++20 modules
8d9132d - Add minimal test infrastructure for manual module compilation
```

**Pattern:** Imperative mood, descriptive, mentions key features

**Examples:**
- ✅ "Add vector module with iterator support"
- ✅ "Complete C++20 string module implementation with comprehensive tests"
- ✅ "Fix alignment handling in custom formatter"
- ❌ "Added some stuff"
- ❌ "WIP"

#### Branch Strategy

- Feature branches merged via pull requests
- Branch naming: `claude/{description}-{session-id}`
- Clean, linear history preferred

#### Push Requirements

**CRITICAL:** When pushing, always use:

```bash
git push -u origin claude/claude-md-mhyb6sx50vx0x652-01GvWb1xstPoWREcHQGWk2oB
```

- Branch MUST start with `claude/` and end with matching session ID
- Use `-u` flag for tracking
- Retry on network errors (up to 4 times with exponential backoff: 2s, 4s, 8s, 16s)

## Common Pitfalls and Important Notes

### Build System

1. **Never use Make generator** - C++20 modules require Ninja
   ```bash
   # ❌ WRONG
   cmake -B build

   # ✅ CORRECT
   cmake -B build -G Ninja
   ```

2. **CMake version matters** - 3.28+ required for `FILE_SET CXX_MODULES`
   ```cmake
   # Check: CMakeLists.txt:1
   cmake_minimum_required(VERSION 3.28)
   ```

3. **Module files need special handling**
   ```cmake
   # ❌ WRONG - treats as regular source
   target_sources(target PRIVATE module.cppm)

   # ✅ CORRECT - handles as module
   target_sources(target PUBLIC FILE_SET CXX_MODULES FILES module.cppm)
   ```

### Module Implementation

1. **Global module fragment required for headers**
   ```cpp
   // ✅ CORRECT
   module;
   #include <format>
   export module std_module.format;

   // ❌ WRONG - include after module declaration
   export module std_module.format;
   #include <format>
   ```

2. **Export the namespace, not individual symbols**
   ```cpp
   // ✅ CORRECT - exports under std namespace
   export namespace std {
       using std::format;
   }

   // ❌ WRONG - pollutes global namespace
   export using std::format;
   ```

3. **Module names use dots, not colons**
   ```cpp
   // ✅ CORRECT
   export module std_module.format;

   // ❌ WRONG
   export module std_module::format;
   ```

### Testing

1. **Module import must come first**
   ```cpp
   // ✅ CORRECT
   import std_module.format;
   #include <iostream>

   // ❌ WRONG - imports after includes
   #include <iostream>
   import std_module.format;
   ```

2. **Tests must use ONLY `import` - NO `#include` of the wrapped header**
   - **Critical Rule:** Tests should rely exclusively on `import std_module.header;`
   - Do NOT add `#include <header>` as a workaround for missing functionality
   - If functionality doesn't work with just `import`, mark it as FIXME
   - This policy ensures we accurately test what the module exports

   ```cpp
   // ✅ CORRECT - Tests only module exports
   import std_module.complex;
   #include <iostream>  // OK - for testing infrastructure
   #include <cassert>   // OK - for testing infrastructure

   // ❌ WRONG - Defeats the purpose of testing the module
   import std_module.complex;
   #include <complex>  // NO! Don't work around module limitations
   ```

3. **C++20 Module ADL Limitation with Non-Member Operators**
   - **Known Issue:** Non-member template operators (like `operator+` for `std::complex`)
     are not found via ADL when imported from modules
   - **Impact:** Some standard library types (complex, valarray) have broken arithmetic operators
   - **Solution:** Comment out affected tests with `// FIXME: C++20 module ADL limitation`
   - **Reference:** https://github.com/cplusplus/papers/issues/1005
   - **Example:** `test/test_complex.cpp` has operator tests commented out

   ```cpp
   // FIXME: C++20 module ADL limitation - operators not found without #include
   // void test_arithmetic_operations() {
   //     std::complex<double> c1(3.0, 4.0);
   //     auto sum = c1 + c2;  // Error: operator+ not found
   // }
   ```

4. **Test all exported symbols** - Easy to miss symbols in export list
   - Check the module file for complete export list
   - Example: `src/format.cppm:13-46` exports 20+ symbols
   - Mark untestable functions with FIXME if they require broken operators

5. **Custom formatters need template specialization**
   ```cpp
   // From test/test_format.cpp:20-29
   template<>
   struct std::formatter<Point> {
       // ...
   };
   ```

### File Organization

1. **Module files use .cppm extension** - Not .cpp or .cxx
2. **One module per file** - Don't combine multiple modules
3. **Test files match module names** - `test_{module}.cpp` pattern

## Quick Reference

### File Path Reference

| Component | Path |
|-----------|------|
| Root build config | `/home/user/std_module/CMakeLists.txt` |
| Module implementations | `/home/user/std_module/src/*.cppm` |
| Module build config | `/home/user/std_module/src/CMakeLists.txt` |
| Test files | `/home/user/std_module/test/test_*.cpp` |
| Test build config | `/home/user/std_module/test/CMakeLists.txt` |
| Package config template | `/home/user/std_module/cmake/std_module-config.cmake.in` |

### Command Quick Reference

```bash
# Clean build from scratch
rm -rf build && cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++

# Build specific module only
cmake -B build -G Ninja -DSTD_MODULE_BUILD_ALL_MODULES=OFF -DSTD_MODULE_BUILD_FORMAT=ON

# Run tests with verbose output
ctest --test-dir build --output-on-failure --verbose

# Check what targets are available
cmake --build build --target help

# Install to custom location
cmake --install build --prefix ~/.local
```

### Integration Examples

**Method 1: Subdirectory**
```cmake
add_subdirectory(external/std_module)
target_link_libraries(myapp PRIVATE std_module::format)
```

**Method 2: Installed Package**
```cmake
find_package(std_module REQUIRED COMPONENTS format)
target_link_libraries(myapp PRIVATE std_module::format)
```

**Method 3: Manual (see test/README.md)**

## Code Quality Standards

### When Writing Module Wrappers

1. **Export completeness** - Export ALL public APIs from the header
   - Check cppreference.com for complete API list
   - Include functions, classes, type aliases, constants

2. **Documentation** - Add brief file header
   ```cpp
   /**
    * @file format.cppm
    * @brief C++20 format module wrapper
    */
   ```

3. **Consistency** - Follow format.cppm pattern exactly
   - Same structure, same ordering
   - Global module fragment → export module → export namespace

### When Writing Tests

1. **Comprehensive coverage** - Test every exported symbol
2. **Self-contained** - Each test function is independent
3. **Readable output** - Use checkmarks and descriptions
4. **Error handling** - Test both success and failure cases
5. **Type variety** - Test with different types (int, float, string, custom, etc.)

From `test/test_format.cpp`:
- 12 test functions covering all format APIs
- 273 lines ensuring complete coverage
- Custom type testing (Point struct)
- Error condition testing
- Wide character support testing

## Security Considerations

This is a wrapper library that re-exports standard library symbols:

- **No network operations** - Pure local compilation
- **No file I/O** - Except during build/install
- **No external dependencies** - Only standard library
- **No unsafe operations** - Just wrapping existing stdlib APIs

## Performance Notes

1. **Module compilation is slower initially** - But faster for consumers
2. **Precompiled modules (.pcm) enable faster builds** - Cached by CMake
3. **No runtime overhead** - Same performance as `#include`

## Future Expansion Roadmap

Based on project structure, planned modules likely include:

- `std_module.vector` - `<vector>` wrapper
- `std_module.string` - `<string>` wrapper
- `std_module.algorithm` - `<algorithm>` wrapper
- `std_module.ranges` - `<ranges>` wrapper
- Many more stdlib headers...

**Aggregate module:** `src/std.cppm` (WIP) will re-export all submodules for convenience:
```cpp
import std_module;  // Gets everything
```

## Troubleshooting Guide

### Build Issues

**Problem:** "CMake 3.28 or higher is required"
- **Solution:** Update CMake or use newer compiler's bundled CMake

**Problem:** "Ninja not found"
- **Solution:** Install ninja-build package: `apt-get install ninja-build`

**Problem:** Module compilation fails with cryptic errors
- **Solution:** Check compiler version (Clang 16+), verify Ninja generator is used

### Test Failures

**Problem:** Test compiles but crashes
- **Solution:** Check that ALL used symbols are exported in the module

**Problem:** Linker errors about undefined symbols
- **Solution:** Verify target links against module target (`std_module::format`)

### Git Issues

**Problem:** Push fails with 403
- **Solution:** Verify branch name starts with `claude/` and ends with session ID

## Version History

- **0.1.0** (Current) - Initial release with format module
  - Flexible CMake build system
  - std_module.format complete with comprehensive tests
  - Multiple integration methods
  - Full installation support

---

**Last Updated:** 2025-11-14
**Repository:** /home/user/std_module
**Primary Maintainer:** AI Assistant
**Documentation Version:** 1.0
