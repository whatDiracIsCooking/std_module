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
std_module_add_test(vector)

# Add more tests here as modules are implemented:
# std_module_add_test(string)
# std_module_add_test(ranges)
# etc.

# ==============================================================================
# Symbol Coverage Analysis
# ==============================================================================

# Add custom target to run symbol usage coverage analysis
find_package(Python3 COMPONENTS Interpreter)

if(Python3_FOUND)
    add_custom_target(symbol-coverage
        COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/scripts/symbol_coverage.py
            --all
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Analyzing symbol usage coverage for all modules"
        VERBATIM
    )

    # Add help message
    add_custom_target(symbol-coverage-help
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "Symbol Coverage Targets:"
        COMMAND ${CMAKE_COMMAND} -E echo "  symbol-coverage        - Analyze all modules"
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "Or run directly:"
        COMMAND ${CMAKE_COMMAND} -E echo "  ./scripts/symbol_coverage.py --all"
        COMMAND ${CMAKE_COMMAND} -E echo "  ./scripts/symbol_coverage.py src/format.cppm test/test_format.cpp"
        VERBATIM
    )
else()
    message(STATUS "Python3 not found - symbol coverage target disabled")
endif()
