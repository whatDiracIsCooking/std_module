/**
 * @file test_span.cpp
 * @brief Tests for std_module.span
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.span;
import std_module.test_framework;

int main() {
    test::test_header("std_module.span");

    test::section("Testing symbol accessibility");

    int arr[] = {1, 2, 3, 4, 5};

    // Test span construction
    std::span<int> s(arr);
    test::assert_equal(s.size(), static_cast<size_t>(5), "span construction");

    // Test fixed extent
    std::span<int, 5> s_fixed(arr);
    static_assert(s_fixed.extent == 5);
    test::success("fixed extent span");

    // Test dynamic extent
    std::span<int, std::dynamic_extent> s_dynamic(arr);
    static_assert(s_dynamic.extent == std::dynamic_extent);
    test::success("dynamic extent span");

    // Test element access
    test::assert_equal(s[0], 1, "operator[]");
    test::assert_equal(s.front(), 1, "front");
    test::assert_equal(s.back(), 5, "back");
    test::assert_true(s.data() == arr, "data");

    // Test iterators
    int sum = 0;
    for (int x : s) sum += x;
    test::assert_equal(sum, 15, "range-based for");

    test::assert_equal(*s.begin(), 1, "begin");
    test::assert_equal(*(s.end() - 1), 5, "end");
    test::assert_equal(*s.rbegin(), 5, "rbegin");
    test::assert_equal(*(s.rend() - 1), 1, "rend");

    // Test subspan operations
    auto first3 = s.first(3);
    test::assert_equal(first3.size(), static_cast<size_t>(3), "first");

    auto last2 = s.last(2);
    test::assert_equal(last2.size(), static_cast<size_t>(2), "last");

    auto sub = s.subspan(1, 3);
    test::assert_equal(sub.size(), static_cast<size_t>(3), "subspan");
    test::assert_equal(sub[0], 2, "subspan content");

    // Test size operations
    test::assert_equal(s.size(), static_cast<size_t>(5), "size");
    test::assert_equal(s.size_bytes(), static_cast<size_t>(5 * sizeof(int)), "size_bytes");
    test::assert_true(!s.empty(), "empty");

    // Test empty span
    std::span<int> empty_s;
    test::assert_true(empty_s.empty(), "empty span");
    test::assert_true(empty_s.data() == nullptr, "empty span data");

    // Test as_bytes
    auto bytes = std::as_bytes(s);
    test::assert_equal(bytes.size(), static_cast<size_t>(5 * sizeof(int)), "as_bytes");

    // Test as_writable_bytes
    auto writable_bytes = std::as_writable_bytes(s);
    test::assert_equal(writable_bytes.size(), static_cast<size_t>(5 * sizeof(int)), "as_writable_bytes");

    // Test deduction guides
    std::span s_deduced(arr);
    test::assert_equal(s_deduced.size(), static_cast<size_t>(5), "deduction guide");

    test::test_footer();
    return 0;
}
