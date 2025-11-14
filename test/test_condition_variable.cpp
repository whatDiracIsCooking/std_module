/**
 * @file test_condition_variable.cpp
 * @brief Comprehensive tests for std_module.condition_variable
 */

import std_module.condition_variable;
#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

// ==============================================================================
// Test 1: Basic condition_variable wait/notify
// ==============================================================================

void test_basic_condition_variable() {
    std::cout << "\n[Test 1] Basic condition_variable functionality\n";

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    // Worker thread
    std::thread worker([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> lock(mtx);
            ready = true;
        }
        cv.notify_one();
    });

    // Wait for notification
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return ready; });
    }

    assert(ready == true);
    std::cout << "  ✓ wait() and notify_one() work correctly\n";

    worker.join();
}

// ==============================================================================
// Test 2: condition_variable with multiple waiters
// ==============================================================================

void test_notify_all() {
    std::cout << "\n[Test 2] notify_all() with multiple waiters\n";

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    int wake_count = 0;

    const int num_threads = 3;
    std::vector<std::thread> threads;

    // Create multiple waiting threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]() { return ready; });
            wake_count++;
        });
    }

    // Give threads time to start waiting
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Wake all threads
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all();

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    assert(wake_count == num_threads);
    std::cout << "  ✓ notify_all() wakes all " << num_threads << " waiting threads\n";
}

// ==============================================================================
// Test 3: wait_for() with timeout
// ==============================================================================

void test_wait_for_timeout() {
    std::cout << "\n[Test 3] wait_for() with timeout\n";

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    std::unique_lock<std::mutex> lock(mtx);

    // Wait for 50ms - should timeout since no one notifies
    auto status = cv.wait_for(lock, std::chrono::milliseconds(50), [&]() { return ready; });

    assert(status == false);  // Timed out
    assert(ready == false);   // Condition not met
    std::cout << "  ✓ wait_for() times out correctly (timeout)\n";
}

// ==============================================================================
// Test 4: wait_for() without timeout
// ==============================================================================

void test_wait_for_no_timeout() {
    std::cout << "\n[Test 4] wait_for() without timeout\n";

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    // Thread that notifies quickly
    std::thread worker([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        {
            std::lock_guard<std::mutex> lock(mtx);
            ready = true;
        }
        cv.notify_one();
    });

    std::unique_lock<std::mutex> lock(mtx);
    auto status = cv.wait_for(lock, std::chrono::milliseconds(200), [&]() { return ready; });

    assert(status == true);   // Notified before timeout
    assert(ready == true);
    std::cout << "  ✓ wait_for() returns before timeout when notified\n";

    worker.join();
}

// ==============================================================================
// Test 5: wait_until() with timeout
// ==============================================================================

void test_wait_until() {
    std::cout << "\n[Test 5] wait_until() functionality\n";

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    std::unique_lock<std::mutex> lock(mtx);

    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(50);
    auto status = cv.wait_until(lock, deadline, [&]() { return ready; });

    assert(status == false);  // Timed out
    assert(ready == false);
    std::cout << "  ✓ wait_until() times out at deadline\n";
}

// ==============================================================================
// Test 6: cv_status enumeration
// ==============================================================================

void test_cv_status() {
    std::cout << "\n[Test 6] cv_status enumeration\n";

    std::mutex mtx;
    std::condition_variable cv;

    std::unique_lock<std::mutex> lock(mtx);

    // Wait with timeout (no predicate version returns cv_status)
    auto status = cv.wait_for(lock, std::chrono::milliseconds(10));

    // Should timeout
    assert(status == std::cv_status::timeout);
    std::cout << "  ✓ cv_status::timeout is correct\n";

    // Test with notification
    bool ready = false;
    std::thread worker([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        {
            std::lock_guard<std::mutex> lk(mtx);
            ready = true;
        }
        cv.notify_one();
    });

    status = cv.wait_for(lock, std::chrono::milliseconds(200));
    assert(status == std::cv_status::no_timeout);
    std::cout << "  ✓ cv_status::no_timeout is correct\n";

    worker.join();
}

// ==============================================================================
// Test 7: condition_variable_any with different lock types
// ==============================================================================

void test_condition_variable_any() {
    std::cout << "\n[Test 7] condition_variable_any functionality\n";

    std::mutex mtx;
    std::condition_variable_any cv_any;
    bool ready = false;

    // Worker thread
    std::thread worker([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        {
            std::lock_guard<std::mutex> lock(mtx);
            ready = true;
        }
        cv_any.notify_one();
    });

    // Wait with unique_lock
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv_any.wait(lock, [&]() { return ready; });
    }

    assert(ready == true);
    std::cout << "  ✓ condition_variable_any works with unique_lock\n";

    worker.join();
}

// ==============================================================================
// Test 8: Producer-consumer pattern
// ==============================================================================

void test_producer_consumer() {
    std::cout << "\n[Test 8] Producer-consumer pattern\n";

    std::mutex mtx;
    std::condition_variable cv;
    std::vector<int> queue;
    bool done = false;

    // Consumer thread
    std::thread consumer([&]() {
        int sum = 0;
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]() { return !queue.empty() || done; });

            while (!queue.empty()) {
                sum += queue.back();
                queue.pop_back();
            }

            if (done && queue.empty()) {
                break;
            }
        }
        // Sum of 1+2+3+4+5 = 15
    });

    // Producer thread
    std::thread producer([&]() {
        for (int i = 1; i <= 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            {
                std::lock_guard<std::mutex> lock(mtx);
                queue.push_back(i);
            }
            cv.notify_one();
        }
        {
            std::lock_guard<std::mutex> lock(mtx);
            done = true;
        }
        cv.notify_one();
    });

    producer.join();
    consumer.join();

    assert(queue.empty());
    std::cout << "  ✓ Producer-consumer pattern works correctly\n";
}

// ==============================================================================
// Test 9: notify_all_at_thread_exit()
// ==============================================================================

void test_notify_all_at_thread_exit() {
    std::cout << "\n[Test 9] notify_all_at_thread_exit()\n";

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    std::thread worker([&]() {
        std::unique_lock<std::mutex> lock(mtx);
        ready = true;
        std::notify_all_at_thread_exit(cv, std::move(lock));
        // Notification will happen when thread exits
    });

    // Wait for notification
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return ready; });
    }

    worker.join();
    assert(ready == true);
    std::cout << "  ✓ notify_all_at_thread_exit() works correctly\n";
}

// ==============================================================================
// Main Test Runner
// ==============================================================================

int main() {
    std::cout << "==============================================\n";
    std::cout << "Testing std_module.condition_variable\n";
    std::cout << "==============================================\n";

    try {
        test_basic_condition_variable();
        test_notify_all();
        test_wait_for_timeout();
        test_wait_for_no_timeout();
        test_wait_until();
        test_cv_status();
        test_condition_variable_any();
        test_producer_consumer();
        test_notify_all_at_thread_exit();

        std::cout << "\n==============================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "==============================================\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
