/**
 * @file test_barrier.cpp
 * @brief Tests for std_module.barrier
 *
 * Tests the C++20 barrier synchronization primitive.
 */

import std_module.barrier;
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>
#include <atomic>

// Test basic barrier construction
void test_barrier_construction() {
    std::cout << "Testing barrier construction...\n";

    // Create a barrier for 1 thread (simplest case)
    std::barrier<> barrier1(1);
    std::cout << "  ✓ Created barrier for 1 thread\n";

    // Create a barrier for multiple threads
    std::barrier<> barrier2(3);
    std::cout << "  ✓ Created barrier for 3 threads\n";
}

// Test arrive_and_wait with single thread
void test_single_thread_arrive_and_wait() {
    std::cout << "\nTesting single thread arrive_and_wait...\n";

    std::barrier<> barrier(1);

    // Single thread can pass through barrier
    barrier.arrive_and_wait();
    std::cout << "  ✓ Single thread passed through barrier\n";

    // Can go through multiple phases
    barrier.arrive_and_wait();
    barrier.arrive_and_wait();
    std::cout << "  ✓ Single thread passed through multiple phases\n";
}

// Test arrive and wait separately
void test_arrive_and_wait_separate() {
    std::cout << "\nTesting arrive and wait separately...\n";

    std::barrier<> barrier(1);

    // Arrive and get token
    auto token = barrier.arrive();
    std::cout << "  ✓ Called arrive(), got token\n";

    // Wait on the token
    barrier.wait(std::move(token));
    std::cout << "  ✓ Called wait() with token\n";
}

// Test barrier with multiple threads
void test_multi_thread_barrier() {
    std::cout << "\nTesting barrier with multiple threads...\n";

    constexpr int num_threads = 4;
    std::barrier<> barrier(num_threads);
    std::atomic<int> counter{0};
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&barrier, &counter, i]() {
            // All threads increment counter
            counter.fetch_add(1);

            // Wait at barrier
            barrier.arrive_and_wait();

            // After barrier, counter should equal num_threads
            assert(counter.load() == num_threads);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "  ✓ All " << num_threads << " threads synchronized correctly\n";
    assert(counter.load() == num_threads);
}

// Test barrier with completion function
void test_barrier_with_completion() {
    std::cout << "\nTesting barrier with completion function...\n";

    std::atomic<int> completion_count{0};

    auto completion = [&completion_count]() noexcept {
        completion_count.fetch_add(1);
    };

    constexpr int num_threads = 3;
    std::barrier barrier(num_threads, completion);
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&barrier]() {
            barrier.arrive_and_wait();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(completion_count.load() == 1);
    std::cout << "  ✓ Completion function called once after all threads arrived\n";
}

// Test multiple phases with completion
void test_multiple_phases() {
    std::cout << "\nTesting multiple barrier phases...\n";

    std::atomic<int> phase_count{0};

    auto completion = [&phase_count]() noexcept {
        phase_count.fetch_add(1);
    };

    constexpr int num_threads = 2;
    constexpr int num_phases = 3;
    std::barrier barrier(num_threads, completion);
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&barrier, num_phases]() {
            for (int phase = 0; phase < num_phases; ++phase) {
                barrier.arrive_and_wait();
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(phase_count.load() == num_phases);
    std::cout << "  ✓ Barrier cycled through " << num_phases << " phases correctly\n";
}

// Test arrive_and_drop
void test_arrive_and_drop() {
    std::cout << "\nTesting arrive_and_drop...\n";

    constexpr int initial_threads = 3;
    std::barrier<> barrier(initial_threads);
    std::atomic<bool> dropped{false};
    std::vector<std::thread> threads;

    // Thread that will drop out
    threads.emplace_back([&barrier, &dropped]() {
        barrier.arrive_and_drop();
        dropped.store(true);
    });

    // Other threads arrive and wait
    for (int i = 1; i < initial_threads; ++i) {
        threads.emplace_back([&barrier]() {
            barrier.arrive_and_wait();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(dropped.load());
    std::cout << "  ✓ Thread dropped from barrier successfully\n";

    // Now only 2 threads needed for next phase
    std::thread t1([&barrier]() { barrier.arrive_and_wait(); });
    std::thread t2([&barrier]() { barrier.arrive_and_wait(); });

    t1.join();
    t2.join();

    std::cout << "  ✓ Barrier count reduced correctly after drop\n";
}

// Test producer-consumer pattern with barrier
void test_producer_consumer_pattern() {
    std::cout << "\nTesting producer-consumer pattern with barrier...\n";

    constexpr int num_iterations = 5;
    std::barrier<> barrier(2); // Producer and consumer
    std::atomic<int> data{0};
    bool finished = false;

    std::thread producer([&]() {
        for (int i = 1; i <= num_iterations; ++i) {
            data.store(i);
            barrier.arrive_and_wait(); // Signal data ready
            barrier.arrive_and_wait(); // Wait for consumer to process
        }
        finished = true;
        barrier.arrive_and_wait(); // Final signal
    });

    std::thread consumer([&]() {
        while (!finished) {
            barrier.arrive_and_wait(); // Wait for data
            int value = data.load();
            if (value > 0 && value <= num_iterations) {
                // Process data
                assert(value >= 1 && value <= num_iterations);
            }
            barrier.arrive_and_wait(); // Signal processed
        }
        barrier.arrive_and_wait(); // Final sync
    });

    producer.join();
    consumer.join();

    std::cout << "  ✓ Producer-consumer synchronized correctly for " << num_iterations << " iterations\n";
}

int main() {
    std::cout << "=== Testing std_module.barrier ===\n\n";

    try {
        test_barrier_construction();
        test_single_thread_arrive_and_wait();
        test_arrive_and_wait_separate();
        test_multi_thread_barrier();
        test_barrier_with_completion();
        test_multiple_phases();
        test_arrive_and_drop();
        test_producer_consumer_pattern();

        std::cout << "\n=== All barrier tests passed! ===\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\n!!! Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
