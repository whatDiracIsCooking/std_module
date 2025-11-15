/**
 * @file test_barrier.cpp
 * @brief Tests for std_module.barrier
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.barrier;
import std_module.test_framework;

int main() {
    test::test_header("std_module.barrier");

    test::section("Testing symbol accessibility");

    // Test that barrier types and functions are accessible and callable
    // Single-threaded sanity checks - not testing correctness

    // Basic construction
    std::barrier<> barrier1(1);
    test::success("barrier construction with count");

    // Completion function construction
    auto completion = []() noexcept {};
    std::barrier barrier2(1, completion);
    test::success("barrier construction with completion function");

    // arrive_and_wait (single thread)
    barrier1.arrive_and_wait();
    test::success("arrive_and_wait");

    // arrive (returns arrival_token)
    [[maybe_unused]] auto token = barrier2.arrive();
    test::success("arrive");

    // arrive_and_drop
    barrier2.arrive_and_drop();
    test::success("arrive_and_drop");

    test::test_footer();
    return 0;
}
