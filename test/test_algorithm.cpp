/**
 * @file test_algorithm.cpp
 * @brief Tests for std_module.algorithm
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.algorithm;
import std_module.vector;
import std_module.test_framework;

int main() {
    test::test_header("std_module.algorithm");

    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    std::vector<int> dest(8);

    test::section("Testing non-modifying algorithms");

    // Sanity check each category is callable (not testing correctness)
    test::assert_true(std::all_of(vec.begin(), vec.end(), [](int x) { return x >= 0; }), "all_of");
    test::assert_true(std::any_of(vec.begin(), vec.end(), [](int x) { return x > 5; }), "any_of");
    test::assert_true(std::none_of(vec.begin(), vec.end(), [](int x) { return x < 0; }), "none_of");

    auto found = std::find(vec.begin(), vec.end(), 4);
    test::success("find");  // Just test it's callable

    test::assert_true(std::count(vec.begin(), vec.end(), 1) > 0, "count");

    test::section("Testing modifying algorithms");

    std::copy(vec.begin(), vec.end(), dest.begin());
    test::success("copy");

    std::fill(dest.begin(), dest.end(), 0);
    test::success("fill");

    std::transform(vec.begin(), vec.end(), dest.begin(), [](int x) { return x * 2; });
    test::success("transform");

    std::replace(dest.begin(), dest.end(), 0, 1);
    test::success("replace");

    std::reverse(dest.begin(), dest.end());
    test::success("reverse");

    test::section("Testing sorting algorithms");

    std::sort(dest.begin(), dest.end());
    test::success("sort");

    test::assert_true(std::is_sorted(dest.begin(), dest.end()), "is_sorted");
    test::assert_true(std::binary_search(dest.begin(), dest.end(), 2), "binary_search");

    test::section("Testing min/max algorithms");

    test::assert_true(std::min(3, 5) > 0, "min");
    test::assert_true(std::max(3, 5) > 0, "max");

    auto min_it = std::min_element(vec.begin(), vec.end());
    auto max_it = std::max_element(vec.begin(), vec.end());
    test::success("min_element / max_element");  // Just test they're callable

    test::assert_true(std::clamp(10, 0, 5) >= 0, "clamp");

    test::section("Testing heap algorithms");

    std::make_heap(dest.begin(), dest.end());
    test::success("make_heap");

    dest.push_back(99);
    std::push_heap(dest.begin(), dest.end());
    test::success("push_heap");

    std::pop_heap(dest.begin(), dest.end());
    dest.pop_back();
    test::success("pop_heap");

    test::section("Testing permutation algorithms");

    std::vector<int> perm = {1, 2, 3};
    test::assert_true(std::is_permutation(perm.begin(), perm.end(), perm.begin()), "is_permutation");
    test::assert_true(std::next_permutation(perm.begin(), perm.end()), "next_permutation");
    test::assert_true(std::prev_permutation(perm.begin(), perm.end()), "prev_permutation");

    test::section("Testing partitioning algorithms");

    std::partition(dest.begin(), dest.end(), [](int x) { return x % 2 == 0; });
    test::success("partition");

    test::assert_true(std::is_partitioned(dest.begin(), dest.end(), [](int x) { return x % 2 == 0; }), "is_partitioned");

    test::test_footer();
    return 0;
}
