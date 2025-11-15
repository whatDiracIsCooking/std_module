/**
 * @file test_ranges.cpp
 * @brief Tests for std_module.ranges
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.ranges;
import std_module.test_framework;

int main() {
    test::test_header("std_module.ranges");

    test::section("Testing symbol accessibility");

    int arr[] = {1, 2, 3, 4, 5};

    // Test range concepts (compile-time checks)
    static_assert(std::ranges::range<int[5]>);
    test::success("range concept");

    static_assert(std::ranges::sized_range<int[5]>);
    test::success("sized_range concept");

    static_assert(std::ranges::random_access_range<int[5]>);
    test::success("random_access_range concept");

    // Test range access functions
    auto b = std::ranges::begin(arr);
    test::assert_equal(*b, 1, "begin");

    auto e = std::ranges::end(arr);
    test::success("end");

    auto s = std::ranges::size(arr);
    test::assert_equal(s, static_cast<size_t>(5), "size");

    auto is_empty = std::ranges::empty(arr);
    test::assert_true(!is_empty, "empty");

    auto d = std::ranges::data(arr);
    test::assert_equal(d[0], 1, "data");

    // Test subrange
    std::ranges::subrange sr(arr + 1, arr + 4);
    test::assert_equal(std::ranges::size(sr), static_cast<size_t>(3), "subrange");

    // Test views
    auto v = std::ranges::views::all(arr);
    test::success("views::all");

    auto filtered = arr | std::ranges::views::filter([](int x) { return x % 2 == 0; });
    test::success("views::filter");

    auto transformed = arr | std::ranges::views::transform([](int x) { return x * 2; });
    test::success("views::transform");

    auto first_three = arr | std::ranges::views::take(3);
    test::success("views::take");

    auto last_two = arr | std::ranges::views::drop(3);
    test::success("views::drop");

    auto reversed = arr | std::ranges::views::reverse;
    test::success("views::reverse");

    // Test special views
    std::ranges::empty_view<int> ev;
    test::assert_true(std::ranges::empty(ev), "empty_view");

    std::ranges::single_view sv(42);
    test::assert_equal(*std::ranges::begin(sv), 42, "single_view");

    std::ranges::iota_view iv(1, 6);
    test::success("iota_view");

    auto counted = std::ranges::views::counted(arr, 3);
    test::success("views::counted");

    test::test_footer();
    return 0;
}
