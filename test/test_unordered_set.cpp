/**
 * @file test_unordered_set.cpp
 * @brief Tests for std_module.unordered_set
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.unordered_set;
import std_module.test_framework;

int main() {
    test::test_header("std_module.unordered_set");

    test::section("Testing symbol accessibility");

    // Basic unordered_set
    std::unordered_set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    test::assert_equal(s.size(), 3ull, "unordered_set construction");

    // insert duplicate
    auto [it, inserted] = s.insert(2);
    test::assert_false(inserted, "insert duplicate");

    // contains (C++20)
    test::assert_true(s.contains(2), "contains");
    test::assert_false(s.contains(99), "contains missing");

    // find
    auto found = s.find(2);
    test::assert_true(found != s.end(), "find");

    // erase
    s.erase(2);
    test::assert_false(s.contains(2), "erase");

    // Iteration
    int sum = 0;
    for (int val : s) {
        sum += val;
    }
    test::assert_true(sum > 0, "iteration");

    // emplace
    s.emplace(10);
    test::assert_true(s.contains(10), "emplace");

    // Bucket interface
    test::assert_true(s.bucket_count() > 0, "bucket_count");
    test::assert_true(s.load_factor() >= 0, "load_factor");
    s.reserve(100);
    test::success("reserve");

    // unordered_multiset
    std::unordered_multiset<int> ms;
    ms.insert(1);
    ms.insert(1);
    ms.insert(1);
    test::assert_equal(ms.count(1), 3ull, "unordered_multiset");

    // erase_if (C++20)
    std::unordered_set<int> s2 = {1, 2, 3, 4, 5};
    std::erase_if(s2, [](int x) { return x % 2 == 0; });
    test::assert_false(s2.contains(2), "erase_if");

    // Hash support
    std::hash<int> hasher;
    test::assert_true(hasher(42) == hasher(42), "hash");

    test::test_footer();
    return 0;
}
