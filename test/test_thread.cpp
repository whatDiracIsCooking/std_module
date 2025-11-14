/**
 * @file test_thread.cpp
 * @brief Comprehensive tests for std_module.thread
 *
 * Tests all exported symbols from <thread> including:
 * - std::thread class
 * - std::jthread class (C++20)
 * - Thread identification and manipulation functions
 * - this_thread namespace functions
 */

import std_module.thread;

#include <iostream>
#include <cassert>
#include <vector>
#include <atomic>
#include <chrono>

// Global counter for testing
std::atomic<int> counter{0};

// Simple function to run in a thread
void increment_counter(int n)
{
    for (int i = 0; i < n; ++i) {
        counter++;
    }
}

// Function that takes multiple arguments
void add_to_counter(int a, int b)
{
    counter += a + b;
}

// Test basic thread creation and joining
void test_basic_thread()
{
    std::cout << "\n=== Testing Basic Thread Creation ===\n";

    counter = 0;

    std::thread t1(increment_counter, 100);
    std::thread t2(increment_counter, 200);

    assert(t1.joinable());
    assert(t2.joinable());
    std::cout << "  ✓ Threads are joinable after creation\n";

    t1.join();
    t2.join();

    assert(!t1.joinable());
    assert(!t2.joinable());
    std::cout << "  ✓ Threads are not joinable after join\n";

    assert(counter == 300);
    std::cout << "  ✓ Counter incremented correctly: " << counter << "\n";
}

// Test thread with multiple arguments
void test_thread_arguments()
{
    std::cout << "\n=== Testing Thread with Arguments ===\n";

    counter = 0;

    std::thread t(add_to_counter, 10, 20);
    t.join();

    assert(counter == 30);
    std::cout << "  ✓ Thread executed with arguments: counter = " << counter << "\n";
}

// Test thread with lambda
void test_thread_lambda()
{
    std::cout << "\n=== Testing Thread with Lambda ===\n";

    counter = 0;

    std::thread t([]() {
        counter = 42;
    });
    t.join();

    assert(counter == 42);
    std::cout << "  ✓ Lambda executed in thread: counter = " << counter << "\n";
}

// Test thread ID
void test_thread_id()
{
    std::cout << "\n=== Testing Thread ID ===\n";

    std::thread::id main_id = std::this_thread::get_id();
    std::cout << "  ✓ Main thread ID obtained\n";

    std::thread::id worker_id;
    std::thread t([&worker_id]() {
        worker_id = std::this_thread::get_id();
    });
    t.join();

    assert(main_id != worker_id);
    std::cout << "  ✓ Worker thread has different ID from main thread\n";

    // Default constructed ID
    std::thread::id default_id;
    std::thread t2;
    assert(t2.get_id() == default_id);
    std::cout << "  ✓ Default-constructed thread has default ID\n";
}

// Test hardware concurrency
void test_hardware_concurrency()
{
    std::cout << "\n=== Testing Hardware Concurrency ===\n";

    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "  ✓ Hardware concurrency: " << cores << " cores\n";

    // Should be at least 1 (though 0 is allowed if not computable)
    if (cores > 0) {
        std::cout << "  ✓ Hardware concurrency is available\n";
    } else {
        std::cout << "  ⚠ Hardware concurrency not computable\n";
    }
}

// Test this_thread::yield
void test_yield()
{
    std::cout << "\n=== Testing this_thread::yield ===\n";

    counter = 0;

    std::thread t([]() {
        for (int i = 0; i < 10; ++i) {
            counter++;
            std::this_thread::yield();  // Give other threads a chance
        }
    });

    t.join();
    assert(counter == 10);
    std::cout << "  ✓ this_thread::yield executed successfully\n";
}

// Test this_thread::sleep_for
void test_sleep_for()
{
    std::cout << "\n=== Testing this_thread::sleep_for ===\n";

    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    assert(duration.count() >= 90);  // Allow some variance
    std::cout << "  ✓ sleep_for(100ms) slept for approximately " << duration.count() << "ms\n";
}

// Test this_thread::sleep_until
void test_sleep_until()
{
    std::cout << "\n=== Testing this_thread::sleep_until ===\n";

    auto wake_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(100);
    std::this_thread::sleep_until(wake_time);
    auto now = std::chrono::steady_clock::now();

    assert(now >= wake_time);
    std::cout << "  ✓ sleep_until executed successfully\n";
}

// Test jthread (C++20) - RAII thread that joins automatically
void test_jthread()
{
    std::cout << "\n=== Testing jthread (C++20) ===\n";

    counter = 0;

    {
        std::jthread jt(increment_counter, 50);
        assert(jt.joinable());
        std::cout << "  ✓ jthread is joinable after creation\n";
        // jt automatically joins when it goes out of scope
    }

    // Give a moment for the thread to finish
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    assert(counter == 50);
    std::cout << "  ✓ jthread automatically joined on destruction: counter = " << counter << "\n";
}

// Test jthread with stop token
void test_jthread_stop_token()
{
    std::cout << "\n=== Testing jthread with Stop Token ===\n";

    counter = 0;

    std::jthread jt([](std::stop_token st) {
        while (!st.stop_requested()) {
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (counter >= 10) break;
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    jt.request_stop();

    // jt will join automatically on destruction

    std::cout << "  ✓ jthread with stop token executed: counter = " << counter << "\n";
}

// Test move semantics
void test_thread_move()
{
    std::cout << "\n=== Testing Thread Move Semantics ===\n";

    counter = 0;

    std::thread t1(increment_counter, 10);
    std::thread t2 = std::move(t1);

    assert(!t1.joinable());
    assert(t2.joinable());
    std::cout << "  ✓ Thread moved successfully\n";

    t2.join();
    assert(counter == 10);
    std::cout << "  ✓ Moved thread executed correctly\n";
}

// Test multiple threads
void test_multiple_threads()
{
    std::cout << "\n=== Testing Multiple Threads ===\n";

    counter = 0;

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(increment_counter, 10);
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(counter == 100);
    std::cout << "  ✓ 10 threads executed successfully: counter = " << counter << "\n";
}

int main()
{
    std::cout << "Testing std_module.thread\n";
    std::cout << "=========================\n";

    test_basic_thread();
    test_thread_arguments();
    test_thread_lambda();
    test_thread_id();
    test_hardware_concurrency();
    test_yield();
    test_sleep_for();
    test_sleep_until();
    test_jthread();
    test_jthread_stop_token();
    test_thread_move();
    test_multiple_threads();

    std::cout << "\n✓ All thread tests passed!\n";
    return 0;
}
