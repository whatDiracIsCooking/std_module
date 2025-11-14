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

## Available Modules

| Header | Status | CMake Option | CMake Target | Import Statement |
|--------|--------|--------------|--------------|------------------|
| *(General options)* | | `STD_MODULE_BUILD_TESTS=ON` | | Build test executables |
| | | `STD_MODULE_BUILD_ALL_MODULES=ON` | | Build all modules |
| | | `STD_MODULE_INSTALL=ON` | | Generate install targets |
| `<algorithm>` | ✅ | `STD_MODULE_BUILD_ALGORITHM=ON` | `std_module::algorithm` | `import std_module.algorithm;` |
| `<bitset>` | ✅ | `STD_MODULE_BUILD_BITSET=ON` | `std_module::bitset` | `import std_module.bitset;` |
| `<complex>` | ✅ | `STD_MODULE_BUILD_COMPLEX=ON` | `std_module::complex` | `import std_module.complex;` |
| `<deque>` | ✅ | `STD_MODULE_BUILD_DEQUE=ON` | `std_module::deque` | `import std_module.deque;` |
| `<exception>` | ✅ | `STD_MODULE_BUILD_EXCEPTION=ON` | `std_module::exception` | `import std_module.exception;` |
| `<format>` | ✅ | `STD_MODULE_BUILD_FORMAT=ON` | `std_module::format` | `import std_module.format;` |
| `<fstream>` | ✅ | `STD_MODULE_BUILD_FSTREAM=ON` | `std_module::fstream` | `import std_module.fstream;` |
| `<functional>` | ✅ | `STD_MODULE_BUILD_FUNCTIONAL=ON` | `std_module::functional` | `import std_module.functional;` |
| `<iomanip>` | ⚠️ | `STD_MODULE_BUILD_IOMANIP=ON` | `std_module::iomanip` | `import std_module.iomanip;` [*](#known-limitations) |
| `<ios>` | ✅ | `STD_MODULE_BUILD_IOS=ON` | `std_module::ios` | `import std_module.ios;` |
| `<iosfwd>` | ✅ | `STD_MODULE_BUILD_IOSFWD=ON` | `std_module::iosfwd` | `import std_module.iosfwd;` |
| `<iostream>` | ✅ | `STD_MODULE_BUILD_IOSTREAM=ON` | `std_module::iostream` | `import std_module.iostream;` |
| `<istream>` | ✅ | `STD_MODULE_BUILD_ISTREAM=ON` | `std_module::istream` | `import std_module.istream;` |
| `<iterator>` | ✅ | `STD_MODULE_BUILD_ITERATOR=ON` | `std_module::iterator` | `import std_module.iterator;` |
| `<limits>` | ✅ | `STD_MODULE_BUILD_LIMITS=ON` | `std_module::limits` | `import std_module.limits;` |
| `<list>` | ✅ | `STD_MODULE_BUILD_LIST=ON` | `std_module::list` | `import std_module.list;` |
| `<locale>` | ✅ | `STD_MODULE_BUILD_LOCALE=ON` | `std_module::locale` | `import std_module.locale;` |
| `<map>` | ✅ | `STD_MODULE_BUILD_MAP=ON` | `std_module::map` | `import std_module.map;` |
| `<memory>` | ✅ | `STD_MODULE_BUILD_MEMORY=ON` | `std_module::memory` | `import std_module.memory;` |
| `<new>` | ✅ | `STD_MODULE_BUILD_NEW=ON` | `std_module::new` | `import std_module.new_;` [†](#notes) |
| `<numeric>` | ✅ | `STD_MODULE_BUILD_NUMERIC=ON` | `std_module::numeric` | `import std_module.numeric;` |
| `<optional>` | ✅ | `STD_MODULE_BUILD_OPTIONAL=ON` | `std_module::optional` | `import std_module.optional;` |
| `<ostream>` | ✅ | `STD_MODULE_BUILD_OSTREAM=ON` | `std_module::ostream` | `import std_module.ostream;` |
| `<queue>` | ✅ | `STD_MODULE_BUILD_QUEUE=ON` | `std_module::queue` | `import std_module.queue;` |
| `<set>` | ✅ | `STD_MODULE_BUILD_SET=ON` | `std_module::set` | `import std_module.set;` |
| `<stack>` | ✅ | `STD_MODULE_BUILD_STACK=ON` | `std_module::stack` | `import std_module.stack;` |
| `<stdexcept>` | ✅ | `STD_MODULE_BUILD_STDEXCEPT=ON` | `std_module::stdexcept` | `import std_module.stdexcept;` |
| `<streambuf>` | ✅ | `STD_MODULE_BUILD_STREAMBUF=ON` | `std_module::streambuf` | `import std_module.streambuf;` |
| `<string>` | ✅ | `STD_MODULE_BUILD_STRING=ON` | `std_module::string` | `import std_module.string;` |
| `<string_view>` | ✅ | `STD_MODULE_BUILD_STRING_VIEW=ON` | `std_module::string_view` | `import std_module.string_view;` |
| `<vector>` | ✅ | `STD_MODULE_BUILD_VECTOR=ON` | `std_module::vector` | `import std_module.vector;` |
| *(Convenience)* | | | `std_module::all` | All modules combined |

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
├── CMakeLists.txt
├── src/
│   ├── CMakeLists.txt
│   ├── algorithm.cppm
│   ├── bitset.cppm
│   ├── complex.cppm
│   ├── deque.cppm
│   ├── exception.cppm
│   ├── format.cppm
│   ├── fstream.cppm
│   ├── functional.cppm
│   ├── iomanip.cppm
│   ├── ios.cppm
│   ├── iosfwd.cppm
│   ├── iostream.cppm
│   ├── istream.cppm
│   ├── iterator.cppm
│   ├── limits.cppm
│   ├── list.cppm
│   ├── locale.cppm
│   ├── map.cppm
│   ├── memory.cppm
│   ├── new.cppm
│   ├── numeric.cppm
│   ├── optional.cppm
│   ├── ostream.cppm
│   ├── queue.cppm
│   ├── set.cppm
│   ├── stack.cppm
│   ├── stdexcept.cppm
│   ├── streambuf.cppm
│   ├── string.cppm
│   ├── string_view.cppm
│   ├── vector.cppm
│   └── std.cppm
├── test/
│   ├── CMakeLists.txt
│   ├── test_algorithm.cpp
│   ├── test_bitset.cpp
│   ├── test_complex.cpp
│   ├── test_deque.cpp
│   ├── test_exception.cpp
│   ├── test_format.cpp
│   ├── test_fstream.cpp
│   ├── test_functional.cpp
│   ├── test_iomanip.cpp
│   ├── test_ios.cpp
│   ├── test_iosfwd.cpp
│   ├── test_iostream.cpp
│   ├── test_istream.cpp
│   ├── test_iterator.cpp
│   ├── test_limits.cpp
│   ├── test_list.cpp
│   ├── test_locale.cpp
│   ├── test_map.cpp
│   ├── test_memory.cpp
│   ├── test_new.cpp
│   ├── test_numeric.cpp
│   ├── test_optional.cpp
│   ├── test_ostream.cpp
│   ├── test_queue.cpp
│   ├── test_set.cpp
│   ├── test_stack.cpp
│   ├── test_stdexcept.cpp
│   ├── test_streambuf.cpp
│   ├── test_string.cpp
│   ├── test_string_view.cpp
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
