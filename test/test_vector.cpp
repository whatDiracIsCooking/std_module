/**
 * @file test_vector.cpp
 * @brief Tests for std_module.vector
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.vector;
import std_module.test_framework;
#include <utility>  // for std::move
#include <cstddef>  // for size_t

int main() {
    test::test_header("std_module.vector");

    test::section("Testing symbol accessibility");

    // Basic construction
    std::vector<int> v1;
    std::vector<int> v2(5);
    std::vector<int> v3(3, 42);
    std::vector<int> v4 = {1, 2, 3, 4, 5};
    test::assert_equal(v4.size(), 5ull, "vector construction");

    // Copy and move
    std::vector<int> v5(v4);
    std::vector<int> v6(std::move(v5));
    test::assert_equal(v6.size(), 5ull, "copy and move");

    // Element access
    test::assert_equal(v4[0], 1, "operator[]");
    test::assert_equal(v4.at(2), 3, "at");
    test::assert_equal(v4.front(), 1, "front");
    test::assert_equal(v4.back(), 5, "back");
    test::assert_true(v4.data() != nullptr, "data");

    // Capacity
    test::assert_false(v4.empty(), "empty");
    test::assert_equal(v4.size(), 5ull, "size");
    test::assert_true(v4.max_size() > 0, "max_size");
    v4.reserve(100);
    test::assert_true(v4.capacity() >= 100, "reserve");
    v4.shrink_to_fit();
    test::success("shrink_to_fit");

    // Modifiers
    v4.push_back(6);
    test::assert_equal(v4.back(), 6, "push_back");
    v4.emplace_back(7);
    test::assert_equal(v4.back(), 7, "emplace_back");
    v4.pop_back();
    test::assert_equal(v4.back(), 6, "pop_back");

    v4.insert(v4.begin(), 0);
    test::assert_equal(v4.front(), 0, "insert");
    v4.emplace(v4.begin() + 1, 99);
    test::success("emplace");
    v4.erase(v4.begin());
    test::success("erase");

    v4.clear();
    test::assert_true(v4.empty(), "clear");

    v4.assign(5, 100);
    test::assert_equal(v4.size(), 5ull, "assign");
    v4.resize(3);
    test::assert_equal(v4.size(), 3ull, "resize");

    // Iterators
    std::vector<int> v7 = {1, 2, 3, 4, 5};
    auto it = v7.begin();
    test::assert_equal(*it, 1, "begin");
    auto eit = v7.end();
    test::success("end");

    // Size-based iteration (avoid range-for which needs operator!=)
    int sum = 0;
    for (size_t i = 0; i < v7.size(); ++i) {
        sum += v7[i];
    }
    test::assert_equal(sum, 15, "index-based iteration");

    // erase and erase_if (C++20)
    std::vector<int> v8 = {1, 2, 3, 2, 4, 2, 5};
    std::erase(v8, 2);
    test::assert_true(v8.size() < 7, "erase");

    std::vector<int> v9 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::erase_if(v9, [](int x) { return x % 2 == 0; });
    test::assert_true(v9.size() < 9, "erase_if");

    // vector<bool>
    std::vector<bool> flags = {true, false, true};
    test::assert_true(flags[0], "vector<bool>");
    flags.flip();
    test::assert_false(flags[0], "flip");

    // swap
    std::vector<int> v10 = {1, 2, 3};
    std::vector<int> v11 = {4, 5, 6, 7};
    v10.swap(v11);
    test::assert_equal(v10.size(), 4ull, "swap");

    test::test_footer();
    return 0;
}
