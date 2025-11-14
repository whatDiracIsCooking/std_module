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

# Test for complex module
if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_COMPLEX)
    add_executable(test_complex test_complex.cpp)

    target_link_libraries(test_complex
        PRIVATE
            std_module::complex
    )

    target_compile_features(test_complex PRIVATE cxx_std_20)

    # Register as a CTest test
    add_test(NAME test_complex COMMAND test_complex)

    message(STATUS "Configured test: test_complex")
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
