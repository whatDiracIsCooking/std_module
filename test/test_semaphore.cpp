/**
 * @file test_semaphore.cpp
 * @brief Tests for std_module.semaphore
 *
 * Tests the C++20 semaphore synchronization primitives.
 */

import std_module.semaphore;
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

// Test binary_semaphore construction
void test_binary_semaphore_construction() {
    std::cout << "Testing binary_semaphore construction...\n";

    // Binary semaphore starts at 0
    std::binary_semaphore sem0(0);
    std::cout << "  ✓ Created binary_semaphore with count 0\n";

    // Binary semaphore starts at 1
    std::binary_semaphore sem1(1);
    std::cout << "  ✓ Created binary_semaphore with count 1\n";
}

// Test counting_semaphore construction
void test_counting_semaphore_construction() {
    std::cout << "\nTesting counting_semaphore construction...\n";

    // Counting semaphore with various initial counts
    std::counting_semaphore<10> sem0(0);
    std::cout << "  ✓ Created counting_semaphore<10> with count 0\n";

    std::counting_semaphore<10> sem5(5);
    std::cout << "  ✓ Created counting_semaphore<10> with count 5\n";

    std::counting_semaphore<100> sem100(100);
    std::cout << "  ✓ Created counting_semaphore<100> with count 100\n";
}

// Test binary_semaphore acquire and release
void test_binary_semaphore_acquire_release() {
    std::cout << "\nTesting binary_semaphore acquire and release...\n";

    std::binary_semaphore sem(1);

    // Acquire the semaphore
    sem.acquire();
    std::cout << "  ✓ Acquired binary_semaphore\n";

    // Release the semaphore
    sem.release();
    std::cout << "  ✓ Released binary_semaphore\n";

    // Acquire again
    sem.acquire();
    std::cout << "  ✓ Acquired again\n";

    sem.release();
}

// Test try_acquire
void test_try_acquire() {
    std::cout << "\nTesting try_acquire...\n";

    std::binary_semaphore sem(1);

    // Should succeed
    bool acquired = sem.try_acquire();
    assert(acquired);
    std::cout << "  ✓ try_acquire() succeeded when count > 0\n";

    // Should fail (count is now 0)
    acquired = sem.try_acquire();
    assert(!acquired);
    std::cout << "  ✓ try_acquire() failed when count == 0\n";

    // Release and try again
    sem.release();
    acquired = sem.try_acquire();
    assert(acquired);
    std::cout << "  ✓ try_acquire() succeeded after release\n";

    sem.release();
}

// Test try_acquire_for
void test_try_acquire_for() {
    std::cout << "\nTesting try_acquire_for...\n";

    std::binary_semaphore sem(0);

    auto start = std::chrono::steady_clock::now();

    // Should timeout
    bool acquired = sem.try_acquire_for(std::chrono::milliseconds(50));
    assert(!acquired);

    auto elapsed = std::chrono::steady_clock::now() - start;
    assert(elapsed >= std::chrono::milliseconds(40)); // Allow some slack

    std::cout << "  ✓ try_acquire_for() timed out correctly\n";

    // Release and try with timeout
    sem.release();
    acquired = sem.try_acquire_for(std::chrono::milliseconds(50));
    assert(acquired);
    std::cout << "  ✓ try_acquire_for() succeeded when available\n";
}

// Test try_acquire_until
void test_try_acquire_until() {
    std::cout << "\nTesting try_acquire_until...\n";

    std::binary_semaphore sem(0);

    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(50);

    // Should timeout
    bool acquired = sem.try_acquire_until(deadline);
    assert(!acquired);
    std::cout << "  ✓ try_acquire_until() timed out correctly\n";

    // Release and try with deadline
    sem.release();
    deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(50);
    acquired = sem.try_acquire_until(deadline);
    assert(acquired);
    std::cout << "  ✓ try_acquire_until() succeeded when available\n";
}

// Test counting_semaphore with multiple permits
void test_counting_semaphore_multiple_permits() {
    std::cout << "\nTesting counting_semaphore with multiple permits...\n";

    std::counting_semaphore<5> sem(3);

    // Acquire 3 times
    sem.acquire();
    sem.acquire();
    sem.acquire();
    std::cout << "  ✓ Acquired 3 permits\n";

    // try_acquire should fail
    bool acquired = sem.try_acquire();
    assert(!acquired);
    std::cout << "  ✓ try_acquire() failed when all permits taken\n";

    // Release 2
    sem.release();
    sem.release();
    std::cout << "  ✓ Released 2 permits\n";

    // Can acquire 2 now
    sem.acquire();
    sem.acquire();
    std::cout << "  ✓ Acquired 2 permits after release\n";

    sem.release(2);
}

// Test semaphore with multiple threads
void test_multi_thread_semaphore() {
    std::cout << "\nTesting semaphore with multiple threads...\n";

    constexpr int max_concurrent = 3;
    constexpr int num_threads = 10;

    std::counting_semaphore<max_concurrent> sem(max_concurrent);
    std::atomic<int> concurrent_count{0};
    std::atomic<int> max_observed{0};
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&sem, &concurrent_count, &max_observed, i]() {
            sem.acquire();

            int current = concurrent_count.fetch_add(1) + 1;

            // Update max observed
            int prev_max = max_observed.load();
            while (current > prev_max && !max_observed.compare_exchange_weak(prev_max, current)) {
                prev_max = max_observed.load();
            }

            // Simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            concurrent_count.fetch_sub(1);
            sem.release();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(max_observed.load() <= max_concurrent);
    std::cout << "  ✓ Max concurrent threads: " << max_observed.load() << " (limit: " << max_concurrent << ")\n";
}

// Test producer-consumer with semaphores
void test_producer_consumer() {
    std::cout << "\nTesting producer-consumer pattern...\n";

    constexpr int buffer_size = 5;
    constexpr int num_items = 20;

    std::counting_semaphore<buffer_size> empty_slots(buffer_size);
    std::counting_semaphore<buffer_size> full_slots(0);
    std::atomic<int> produced{0};
    std::atomic<int> consumed{0};

    std::thread producer([&]() {
        for (int i = 0; i < num_items; ++i) {
            empty_slots.acquire();
            produced.fetch_add(1);
            full_slots.release();
        }
    });

    std::thread consumer([&]() {
        for (int i = 0; i < num_items; ++i) {
            full_slots.acquire();
            consumed.fetch_add(1);
            empty_slots.release();
        }
    });

    producer.join();
    consumer.join();

    assert(produced.load() == num_items);
    assert(consumed.load() == num_items);
    std::cout << "  ✓ Produced and consumed " << num_items << " items successfully\n";
}

// Test binary_semaphore as mutex alternative
void test_binary_semaphore_as_mutex() {
    std::cout << "\nTesting binary_semaphore as mutex alternative...\n";

    std::binary_semaphore sem(1);
    int shared_counter = 0;
    constexpr int num_threads = 10;
    constexpr int increments_per_thread = 1000;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&sem, &shared_counter]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                sem.acquire();
                ++shared_counter;
                sem.release();
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(shared_counter == num_threads * increments_per_thread);
    std::cout << "  ✓ Binary semaphore protected " << shared_counter << " increments correctly\n";
}

// Test release with count parameter
void test_release_with_count() {
    std::cout << "\nTesting release with count parameter...\n";

    std::counting_semaphore<10> sem(0);

    // Release multiple at once
    sem.release(5);
    std::cout << "  ✓ Released 5 permits at once\n";

    // Acquire 5 times
    for (int i = 0; i < 5; ++i) {
        bool acquired = sem.try_acquire();
        assert(acquired);
    }
    std::cout << "  ✓ Successfully acquired all 5 permits\n";

    // Should fail now
    bool acquired = sem.try_acquire();
    assert(!acquired);
    std::cout << "  ✓ try_acquire() correctly failed after all permits used\n";
}

// Test semaphore with work queue pattern
void test_work_queue_pattern() {
    std::cout << "\nTesting work queue pattern...\n";

    constexpr int num_workers = 3;
    constexpr int num_tasks = 10;

    std::counting_semaphore<num_tasks> tasks_available(0);
    std::atomic<int> tasks_completed{0};
    std::atomic<bool> done{false};
    std::vector<std::thread> workers;

    // Worker threads
    for (int i = 0; i < num_workers; ++i) {
        workers.emplace_back([&]() {
            while (!done.load() || tasks_available.try_acquire()) {
                if (tasks_available.try_acquire_for(std::chrono::milliseconds(10))) {
                    // Process task
                    tasks_completed.fetch_add(1);
                }
            }
        });
    }

    // Add tasks
    std::thread task_adder([&]() {
        for (int i = 0; i < num_tasks; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            tasks_available.release();
        }
        done.store(true);
    });

    task_adder.join();

    // Give workers time to finish
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    for (auto& w : workers) {
        w.join();
    }

    assert(tasks_completed.load() == num_tasks);
    std::cout << "  ✓ Work queue processed all " << num_tasks << " tasks\n";
}

int main() {
    std::cout << "=== Testing std_module.semaphore ===\n\n";

    try {
        test_binary_semaphore_construction();
        test_counting_semaphore_construction();
        test_binary_semaphore_acquire_release();
        test_try_acquire();
        test_try_acquire_for();
        test_try_acquire_until();
        test_counting_semaphore_multiple_permits();
        test_multi_thread_semaphore();
        test_producer_consumer();
        test_binary_semaphore_as_mutex();
        test_release_with_count();
        test_work_queue_pattern();

        std::cout << "\n=== All semaphore tests passed! ===\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\n!!! Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
