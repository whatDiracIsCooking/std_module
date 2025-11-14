# ==============================================================================
# Tests for std_module
# ==============================================================================

# Note: The std_module_add_test() macro is defined in cmake/StdModuleMacros.cmake
# It handles:
#   - Creating the test executable
#   - Linking against the module library
#   - Setting C++20 requirement
#   - Registering with CTest
#   - Printing status message

# Add tests for all available modules
std_module_add_test(format)
std_module_add_test(algorithm)
std_module_add_test(bitset)
std_module_add_test(string_view)
std_module_add_test(complex)
std_module_add_test(vector)
std_module_add_test(exception)
std_module_add_test(deque)
std_module_add_test(fstream)
std_module_add_test(functional)
std_module_add_test(iomanip)
std_module_add_test(ios)
std_module_add_test(iosfwd)
std_module_add_test(iostream)
std_module_add_test(istream)
std_module_add_test(iterator)
std_module_add_test(limits)
std_module_add_test(list)
std_module_add_test(locale)
std_module_add_test(map)
std_module_add_test(new)
std_module_add_test(queue)

# Add more tests here as modules are implemented:
# std_module_add_test(string)
# std_module_add_test(ranges)
# etc.

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
