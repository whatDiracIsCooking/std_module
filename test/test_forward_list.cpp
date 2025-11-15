/**
 * @file test_forward_list.cpp
 * @brief Tests for std_module.forward_list
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.forward_list;
import std_module.test_framework;

int main() {
    test::test_header("std_module.forward_list");

    test::section("Testing construction and basic operations");

    // Test construction (just check it's callable)
    std::forward_list<int> list1;
    test::assert_true(list1.empty(), "default construction");

    std::forward_list<int> list2{1, 2, 3, 4, 5};
    test::assert_false(list2.empty(), "initializer_list construction");
    test::assert_equal(list2.front(), 1, "front");

    std::forward_list<int> list3(5, 42);
    test::success("construction with count and value accessible");

    test::section("Testing iterators");

    // Test iterators (just check they're accessible)
    int sum = 0;
    for (int val : list2) {
        sum += val;
    }
    test::assert_true(sum > 0, "range-based for");

    // Test before_begin
    auto it = list2.before_begin();
    ++it;
    test::assert_equal(*it, 1, "before_begin");

    test::section("Testing capacity operations");

    // Test empty and max_size
    test::assert_false(list2.empty(), "empty");
    auto max = list2.max_size();
    test::assert_true(max > 0, "max_size");

    test::section("Testing modifiers");

    // Test push_front, pop_front
    std::forward_list<int> list4;
    list4.push_front(10);
    test::assert_equal(list4.front(), 10, "push_front");

    list4.pop_front();
    test::assert_true(list4.empty(), "pop_front");

    // Test insert_after, erase_after
    std::forward_list<int> list5{1, 2, 4};
    auto pos = list5.begin();
    list5.insert_after(pos, 99);
    test::success("insert_after accessible");

    pos = list5.begin();
    list5.erase_after(pos);
    test::success("erase_after accessible");

    // Test clear and resize
    list5.clear();
    test::assert_true(list5.empty(), "clear");

    list5.resize(3);
    test::success("resize accessible");

    test::section("Testing list operations");

    // Test sort, reverse, unique
    std::forward_list<int> list6{5, 2, 8, 1, 9};
    list6.sort();
    test::assert_equal(*list6.begin(), 1, "sort");

    list6.reverse();
    test::assert_equal(*list6.begin(), 9, "reverse");

    std::forward_list<int> list7{1, 1, 2, 3, 3};
    list7.unique();
    test::success("unique accessible");

    // Test remove and remove_if
    list6.remove(5);
    test::success("remove accessible");

    list6.remove_if([](int n) { return n % 2 == 0; });
    test::success("remove_if accessible");

    // Test merge
    std::forward_list<int> list8{1, 3, 5};
    std::forward_list<int> list9{2, 4, 6};
    list8.merge(list9);
    test::assert_true(list9.empty(), "merge");

    // Test splice_after
    std::forward_list<int> list10{1, 2, 3};
    std::forward_list<int> list11{10, 20};
    list10.splice_after(list10.begin(), list11);
    test::assert_true(list11.empty(), "splice_after");

    test::section("Testing comparison operators");

    // Test comparison operators (just check they compile)
    std::forward_list<int> list12{1, 2, 3};
    std::forward_list<int> list13{1, 2, 3};
    test::assert_true(list12 == list13, "operator==");
    test::assert_false(list12 != list13, "operator!=");

    test::section("Testing swap");

    // Test swap
    std::forward_list<int> list14{1, 2, 3};
    std::forward_list<int> list15{10, 20};
    list14.swap(list15);
    test::assert_equal(list14.front(), 10, "swap");

    test::section("Testing erase functions (C++20)");

    // Test std::erase and std::erase_if
    std::forward_list<int> list16{1, 2, 3, 2, 4};
    auto removed = std::erase(list16, 2);
    test::assert_true(removed > 0, "std::erase");

    std::forward_list<int> list17{1, 2, 3, 4, 5};
    removed = std::erase_if(list17, [](int n) { return n % 2 == 0; });
    test::assert_true(removed > 0, "std::erase_if");

    test::test_footer();
    return 0;
}
