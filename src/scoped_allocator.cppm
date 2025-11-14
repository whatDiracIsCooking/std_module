/**
 * @file scoped_allocator.cppm
 * @brief C++20 scoped_allocator module wrapper
 */

module;

#include <scoped_allocator>

export module std_module.scoped_allocator;

export namespace std
{
// Scoped allocator adaptor
using std::scoped_allocator_adaptor;

// Helper traits
using std::allocator_arg_t;
using std::allocator_arg;
}  // namespace std
