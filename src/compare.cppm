/**
 * @file compare.cppm
 * @brief C++20 compare module wrapper
 */

module;

#include <compare>

export module std_module.compare;

export namespace std
{
// Comparison category types
using std::partial_ordering;
using std::weak_ordering;
using std::strong_ordering;

// Common comparison category type
using std::common_comparison_category;
using std::common_comparison_category_t;

// Comparison concepts
using std::three_way_comparable;
using std::three_way_comparable_with;

// Comparison function objects
using std::compare_three_way;
using std::compare_three_way_result;
using std::compare_three_way_result_t;
using std::compare_partial_order_fallback;
using std::compare_weak_order_fallback;
using std::compare_strong_order_fallback;

// Named comparison functions
using std::strong_order;
using std::weak_order;
using std::partial_order;

// Type trait for synthesized three-way comparison
using std::is_eq;
using std::is_neq;
using std::is_lt;
using std::is_lteq;
using std::is_gt;
using std::is_gteq;
}  // namespace std
