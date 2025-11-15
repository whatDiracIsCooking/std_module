# ==============================================================================
# Tests for std_module
# ==============================================================================

# ==============================================================================
# Test Framework - Testing Utility Module
# ==============================================================================
# Build test_framework FIRST so it's available for tests that need it

if(STD_MODULE_BUILD_TESTS)
    # Build the test_framework module library
    add_library(std_module_test_framework)
    target_sources(std_module_test_framework
        PUBLIC
            FILE_SET CXX_MODULES FILES
                test_framework.cppm
    )
    target_compile_features(std_module_test_framework PUBLIC cxx_std_20)
    add_library(std_module::test_framework ALIAS std_module_test_framework)
    message(STATUS "Configured test utility: std_module::test_framework")

    # Test the test_framework itself
    add_executable(test_test_framework test_test_framework.cpp)
    target_link_libraries(test_test_framework PRIVATE std_module::test_framework)
    target_compile_features(test_test_framework PRIVATE cxx_std_20)
    add_test(NAME test_test_framework COMMAND test_test_framework)
    message(STATUS "Configured test: test_test_framework")
endif()

# ==============================================================================
# Module Tests
# ==============================================================================

# Note: The std_module_add_test() macro is defined in cmake/StdModuleMacros.cmake
# It handles:
#   - Creating the test executable
#   - Linking against the module library
#   - Setting C++20 requirement
#   - Registering with CTest
#   - Printing status message
#
# Additional linking (test_framework, system libraries, etc.) is done below

# Define all available modules (alphabetical order)
set(STD_MODULES
    algorithm
    any
    array
    atomic
    barrier
    bit
    bitset
    charconv
    chrono
    codecvt
    compare
    complex
    concepts
    condition_variable
    coroutine
    deque
    exception
    execution
    filesystem
    format
    forward_list
    fstream
    functional
    future
    initializer_list
    iomanip
    ios
    iosfwd
    iostream
    istream
    iterator
    latch
    limits
    list
    locale
    map
    memory
    memory_resource
    mutex
    new
    numbers
    numeric
    optional
    ostream
    queue
    random
    ranges
    ratio
    regex
    scoped_allocator
    semaphore
    set
    source_location
    span
    stack
    stdexcept
    stop_token
    streambuf
    string
    string_view
    syncstream
    system_error
    thread
    tuple
    type_traits
    typeindex
    typeinfo
    unordered_map
    unordered_set
    valarray
    variant
    vector
)

# Add tests for all modules and link test_framework
foreach(module IN LISTS STD_MODULES)
    std_module_add_test(${module})
    std_module_link_test_framework(${module})
endforeach()

# ==============================================================================
# Additional Test Linking (Ad Hoc Dependencies)
# ==============================================================================

# test_numeric needs functional module
if(TARGET test_numeric)
    target_link_libraries(test_numeric PRIVATE std_module::functional)
endif()

# test_scoped_allocator needs memory module
if(TARGET test_scoped_allocator)
    target_link_libraries(test_scoped_allocator PRIVATE std_module::memory)
endif()

# test_semaphore needs chrono module
if(TARGET test_semaphore)
    target_link_libraries(test_semaphore PRIVATE std_module::chrono)
endif()

# test_atomic needs libatomic for lock-free atomic operations on some platforms
if(TARGET test_atomic)
    target_link_options(test_atomic PRIVATE -latomic)
endif()

# test_chrono needs iostream module (it imports std_module.iostream)
if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_CHRONO)
    if(TARGET std_module::iostream)
        target_link_libraries(test_chrono PRIVATE std_module::iostream)
    endif()
endif()

# ==============================================================================
# Symbol Coverage Analysis
# ==============================================================================

# Add symbol coverage analysis as part of the test suite
find_package(Python3 COMPONENTS Interpreter)

if(Python3_FOUND)
    # Add as a CTest test - runs automatically with 'ctest' or 'cmake --build build --target test'
    add_test(
        NAME symbol-coverage
        COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/scripts/symbol_coverage.py
            --all
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    # Set test properties
    set_tests_properties(symbol-coverage PROPERTIES
        LABELS "coverage"
        TIMEOUT 30
    )

    # Also keep as a custom target for manual invocation
    add_custom_target(symbol-coverage-target
        COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/scripts/symbol_coverage.py
            --all
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Analyzing symbol usage coverage for all modules"
        VERBATIM
    )

    message(STATUS "Symbol coverage enabled - runs automatically with tests")
else()
    message(STATUS "Python3 not found - symbol coverage disabled")
endif()
