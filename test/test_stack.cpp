/**
 * @file test_stack.cpp
 * @brief Tests for std_module.stack
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.stack;
import std_module.test_framework;
#include <cstddef>  // For size_t

int main() {
    test::test_header("std_module.stack");

    test::section("Testing symbol accessibility");

    // Test basic stack operations
    std::stack<int> s;
    test::assert_true(s.empty(), "empty");
    test::assert_equal(s.size(), static_cast<size_t>(0), "size");

    s.push(10);
    s.push(20);
    s.push(30);
    test::assert_equal(s.size(), static_cast<size_t>(3), "push");
    test::assert_equal(s.top(), 30, "top");

    s.pop();
    test::assert_equal(s.size(), static_cast<size_t>(2), "pop");
    test::assert_equal(s.top(), 20, "top after pop");

    s.emplace(40);
    test::assert_equal(s.top(), 40, "emplace");

    // Test swap
    std::stack<int> s2;
    s2.push(100);
    s.swap(s2);
    test::assert_equal(s.top(), 100, "swap");

    // Test LIFO behavior
    std::stack<int> lifo;
    lifo.push(1);
    lifo.push(2);
    lifo.push(3);
    test::assert_equal(lifo.top(), 3, "LIFO order");
    lifo.pop();
    test::assert_equal(lifo.top(), 2, "LIFO order");
    lifo.pop();
    test::assert_equal(lifo.top(), 1, "LIFO order");

    test::test_footer();
    return 0;
}
