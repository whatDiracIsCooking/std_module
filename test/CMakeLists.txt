# ==============================================================================
# Tests for std_module
# ==============================================================================

# Test for format module
if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_FORMAT)
    add_executable(test_format test_format.cpp)

    target_link_libraries(test_format
        PRIVATE
            std_module::format
    )

    target_compile_features(test_format PRIVATE cxx_std_20)

    # Register as a CTest test
    add_test(NAME test_format COMMAND test_format)

    message(STATUS "Configured test: test_format")
endif()

# Test for algorithm module
if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_ALGORITHM)
    add_executable(test_algorithm test_algorithm.cpp)

    target_link_libraries(test_algorithm
        PRIVATE
            std_module::algorithm
    )

    target_compile_features(test_algorithm PRIVATE cxx_std_20)

    # Register as a CTest test
    add_test(NAME test_algorithm COMMAND test_algorithm)

    message(STATUS "Configured test: test_algorithm")
endif()

# Test for bitset module
if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_BITSET)
    add_executable(test_bitset test_bitset.cpp)

    target_link_libraries(test_bitset
        PRIVATE
            std_module::bitset
    )

    target_compile_features(test_bitset PRIVATE cxx_std_20)

    # Register as a CTest test
    add_test(NAME test_bitset COMMAND test_bitset)

    message(STATUS "Configured test: test_bitset")
endif()

# Test for string_view module
if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_STRING_VIEW)
    add_executable(test_string_view test_string_view.cpp)

    target_link_libraries(test_string_view
        PRIVATE
            std_module::string_view
    )

    target_compile_features(test_string_view PRIVATE cxx_std_20)

    # Register as a CTest test
    add_test(NAME test_string_view COMMAND test_string_view)

    message(STATUS "Configured test: test_string_view")
endif()

# ==============================================================================
# Add more tests here as modules are implemented
# ==============================================================================

# Example template:
#
# if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_VECTOR)
#     add_executable(test_vector test_vector.cpp)
#     target_link_libraries(test_vector PRIVATE std_module::vector)
#     target_compile_features(test_vector PRIVATE cxx_std_20)
#     add_test(NAME test_vector COMMAND test_vector)
# endif()
