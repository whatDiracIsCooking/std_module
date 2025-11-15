/**
 * @file test_iterator.cpp
 * @brief Tests for std_module.iterator
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that iterator utilities and types are accessible through the module.
 */

import std_module.iterator;
import std_module.test_framework;

#include <vector>  // For testing iterators

int main() {
    test::test_header("std_module.iterator");

    test::section("Testing symbol accessibility");

    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Test iterator operations
    auto it = vec.begin();
    std::advance(it, 2);
    auto dist = std::distance(vec.begin(), vec.end());
    auto it2 = std::next(vec.begin(), 3);
    auto it3 = std::prev(vec.end(), 1);
    test::success("advance, distance, next, prev");

    // Test reverse_iterator
    std::reverse_iterator<std::vector<int>::iterator> rit(vec.end());
    auto rit2 = std::make_reverse_iterator(vec.end());
    test::success("reverse_iterator and make_reverse_iterator");

    // Test move_iterator
    auto move_it = std::make_move_iterator(vec.begin());
    test::success("make_move_iterator");

    // Test insert iterators
    std::vector<int> vec2;
    auto back_it = std::back_inserter(vec2);
    *back_it = 10;
    test::success("back_inserter");

    std::vector<int> vec3 = {1, 2, 5};
    auto ins_it = std::inserter(vec3, vec3.begin() + 2);
    *ins_it = 3;
    test::success("inserter");

    // Test container access functions
    auto b = std::begin(vec);
    auto e = std::end(vec);
    auto cb = std::cbegin(vec);
    auto ce = std::cend(vec);
    auto rb = std::rbegin(vec);
    auto re = std::rend(vec);
    auto crb = std::crbegin(vec);
    auto cre = std::crend(vec);
    test::success("begin, end, cbegin, cend, rbegin, rend, crbegin, crend");

    // Test container operations
    auto s = std::size(vec);
    auto ss = std::ssize(vec);
    bool empty = std::empty(vec);
    int* ptr = std::data(vec);
    test::success("size, ssize, empty, data");

    // Test iterator_traits
    using traits = std::iterator_traits<std::vector<int>::iterator>;
    test::success("iterator_traits");

    // Test C++20 iterators
    auto counted = std::counted_iterator(vec.begin(), 3);
    test::success("counted_iterator");

    std::common_iterator<std::counted_iterator<std::vector<int>::iterator>, std::default_sentinel_t>
        common_it(std::counted_iterator(vec.begin(), 2));
    test::success("common_iterator");

    test::assert_true(vec.begin() != std::unreachable_sentinel, "unreachable_sentinel");

    // Test ranges iter operations
    std::vector<int> vec4 = {1, 2, 3};
    std::vector<int> vec5 = {0, 0, 0};
    std::ranges::iter_swap(vec4.begin(), vec5.begin());
    test::success("ranges::iter_swap");

    test::test_footer();
    return 0;
}
