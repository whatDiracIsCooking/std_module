# std_module

A C++20 module wrapper for the C++ standard library. Instead of `#include <format>`, use `import std_module.format;`.

## Overview

This project provides C++20 module interfaces for the C++ standard library, allowing you to use `import` statements instead of traditional `#include` directives. The build system is designed to be flexible and non-opinionated, supporting multiple integration methods.

## Features

- **Comprehensive**: 72 standard library modules with full test coverage
- **Modular**: Import only what you need (`import std_module.format;`)
- **Flexible Build System**: Use as subdirectory, installed library, or manual compilation
- **Compiler Support**: Clang 16+, GCC 11+, MSVC 19.30+ (tested on multiple stdlib combinations)
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

## Available Modules

**72 modules implemented** with comprehensive tests. The table below is the **single source of truth** for all available modules.

**Global Build Options:**
- `STD_MODULE_BUILD_TESTS=ON` - Build test executables
- `STD_MODULE_BUILD_ALL_MODULES=ON` - Build all modules (default)
- `STD_MODULE_INSTALL=ON` - Generate installation targets

**Per-Module Pattern:**
- CMake Option: `STD_MODULE_BUILD_<NAME>=ON` (all default ON)
- CMake Target: `std_module::<name>`
- Import Statement: `import std_module.<name>;`

| Header | Status | Notes |
|--------|--------|-------|
| `<algorithm>` | ✅ | Algorithms library |
| `<any>` | ✅ | Type-safe container for single values |
| `<array>` | ✅ | Fixed-size arrays |
| `<atomic>` | ✅ | Atomic operations |
| `<barrier>` | ✅ | Thread coordination (C++20) |
| `<bit>` | ✅ | Bit manipulation (C++20) |
| `<bitset>` | ✅ | Fixed-size bit arrays |
| `<charconv>` | ✅ | Low-level numeric conversions |
| `<chrono>` | ✅ | Time utilities |
| `<codecvt>` | ✅ | Character encoding conversion |
| `<compare>` | ✅ | Three-way comparison (C++20) |
| `<complex>` | ✅ | Complex numbers |
| `<concepts>` | ✅ | Concept definitions (C++20) |
| `<condition_variable>` | ✅ | Thread synchronization |
| `<coroutine>` | ✅ | Coroutine support (C++20) |
| `<deque>` | ✅ | Double-ended queue |
| `<exception>` | ✅ | Exception handling |
| `<execution>` | ✅ | Parallel algorithm policies |
| `<filesystem>` | ✅ | Filesystem library |
| `<format>` | ✅ | Text formatting (C++20) |
| `<forward_list>` | ✅ | Singly-linked list |
| `<fstream>` | ✅ | File streams |
| `<functional>` | ✅ | Function objects |
| `<future>` | ⚠️ | Async operations (`packaged_task` broken) |
| `<initializer_list>` | ✅ | Initializer list support |
| `<iomanip>` | ⚠️ | I/O manipulators (ADL limitations) |
| `<ios>` | ✅ | I/O base classes |
| `<iosfwd>` | ✅ | Forward declarations for I/O |
| `<iostream>` | ✅ | Standard I/O streams |
| `<istream>` | ✅ | Input streams |
| `<iterator>` | ✅ | Iterator utilities |
| `<latch>` | ✅ | Single-use thread barrier (C++20) |
| `<limits>` | ✅ | Numeric limits |
| `<list>` | ✅ | Doubly-linked list |
| `<locale>` | ✅ | Localization |
| `<map>` | ✅ | Associative containers (map, multimap) |
| `<memory>` | ✅ | Memory management |
| `<memory_resource>` | ✅ | Polymorphic allocators |
| `<mutex>` | ✅ | Mutual exclusion |
| `<new>` | ✅ | Dynamic memory (import as `std_module.new_`) |
| `<numbers>` | ✅ | Mathematical constants (C++20) |
| `<numeric>` | ✅ | Numeric operations |
| `<optional>` | ✅ | Optional values |
| `<ostream>` | ✅ | Output streams |
| `<queue>` | ✅ | Queue adapters |
| `<random>` | ✅ | Random number generation |
| `<ranges>` | ✅ | Ranges library (C++20) |
| `<ratio>` | ✅ | Compile-time rational arithmetic |
| `<regex>` | ✅ | Regular expressions |
| `<scoped_allocator>` | ✅ | Nested allocator support |
| `<semaphore>` | ✅ | Semaphores (C++20) |
| `<set>` | ✅ | Associative containers (set, multiset) |
| `<source_location>` | ✅ | Source code location (C++20) |
| `<span>` | ✅ | Non-owning array view (C++20) |
| `<stack>` | ✅ | Stack adapter |
| `<stdexcept>` | ✅ | Standard exceptions |
| `<streambuf>` | ✅ | Stream buffers |
| `<string>` | ✅ | String class |
| `<string_view>` | ✅ | Non-owning string view |
| `<syncstream>` | ✅ | Synchronized output streams (C++20) |
| `<system_error>` | ✅ | System error support |
| `<thread>` | ✅ | Threading |
| `<tuple>` | ✅ | Tuple type |
| `<type_traits>` | ✅ | Type trait utilities |
| `<typeindex>` | ✅ | Type index wrapper |
| `<typeinfo>` | ✅ | Runtime type information |
| `<unordered_map>` | ✅ | Hash maps |
| `<unordered_set>` | ✅ | Hash sets |
| `<valarray>` | ✅ | Numeric arrays |
| `<variant>` | ✅ | Type-safe unions |
| `<vector>` | ✅ | Dynamic arrays |

**Special Targets:**
- `std_module::all` - Convenience target that links all modules

**Build examples:**

```bash
# Build only specific modules
cmake -B build -G Ninja \
  -DSTD_MODULE_BUILD_ALL_MODULES=OFF \
  -DSTD_MODULE_BUILD_FORMAT=ON \
  -DSTD_MODULE_BUILD_VECTOR=ON

# Link specific modules
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
├── CMakeLists.txt              # Root build configuration
├── README.md                   # This file
├── CLAUDE.md                   # Comprehensive AI assistant guide
├── src/                        # Module implementations (72 .cppm files)
│   ├── CMakeLists.txt
│   ├── algorithm.cppm
│   ├── format.cppm
│   ├── vector.cppm
│   ⋮                           # ... 69 more modules
│   └── std.cppm
├── test/                       # Test suite (71 test files)
│   ├── CMakeLists.txt
│   ├── test_algorithm.cpp
│   ├── test_format.cpp
│   ├── test_vector.cpp
│   ⋮                           # ... 68 more tests
│   ├── build_manual.sh         # Manual compilation demo
│   └── README.md               # Manual build documentation
├── cmake/                      # CMake infrastructure
│   ├── StdModuleMacros.cmake
│   └── std_module-config.cmake.in
└── scripts/                    # Automation tools
    ├── symbol_coverage.py      # Symbol coverage analyzer
    └── README.md
```

## Known Limitations

Two modules have minor limitations:

- **`<iomanip>`** (⚠️) - I/O manipulators like `std::setw()`, `std::setfill()` have limited functionality
- **`<future>`** (⚠️) - `std::packaged_task` is not functional; other async components work

All other 70 modules are fully functional with pure module-only usage (no `#include` needed).

## Contributing

When adding a new stdlib header wrapper:

1. Create `src/<header>.cppm` following the pattern in existing modules
2. Add one line to `src/CMakeLists.txt`: `std_module_add_module(header)`
3. Add one line to `test/CMakeLists.txt`: `std_module_add_test(header)`
4. Create `test/test_<header>.cpp` with comprehensive tests
5. Update the "Available Modules" table in this README
6. **Remember to export operators** for ADL functionality!

See `CLAUDE.md` for detailed contributor guidelines and patterns.

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

✅ **Production-ready** - 72 standard library modules implemented with comprehensive tests. The module interface is stable and tested across multiple compiler/stdlib combinations (Clang, GCC, libstdc++, libc++).
