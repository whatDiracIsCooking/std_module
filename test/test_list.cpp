/**
 * @file test_list.cpp
 * @brief Tests for std_module.list
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that list container and operations are accessible through the module.
 */

import std_module.list;
import std_module.test_framework;

int main() {
    test::test_header("std_module.list");

    test::section("Testing symbol accessibility");

    // Test basic construction and operations
    std::list<int> lst{1, 2, 3, 4, 5};
    test::assert_true(lst.size() == 5, "construction and size");
    test::assert_true(lst.front() == 1, "front");
    test::assert_true(lst.back() == 5, "back");

    // Test modifiers
    lst.push_back(6);
    lst.push_front(0);
    lst.pop_back();
    lst.pop_front();
    test::success("push_back, push_front, pop_back, pop_front");

    lst.insert(lst.begin(), 99);
    lst.erase(lst.begin());
    test::success("insert, erase");

    lst.resize(10, 42);
    lst.clear();
    test::success("resize, clear");

    // Test iterators
    lst = {1, 2, 3};
    int sum = 0;
    for (int val : lst) sum += val;
    test::assert_true(sum > 0, "range-based for / iterators");

    // Test list operations
    std::list<int> lst2{5, 2, 8, 1};
    lst2.sort();
    test::success("sort");

    lst2.reverse();
    test::success("reverse");

    std::list<int> lst3{1, 1, 2, 2, 3};
    lst3.unique();
    test::success("unique");

    std::list<int> lst4{1, 2, 3, 2, 4};
    lst4.remove(2);
    test::success("remove");

    std::list<int> lst5{1, 2, 3, 4, 5};
    lst5.remove_if([](int n) { return n % 2 == 0; });
    test::success("remove_if");

    // Test merge and splice
    std::list<int> a{1, 3, 5};
    std::list<int> b{2, 4, 6};
    a.merge(b);
    test::success("merge");

    std::list<int> c{1, 2, 3};
    std::list<int> d{4, 5, 6};
    c.splice(c.end(), d);
    test::success("splice");

    // Test emplace
    std::list<int> lst6;
    lst6.emplace_back(42);
    lst6.emplace_front(1);
    test::success("emplace_back, emplace_front");

    // Test erase/erase_if (C++20)
    std::list<int> lst7{1, 2, 3, 2, 4};
    auto count = std::erase(lst7, 2);
    test::assert_true(count > 0, "std::erase");

    std::list<int> lst8{1, 2, 3, 4, 5};
    count = std::erase_if(lst8, [](int n) { return n % 2 == 0; });
    test::assert_true(count > 0, "std::erase_if");

    test::test_footer();
    return 0;
}
