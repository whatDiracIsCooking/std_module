# std_module

A production-ready C++20 module wrapper for the C++ standard library. Instead of `#include <format>`, use `import std_module.format;`.

## Overview

This project provides C++20 module interfaces for 45+ standard library headers, allowing you to use modern `import` statements instead of traditional `#include` directives. The build system is designed to be flexible and non-opinionated, supporting multiple integration methods.

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

| Header | Status |
|--------|--------|
| `<algorithm>` | ✅ |
| `<any>` | ✅ |
| `<barrier>` | ✅ |
| `<bit>` | ✅ |
| `<bitset>` | ✅ |
| `<charconv>` | ✅ |
| `<compare>` | ✅ |
| `<complex>` | ✅ |
| `<concepts>` | ✅ |
| `<coroutine>` | ✅ |
| `<deque>` | ✅ |
| `<exception>` | ✅ |
| `<execution>` | ✅ |
| `<filesystem>` | ✅ |
| `<format>` | ✅ |
| `<fstream>` | ✅ |
| `<functional>` | ✅ |
| `<iomanip>` | ⚠️ |
| `<ios>` | ✅ |
| `<iosfwd>` | ✅ |
| `<iostream>` | ✅ |
| `<istream>` | ✅ |
| `<iterator>` | ✅ |
| `<latch>` | ✅ |
| `<limits>` | ✅ |
| `<list>` | ✅ |
| `<locale>` | ✅ |
| `<map>` | ✅ |
| `<memory_resource>` | ✅ |
| `<new>` | ✅ |
| `<numbers>` | ✅ |
| `<numeric>` | ✅ |
| `<optional>` | ✅ |
| `<queue>` | ✅ |
| `<random>` | ✅ |
| `<ranges>` | ✅ |
| `<semaphore>` | ✅ |
| `<source_location>` | ✅ |
| `<span>` | ✅ |
| `<string_view>` | ✅ |
| `<syncstream>` | ✅ |
| `<system_error>` | ✅ |
| `<typeindex>` | ✅ |
| `<variant>` | ✅ |
| `<vector>` | ✅ |

**Special Cases:**
- `<new>` uses `import std_module.new_;` (underscore suffix) to avoid C++ keyword conflicts
- `<iomanip>` marked ⚠️ - see [Known Limitations](#known-limitations) for details

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

1. Create `src/<header>.cppm` following the pattern in existing modules
2. Add one line to `src/CMakeLists.txt`: `std_module_add_module(<header>)`
3. Add one line to `src/CMakeLists.txt` (aggregate section): `std_module_add_to_aggregate(<header>)`
4. Create `test/test_<header>.cpp` with comprehensive tests
5. Add one line to `test/CMakeLists.txt`: `std_module_add_test(<header>)`
6. Update this README

See `CLAUDE.md` for detailed development guidelines.

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

✅ **Production Ready** - 45 standard library modules implemented with comprehensive test coverage. The module interface is stable and ready for use in production code.
