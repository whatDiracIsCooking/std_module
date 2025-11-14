# std_module

A C++20 module wrapper for the C++ standard library. Instead of `#include <format>`, use `import std_module.format;`.

## Overview

This project provides C++20 module interfaces for the C++ standard library, allowing you to use `import` statements instead of traditional `#include` directives. The build system is designed to be flexible and non-opinionated, supporting multiple integration methods.

## Features

- **Modular**: Import only what you need (`import std_module.format;`)
- **Flexible Build System**: Use as subdirectory, installed library, or manual compilation
- **Compiler Support**: Clang 16+, GCC 11+, MSVC 19.30+
- **Opt-in Architecture**: Build only the modules you need
- **Standard Compliant**: Wraps the standard library without modifications

## Requirements

- CMake 3.28+
- Ninja build system (required for C++20 modules)
- C++20 compiler with module support:
  - Clang 16+ (recommended)
  - GCC 11+ (experimental)
  - MSVC 19.30+ (Visual Studio 2022)

## Quick Start

### Building with CMake

```bash
# Configure (Ninja generator is required for C++20 modules)
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++

# Build
cmake --build build

# Run tests
ctest --test-dir build --output-on-failure

# Install (optional)
cmake --install build --prefix /usr/local
```

## Integration Methods

### Method 1: CMake Subdirectory

Add to your project:

```cmake
add_subdirectory(external/std_module)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE std_module::format)
```

### Method 2: Installed Library

After installation:

```cmake
find_package(std_module REQUIRED COMPONENTS format)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE std_module::format)
```

### Method 3: Manual Compilation

See [`test/README.md`](test/README.md) for manual build instructions.

## Module Naming Conventions

All modules follow consistent naming patterns:

**CMake Options:**
- Global options: `STD_MODULE_BUILD_TESTS`, `STD_MODULE_BUILD_ALL_MODULES`, `STD_MODULE_INSTALL`
- Per-module options: `STD_MODULE_BUILD_<UPPERCASE_NAME>=ON`
  - Example: `STD_MODULE_BUILD_FORMAT=ON`, `STD_MODULE_BUILD_VECTOR=ON`

**CMake Targets:**
- Individual modules: `std_module::<lowercase_name>`
  - Example: `std_module::format`, `std_module::vector`
- All modules: `std_module::all` (convenience target)

**Import Statements:**
- Pattern: `import std_module.<lowercase_name>;`
  - Example: `import std_module.format;`, `import std_module.vector;`
- Special case: `<new>` uses `import std_module.new_;` (underscore suffix to avoid C++ keyword conflicts)

## Available Modules

The table below lists all implemented modules. See [Module Naming Conventions](#module-naming-conventions) above for CMake options, targets, and import statements.

| Header | Status | Notes |
|--------|--------|-------|
| `<algorithm>` | ✅ | Sorting, searching, transforming |
| `<any>` | ✅ | Type-safe container for any type |
| `<barrier>` | ✅ | Thread synchronization barrier |
| `<bitset>` | ✅ | Fixed-size bit arrays |
| `<charconv>` | ✅ | Low-level character conversions |
| `<complex>` | ✅ | Complex number arithmetic |
| `<concepts>` | ✅ | Concept definitions for templates |
| `<deque>` | ✅ | Double-ended queue container |
| `<exception>` | ✅ | Exception handling utilities |
| `<execution>` | ✅ | Execution policies for algorithms |
| `<format>` | ✅ | Text formatting (C++20) |
| `<fstream>` | ✅ | File stream I/O |
| `<filesystem>` | ✅ | Filesystem operations |
| `<functional>` | ✅ | Function objects and utilities |
| `<iomanip>` | ⚠️ | [Limited functionality*](#known-limitations) |
| `<ios>` | ✅ | I/O stream base classes |
| `<iosfwd>` | ✅ | Forward declarations for I/O |
| `<iostream>` | ✅ | Standard input/output streams |
| `<istream>` | ✅ | Input stream operations |
| `<iterator>` | ✅ | Iterator utilities and adaptors |
| `<latch>` | ✅ | Single-use countdown latch |
| `<limits>` | ✅ | Numeric limits |
| `<list>` | ✅ | Doubly-linked list container |
| `<locale>` | ✅ | Localization utilities |
| `<map>` | ✅ | Associative container (tree-based) |
| `<memory_resource>` | ✅ | Polymorphic memory resources |
| `<new>` | ✅ | Dynamic memory management† |
| `<numeric>` | ✅ | Numeric algorithms |
| `<optional>` | ✅ | Optional value wrapper |
| `<queue>` | ✅ | Queue and priority queue adaptors |
| `<random>` | ✅ | Random number generation |
| `<semaphore>` | ✅ | Counting semaphore |
| `<string_view>` | ✅ | Non-owning string view |
| `<syncstream>` | ✅ | Synchronized output streams |
| `<system_error>` | ✅ | System error codes |
| `<typeindex>` | ✅ | Type identification wrapper |
| `<variant>` | ✅ | Type-safe union |
| `<vector>` | ✅ | Dynamic array container |

**Special Cases:**
- † `<new>` uses `import std_module.new_;` (underscore suffix) to avoid C++ keyword conflicts
- \* See [Known Limitations](#known-limitations) for modules with reduced functionality

### Build Examples

Using the [naming conventions](#module-naming-conventions) above, here are common build patterns:

```bash
# Build only specific modules (using STD_MODULE_BUILD_<NAME> options)
cmake -B build -G Ninja \
  -DSTD_MODULE_BUILD_ALL_MODULES=OFF \
  -DSTD_MODULE_BUILD_FORMAT=ON \
  -DSTD_MODULE_BUILD_VECTOR=ON

# Link specific modules (using std_module::<name> targets)
target_link_libraries(myapp PRIVATE std_module::format std_module::vector)

# Or link everything
target_link_libraries(myapp PRIVATE std_module::all)
```

## Usage Example

```cpp
import std_module.format;

#include <iostream>

int main() {
    auto msg = std::format("Hello, {}!", "World");
    std::cout << msg << std::endl;
    return 0;
}
```

## Project Structure

```
std_module/
├── CMakeLists.txt
├── src/
│   ├── CMakeLists.txt
│   ├── algorithm.cppm
│   ├── bitset.cppm
│   ⋮
│   ├── queue.cppm
│   ├── vector.cppm
│   └── std.cppm
├── test/
│   ├── CMakeLists.txt
│   ├── test_algorithm.cpp
│   ├── test_bitset.cpp
│   ⋮
│   ├── test_queue.cpp
│   ├── test_vector.cpp
│   └── build_manual.sh
└── cmake/
```

## Known Limitations

### C++20 Module ADL Issues

Some standard library modules are affected by **Argument-Dependent Lookup (ADL) limitations** in current C++20 module implementations. This is a language/compiler issue, not a bug in this library.

**Affected Modules:**

- **`<iomanip>`** - ⚠️ **Non-functional**
  - **Problem:** I/O manipulators like `std::setw()`, `std::setfill()`, etc. return hidden implementation types
  - **Impact:** The `operator<<` overloads for these types are not found through module boundaries
  - **Status:** All manipulators are unusable when using `import std_module.iomanip;` alone
  - **Workaround:** Must `#include <iomanip>` in addition to `import` (defeats the purpose)

- **`<complex>`** - ⚠️ **Partially functional**
  - **Problem:** Arithmetic operators (`operator+`, `operator-`, etc.) not found via ADL
  - **Impact:** Cannot perform arithmetic on `std::complex` values using modules alone
  - **Status:** Construction, member functions work; operators don't

**Technical Details:**

The core issue is that non-member operator overloads and functions depending on ADL are not properly exported/found when using C++20 modules. Even when using-declarations export these symbols, the compiler's ADL mechanism doesn't find them across module boundaries.

**Reference:** https://github.com/cplusplus/papers/issues/1005

**What This Means:**

- Modules marked ⚠️ have limited functionality when using `import` alone
- Users can work around by combining `import std_module.header;` with `#include <header>`
- Module implementations are kept complete for when compiler/standard fixes arrive
- See `CLAUDE.md` for complete technical documentation

## Contributing

When adding a new stdlib header wrapper:

1. Create `src/<header>.cppm` following the pattern in `format.cppm`
2. Add build option in root `CMakeLists.txt`
3. Add library target in `src/CMakeLists.txt`
4. Add test in `test/`
5. Update this README

## Design Philosophy

This project prioritizes **flexibility over opinion**:

- No forced dependencies between modules
- Multiple integration methods supported
- Minimal assumptions about your build environment
- Opt-in module selection
- Standard library semantics preserved exactly

## License

[Add your license here]

## Status

⚠️ **Early Development** - This project is in active development. The module interface is stable, but more stdlib headers need to be wrapped.
