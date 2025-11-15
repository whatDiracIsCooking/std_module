/**
 * @file test_unordered_map.cpp
 * @brief Tests for std_module.unordered_map
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.unordered_map;
import std_module.test_framework;

int main() {
    test::test_header("std_module.unordered_map");

    test::section("Testing symbol accessibility");

    // Basic unordered_map
    std::unordered_map<int, int> m;
    m[1] = 10;
    m[2] = 20;
    test::assert_equal(m.size(), 2ull, "unordered_map construction");

    // insert
    auto [it, inserted] = m.insert({3, 30});
    test::assert_true(inserted, "insert");

    // find
    auto found = m.find(2);
    test::assert_true(found != m.end(), "find");

    // erase
    m.erase(2);
    test::assert_true(m.find(2) == m.end(), "erase");

    // Iteration
    int count = 0;
    for ([[maybe_unused]] const auto& [k, v] : m) {
        count++;
    }
    test::assert_true(count > 0, "iteration");

    // emplace and try_emplace
    m.emplace(4, 40);
    m.try_emplace(5, 50);
    test::assert_true(m.size() > 2, "emplace/try_emplace");

    // Bucket interface
    test::assert_true(m.bucket_count() > 0, "bucket_count");
    test::assert_true(m.load_factor() >= 0, "load_factor");
    m.rehash(100);
    test::success("rehash");

    // contains (C++20)
    test::assert_true(m.contains(1), "contains");

    // unordered_multimap
    std::unordered_multimap<int, int> mm;
    mm.insert({1, 10});
    mm.insert({1, 20});
    test::assert_equal(mm.count(1), 2ull, "unordered_multimap");

    // erase_if (C++20)
    std::unordered_map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}};
    std::erase_if(m2, [](const auto& p) { return p.first == 2; });
    test::assert_false(m2.contains(2), "erase_if");

    test::test_footer();
    return 0;
}
