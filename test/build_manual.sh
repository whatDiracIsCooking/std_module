#!/bin/bash
# Manual build script for testing C++20 modules
# This demonstrates the build process before automating it

set -e  # Exit on error

echo "=== Building std_module manually ==="
echo ""

# Compiler selection (try clang++ first, fall back to g++)
if command -v clang++ &> /dev/null; then
    CXX=clang++
    echo "Using clang++"
elif command -v g++ &> /dev/null; then
    CXX=g++
    echo "Using g++"
else
    echo "Error: No suitable C++ compiler found"
    exit 1
fi

# Compiler version check
echo "Compiler version:"
$CXX --version | head -n 1
echo ""

# Build flags
CXXFLAGS="-std=c++20"

# Step 1: Precompile the format module interface
echo "Step 1: Precompiling format.cppm module interface..."
$CXX $CXXFLAGS -x c++-module ../src/format.cppm --precompile -o format.pcm
echo "  ✓ format.pcm created"
echo ""

# Step 2: Compile the precompiled module to object file
echo "Step 2: Compiling module to object file..."
$CXX $CXXFLAGS -c format.pcm -o format.o
echo "  ✓ format.o created"
echo ""

# Step 3: Compile the test program
echo "Step 3: Compiling test_format.cpp..."
$CXX $CXXFLAGS -fmodule-file=std_module.format=format.pcm -c test_format.cpp -o test_format.o
echo "  ✓ test_format.o created"
echo ""

# Step 4: Link everything together
echo "Step 4: Linking..."
$CXX $CXXFLAGS format.o test_format.o -o test_format
echo "  ✓ test_format executable created"
echo ""

# Step 5: Run the test
echo "Step 5: Running test..."
echo "---"
./test_format
echo "---"
echo ""

echo "=== Build and test successful! ==="
