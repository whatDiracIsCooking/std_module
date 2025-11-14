# ==============================================================================
# Individual Module Libraries
# ==============================================================================

# Each module is a separate library target for maximum flexibility.
# Users can link only what they need: target_link_libraries(app std_module::format)

# Note: The std_module_add_module() macro is defined in cmake/StdModuleMacros.cmake
# It handles:
#   - Creating the library target
#   - Adding the .cppm file as a CXX_MODULE
#   - Setting C++20 requirement
#   - Creating the namespaced alias (std_module::name)
#   - Installing the target (if enabled)
#   - Printing status message

# Add all available modules
std_module_add_module(format)
std_module_add_module(algorithm)
std_module_add_module(bitset)
std_module_add_module(string_view)
std_module_add_module(complex)
std_module_add_module(vector)
std_module_add_module(exception)
std_module_add_module(deque)
std_module_add_module(fstream)
std_module_add_module(functional)
std_module_add_module(iomanip)
std_module_add_module(ios)
std_module_add_module(iosfwd)
std_module_add_module(iostream)
std_module_add_module(istream)
std_module_add_module(iterator)
std_module_add_module(limits)
std_module_add_module(locale)

# Add more modules here as they are implemented:
# std_module_add_module(string)
# std_module_add_module(ranges)
# etc.

# ==============================================================================
# Aggregate "All Modules" Library
# ==============================================================================

# This is a convenience target that depends on all available modules.
# Users can link this to get everything: target_link_libraries(app std_module::all)

add_library(std_module_all INTERFACE)
add_library(std_module::all ALIAS std_module_all)

# Add dependencies to all built modules using the helper macro
std_module_add_to_aggregate(format)
std_module_add_to_aggregate(algorithm)
std_module_add_to_aggregate(bitset)
std_module_add_to_aggregate(string_view)
std_module_add_to_aggregate(complex)
std_module_add_to_aggregate(vector)
std_module_add_to_aggregate(exception)
std_module_add_to_aggregate(deque)
std_module_add_to_aggregate(fstream)
std_module_add_to_aggregate(functional)
std_module_add_to_aggregate(iomanip)
std_module_add_to_aggregate(ios)
std_module_add_to_aggregate(iosfwd)
std_module_add_to_aggregate(iostream)
std_module_add_to_aggregate(istream)
std_module_add_to_aggregate(iterator)
std_module_add_to_aggregate(limits)
std_module_add_to_aggregate(locale)

# Add more module dependencies here as they are implemented:
# std_module_add_to_aggregate(string)
# std_module_add_to_aggregate(ranges)
# etc.

if(STD_MODULE_INSTALL)
    install(TARGETS std_module_all
        EXPORT std_module-targets
    )
endif()

message(STATUS "Configured aggregate target: std_module::all")
