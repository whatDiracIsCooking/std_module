/**
 * @file test_thread.cpp
 * @brief Tests for std_module.thread
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.thread;
import std_module.test_framework;

int main() {
    test::test_header("std_module.thread");

    test::section("Testing symbol accessibility");

    // Basic thread
    std::thread t([]() {});
    test::assert_true(t.joinable(), "thread construction");
    t.join();
    test::assert_false(t.joinable(), "join");

    // Thread ID
    std::thread::id id = std::this_thread::get_id();
    test::assert_true(id != std::thread::id(), "get_id");

    // Hardware concurrency
    unsigned int cores = std::thread::hardware_concurrency();
    test::success("hardware_concurrency");

    // this_thread functions
    std::this_thread::yield();
    test::success("yield");

    // jthread (C++20)
    std::jthread jt([]() {});
    test::assert_true(jt.joinable(), "jthread");

    // jthread with stop token
    std::jthread jt2([](std::stop_token st) {
        while (!st.stop_requested()) {
            break;
        }
    });
    jt2.request_stop();
    test::success("jthread with stop_token");

    test::test_footer();
    return 0;
}
