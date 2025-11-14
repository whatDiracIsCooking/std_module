# Dockerfile for building and testing std_module C++20 library
# This container provides a complete environment for building and testing the project

FROM ubuntu:24.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    clang-18 \
    cmake \
    ninja-build \
    python3 \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set Clang 18 as the default C++ compiler
ENV CXX=clang++-18
ENV CC=clang-18

# Create working directory
WORKDIR /workspace

# Copy project files
COPY . .

# Configure the build with Ninja generator and Clang
RUN cmake -B build -G Ninja \
    -DCMAKE_CXX_COMPILER=clang++-18 \
    -DCMAKE_BUILD_TYPE=Release \
    -DSTD_MODULE_BUILD_TESTS=ON \
    -DSTD_MODULE_BUILD_ALL_MODULES=ON

# Build all modules and tests
RUN cmake --build build --parallel

# Run tests by default when container starts
CMD ["ctest", "--test-dir", "build", "--output-on-failure", "--parallel"]

# Alternative: Run tests during build (uncomment if desired)
# RUN ctest --test-dir build --output-on-failure

# Usage:
# Build the image:
#   docker build -t std_module -f docker/Dockerfile .
#
# Run tests:
#   docker run --rm std_module
#
# Interactive shell:
#   docker run --rm -it std_module /bin/bash
#
# Run specific test:
#   docker run --rm std_module ctest --test-dir build -R test_format --output-on-failure
