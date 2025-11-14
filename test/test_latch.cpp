/**
 * @file test_latch.cpp
 * @brief Tests for std_module.latch
 *
 * Tests the C++20 latch synchronization primitive.
 */

import std_module.latch;
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

// Test basic latch construction
void test_latch_construction() {
    std::cout << "Testing latch construction...\n";

    // Create a latch with count 1
    std::latch latch1(1);
    std::cout << "  ✓ Created latch with count 1\n";

    // Create a latch with larger count
    std::latch latch5(5);
    std::cout << "  ✓ Created latch with count 5\n";
}

// Test single thread count_down and wait
void test_single_thread_operations() {
    std::cout << "\nTesting single thread operations...\n";

    std::latch latch(1);

    // Count down
    latch.count_down();
    std::cout << "  ✓ Called count_down()\n";

    // Wait should not block since count is now 0
    latch.wait();
    std::cout << "  ✓ wait() returned immediately after count reached 0\n";
}

// Test arrive_and_wait
void test_arrive_and_wait() {
    std::cout << "\nTesting arrive_and_wait...\n";

    std::latch latch(1);

    // This combines count_down and wait
    latch.arrive_and_wait();
    std::cout << "  ✓ arrive_and_wait() completed\n";
}

// Test try_wait
void test_try_wait() {
    std::cout << "\nTesting try_wait...\n";

    std::latch latch(2);

    // try_wait should return false when count > 0
    bool ready = latch.try_wait();
    assert(!ready);
    std::cout << "  ✓ try_wait() returned false when count > 0\n";

    // Count down to 0
    latch.count_down(2);

    // try_wait should return true when count == 0
    ready = latch.try_wait();
    assert(ready);
    std::cout << "  ✓ try_wait() returned true when count == 0\n";
}

// Test count_down with parameter
void test_count_down_with_parameter() {
    std::cout << "\nTesting count_down with parameter...\n";

    std::latch latch(5);

    // Count down by 3
    latch.count_down(3);

    // Should still be waiting
    bool ready = latch.try_wait();
    assert(!ready);
    std::cout << "  ✓ count_down(3) on latch(5): not ready yet\n";

    // Count down by 2 more
    latch.count_down(2);

    // Should now be ready
    ready = latch.try_wait();
    assert(ready);
    std::cout << "  ✓ count_down(2) more: now ready\n";
}

// Test multi-threaded coordination
void test_multi_thread_coordination() {
    std::cout << "\nTesting multi-thread coordination...\n";

    constexpr int num_threads = 4;
    std::latch latch(num_threads);
    std::atomic<int> ready_count{0};
    std::atomic<int> done_count{0};
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&latch, &ready_count, &done_count]() {
            // Do some setup work
            ready_count.fetch_add(1);

            // Signal ready and wait for all threads
            latch.arrive_and_wait();

            // All threads proceed together
            done_count.fetch_add(1);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(ready_count.load() == num_threads);
    assert(done_count.load() == num_threads);
    std::cout << "  ✓ All " << num_threads << " threads coordinated successfully\n";
}

// Test worker/main thread pattern
void test_worker_main_pattern() {
    std::cout << "\nTesting worker/main thread pattern...\n";

    constexpr int num_workers = 3;
    std::latch work_done(num_workers);
    std::atomic<int> work_completed{0};
    std::vector<std::thread> workers;

    // Spawn worker threads
    for (int i = 0; i < num_workers; ++i) {
        workers.emplace_back([&work_done, &work_completed, i]() {
            // Simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * (i + 1)));
            work_completed.fetch_add(1);

            // Signal work complete
            work_done.count_down();
        });
    }

    // Main thread waits for all workers
    work_done.wait();

    assert(work_completed.load() == num_workers);
    std::cout << "  ✓ Main thread waited for all " << num_workers << " workers\n";

    for (auto& t : workers) {
        t.join();
    }
}

// Test start gate pattern
void test_start_gate_pattern() {
    std::cout << "\nTesting start gate pattern...\n";

    std::latch start_gate(1);
    constexpr int num_threads = 5;
    std::atomic<bool> all_started{false};
    std::vector<std::thread> threads;
    std::atomic<int> started_count{0};

    // Create threads that wait for start signal
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&start_gate, &started_count]() {
            // Wait for start signal
            start_gate.wait();

            // Start working
            started_count.fetch_add(1);
        });
    }

    // Give threads time to reach the wait
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Open the gate
    start_gate.count_down();

    for (auto& t : threads) {
        t.join();
    }

    assert(started_count.load() == num_threads);
    std::cout << "  ✓ Start gate released all " << num_threads << " threads\n";
}

// Test multiple count_downs from different threads
void test_distributed_count_down() {
    std::cout << "\nTesting distributed count_down...\n";

    constexpr int num_threads = 6;
    std::latch latch(num_threads);
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&latch]() {
            // Each thread counts down once
            latch.count_down();
        });
    }

    // Main thread waits
    latch.wait();
    std::cout << "  ✓ Distributed count_down from " << num_threads << " threads completed\n";

    for (auto& t : threads) {
        t.join();
    }
}

// Test latch is single-use
void test_single_use_latch() {
    std::cout << "\nTesting single-use nature of latch...\n";

    std::latch latch(1);

    latch.count_down();
    latch.wait();

    // Wait again - should return immediately since count is still 0
    latch.wait();
    std::cout << "  ✓ Multiple wait() calls work on depleted latch\n";

    // try_wait should still return true
    bool ready = latch.try_wait();
    assert(ready);
    std::cout << "  ✓ Latch stays in released state\n";
}

int main() {
    std::cout << "=== Testing std_module.latch ===\n\n";

    try {
        test_latch_construction();
        test_single_thread_operations();
        test_arrive_and_wait();
        test_try_wait();
        test_count_down_with_parameter();
        test_multi_thread_coordination();
        test_worker_main_pattern();
        test_start_gate_pattern();
        test_distributed_count_down();
        test_single_use_latch();

        std::cout << "\n=== All latch tests passed! ===\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\n!!! Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
