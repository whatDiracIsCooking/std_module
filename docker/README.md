# Docker Build Environment for std_module

This directory contains a Dockerfile for building and testing the std_module C++20 library in a containerized environment.

## Prerequisites

- Docker installed on your system
- At least 2GB of free disk space for the image

## Quick Start

### Build the Docker Image

From the repository root:

```bash
docker build -t std_module -f docker/Dockerfile .
```

### Run Tests

```bash
docker run --rm std_module
```

This will execute all tests using `ctest`.

## Advanced Usage

### Interactive Shell

To explore the built project interactively:

```bash
docker run --rm -it std_module /bin/bash
```

### Run Specific Tests

```bash
# Run only the format module tests
docker run --rm std_module ctest --test-dir build -R test_format --output-on-failure

# Run with verbose output
docker run --rm std_module ctest --test-dir build --verbose
```

### Build with Custom Options

To modify build options, edit the Dockerfile's CMake configure step:

```dockerfile
RUN cmake -B build -G Ninja \
    -DCMAKE_CXX_COMPILER=clang++-18 \
    -DCMAKE_BUILD_TYPE=Debug \
    -DSTD_MODULE_BUILD_ALL_MODULES=OFF \
    -DSTD_MODULE_BUILD_FORMAT=ON
```

## Image Details

- **Base Image:** Ubuntu 24.04
- **Compiler:** Clang 18
- **Build System:** CMake 3.28+ with Ninja
- **Python:** 3.x (for symbol coverage analysis)

## Troubleshooting

### Build Fails

If the Docker build fails, check:
1. You're running the command from the repository root
2. You have a stable internet connection (for downloading packages)
3. You have sufficient disk space

### Tests Fail

If tests fail inside the container:
1. Check if they also fail in a local build
2. Review test output with `--verbose` flag
3. Ensure your Docker daemon has sufficient memory allocated

## Container Size

The final image is approximately 1-2GB due to:
- Clang compiler toolchain
- CMake and Ninja build tools
- Built module files and test executables

To reduce size, consider using a multi-stage build that only keeps test artifacts in the final image.
