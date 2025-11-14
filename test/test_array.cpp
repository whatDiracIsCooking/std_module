/**
 * @file test_array.cpp
 * @brief Tests for std_module.array
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.array;
import std_module.stdexcept;
import std_module.test_framework;

int main() {
    test::test_header("std_module.array");

    test::section("Testing construction and element access");

    // Sanity check each operation is callable (not testing correctness)
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    test::assert_true(arr.size() == 5, "size()");
    test::assert_true(arr[0] == 1, "operator[]");
    test::assert_true(arr.at(2) == 3, "at()");
    test::assert_true(arr.front() == 1, "front()");
    test::assert_true(arr.back() == 5, "back()");
    test::assert_true(arr.data() != nullptr, "data()");

    // std::get
    test::assert_true(std::get<0>(arr) == 1, "std::get");

    test::section("Testing bounds checking");

    try {
        arr.at(10);
        test::failure("at() should throw out_of_range");
    } catch (const std::out_of_range&) {
        test::success("at() throws out_of_range");
    }

    test::section("Testing iterators");

    int sum = 0;
    for (int val : arr) {
        sum += val;
    }
    test::assert_true(sum == 15, "range-based for");

    test::section("Testing capacity");

    test::assert_true(arr.max_size() == 5, "max_size()");
    test::assert_false(arr.empty(), "empty()");

    std::array<int, 0> empty_arr{};
    test::assert_true(empty_arr.empty(), "zero-size array");

    test::section("Testing operations");

    std::array<int, 3> arr1 = {1, 2, 3};
    std::array<int, 3> arr2 = {4, 5, 6};

    arr1.swap(arr2);
    test::assert_true(arr1[0] == 4, "swap()");

    arr1.fill(99);
    test::assert_true(arr1[0] == 99, "fill()");

    test::section("Testing to_array (C++20)");

    auto arr3 = std::to_array({1, 2, 3});
    test::assert_true(arr3.size() == 3, "to_array");

    test::test_footer();
    return 0;
}
