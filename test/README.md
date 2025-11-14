# Manual Build Test

This directory contains minimal tests to validate the module setup before creating a full build system.

## Files

- **test_format.cpp** - Simple test that uses `std_module.format`
- **build_manual.sh** - Shell script showing manual compilation steps
- **README.md** - This file

## Manual Build Process

### Prerequisites

You need a C++20 compatible compiler with modules support:
- **Clang 16+** (recommended)
- **GCC 11+** (experimental modules support)

### Building and Running

```bash
cd test
./build_manual.sh
```

### What the Build Script Does

1. **Compiles the module** (`format.cppm`) into a Binary Module Interface (`.pcm` file)
2. **Compiles the test program** that imports the module
3. **Links and creates** the test executable
4. **Runs the test** to verify everything works

### Expected Output

```
Hello, World!
The answer is 42 and pi is approximately 3.14
first comes before second
All tests passed!
```

## Manual Commands (for reference)

If you want to build manually without the script:

```bash
# Step 1: Precompile the module interface
clang++ -std=c++20 -x c++-module ../src/format.cppm --precompile -o format.pcm

# Step 2: Compile the module to object file
clang++ -std=c++20 -c format.pcm -o format.o

# Step 3: Compile the test program (with module mapping)
clang++ -std=c++20 -fmodule-file=std_module.format=format.pcm -c test_format.cpp -o test_format.o

# Step 4: Link everything together
clang++ -std=c++20 format.o test_format.o -o test_format

# Step 5: Run
./test_format
```

## Notes

- Module compilation creates `.pcm` files (precompiled module interfaces)
- The `-fmodule-file=<module-name>=<pcm-file>` flag tells the compiler where to find imported modules
- Both the module and the test program need to be compiled to object files before linking
- Different compilers may use different flags and file extensions
- Warnings from the standard library implementation itself are normal and can be ignored
