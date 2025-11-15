/**
 * @file test_latch.cpp
 * @brief Tests for std_module.latch
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that latch synchronization primitive is accessible through the module.
 */

import std_module.latch;
import std_module.test_framework;

#include <thread>

int main() {
    test::test_header("std_module.latch");

    test::section("Testing symbol accessibility");

    // Test latch construction
    std::latch latch1(1);
    std::latch latch5(5);
    test::success("latch construction");

    // Test basic latch operations (single-threaded sanity checks)
    std::latch test_latch(1);
    test_latch.count_down();
    test_latch.wait();
    test::success("count_down and wait");

    // Test arrive_and_wait
    std::latch test_latch2(1);
    test_latch2.arrive_and_wait();
    test::success("arrive_and_wait");

    // Test try_wait
    std::latch test_latch3(2);
    bool ready = test_latch3.try_wait();
    test::assert_true(!ready, "try_wait (not ready)");
    test_latch3.count_down(2);
    ready = test_latch3.try_wait();
    test::assert_true(ready, "try_wait (ready)");

    // Test count_down with parameter
    std::latch test_latch4(5);
    test_latch4.count_down(3);
    test_latch4.count_down(2);
    test::success("count_down with parameter");

    // Quick multithreaded test
    std::latch mt_latch(2);
    std::thread t1([&]() { mt_latch.count_down(); });
    std::thread t2([&]() { mt_latch.count_down(); });
    mt_latch.wait();
    t1.join();
    t2.join();
    test::success("multithreaded coordination");

    test::test_footer();
    return 0;
}
