# std_module

A C++20 module wrapper for the C++ standard library. Use `import std_module.format;` instead of `#include <format>`.

## Status

✅ **Production Ready** - 49 standard library modules implemented with comprehensive test coverage.

## Requirements

- CMake 3.28+
- Ninja build system (required for C++20 modules)
- C++20 compiler with module support:
  - Clang 16+ (recommended)
  - GCC 11+ (experimental)
  - MSVC 19.30+ (Visual Studio 2022)

## Quick Start

```bash
# Configure (Ninja generator is required)
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++

# Build
cmake --build build

# Run tests
ctest --test-dir build --output-on-failure

# Install (optional)
cmake --install build --prefix /usr/local
```

## Usage Example

```cpp
import std_module.format;
import std_module.vector;

#include <iostream>  // Still needed for non-modularized components

int main() {
    std::vector<int> numbers = {1, 2, 3};
    auto msg = std::format("Numbers: {}", numbers.size());
    std::cout << msg << std::endl;
    return 0;
}
```

## Integration Methods

### Method 1: CMake Subdirectory

```cmake
add_subdirectory(external/std_module)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE
    std_module::format
    std_module::vector
)
```

### Method 2: Installed Library

```cmake
find_package(std_module REQUIRED COMPONENTS format vector)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE std_module::format std_module::vector)
```

### Method 3: Manual Compilation

See [`test/README.md`](test/README.md) for manual build instructions.

## CMake Options

**Global Options:**
- `STD_MODULE_BUILD_TESTS` - Build test executables (default: ON)
- `STD_MODULE_BUILD_ALL_MODULES` - Build all available modules (default: ON)
- `STD_MODULE_BUILD_INSTALL` - Generate installation targets (default: ON)

**Per-Module Options:**

Each module has a build option following the pattern `STD_MODULE_BUILD_<NAME>` (all default to ON). For example:
- `STD_MODULE_BUILD_FORMAT` - Build the format module
- `STD_MODULE_BUILD_VECTOR` - Build the vector module
- `STD_MODULE_BUILD_RANGES` - Build the ranges module

See [Available Modules](#available-modules) below for the complete list.

**Examples:**

```bash
# Build only specific modules
cmake -B build -G Ninja \
  -DSTD_MODULE_BUILD_ALL_MODULES=OFF \
  -DSTD_MODULE_BUILD_FORMAT=ON \
  -DSTD_MODULE_BUILD_VECTOR=ON

# Build everything except iomanip
cmake -B build -G Ninja -DSTD_MODULE_BUILD_IOMANIP=OFF

# Build without tests
cmake -B build -G Ninja -DSTD_MODULE_BUILD_TESTS=OFF
```

## Library Targets

All modules follow the naming pattern `std_module::<name>`. For example:
- `std_module::format` - The format module
- `std_module::vector` - The vector module
- `std_module::ranges` - The ranges module
- `std_module::all` - All available modules (convenience target)

Link only what you need:

```cmake
# Link specific modules
target_link_libraries(myapp PRIVATE std_module::format std_module::vector)

# Or link everything
target_link_libraries(myapp PRIVATE std_module::all)
```

## Module Naming Conventions

- **Import statement:** `import std_module.<name>;`
- **CMake target:** `std_module::<name>`
- **CMake option:** `STD_MODULE_BUILD_<NAME>`
- **Source file:** `src/<name>.cppm`
- **Test file:** `test/test_<name>.cpp`

**Special case:** `<new>` uses `std_module.new_` (with underscore) to avoid C++ keyword conflicts.

## Available Modules

Currently wrapped standard library headers (49 modules):

| Header | Module | Status | Notes |
|--------|--------|--------|-------|
| `<algorithm>` | `std_module.algorithm` | ✅ | |
| `<any>` | `std_module.any` | ✅ | |
| `<barrier>` | `std_module.barrier` | ✅ | |
| `<bit>` | `std_module.bit` | ✅ | |
| `<bitset>` | `std_module.bitset` | ✅ | |
| `<charconv>` | `std_module.charconv` | ✅ | |
| `<compare>` | `std_module.compare` | ✅ | |
| `<complex>` | `std_module.complex` | ✅ | |
| `<concepts>` | `std_module.concepts` | ✅ | |
| `<condition_variable>` | `std_module.condition_variable` | ✅ | |
| `<coroutine>` | `std_module.coroutine` | ✅ | |
| `<deque>` | `std_module.deque` | ✅ | |
| `<exception>` | `std_module.exception` | ✅ | |
| `<execution>` | `std_module.execution` | ✅ | |
| `<filesystem>` | `std_module.filesystem` | ✅ | |
| `<format>` | `std_module.format` | ✅ | |
| `<forward_list>` | `std_module.forward_list` | ✅ | |
| `<fstream>` | `std_module.fstream` | ✅ | |
| `<functional>` | `std_module.functional` | ✅ | |
| `<future>` | `std_module.future` | ⚠️ | `packaged_task` unusable due to C++20 module limitations |
| `<initializer_list>` | `std_module.initializer_list` | ✅ | |
| `<iomanip>` | `std_module.iomanip` | ⚠️ | Manipulators unusable - see [Known Limitations](#known-limitations) |
| `<ios>` | `std_module.ios` | ✅ | |
| `<iosfwd>` | `std_module.iosfwd` | ✅ | |
| `<iostream>` | `std_module.iostream` | ✅ | |
| `<istream>` | `std_module.istream` | ✅ | |
| `<iterator>` | `std_module.iterator` | ✅ | |
| `<latch>` | `std_module.latch` | ✅ | |
| `<limits>` | `std_module.limits` | ✅ | |
| `<list>` | `std_module.list` | ✅ | |
| `<locale>` | `std_module.locale` | ✅ | |
| `<map>` | `std_module.map` | ✅ | |
| `<memory_resource>` | `std_module.memory_resource` | ✅ | |
| `<new>` | `std_module.new_` | ✅ | Note: underscore suffix to avoid keyword conflict |
| `<numbers>` | `std_module.numbers` | ✅ | |
| `<numeric>` | `std_module.numeric` | ✅ | |
| `<optional>` | `std_module.optional` | ✅ | |
| `<queue>` | `std_module.queue` | ✅ | |
| `<random>` | `std_module.random` | ✅ | |
| `<ranges>` | `std_module.ranges` | ✅ | |
| `<semaphore>` | `std_module.semaphore` | ✅ | |
| `<source_location>` | `std_module.source_location` | ✅ | |
| `<span>` | `std_module.span` | ✅ | |
| `<string_view>` | `std_module.string_view` | ✅ | |
| `<syncstream>` | `std_module.syncstream` | ✅ | |
| `<system_error>` | `std_module.system_error` | ✅ | |
| `<typeindex>` | `std_module.typeindex` | ✅ | |
| `<variant>` | `std_module.variant` | ✅ | |
| `<vector>` | `std_module.vector` | ✅ | |

## Project Structure

```
std_module/
├── CMakeLists.txt          # Root build configuration
├── README.md               # This file
├── CLAUDE.md              # AI assistant development guide
├── src/                    # Module implementations (.cppm files)
│   ├── CMakeLists.txt
│   ├── format.cppm
│   ├── vector.cppm
│   ⋮
│   └── std.cppm           # Aggregate module (WIP)
├── test/                   # Test suite
│   ├── CMakeLists.txt
│   ├── README.md          # Manual build documentation
│   ├── test_format.cpp
│   ├── test_vector.cpp
│   ⋮
│   └── build_manual.sh    # Manual build demo script
├── cmake/                  # CMake infrastructure
│   ├── StdModuleMacros.cmake
│   └── std_module-config.cmake.in
└── scripts/                # Automation tools
    ├── README.md
    └── symbol_coverage.py  # Symbol coverage analyzer
```

## Known Limitations

### C++20 Module ADL Issues

Some modules are affected by **Argument-Dependent Lookup (ADL) limitations** in current C++20 module implementations. This is a language/compiler issue, not a bug in this library.

**Affected Modules:**

- **`<iomanip>`** ⚠️ - I/O manipulators like `std::setw()` return hidden implementation types whose `operator<<` overloads are not found through module boundaries. Manipulators are unusable with modules alone.

- **`<future>`** ⚠️ - `std::packaged_task` internal machinery not properly exposed. Other components (`promise`, `future`, `shared_future`, `async`) work correctly.

**Workaround:** Combine `import std_module.header;` with `#include <header>` if needed.

**Reference:** https://github.com/cplusplus/papers/issues/1005

See `CLAUDE.md` for complete technical documentation.

## Contributing

To add a new standard library header wrapper:

1. Create `src/<header>.cppm` following existing patterns
2. Add to `src/CMakeLists.txt`: `std_module_add_module(<header>)`
3. Add to `src/CMakeLists.txt` (aggregate section): `std_module_add_to_aggregate(<header>)`
4. Create `test/test_<header>.cpp` with comprehensive tests
5. Add to `test/CMakeLists.txt`: `std_module_add_test(<header>)`
6. Update this README's [Available Modules](#available-modules) table

See `CLAUDE.md` for detailed development guidelines.

## Design Philosophy

This project prioritizes **flexibility over opinion**:

- No forced dependencies between modules
- Multiple integration methods supported
- Opt-in module selection (build only what you need)
- Standard library semantics preserved exactly (no modifications)

## License

[Add your license here]
