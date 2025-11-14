/**
 * @file test_compare.cpp
 * @brief Tests for std_module.compare
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.compare;
import std_module.test_framework;

#include <type_traits>  // TEMP: For is_same_v

// Test type with three-way comparison
struct Point {
    int x, y;
    auto operator<=>(const Point&) const = default;
};

int main() {
    test::test_header("std_module.compare");

    test::section("Testing comparison categories");

    // Test that comparison category types are accessible
    [[maybe_unused]] auto less_p = std::partial_ordering::less;
    [[maybe_unused]] auto equiv_p = std::partial_ordering::equivalent;
    [[maybe_unused]] auto greater_p = std::partial_ordering::greater;
    [[maybe_unused]] auto unordered_p = std::partial_ordering::unordered;

    [[maybe_unused]] auto less_w = std::weak_ordering::less;
    [[maybe_unused]] auto equiv_w = std::weak_ordering::equivalent;
    [[maybe_unused]] auto greater_w = std::weak_ordering::greater;

    [[maybe_unused]] auto less_s = std::strong_ordering::less;
    [[maybe_unused]] auto equal_s = std::strong_ordering::equal;
    [[maybe_unused]] auto equiv_s = std::strong_ordering::equivalent;
    [[maybe_unused]] auto greater_s = std::strong_ordering::greater;
    test::success("comparison category types accessible");

    test::section("Testing comparison helper functions");

    // Test that is_* helper functions are callable
    test::assert_true(std::is_lt(less_p), "is_lt");
    test::assert_true(std::is_eq(equal_s), "is_eq");
    test::assert_true(std::is_gt(greater_p), "is_gt");
    test::assert_true(std::is_neq(less_p), "is_neq");
    test::assert_true(std::is_lteq(less_p), "is_lteq");
    test::assert_true(std::is_gteq(greater_p), "is_gteq");

    test::section("Testing comparison category conversions");

    // Test conversions are callable
    std::partial_ordering p = less_w;
    std::weak_ordering w = less_s;
    test::success("comparison category conversions");

    test::section("Testing common_comparison_category");

    // Test trait is accessible (compile-time check)
    using cat1 = std::common_comparison_category_t<std::strong_ordering>;
    using cat2 = std::common_comparison_category_t<std::strong_ordering, std::weak_ordering>;
    using cat3 = std::common_comparison_category_t<std::strong_ordering, std::partial_ordering>;
    static_assert(std::is_same_v<cat1, std::strong_ordering>);
    static_assert(std::is_same_v<cat2, std::weak_ordering>);
    static_assert(std::is_same_v<cat3, std::partial_ordering>);
    test::success("common_comparison_category trait");

    test::section("Testing three_way_comparable concept");

    // Test concept is accessible (compile-time check)
    static_assert(std::three_way_comparable<int>);
    static_assert(std::three_way_comparable<double>);
    static_assert(std::three_way_comparable<Point>);
    static_assert(std::three_way_comparable_with<int, int>);
    static_assert(std::three_way_comparable_with<int, long>);
    test::success("three_way_comparable concept");

    test::section("Testing compare_three_way");

    // Test compare_three_way is constructible and callable
    std::compare_three_way cmp;
    auto r1 = cmp(1, 2);
    auto r2 = cmp(5, 5);
    Point p1{1, 2};
    Point p2{1, 3};
    auto r3 = cmp(p1, p2);
    test::assert_true(std::is_lt(r1), "compare_three_way");

    test::section("Testing compare_three_way_result");

    // Test trait is accessible (compile-time check)
    using result_int = std::compare_three_way_result_t<int>;
    using result_double = std::compare_three_way_result_t<double>;
    using result_point = std::compare_three_way_result_t<Point>;
    static_assert(std::is_same_v<result_int, std::strong_ordering>);
    static_assert(std::is_same_v<result_double, std::partial_ordering>);
    static_assert(std::is_same_v<result_point, std::strong_ordering>);
    test::success("compare_three_way_result trait");

    test::section("Testing comparison order functions");

    // Test that strong_order, weak_order, partial_order are callable
    auto so = std::strong_order(1, 2);
    auto wo = std::weak_order(1, 2);
    auto po = std::partial_order(1.0, 2.0);
    test::assert_true(std::is_lt(so), "strong_order");
    test::assert_true(std::is_lt(wo), "weak_order");
    test::assert_true(std::is_lt(po), "partial_order");

    test::section("Testing comparison fallback functions");

    // Test that fallback functions are callable
    auto sof = std::compare_strong_order_fallback(1, 2);
    auto wof = std::compare_weak_order_fallback(1, 2);
    auto pof = std::compare_partial_order_fallback(1.0, 2.0);
    test::assert_true(std::is_lt(sof), "compare_strong_order_fallback");
    test::assert_true(std::is_lt(wof), "compare_weak_order_fallback");
    test::assert_true(std::is_lt(pof), "compare_partial_order_fallback");

    test::test_footer();
    return 0;
}
