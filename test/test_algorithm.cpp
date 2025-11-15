/**
 * @file test_algorithm.cpp
 * @brief Tests for std_module.algorithm
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.algorithm;
import std_module.test_framework;

int main() {
    test::test_header("std_module.algorithm");

    // Use raw arrays to avoid vector dependency
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int dest[8] = {};
    const int size = 8;

    test::section("Testing non-modifying algorithms");

    // Sanity check each category is callable (not testing correctness)
    test::assert_true(std::all_of(arr, arr + size, [](int x) { return x >= 0; }), "all_of");
    test::assert_true(std::any_of(arr, arr + size, [](int x) { return x > 5; }), "any_of");
    test::assert_true(std::none_of(arr, arr + size, [](int x) { return x < 0; }), "none_of");

    auto found = std::find(arr, arr + size, 4);
    test::success("find");  // Just test it's callable

    test::assert_true(std::count(arr, arr + size, 1) > 0, "count");

    test::section("Testing modifying algorithms");

    std::copy(arr, arr + size, dest);
    test::success("copy");

    std::fill(dest, dest + size, 0);
    test::success("fill");

    std::transform(arr, arr + size, dest, [](int x) { return x * 2; });
    test::success("transform");

    std::replace(dest, dest + size, 0, 1);
    test::success("replace");

    std::reverse(dest, dest + size);
    test::success("reverse");

    test::section("Testing sorting algorithms");

    std::sort(dest, dest + size);
    test::success("sort");

    test::assert_true(std::is_sorted(dest, dest + size), "is_sorted");
    test::assert_true(std::binary_search(dest, dest + size, 2), "binary_search");

    test::section("Testing min/max algorithms");

    test::assert_true(std::min(3, 5) > 0, "min");
    test::assert_true(std::max(3, 5) > 0, "max");

    auto min_it = std::min_element(arr, arr + size);
    auto max_it = std::max_element(arr, arr + size);
    test::success("min_element / max_element");  // Just test they're callable

    test::assert_true(std::clamp(10, 0, 5) >= 0, "clamp");

    test::section("Testing heap algorithms");

    int heap[] = {1, 2, 3, 4, 5};
    int heap_size = 5;

    std::make_heap(heap, heap + heap_size);
    test::success("make_heap");

    std::push_heap(heap, heap + heap_size);
    test::success("push_heap");

    std::pop_heap(heap, heap + heap_size);
    test::success("pop_heap");

    test::section("Testing permutation algorithms");

    int perm[] = {1, 2, 3};
    test::assert_true(std::is_permutation(perm, perm + 3, perm), "is_permutation");
    test::assert_true(std::next_permutation(perm, perm + 3), "next_permutation");
    test::assert_true(std::prev_permutation(perm, perm + 3), "prev_permutation");

    test::section("Testing partitioning algorithms");

    std::partition(dest, dest + size, [](int x) { return x % 2 == 0; });
    test::success("partition");

    test::assert_true(std::is_partitioned(dest, dest + size, [](int x) { return x % 2 == 0; }), "is_partitioned");

    test::test_footer();
    return 0;
}
