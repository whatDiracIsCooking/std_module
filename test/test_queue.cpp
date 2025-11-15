/**
 * @file test_queue.cpp
 * @brief Tests for std_module.queue
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.queue;
import std_module.test_framework;
#include <cstddef>  // For size_t

int main() {
    test::test_header("std_module.queue");

    test::section("Testing symbol accessibility");

    // Test basic queue operations
    std::queue<int> q;
    test::assert_true(q.empty(), "queue empty");
    test::assert_equal(q.size(), static_cast<size_t>(0), "queue size");

    q.push(10);
    q.push(20);
    test::assert_equal(q.size(), static_cast<size_t>(2), "push");
    test::assert_equal(q.front(), 10, "front");
    test::assert_equal(q.back(), 20, "back");

    q.pop();
    test::assert_equal(q.front(), 20, "pop");

    q.emplace(30);
    test::success("emplace");

    q.swap(q);
    test::success("swap");

    // Test priority_queue
    std::priority_queue<int> pq;
    test::assert_true(pq.empty(), "priority_queue empty");

    pq.push(30);
    pq.push(10);
    pq.push(50);
    test::assert_equal(pq.top(), 50, "priority_queue top");

    pq.pop();
    test::success("priority_queue pop");

    pq.emplace(40);
    test::success("priority_queue emplace");

    test::test_footer();
    return 0;
}
