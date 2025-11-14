# Dockerfile for building and testing std_module C++20 library
# This container provides a complete environment for building and testing the project

FROM ubuntu:24.04

# Clang version to install (can be overridden at build time)
ARG CLANG_VERSION=18

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install base build dependencies (cached layer for faster clang version changes)
RUN apt-get update && apt-get install -y \
    cmake \
    ninja-build \
    python3 \
    git \
    && rm -rf /var/lib/apt/lists/*

# Install clang packages (separate layer allows fast rebuilds when testing different versions)
RUN apt-get update && apt-get install -y \
    clang-${CLANG_VERSION} \
    clang-tools-${CLANG_VERSION} \
    && rm -rf /var/lib/apt/lists/*

# Set Clang as the default C++ compiler
ENV CXX=clang++-${CLANG_VERSION}
ENV CC=clang-${CLANG_VERSION}

# Create working directory
WORKDIR /workspace

# Copy project files
COPY . .

# Configure the build with Ninja generator and Clang
RUN cmake -B build-clang-${CLANG_VERSION} -G Ninja \
    -DCMAKE_CXX_COMPILER=clang++-${CLANG_VERSION} \
    -DCMAKE_BUILD_TYPE=Release \
    -DSTD_MODULE_BUILD_TESTS=ON \
    -DSTD_MODULE_BUILD_ALL_MODULES=ON

# Build all modules and tests
RUN cmake --build build-clang-${CLANG_VERSION} --parallel

# Run tests during build (ensures build fails if tests fail)
RUN ctest --test-dir build-clang-${CLANG_VERSION} --output-on-failure

# Run tests by default when container starts (optional - can be overridden)
CMD ["sh", "-c", "ctest --test-dir build-clang-${CLANG_VERSION} --output-on-failure --parallel"]

# Usage:
# Build the image (default Clang 18):
#   docker build -t std_module -f docker/Dockerfile .
#
# Build with a different Clang version:
#   docker build -t std_module --build-arg CLANG_VERSION=16 -f docker/Dockerfile .
#   docker build -t std_module --build-arg CLANG_VERSION=17 -f docker/Dockerfile .
#
# Run tests:
#   docker run --rm std_module
#
# Interactive shell:
#   docker run --rm -it std_module /bin/bash
#
# Run specific test (build dir is build-clang-<version>):
#   docker run --rm std_module sh -c "ctest --test-dir build-clang-18 -R test_format --output-on-failure"
