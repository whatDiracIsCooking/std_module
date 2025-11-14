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
| `STD_MODULE_BUILD_DEQUE` | ON | Build std_module.deque |

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
- ✅ `<deque>` → `import std_module.deque;`

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
│   └── std.cppm           # Aggregate module (WIP)
├── test/                   # Tests and examples
│   ├── CMakeLists.txt
│   ├── test_format.cpp
│   ├── test_vector.cpp
│   ├── test_algorithm.cpp
│   ├── test_bitset.cpp
│   ├── test_string_view.cpp
│   └── build_manual.sh    # Manual build demo
└── cmake/                  # CMake configuration files
```

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
