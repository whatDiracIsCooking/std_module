/**
 * @file test_numeric.cpp
 * @brief Tests for std_module.numeric
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.numeric;
import std_module.test_framework;

int main() {
    test::test_header("std_module.numeric");

    test::section("Testing symbol accessibility");

    int arr[] = {1, 2, 3, 4, 5};
    int result[5];

    // Test basic algorithms are callable
    test::assert_true(std::accumulate(arr, arr + 5, 0) > 0, "accumulate");
    test::assert_true(std::reduce(arr, arr + 5) > 0, "reduce");
    test::assert_true(std::inner_product(arr, arr + 3, arr, 0) >= 0, "inner_product");
    test::assert_true(std::transform_reduce(arr, arr + 3, arr, 0) >= 0, "transform_reduce");

    std::adjacent_difference(arr, arr + 5, result);
    test::success("adjacent_difference");

    std::partial_sum(arr, arr + 5, result);
    test::success("partial_sum");

    std::exclusive_scan(arr, arr + 5, result, 0);
    test::success("exclusive_scan");

    std::inclusive_scan(arr, arr + 5, result);
    test::success("inclusive_scan");

    std::transform_exclusive_scan(arr, arr + 5, result, 0, std::plus<>(), [](int x) { return x; });
    test::success("transform_exclusive_scan");

    std::transform_inclusive_scan(arr, arr + 5, result, std::plus<>(), [](int x) { return x; });
    test::success("transform_inclusive_scan");

    std::iota(result, result + 5, 0);
    test::success("iota");

    // Test gcd, lcm, midpoint
    test::assert_equal(std::gcd(12, 18), 6, "gcd");
    test::assert_equal(std::lcm(4, 6), 12, "lcm");
    test::assert_equal(std::midpoint(10, 20), 15, "midpoint");

    test::test_footer();
    return 0;
}
