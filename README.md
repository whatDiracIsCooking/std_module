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

## CMake Options

Configure the build with these options:

| Option | Default | Description |
|--------|---------|-------------|
| `STD_MODULE_BUILD_TESTS` | ON | Build test executables |
| `STD_MODULE_BUILD_ALL_MODULES` | ON | Build all available modules |
| `STD_MODULE_INSTALL` | ON | Generate installation targets |
| `STD_MODULE_BUILD_FORMAT` | ON | Build std_module.format |
| `STD_MODULE_BUILD_VECTOR` | ON | Build std_module.vector |
| `STD_MODULE_BUILD_ALGORITHM` | ON | Build std_module.algorithm |
| `STD_MODULE_BUILD_BITSET` | ON | Build std_module.bitset |
| `STD_MODULE_BUILD_STRING_VIEW` | ON | Build std_module.string_view |
| `STD_MODULE_BUILD_EXCEPTION` | ON | Build std_module.exception |
| `STD_MODULE_BUILD_COMPLEX` | ON | Build std_module.complex |
| `STD_MODULE_BUILD_DEQUE` | ON | Build std_module.deque |
| `STD_MODULE_BUILD_FSTREAM` | ON | Build std_module.fstream |
| `STD_MODULE_BUILD_FUNCTIONAL` | ON | Build std_module.functional |
| `STD_MODULE_BUILD_IOMANIP` | ON | Build std_module.iomanip |
| `STD_MODULE_BUILD_IOS` | ON | Build std_module.ios |
| `STD_MODULE_BUILD_IOSFWD` | ON | Build std_module.iosfwd |
| `STD_MODULE_BUILD_IOSTREAM` | ON | Build std_module.iostream |

Example:

```bash
cmake -B build \
  -DSTD_MODULE_BUILD_TESTS=OFF \
  -DSTD_MODULE_BUILD_ALL_MODULES=OFF \
  -DSTD_MODULE_BUILD_FORMAT=ON
```

## Available Modules

Currently wrapped standard library headers:

- ✅ `<format>` → `import std_module.format;`
- ✅ `<vector>` → `import std_module.vector;`
- ✅ `<algorithm>` → `import std_module.algorithm;`
- ✅ `<bitset>` → `import std_module.bitset;`
- ✅ `<string_view>` → `import std_module.string_view;`
- ✅ `<exception>` → `import std_module.exception;`
- ✅ `<complex>` → `import std_module.complex;`
- ✅ `<deque>` → `import std_module.deque;`
- ✅ `<fstream>` → `import std_module.fstream;`
- ✅ `<functional>` → `import std_module.functional;`
- ⚠️ `<iomanip>` → `import std_module.iomanip;` **(non-functional - see [limitations](#known-limitations))**
- ✅ `<ios>` → `import std_module.ios;`
- ✅ `<iosfwd>` → `import std_module.iosfwd;`
- ✅ `<iostream>` → `import std_module.iostream;`

*More modules coming soon!*

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

## Library Targets

The build system provides these CMake targets:

- `std_module::format` - Just the format module
- `std_module::vector` - Just the vector module
- `std_module::algorithm` - Just the algorithm module
- `std_module::bitset` - Just the bitset module
- `std_module::string_view` - Just the string_view module
- `std_module::exception` - Just the exception module
- `std_module::complex` - Just the complex module
- `std_module::deque` - Just the deque module
- `std_module::fstream` - Just the fstream module
- `std_module::functional` - Just the functional module
- `std_module::iomanip` - Just the iomanip module
- `std_module::ios` - Just the ios module
- `std_module::iosfwd` - Just the iosfwd module
- `std_module::iostream` - Just the iostream module
- `std_module::all` - All available modules (convenience target)

Link only what you need:

```cmake
# Link specific modules
target_link_libraries(myapp PRIVATE std_module::format)
target_link_libraries(myapp PRIVATE std_module::vector)
target_link_libraries(myapp PRIVATE std_module::algorithm)
target_link_libraries(myapp PRIVATE std_module::string_view)

# Or link everything
target_link_libraries(myapp PRIVATE std_module::all)
```

## Project Structure

```
std_module/
├── CMakeLists.txt          # Root build configuration
├── src/                    # Module implementations
│   ├── CMakeLists.txt
│   ├── format.cppm         # <format> wrapper
│   ├── vector.cppm         # <vector> wrapper
│   ├── algorithm.cppm      # <algorithm> wrapper
│   ├── bitset.cppm         # <bitset> wrapper
│   ├── string_view.cppm    # <string_view> wrapper
│   ├── exception.cppm      # <exception> wrapper
│   ├── complex.cppm        # <complex> wrapper
│   ├── deque.cppm          # <deque> wrapper
│   ├── fstream.cppm        # <fstream> wrapper
│   ├── functional.cppm     # <functional> wrapper
│   ├── iomanip.cppm        # <iomanip> wrapper
│   ├── ios.cppm            # <ios> wrapper
│   ├── iosfwd.cppm         # <iosfwd> wrapper
│   ├── iostream.cppm       # <iostream> wrapper
│   └── std.cppm           # Aggregate module (WIP)
├── test/                   # Tests and examples
│   ├── CMakeLists.txt
│   ├── test_format.cpp
│   ├── test_vector.cpp
│   ├── test_algorithm.cpp
│   ├── test_bitset.cpp
│   ├── test_string_view.cpp
│   ├── test_exception.cpp
│   ├── test_complex.cpp
│   ├── test_deque.cpp
│   ├── test_fstream.cpp
│   ├── test_functional.cpp
│   ├── test_iomanip.cpp
│   ├── test_ios.cpp
│   ├── test_iosfwd.cpp
│   ├── test_iostream.cpp
│   └── build_manual.sh    # Manual build demo
└── cmake/                  # CMake configuration files
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
