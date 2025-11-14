cmake_minimum_required(VERSION 3.28)
project(std_module
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "C++20 module wrapper for the C++ standard library"
)

# ==============================================================================
# Build Options
# ==============================================================================

option(STD_MODULE_BUILD_TESTS "Build tests" ON)
option(STD_MODULE_BUILD_ALL_MODULES "Build all available standard library modules" ON)
option(STD_MODULE_INSTALL "Generate installation targets" ON)

# Individual module options (opt-in when BUILD_ALL_MODULES is OFF)
option(STD_MODULE_BUILD_FORMAT "Build std_module.format" ON)
option(STD_MODULE_BUILD_VECTOR "Build std_module.vector" ON)
option(STD_MODULE_BUILD_ALGORITHM "Build std_module.algorithm" ON)
option(STD_MODULE_BUILD_BITSET "Build std_module.bitset" ON)
option(STD_MODULE_BUILD_STRING_VIEW "Build std_module.string_view" ON)
option(STD_MODULE_BUILD_EXCEPTION "Build std_module.exception" ON)
option(STD_MODULE_BUILD_COMPLEX "Build std_module.complex" ON)
option(STD_MODULE_BUILD_DEQUE "Build std_module.deque" ON)
option(STD_MODULE_BUILD_FSTREAM "Build std_module.fstream" ON)
option(STD_MODULE_BUILD_FUNCTIONAL "Build std_module.functional" ON)
option(STD_MODULE_BUILD_IOMANIP "Build std_module.iomanip" ON)
option(STD_MODULE_BUILD_IOS "Build std_module.ios" ON)
option(STD_MODULE_BUILD_IOSFWD "Build std_module.iosfwd" ON)
option(STD_MODULE_BUILD_IOSTREAM "Build std_module.iostream" ON)
option(STD_MODULE_BUILD_ISTREAM "Build std_module.istream" ON)
option(STD_MODULE_BUILD_ITERATOR "Build std_module.iterator" ON)
option(STD_MODULE_BUILD_LIMITS "Build std_module.limits" ON)
option(STD_MODULE_BUILD_LIST "Build std_module.list" ON)
option(STD_MODULE_BUILD_LOCALE "Build std_module.locale" ON)
option(STD_MODULE_BUILD_MAP "Build std_module.map" ON)
option(STD_MODULE_BUILD_NEW "Build std_module.new" ON)
option(STD_MODULE_BUILD_NUMERIC "Build std_module.numeric" ON)
option(STD_MODULE_BUILD_QUEUE "Build std_module.queue" ON)
# More options will be added as we wrap more headers:
# option(STD_MODULE_BUILD_STRING "Build std_module.string" ON)
# etc.

# ==============================================================================
# Project Configuration
# ==============================================================================

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ==============================================================================
# Compiler Detection and Configuration
# ==============================================================================

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Detect compiler support for C++20 modules
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "16.0")
        message(WARNING "Clang 16+ recommended for best C++20 module support")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.0")
        message(FATAL_ERROR "GCC 11+ required for C++20 module support")
    endif()
    message(STATUS "GCC module support is experimental")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "19.30")
        message(FATAL_ERROR "MSVC 19.30+ (VS 2022) required for C++20 module support")
    endif()
else()
    message(WARNING "Untested compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# ==============================================================================
# CMake Macros
# ==============================================================================

# Include helper macros for adding modules and tests
include(cmake/StdModuleMacros.cmake)

# ==============================================================================
# Source Modules
# ==============================================================================

add_subdirectory(src)

# ==============================================================================
# Tests
# ==============================================================================

if(STD_MODULE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# ==============================================================================
# Installation
# ==============================================================================

if(STD_MODULE_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    # Install module files
    install(DIRECTORY ${CMAKE_BINARY_DIR}/CMakeFiles/std_module.dir/
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/std_module
        FILES_MATCHING PATTERN "*.pcm"
    )

    # Generate package config files for find_package() support
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/std_module-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/std_module-config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/std_module-config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/std_module
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/std_module-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/std_module-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/std_module
    )

    # Export targets
    install(EXPORT std_module-targets
        FILE std_module-targets.cmake
        NAMESPACE std_module::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/std_module
    )
endif()

# ==============================================================================
# Summary
# ==============================================================================

message(STATUS "")
message(STATUS "std_module configuration summary:")
message(STATUS "  Version:                ${PROJECT_VERSION}")
message(STATUS "  Build all modules:      ${STD_MODULE_BUILD_ALL_MODULES}")
message(STATUS "  Build tests:            ${STD_MODULE_BUILD_TESTS}")
message(STATUS "  Install targets:        ${STD_MODULE_INSTALL}")
message(STATUS "")
message(STATUS "Available modules:")
message(STATUS "  format:                 ${STD_MODULE_BUILD_FORMAT}")
message(STATUS "  vector:                 ${STD_MODULE_BUILD_VECTOR}")
message(STATUS "  algorithm:              ${STD_MODULE_BUILD_ALGORITHM}")
message(STATUS "  bitset:                 ${STD_MODULE_BUILD_BITSET}")
message(STATUS "  string_view:            ${STD_MODULE_BUILD_STRING_VIEW}")
message(STATUS "  exception:              ${STD_MODULE_BUILD_EXCEPTION}")
message(STATUS "  complex:                ${STD_MODULE_BUILD_COMPLEX}")
message(STATUS "  deque:                  ${STD_MODULE_BUILD_DEQUE}")
message(STATUS "  fstream:                ${STD_MODULE_BUILD_FSTREAM}")
message(STATUS "  functional:             ${STD_MODULE_BUILD_FUNCTIONAL}")
message(STATUS "  iomanip:                ${STD_MODULE_BUILD_IOMANIP}")
message(STATUS "  ios:                    ${STD_MODULE_BUILD_IOS}")
message(STATUS "  iosfwd:                 ${STD_MODULE_BUILD_IOSFWD}")
message(STATUS "  iostream:               ${STD_MODULE_BUILD_IOSTREAM}")
message(STATUS "  istream:                ${STD_MODULE_BUILD_ISTREAM}")
message(STATUS "  iterator:               ${STD_MODULE_BUILD_ITERATOR}")
message(STATUS "  limits:                 ${STD_MODULE_BUILD_LIMITS}")
message(STATUS "  list:                   ${STD_MODULE_BUILD_LIST}")
message(STATUS "  locale:                 ${STD_MODULE_BUILD_LOCALE}")
message(STATUS "  map:                    ${STD_MODULE_BUILD_MAP}")
message(STATUS "  new:                    ${STD_MODULE_BUILD_NEW}")
message(STATUS "  numeric:                ${STD_MODULE_BUILD_NUMERIC}")
message(STATUS "  queue:                  ${STD_MODULE_BUILD_QUEUE}")
message(STATUS "")
