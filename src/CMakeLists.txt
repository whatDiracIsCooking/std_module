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
# Add more modules here as they are implemented
# ------------------------------------------------------------------------------

# Example template for future modules:
#
# if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_VECTOR)
#     add_library(std_module_vector)
#
#     target_sources(std_module_vector
#         PUBLIC
#             FILE_SET CXX_MODULES FILES
#                 vector.cppm
#     )
#
#     target_compile_features(std_module_vector PUBLIC cxx_std_20)
#     add_library(std_module::vector ALIAS std_module_vector)
#
#     if(STD_MODULE_INSTALL)
#         install(TARGETS std_module_vector
#             EXPORT std_module-targets
#             FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}/std_module
#             LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#             ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         )
#     endif()
# endif()

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

# Add more module dependencies here as they are implemented
# if(STD_MODULE_BUILD_ALL_MODULES OR STD_MODULE_BUILD_VECTOR)
#     target_link_libraries(std_module_all INTERFACE std_module::vector)
# endif()

if(STD_MODULE_INSTALL)
    install(TARGETS std_module_all
        EXPORT std_module-targets
    )
endif()

message(STATUS "Configured aggregate target: std_module::all")
