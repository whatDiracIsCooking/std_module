/**
 * @file test_set.cpp
 * @brief Tests for std_module.set
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.set;
import std_module.test_framework;

int main() {
    test::test_header("std_module.set");

    test::section("Testing symbol accessibility");

    // Test basic set operations
    std::set<int> s;
    test::assert_true(s.empty(), "empty");
    test::assert_equal(s.size(), static_cast<size_t>(0), "size");

    auto [it1, inserted1] = s.insert(42);
    test::assert_true(inserted1, "insert");
    test::assert_equal(*it1, 42, "insert iterator");

    auto [it2, inserted2] = s.insert(42);
    test::assert_true(!inserted2, "insert duplicate");

    s.insert(10);
    s.insert(30);
    test::assert_equal(s.size(), static_cast<size_t>(3), "size after inserts");

    // Test lookup
    auto it = s.find(30);
    test::assert_true(it != s.end(), "find");

    test::assert_equal(s.count(30), static_cast<size_t>(1), "count");

    test::assert_true(s.contains(30), "contains (C++20)");

    it = s.lower_bound(25);
    test::assert_equal(*it, 30, "lower_bound");

    it = s.upper_bound(10);
    test::assert_equal(*it, 30, "upper_bound");

    // Test modification
    size_t erased = s.erase(30);
    test::assert_equal(erased, static_cast<size_t>(1), "erase by value");

    s.clear();
    test::assert_true(s.empty(), "clear");

    // Test emplace
    auto [it3, inserted3] = s.emplace(100);
    test::assert_true(inserted3, "emplace");

    auto it4 = s.emplace_hint(s.begin(), 200);
    test::assert_equal(*it4, 200, "emplace_hint");

    // Test iterators
    s.clear();
    s.insert(1);
    s.insert(2);
    s.insert(3);

    int sum = 0;
    for (int val : s) sum += val;
    test::assert_equal(sum, 6, "range-based for");

    sum = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it) sum += *it;
    test::assert_equal(sum, 6, "reverse iteration");

    // Test swap
    std::set<int> s2 = {10, 20};
    s.swap(s2);
    test::assert_true(s.contains(10), "swap");

    // Test multiset
    std::multiset<int> ms;
    ms.insert(42);
    ms.insert(42);
    test::assert_equal(ms.count(42), static_cast<size_t>(2), "multiset allows duplicates");

    auto [first, last] = ms.equal_range(42);
    test::success("equal_range");

    // Test extract and merge (C++17)
    s.clear();
    s.insert(1);
    s.insert(2);
    auto node = s.extract(1);
    test::assert_true(!s.contains(1), "extract");

    s.insert(std::move(node));
    test::assert_true(s.contains(1), "reinsert node");

    std::set<int> s3 = {3, 4};
    s.merge(s3);
    test::assert_true(s.contains(3), "merge");

    test::test_footer();
    return 0;
}
