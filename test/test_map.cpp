/**
 * @file test_map.cpp
 * @brief Tests for std_module.map
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that map/multimap containers are accessible through the module.
 */

import std_module.map;
import std_module.test_framework;

#include <string>

int main() {
    test::test_header("std_module.map");

    test::section("Testing symbol accessibility");

    // Test basic map operations
    std::map<int, std::string> ages;
    ages[25] = "Alice";
    ages[30] = "Bob";
    test::assert_true(ages.size() == 2, "construction and insertion");
    test::assert_true(ages[25] == "Alice", "operator[]");

    // Test insert
    auto result = ages.insert({20, "Charlie"});
    test::assert_true(result.second, "insert");

    auto result2 = ages.insert_or_assign(25, "Alicia");
    test::success("insert_or_assign");

    // Test find and contains
    auto it = ages.find(25);
    test::assert_true(it != ages.end(), "find");
    test::assert_true(ages.contains(25), "contains");
    test::assert_true(ages.count(25) == 1, "count");

    // Test erase
    ages.erase(30);
    test::success("erase");

    ages.clear();
    test::assert_true(ages.empty(), "clear");

    // Test emplace
    ages.emplace(1, "One");
    ages.try_emplace(2, "Two");
    test::success("emplace, try_emplace");

    // Test bounds
    std::map<int, char> m{{10, 'a'}, {20, 'b'}, {30, 'c'}};
    auto lb = m.lower_bound(15);
    auto ub = m.upper_bound(20);
    auto eq = m.equal_range(20);
    test::success("lower_bound, upper_bound, equal_range");

    // Test multimap
    std::multimap<std::string, int> grades;
    grades.insert({"Alice", 95});
    grades.insert({"Alice", 92});
    test::assert_true(grades.count("Alice") == 2, "multimap");

    // Test erase_if (C++20)
    std::map<int, int> nums{{1, 1}, {2, 4}, {3, 9}, {4, 16}};
    auto removed = std::erase_if(nums, [](const auto& p) { return p.first % 2 == 0; });
    test::assert_true(removed > 0, "erase_if");

    test::test_footer();
    return 0;
}
