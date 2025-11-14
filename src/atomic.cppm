/**
 * @file atomic.cppm
 * @brief C++20 atomic module wrapper
 */

module;

#include <atomic>

export module std_module.atomic;

export namespace std
{
// Core atomic types
using std::atomic;
using std::atomic_ref;
using std::atomic_flag;

// Memory ordering
using std::memory_order;

// Atomic type aliases for integral types
using std::atomic_bool;
using std::atomic_char;
using std::atomic_schar;
using std::atomic_uchar;
using std::atomic_short;
using std::atomic_ushort;
using std::atomic_int;
using std::atomic_uint;
using std::atomic_long;
using std::atomic_ulong;
using std::atomic_llong;
using std::atomic_ullong;
using std::atomic_char8_t;
using std::atomic_char16_t;
using std::atomic_char32_t;
using std::atomic_wchar_t;

// Atomic type aliases for standard typedefs
using std::atomic_int8_t;
using std::atomic_uint8_t;
using std::atomic_int16_t;
using std::atomic_uint16_t;
using std::atomic_int32_t;
using std::atomic_uint32_t;
using std::atomic_int64_t;
using std::atomic_uint64_t;
using std::atomic_int_least8_t;
using std::atomic_uint_least8_t;
using std::atomic_int_least16_t;
using std::atomic_uint_least16_t;
using std::atomic_int_least32_t;
using std::atomic_uint_least32_t;
using std::atomic_int_least64_t;
using std::atomic_uint_least64_t;
using std::atomic_int_fast8_t;
using std::atomic_uint_fast8_t;
using std::atomic_int_fast16_t;
using std::atomic_uint_fast16_t;
using std::atomic_int_fast32_t;
using std::atomic_uint_fast32_t;
using std::atomic_int_fast64_t;
using std::atomic_uint_fast64_t;
using std::atomic_intptr_t;
using std::atomic_uintptr_t;
using std::atomic_size_t;
using std::atomic_ptrdiff_t;
using std::atomic_intmax_t;
using std::atomic_uintmax_t;

// Lock-free atomic types (C++20)
using std::atomic_signed_lock_free;
using std::atomic_unsigned_lock_free;

// Atomic operations on atomic types
using std::atomic_is_lock_free;
using std::atomic_store;
using std::atomic_store_explicit;
using std::atomic_load;
using std::atomic_load_explicit;
using std::atomic_exchange;
using std::atomic_exchange_explicit;
using std::atomic_compare_exchange_weak;
using std::atomic_compare_exchange_weak_explicit;
using std::atomic_compare_exchange_strong;
using std::atomic_compare_exchange_strong_explicit;

// Atomic arithmetic operations
using std::atomic_fetch_add;
using std::atomic_fetch_add_explicit;
using std::atomic_fetch_sub;
using std::atomic_fetch_sub_explicit;
using std::atomic_fetch_and;
using std::atomic_fetch_and_explicit;
using std::atomic_fetch_or;
using std::atomic_fetch_or_explicit;
using std::atomic_fetch_xor;
using std::atomic_fetch_xor_explicit;

// Atomic min/max operations (C++26, may not be available)
#if __cplusplus > 202302L
using std::atomic_fetch_max;
using std::atomic_fetch_max_explicit;
using std::atomic_fetch_min;
using std::atomic_fetch_min_explicit;
#endif

// Atomic flag operations
using std::atomic_flag_test_and_set;
using std::atomic_flag_test_and_set_explicit;
using std::atomic_flag_clear;
using std::atomic_flag_clear_explicit;

// Atomic waiting operations (C++20)
using std::atomic_wait;
using std::atomic_wait_explicit;
using std::atomic_notify_one;
using std::atomic_notify_all;

// Flag waiting operations (C++20)
using std::atomic_flag_wait;
using std::atomic_flag_wait_explicit;
using std::atomic_flag_notify_one;
using std::atomic_flag_notify_all;

// Flag test operations (C++20)
using std::atomic_flag_test;
using std::atomic_flag_test_explicit;

// Fence operations
using std::atomic_thread_fence;
using std::atomic_signal_fence;

// Initialization (C++20)
using std::atomic_init;
}  // namespace std
