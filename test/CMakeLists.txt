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

# Add tests for all available modules (alphabetical order)
std_module_add_test(algorithm)
std_module_add_test(any)
std_module_add_test(array)
std_module_add_test(atomic)
std_module_add_test(barrier)
std_module_add_test(bit)
std_module_add_test(bitset)
std_module_add_test(charconv)
std_module_add_test(chrono)
std_module_add_test(codecvt)
std_module_add_test(compare)
std_module_add_test(complex)
std_module_add_test(concepts)
std_module_add_test(condition_variable)
std_module_add_test(coroutine)
std_module_add_test(deque)
std_module_add_test(exception)
std_module_add_test(execution)
std_module_add_test(filesystem)
std_module_add_test(format)
std_module_add_test(forward_list)
std_module_add_test(fstream)
std_module_add_test(functional)
std_module_add_test(future)
std_module_add_test(initializer_list)
std_module_add_test(iomanip)
std_module_add_test(ios)
std_module_add_test(iosfwd)
std_module_add_test(iostream)
std_module_add_test(istream)
std_module_add_test(iterator)
std_module_add_test(latch)
std_module_add_test(limits)
std_module_add_test(list)
std_module_add_test(locale)
std_module_add_test(map)
std_module_add_test(memory)
std_module_add_test(memory_resource)
std_module_add_test(mutex)
std_module_add_test(new)
std_module_add_test(numbers)
std_module_add_test(numeric)
std_module_add_test(optional)
std_module_add_test(ostream)
std_module_add_test(queue)
std_module_add_test(random)
std_module_add_test(ranges)
std_module_add_test(ratio)
std_module_add_test(regex)
std_module_add_test(scoped_allocator)
std_module_add_test(semaphore)
std_module_add_test(set)
std_module_add_test(source_location)
std_module_add_test(span)
std_module_add_test(stack)
std_module_add_test(stdexcept)
std_module_add_test(stop_token)
std_module_add_test(streambuf)
std_module_add_test(string)
std_module_add_test(string_view)
std_module_add_test(syncstream)
std_module_add_test(system_error)
std_module_add_test(thread)
std_module_add_test(tuple)
std_module_add_test(type_traits)
std_module_add_test(typeindex)
std_module_add_test(typeinfo)
std_module_add_test(unordered_map)
std_module_add_test(unordered_set)
std_module_add_test(valarray)
std_module_add_test(variant)
std_module_add_test(vector)

# ==============================================================================
# Additional Test Linking
# ==============================================================================

# Link test_framework for tests that use it
std_module_link_test_framework(algorithm)
std_module_link_test_framework(any)
std_module_link_test_framework(array)
std_module_link_test_framework(atomic)
std_module_link_test_framework(barrier)
std_module_link_test_framework(bit)
std_module_link_test_framework(bitset)
std_module_link_test_framework(charconv)
std_module_link_test_framework(chrono)
std_module_link_test_framework(codecvt)
std_module_link_test_framework(compare)
std_module_link_test_framework(complex)
std_module_link_test_framework(concepts)
std_module_link_test_framework(condition_variable)
std_module_link_test_framework(coroutine)
std_module_link_test_framework(deque)
std_module_link_test_framework(exception)
std_module_link_test_framework(execution)
std_module_link_test_framework(filesystem)
std_module_link_test_framework(format)
std_module_link_test_framework(forward_list)
std_module_link_test_framework(fstream)
std_module_link_test_framework(functional)
std_module_link_test_framework(future)
std_module_link_test_framework(initializer_list)
std_module_link_test_framework(iomanip)
std_module_link_test_framework(ios)
std_module_link_test_framework(iosfwd)
std_module_link_test_framework(iostream)
std_module_link_test_framework(istream)
std_module_link_test_framework(iterator)
std_module_link_test_framework(latch)
std_module_link_test_framework(limits)
std_module_link_test_framework(list)
std_module_link_test_framework(locale)
std_module_link_test_framework(map)
std_module_link_test_framework(memory)
std_module_link_test_framework(memory_resource)
std_module_link_test_framework(mutex)
std_module_link_test_framework(new)
std_module_link_test_framework(numbers)
std_module_link_test_framework(numeric)
std_module_link_test_framework(optional)
std_module_link_test_framework(ostream)
std_module_link_test_framework(queue)
std_module_link_test_framework(random)
std_module_link_test_framework(ranges)
std_module_link_test_framework(ratio)
std_module_link_test_framework(regex)
std_module_link_test_framework(scoped_allocator)
std_module_link_test_framework(semaphore)
std_module_link_test_framework(set)
std_module_link_test_framework(source_location)
std_module_link_test_framework(span)
std_module_link_test_framework(stack)
std_module_link_test_framework(stdexcept)
std_module_link_test_framework(stop_token)
std_module_link_test_framework(streambuf)
std_module_link_test_framework(string)
std_module_link_test_framework(string_view)
std_module_link_test_framework(syncstream)
std_module_link_test_framework(system_error)
std_module_link_test_framework(thread)
std_module_link_test_framework(tuple)
std_module_link_test_framework(type_traits)
std_module_link_test_framework(typeindex)
std_module_link_test_framework(typeinfo)
std_module_link_test_framework(unordered_map)
std_module_link_test_framework(unordered_set)
std_module_link_test_framework(valarray)
std_module_link_test_framework(variant)
std_module_link_test_framework(vector)

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
