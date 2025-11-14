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
std_module_add_test(deque)
std_module_add_test(fstream)
std_module_add_test(functional)

# Add more tests here as modules are implemented:
# std_module_add_test(string)
# std_module_add_test(ranges)
# etc.
