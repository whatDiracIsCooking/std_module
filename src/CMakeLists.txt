# ==============================================================================
# Individual Module Libraries
# ==============================================================================

# Each module is a separate library target for maximum flexibility.
# Users can link only what they need: target_link_libraries(app std_module::format)

# ------------------------------------------------------------------------------
# std_module.format
# ------------------------------------------------------------------------------

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_FORMAT)
    add_library(std_module_format)

    target_sources(std_module_format
        PUBLIC
            FILE_SET CXX_MODULES FILES
                format.cppm
    )

    target_compile_features(std_module_format PUBLIC cxx_std_20)

    # Alias for consistent namespacing
    add_library(std_module::format ALIAS std_module_format)

    # Installation
    if(STD_MODULE_INSTALL)
        install(TARGETS std_module_format
            EXPORT std_module-targets
            FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}/std_module
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()

    message(STATUS "Configured module: std_module::format")
endif()

# ------------------------------------------------------------------------------
# std_module.algorithm
# ------------------------------------------------------------------------------

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_ALGORITHM)
    add_library(std_module_algorithm)

    target_sources(std_module_algorithm
        PUBLIC
            FILE_SET CXX_MODULES FILES
                algorithm.cppm
    )

    target_compile_features(std_module_algorithm PUBLIC cxx_std_20)

    # Alias for consistent namespacing
    add_library(std_module::algorithm ALIAS std_module_algorithm)

    # Installation
    if(STD_MODULE_INSTALL)
        install(TARGETS std_module_algorithm
            EXPORT std_module-targets
            FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}/std_module
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()

    message(STATUS "Configured module: std_module::algorithm")
endif()

# ------------------------------------------------------------------------------
# std_module.bitset
# ------------------------------------------------------------------------------

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_BITSET)
    add_library(std_module_bitset)

    target_sources(std_module_bitset
        PUBLIC
            FILE_SET CXX_MODULES FILES
                bitset.cppm
    )

    target_compile_features(std_module_bitset PUBLIC cxx_std_20)

    # Alias for consistent namespacing
    add_library(std_module::bitset ALIAS std_module_bitset)

    # Installation
    if(STD_MODULE_INSTALL)
        install(TARGETS std_module_bitset
            EXPORT std_module-targets
            FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}/std_module
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()

    message(STATUS "Configured module: std_module::bitset")
endif()

# ------------------------------------------------------------------------------
# std_module.string_view
# ------------------------------------------------------------------------------

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_STRING_VIEW)
    add_library(std_module_string_view)

    target_sources(std_module_string_view
        PUBLIC
            FILE_SET CXX_MODULES FILES
                string_view.cppm
    )

    target_compile_features(std_module_string_view PUBLIC cxx_std_20)

    # Alias for consistent namespacing
    add_library(std_module::string_view ALIAS std_module_string_view)

    # Installation
    if(STD_MODULE_INSTALL)
        install(TARGETS std_module_string_view
            EXPORT std_module-targets
            FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}/std_module
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()

    message(STATUS "Configured module: std_module::string_view")
endif()

# ------------------------------------------------------------------------------
# std_module.vector
# ------------------------------------------------------------------------------

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_VECTOR)
    add_library(std_module_vector)

    target_sources(std_module_vector
        PUBLIC
            FILE_SET CXX_MODULES FILES
                vector.cppm
    )

    target_compile_features(std_module_vector PUBLIC cxx_std_20)

    # Alias for consistent namespacing
    add_library(std_module::vector ALIAS std_module_vector)

    # Installation
    if(STD_MODULE_INSTALL)
        install(TARGETS std_module_vector
            EXPORT std_module-targets
            FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}/std_module
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()

    message(STATUS "Configured module: std_module::vector")
endif()

# ------------------------------------------------------------------------------
# Add more modules here as they are implemented
# ------------------------------------------------------------------------------

# ==============================================================================
# Aggregate "All Modules" Library
# ==============================================================================

# This is a convenience target that depends on all available modules.
# Users can link this to get everything: target_link_libraries(app std_module::all)

add_library(std_module_all INTERFACE)
add_library(std_module::all ALIAS std_module_all)

# Add dependencies to all built modules
if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_FORMAT)
    target_link_libraries(std_module_all INTERFACE std_module::format)
endif()

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_VECTOR)
    target_link_libraries(std_module_all INTERFACE std_module::vector)
endif()

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_ALGORITHM)
    target_link_libraries(std_module_all INTERFACE std_module::algorithm)
endif()

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_BITSET)
    target_link_libraries(std_module_all INTERFACE std_module::bitset)
endif()

if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_STRING_VIEW)
    target_link_libraries(std_module_all INTERFACE std_module::string_view)
endif()

# Add more module dependencies here as they are implemented

if(STD_MODULE_INSTALL)
    install(TARGETS std_module_all
        EXPORT std_module-targets
    )
endif()

message(STATUS "Configured aggregate target: std_module::all")
