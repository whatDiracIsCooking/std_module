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
std_module_add_module(algorithm)
std_module_add_module(any)
std_module_add_module(bitset)
std_module_add_module(complex)
std_module_add_module(compare)
std_module_add_module(condition_variable)
std_module_add_module(deque)
std_module_add_module(exception)
std_module_add_module(execution)
std_module_add_module(format)
std_module_add_module(forward_list)
std_module_add_module(fstream)
std_module_add_module(functional)
std_module_add_module(future)
std_module_add_module(iomanip)
std_module_add_module(ios)
std_module_add_module(iosfwd)
std_module_add_module(iostream)
std_module_add_module(istream)
std_module_add_module(initializer_list)
std_module_add_module(iterator)
std_module_add_module(limits)
std_module_add_module(list)
std_module_add_module(locale)
std_module_add_module(map)
std_module_add_module(memory_resource)
std_module_add_module(new)
std_module_add_module(numeric)
std_module_add_module(queue)
std_module_add_module(barrier)
std_module_add_module(charconv)
std_module_add_module(concepts)
std_module_add_module(filesystem)
std_module_add_module(latch)
std_module_add_module(optional)
std_module_add_module(random)
std_module_add_module(bit)
std_module_add_module(coroutine)
std_module_add_module(numbers)
std_module_add_module(ranges)
std_module_add_module(semaphore)
std_module_add_module(source_location)
std_module_add_module(span)
std_module_add_module(string_view)
std_module_add_module(syncstream)
std_module_add_module(system_error)
std_module_add_module(typeindex)
std_module_add_module(variant)
std_module_add_module(vector)

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
std_module_add_to_aggregate(algorithm)
std_module_add_to_aggregate(any)
std_module_add_to_aggregate(bitset)
std_module_add_to_aggregate(complex)
std_module_add_to_aggregate(compare)
std_module_add_to_aggregate(condition_variable)
std_module_add_to_aggregate(deque)
std_module_add_to_aggregate(exception)
std_module_add_to_aggregate(execution)
std_module_add_to_aggregate(format)
std_module_add_to_aggregate(forward_list)
std_module_add_to_aggregate(fstream)
std_module_add_to_aggregate(functional)
std_module_add_to_aggregate(future)
std_module_add_to_aggregate(iomanip)
std_module_add_to_aggregate(ios)
std_module_add_to_aggregate(iosfwd)
std_module_add_to_aggregate(iostream)
std_module_add_to_aggregate(istream)
std_module_add_to_aggregate(initializer_list)
std_module_add_to_aggregate(iterator)
std_module_add_to_aggregate(limits)
std_module_add_to_aggregate(list)
std_module_add_to_aggregate(locale)
std_module_add_to_aggregate(map)
std_module_add_to_aggregate(memory_resource)
std_module_add_to_aggregate(new)
std_module_add_to_aggregate(numeric)
std_module_add_to_aggregate(queue)
std_module_add_to_aggregate(barrier)
std_module_add_to_aggregate(charconv)
std_module_add_to_aggregate(concepts)
std_module_add_to_aggregate(filesystem)
std_module_add_to_aggregate(latch)
std_module_add_to_aggregate(optional)
std_module_add_to_aggregate(random)
std_module_add_to_aggregate(bit)
std_module_add_to_aggregate(coroutine)
std_module_add_to_aggregate(numbers)
std_module_add_to_aggregate(ranges)
std_module_add_to_aggregate(semaphore)
std_module_add_to_aggregate(source_location)
std_module_add_to_aggregate(span)
std_module_add_to_aggregate(string_view)
std_module_add_to_aggregate(syncstream)
std_module_add_to_aggregate(system_error)
std_module_add_to_aggregate(typeindex)
std_module_add_to_aggregate(variant)
std_module_add_to_aggregate(vector)

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
