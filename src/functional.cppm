/**
 * @file functional.cppm
 * @brief C++20 functional module wrapper
 */

module;

#include <functional>

export module std_module.functional;

export namespace std
{
// Function wrapper
using std::function;
using std::bad_function_call;

// Reference wrappers
using std::reference_wrapper;
using std::ref;
using std::cref;
using std::unwrap_reference;
using std::unwrap_reference_t;
using std::unwrap_ref_decay;
using std::unwrap_ref_decay_t;

// Invoke utilities
using std::invoke;
using std::invoke_result;
using std::invoke_result_t;
using std::is_invocable;
using std::is_invocable_r;
using std::is_invocable_v;
using std::is_invocable_r_v;
using std::is_nothrow_invocable;
using std::is_nothrow_invocable_r;
using std::is_nothrow_invocable_v;
using std::is_nothrow_invocable_r_v;

// Bind
using std::bind;
using std::bind_front;
using std::is_bind_expression;
using std::is_bind_expression_v;
using std::is_placeholder;
using std::is_placeholder_v;

// Member function adapters
using std::mem_fn;

// Negators
using std::not_fn;

// Hash
using std::hash;

// Arithmetic operations
using std::plus;
using std::minus;
using std::multiplies;
using std::divides;
using std::modulus;
using std::negate;

// Comparisons
using std::equal_to;
using std::not_equal_to;
using std::greater;
using std::less;
using std::greater_equal;
using std::less_equal;
using std::compare_three_way;

// Logical operations
using std::logical_and;
using std::logical_or;
using std::logical_not;

// Bitwise operations
using std::bit_and;
using std::bit_or;
using std::bit_xor;
using std::bit_not;

// Identity
using std::identity;

// Searchers
using std::default_searcher;
using std::boyer_moore_searcher;
using std::boyer_moore_horspool_searcher;
}  // namespace std

// Export placeholders namespace
export namespace std::placeholders
{
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    using std::placeholders::_4;
    using std::placeholders::_5;
    using std::placeholders::_6;
    using std::placeholders::_7;
    using std::placeholders::_8;
    using std::placeholders::_9;
    using std::placeholders::_10;
}
