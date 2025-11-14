/**
 * @file memory.cppm
 * @brief C++20 memory module wrapper
 */

module;

#include <memory>

export module std_module.memory;

export namespace std
{
// Smart pointers
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

// Smart pointer creation
using std::make_unique;
using std::make_shared;
using std::allocate_shared;
using std::make_unique_for_overwrite;
using std::make_shared_for_overwrite;

// Smart pointer observers and modifiers
using std::owner_less;
using std::enable_shared_from_this;
using std::bad_weak_ptr;

// Smart pointer deleter types
using std::default_delete;

// Pointer utilities
using std::addressof;
using std::pointer_traits;
using std::to_address;

// C++20 pointer safety
using std::assume_aligned;

// Allocators
using std::allocator;
using std::allocator_traits;
using std::allocator_arg_t;
using std::allocator_arg;
using std::uses_allocator;
using std::uses_allocator_v;

// Uninitialized memory algorithms
using std::uninitialized_copy;
using std::uninitialized_copy_n;
using std::uninitialized_fill;
using std::uninitialized_fill_n;
using std::uninitialized_move;
using std::uninitialized_move_n;
using std::uninitialized_default_construct;
using std::uninitialized_default_construct_n;
using std::uninitialized_value_construct;
using std::uninitialized_value_construct_n;

// Object lifetime management
using std::destroy;
using std::destroy_at;
using std::destroy_n;
using std::construct_at;

// Raw pointer operations (C++17/20)
using std::raw_storage_iterator;

// C++17 polymorphic allocator (basic types only, pool resources not available in all implementations)
using std::pmr::memory_resource;
using std::pmr::polymorphic_allocator;

// Smart pointer casting
using std::static_pointer_cast;
using std::dynamic_pointer_cast;
using std::const_pointer_cast;
using std::reinterpret_pointer_cast;

// get_deleter
using std::get_deleter;

// Pointer comparison operators
using std::operator==;
using std::operator!=;
using std::operator<;
using std::operator<=;
using std::operator>;
using std::operator>=;
using std::operator<=>;

// Stream output (for unique_ptr/shared_ptr)
using std::operator<<;

// Hash support
using std::hash;
}  // namespace std
