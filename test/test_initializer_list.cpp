/**
 * @file test_initializer_list.cpp
 * @brief Tests for std_module.initializer_list
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.initializer_list;
import std_module.test_framework;

// Helper function to test passing initializer_list
int sum_values(std::initializer_list<int> list) {
    int sum = 0;
    for (auto val : list) {
        sum += val;
    }
    return sum;
}

int main() {
    test::test_header("std_module.initializer_list");

    test::section("Testing basic construction");

    // Test initializer_list construction
    std::initializer_list<int> list1 = {1, 2, 3, 4, 5};
    test::assert_equal(list1.size(), 5u, "size");
    test::assert_equal(*list1.begin(), 1, "begin");

    // Test empty list
    std::initializer_list<int> list2;
    test::assert_equal(list2.size(), 0u, "empty list size");
    test::assert_true(list2.begin() == list2.end(), "empty list begin==end");

    test::section("Testing iteration");

    // Test range-based for loop
    std::initializer_list<int> list3 = {10, 20, 30};
    int sum = 0;
    for (int val : list3) {
        sum += val;
    }
    test::assert_equal(sum, 60, "range-based for");

    // Test begin/end iteration
    sum = 0;
    for (auto it = list3.begin(); it != list3.end(); ++it) {
        sum += *it;
    }
    test::assert_equal(sum, 60, "iterator-based iteration");

    test::section("Testing std::begin and std::end");

    // Test std::begin and std::end
    std::initializer_list<int> list4 = {1, 2, 3};
    auto it_begin = std::begin(list4);
    auto it_end = std::end(list4);
    test::assert_equal(*it_begin, 1, "std::begin");
    int count = 0;
    for (auto it = it_begin; it != it_end; ++it) {
        count++;
    }
    test::assert_equal(count, 3, "std::begin/end iteration");

    test::section("Testing function parameter passing");

    // Test passing initializer_list to function
    auto result = sum_values({1, 2, 3, 4, 5});
    test::assert_equal(result, 15, "function parameter");

    result = sum_values({10, 20});
    test::assert_equal(result, 30, "function parameter variation");

    test::section("Testing with different types");

    // Test with string
    std::initializer_list<test::string> str_list = {"hello", "world"};
    test::assert_equal(str_list.size(), 2u, "string initializer_list");
    test::assert_equal(*str_list.begin(), "hello", "string first element");

    // Test with double
    std::initializer_list<double> dbl_list = {1.5, 2.5, 3.5};
    test::assert_equal(dbl_list.size(), 3u, "double initializer_list");

    test::section("Testing copy semantics");

    // Test copy
    std::initializer_list<int> list5 = {1, 2, 3};
    std::initializer_list<int> list6 = list5;
    test::assert_equal(list5.size(), list6.size(), "copy preserves size");
    test::assert_true(list5.begin() == list6.begin(), "shallow copy");

    test::section("Testing auto deduction");

    // Test auto deduction
    auto list7 = {1, 2, 3, 4, 5};
    // Type should be std::initializer_list<int>
    test::assert_equal(list7.size(), 5u, "auto deduction");

    test::test_footer();
    return 0;
}
