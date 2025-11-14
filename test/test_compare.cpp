/**
 * @file test_compare.cpp
 * @brief Comprehensive tests for std_module.compare
 *
 * Tests all comparison category types, comparison functions, and helper utilities
 * from the C++20 <compare> header.
 */

import std_module.compare;
#include <cassert>
#include <cstdio>
#include <type_traits>

// Test partial_ordering
void test_partial_ordering()
{
    puts("\n=== Testing partial_ordering ===");

    auto less = std::partial_ordering::less;
    auto equivalent = std::partial_ordering::equivalent;
    auto greater = std::partial_ordering::greater;
    auto unordered = std::partial_ordering::unordered;

    // Test comparisons
    assert(less < 0);
    assert(equivalent == 0);
    assert(greater > 0);
    puts("  ✓ Partial ordering basic comparisons");

    // Test is_* functions
    assert(std::is_lt(less));
    assert(std::is_eq(equivalent));
    assert(std::is_gt(greater));
    assert(std::is_neq(less));
    assert(std::is_lteq(less));
    assert(std::is_lteq(equivalent));
    assert(std::is_gteq(greater));
    assert(std::is_gteq(equivalent));
    puts("  ✓ Partial ordering is_* helper functions");
}

// Test weak_ordering
void test_weak_ordering()
{
    puts( "\n=== Testing weak_ordering ===");

    auto less = std::weak_ordering::less;
    auto equivalent = std::weak_ordering::equivalent;
    auto greater = std::weak_ordering::greater;

    assert(less < 0);
    assert(equivalent == 0);
    assert(greater > 0);
    puts( "  ✓ Weak ordering basic comparisons");

    // Conversion to partial_ordering
    std::partial_ordering p = less;
    assert(std::is_lt(p));
    puts( "  ✓ Weak ordering converts to partial ordering");
}

// Test strong_ordering
void test_strong_ordering()
{
    puts( "\n=== Testing strong_ordering ===");

    auto less = std::strong_ordering::less;
    auto equal = std::strong_ordering::equal;
    auto equivalent = std::strong_ordering::equivalent;
    auto greater = std::strong_ordering::greater;

    assert(less < 0);
    assert(equal == 0);
    assert(equivalent == 0);
    assert(equal == equivalent);
    assert(greater > 0);
    puts( "  ✓ Strong ordering basic comparisons");

    // Conversion to weak_ordering
    std::weak_ordering w = less;
    assert(std::is_lt(w));

    // Conversion to partial_ordering
    std::partial_ordering p = less;
    assert(std::is_lt(p));
    puts( "  ✓ Strong ordering converts to weak and partial ordering");
}

// Test common_comparison_category
void test_common_comparison_category()
{
    puts( "\n=== Testing common_comparison_category ===");

    // Single type
    using cat1 = std::common_comparison_category_t<std::strong_ordering>;
    static_assert(std::is_same_v<cat1, std::strong_ordering>);
    puts( "  ✓ common_comparison_category for single strong_ordering");

    // Multiple strong types
    using cat2 = std::common_comparison_category_t<std::strong_ordering, std::strong_ordering>;
    static_assert(std::is_same_v<cat2, std::strong_ordering>);
    puts( "  ✓ common_comparison_category for multiple strong_ordering");

    // Mixed strong and weak
    using cat3 = std::common_comparison_category_t<std::strong_ordering, std::weak_ordering>;
    static_assert(std::is_same_v<cat3, std::weak_ordering>);
    puts( "  ✓ common_comparison_category for mixed strong/weak");

    // Mixed with partial
    using cat4 = std::common_comparison_category_t<std::strong_ordering, std::partial_ordering>;
    static_assert(std::is_same_v<cat4, std::partial_ordering>);
    puts( "  ✓ common_comparison_category for mixed with partial");
}

// Test type with three-way comparison
struct Point {
    int x, y;

    auto operator<=>(const Point&) const = default;
};

void test_three_way_comparable()
{
    puts( "\n=== Testing three_way_comparable ===");

    static_assert(std::three_way_comparable<int>);
    static_assert(std::three_way_comparable<double>);
    static_assert(std::three_way_comparable<Point>);
    puts( "  ✓ three_way_comparable concept");

    static_assert(std::three_way_comparable_with<int, int>);
    static_assert(std::three_way_comparable_with<int, long>);
    puts( "  ✓ three_way_comparable_with concept");
}

// Test compare_three_way
void test_compare_three_way()
{
    puts( "\n=== Testing compare_three_way ===");

    std::compare_three_way cmp;

    auto r1 = cmp(1, 2);
    assert(std::is_lt(r1));

    auto r2 = cmp(5, 5);
    assert(std::is_eq(r2));

    auto r3 = cmp(10, 3);
    assert(std::is_gt(r3));

    puts( "  ✓ compare_three_way function object");

    // Test with custom type
    Point p1{1, 2};
    Point p2{1, 3};
    auto r4 = cmp(p1, p2);
    assert(std::is_lt(r4));
    puts( "  ✓ compare_three_way with custom type");
}

// Test compare_three_way_result
void test_compare_three_way_result()
{
    puts( "\n=== Testing compare_three_way_result ===");

    using result_int = std::compare_three_way_result_t<int>;
    static_assert(std::is_same_v<result_int, std::strong_ordering>);
    puts( "  ✓ compare_three_way_result_t for int");

    using result_double = std::compare_three_way_result_t<double>;
    static_assert(std::is_same_v<result_double, std::partial_ordering>);
    puts( "  ✓ compare_three_way_result_t for double");

    using result_point = std::compare_three_way_result_t<Point>;
    static_assert(std::is_same_v<result_point, std::strong_ordering>);
    puts( "  ✓ compare_three_way_result_t for custom type");
}

// Test strong_order
void test_strong_order()
{
    puts( "\n=== Testing strong_order ===");

    auto r1 = std::strong_order(1, 2);
    assert(std::is_lt(r1));

    auto r2 = std::strong_order(5, 5);
    assert(std::is_eq(r2));

    auto r3 = std::strong_order(10, 3);
    assert(std::is_gt(r3));

    puts( "  ✓ strong_order function");

    Point p1{1, 2};
    Point p2{1, 3};
    auto r4 = std::strong_order(p1, p2);
    assert(std::is_lt(r4));
    puts( "  ✓ strong_order with custom type");
}

// Test weak_order
void test_weak_order()
{
    puts( "\n=== Testing weak_order ===");

    auto r1 = std::weak_order(1, 2);
    assert(std::is_lt(r1));

    auto r2 = std::weak_order(5, 5);
    assert(std::is_eq(r2));

    auto r3 = std::weak_order(10, 3);
    assert(std::is_gt(r3));

    puts( "  ✓ weak_order function");
}

// Test partial_order
void test_partial_order()
{
    puts( "\n=== Testing partial_order ===");

    auto r1 = std::partial_order(1.0, 2.0);
    assert(std::is_lt(r1));

    auto r2 = std::partial_order(5.0, 5.0);
    assert(std::is_eq(r2));

    auto r3 = std::partial_order(10.0, 3.0);
    assert(std::is_gt(r3));

    puts( "  ✓ partial_order function");
}

// Test comparison fallbacks
void test_comparison_fallbacks()
{
    puts( "\n=== Testing comparison fallbacks ===");

    auto r1 = std::compare_strong_order_fallback(1, 2);
    assert(std::is_lt(r1));

    auto r2 = std::compare_weak_order_fallback(5, 5);
    assert(std::is_eq(r2));

    auto r3 = std::compare_partial_order_fallback(10.0, 3.0);
    assert(std::is_gt(r3));

    puts( "  ✓ compare_*_order_fallback functions");
}

int main()
{
    puts( "Testing std_module.compare...");

    test_partial_ordering();
    test_weak_ordering();
    test_strong_ordering();
    test_common_comparison_category();
    test_three_way_comparable();
    test_compare_three_way();
    test_compare_three_way_result();
    test_strong_order();
    test_weak_order();
    test_partial_order();
    test_comparison_fallbacks();

    puts( "\n✓ All tests passed!");
    return 0;
}
