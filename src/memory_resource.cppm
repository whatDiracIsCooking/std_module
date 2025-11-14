/**
 * @file memory_resource.cppm
 * @brief C++20 memory_resource module wrapper
 */

module;

#include <memory_resource>

export module std_module.memory_resource;

export namespace std::pmr
{
// Memory resource base class
using std::pmr::memory_resource;

// Polymorphic allocator
using std::pmr::polymorphic_allocator;

// Memory resource functions
using std::pmr::get_default_resource;
using std::pmr::set_default_resource;
using std::pmr::new_delete_resource;
using std::pmr::null_memory_resource;

// Pool resources
using std::pmr::synchronized_pool_resource;
using std::pmr::unsynchronized_pool_resource;
using std::pmr::monotonic_buffer_resource;

// Pool options
using std::pmr::pool_options;
}  // namespace std::pmr
