# ==============================================================================
# CMake Macros for std_module
# ==============================================================================
#
# This file provides helper macros to reduce boilerplate when adding new
# standard library module wrappers.

# ------------------------------------------------------------------------------
# std_module_add_module
# ------------------------------------------------------------------------------
# Creates a C++20 module library target for a standard library wrapper.
#
# Usage:
#   std_module_add_module(format)
#   std_module_add_module(vector)
#
# This macro will:
#   - Check if STD_MODULE_BUILD_ALL_MODULES or STD_MODULE_BUILD_<NAME> is ON
#   - Create library target std_module_<name>
#   - Add the <name>.cppm file as a CXX_MODULE file set
#   - Set C++20 requirement
#   - Create namespaced alias std_module::<name>
#   - Install the target if STD_MODULE_INSTALL is ON
#   - Print status message
#
# Parameters:
#   MODULE_NAME - The name of the module (e.g., "format", "vector")
#
macro(std_module_add_module MODULE_NAME)
    # Convert module name to uppercase for option checking
    string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

    # Check if this module should be built
    if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_${MODULE_NAME_UPPER})
        # Create the library target
        add_library(std_module_${MODULE_NAME})

        # Add the module source file
        target_sources(std_module_${MODULE_NAME}
            PUBLIC
                FILE_SET CXX_MODULES FILES
                    ${MODULE_NAME}.cppm
        )

        # Require C++20
        target_compile_features(std_module_${MODULE_NAME} PUBLIC cxx_std_20)

        # Create namespaced alias for consistent usage
        add_library(std_module::${MODULE_NAME} ALIAS std_module_${MODULE_NAME})

        # Installation
        if(STD_MODULE_INSTALL)
            install(TARGETS std_module_${MODULE_NAME}
                EXPORT std_module-targets
                FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}/std_module
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            )
        endif()

        message(STATUS "Configured module: std_module::${MODULE_NAME}")
    endif()
endmacro()

# ------------------------------------------------------------------------------
# std_module_add_test
# ------------------------------------------------------------------------------
# Creates a test executable for a standard library module wrapper.
#
# Usage:
#   std_module_add_test(format)
#   std_module_add_test(vector)
#
# This macro will:
#   - Check if STD_MODULE_BUILD_ALL_MODULES or STD_MODULE_BUILD_<NAME> is ON
#   - Create test executable test_<name>
#   - Link against std_module::<name>
#   - Set C++20 requirement
#   - Register with CTest
#   - Print status message
#
# Note: To link test_framework, add target_link_libraries after std_module_add_test:
#   std_module_add_test(format)
#   if(TARGET test_format)
#       target_link_libraries(test_format PRIVATE std_module::test_framework)
#   endif()
#
# Parameters:
#   MODULE_NAME - The name of the module (e.g., "format", "vector")
#
macro(std_module_add_test MODULE_NAME)
    # Convert module name to uppercase for option checking
    string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

    # Check if this module should be built
    if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_${MODULE_NAME_UPPER})
        # Create test executable
        add_executable(test_${MODULE_NAME} test_${MODULE_NAME}.cpp)

        # Link against the module
        target_link_libraries(test_${MODULE_NAME}
            PRIVATE
                std_module::${MODULE_NAME}
        )

        # Special handling for modules requiring additional system libraries
        if(MODULE_NAME STREQUAL "atomic")
            target_link_options(test_${MODULE_NAME} PRIVATE -latomic)
        elseif(MODULE_NAME STREQUAL "thread")
            find_package(Threads REQUIRED)
            target_link_libraries(test_${MODULE_NAME} PRIVATE Threads::Threads)
        elseif(MODULE_NAME STREQUAL "filesystem")
            # Some compilers need explicit filesystem library
            if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.1)
                target_link_libraries(test_${MODULE_NAME} PRIVATE stdc++fs)
            endif()
        endif()

        # Require C++20
        target_compile_features(test_${MODULE_NAME} PRIVATE cxx_std_20)

        # Register as a CTest test
        add_test(NAME test_${MODULE_NAME} COMMAND test_${MODULE_NAME})

        message(STATUS "Configured test: test_${MODULE_NAME}")
    endif()
endmacro()

# ------------------------------------------------------------------------------
# std_module_add_to_aggregate
# ------------------------------------------------------------------------------
# Adds a module to the aggregate "all" target if it's enabled.
#
# Usage:
#   std_module_add_to_aggregate(format)
#   std_module_add_to_aggregate(vector)
#
# This macro will:
#   - Check if STD_MODULE_BUILD_ALL_MODULES or STD_MODULE_BUILD_<NAME> is ON
#   - Add the module as a dependency to std_module_all interface library
#
# Parameters:
#   MODULE_NAME - The name of the module (e.g., "format", "vector")
#
macro(std_module_add_to_aggregate MODULE_NAME)
    # Convert module name to uppercase for option checking
    string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

    # Check if this module was built
    if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_${MODULE_NAME_UPPER})
        target_link_libraries(std_module_all INTERFACE std_module::${MODULE_NAME})
    endif()
endmacro()

# ------------------------------------------------------------------------------
# std_module_link_test_framework
# ------------------------------------------------------------------------------
# Links a test executable to the test_framework module (if tests are enabled).
#
# Usage:
#   std_module_link_test_framework(bit)
#   std_module_link_test_framework(vector)
#
# This macro will:
#   - Check if target test_<name> exists
#   - Link it against std_module::test_framework
#
# Parameters:
#   MODULE_NAME - The name of the module being tested (e.g., "bit", "vector")
#
macro(std_module_link_test_framework MODULE_NAME)
    if(TARGET test_${MODULE_NAME})
        target_link_libraries(test_${MODULE_NAME} PRIVATE std_module::test_framework)
    endif()
endmacro()
