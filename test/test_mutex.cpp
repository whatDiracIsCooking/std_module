/**
 * @file test_mutex.cpp
 * @brief Comprehensive tests for std_module.mutex
 *
 * Tests all mutex types, lock guards, and synchronization primitives
 * exported by the mutex module.
 *
 * Note: shared_mutex, shared_timed_mutex, and shared_lock are in <shared_mutex>
 * header, not <mutex>, so they are not tested here.
 */

import std_module.mutex;

#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include <vector>

// Test basic mutex operations
void test_basic_mutex() {
    std::cout << "\n=== Testing std::mutex ===\n";

    std::mutex mtx;
    int counter = 0;

    // Lock and unlock
    mtx.lock();
    counter++;
    mtx.unlock();
    assert(counter == 1);
    std::cout << "  ✓ Basic lock/unlock: " << counter << "\n";

    // try_lock
    bool locked = mtx.try_lock();
    assert(locked == true);
    counter++;
    mtx.unlock();
    assert(counter == 2);
    std::cout << "  ✓ try_lock successful: " << counter << "\n";
}

// Test recursive mutex
void test_recursive_mutex() {
    std::cout << "\n=== Testing std::recursive_mutex ===\n";

    std::recursive_mutex rmtx;
    int depth = 0;

    // Multiple locks by same thread
    rmtx.lock();
    depth++;
    rmtx.lock();
    depth++;
    rmtx.lock();
    depth++;
    assert(depth == 3);
    std::cout << "  ✓ Recursive locking depth: " << depth << "\n";

    rmtx.unlock();
    rmtx.unlock();
    rmtx.unlock();
    std::cout << "  ✓ Recursive unlocking successful\n";
}

// Test timed mutex
void test_timed_mutex() {
    std::cout << "\n=== Testing std::timed_mutex ===\n";

    std::timed_mutex tmtx;

    // try_lock_for
    bool locked = tmtx.try_lock_for(std::chrono::milliseconds(10));
    assert(locked == true);
    std::cout << "  ✓ try_lock_for successful\n";
    tmtx.unlock();

    // try_lock_until
    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
    locked = tmtx.try_lock_until(deadline);
    assert(locked == true);
    std::cout << "  ✓ try_lock_until successful\n";
    tmtx.unlock();
}

// Test recursive timed mutex
void test_recursive_timed_mutex() {
    std::cout << "\n=== Testing std::recursive_timed_mutex ===\n";

    std::recursive_timed_mutex rtmtx;

    // Recursive timed locking
    bool locked1 = rtmtx.try_lock_for(std::chrono::milliseconds(10));
    bool locked2 = rtmtx.try_lock_for(std::chrono::milliseconds(10));
    assert(locked1 == true);
    assert(locked2 == true);
    std::cout << "  ✓ Recursive timed locking successful\n";

    rtmtx.unlock();
    rtmtx.unlock();
}


// Test lock_guard
void test_lock_guard() {
    std::cout << "\n=== Testing std::lock_guard ===\n";

    std::mutex mtx;
    int value = 0;

    {
        std::lock_guard<std::mutex> lock(mtx);
        value = 42;
        std::cout << "  ✓ lock_guard acquired, value set to: " << value << "\n";
    }
    // lock_guard destructor releases the lock
    assert(value == 42);
    std::cout << "  ✓ lock_guard automatically released\n";

    // Test with adopt_lock
    mtx.lock();
    {
        std::lock_guard<std::mutex> lock(mtx, std::adopt_lock);
        value = 100;
        std::cout << "  ✓ lock_guard with adopt_lock, value: " << value << "\n";
    }
}

// Test scoped_lock
void test_scoped_lock() {
    std::cout << "\n=== Testing std::scoped_lock ===\n";

    std::mutex mtx1, mtx2;
    int value1 = 0, value2 = 0;

    {
        std::scoped_lock lock(mtx1, mtx2);
        value1 = 10;
        value2 = 20;
        std::cout << "  ✓ scoped_lock with multiple mutexes: "
                  << value1 << ", " << value2 << "\n";
    }
    assert(value1 == 10);
    assert(value2 == 20);
    std::cout << "  ✓ scoped_lock automatically released all mutexes\n";
}

// Test unique_lock
void test_unique_lock() {
    std::cout << "\n=== Testing std::unique_lock ===\n";

    std::mutex mtx;
    int value = 0;

    // Basic usage
    {
        std::unique_lock<std::mutex> lock(mtx);
        value = 50;
        assert(lock.owns_lock());
        std::cout << "  ✓ unique_lock acquired, value: " << value << "\n";
    }

    // Deferred locking
    {
        std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
        assert(!lock.owns_lock());
        std::cout << "  ✓ unique_lock with defer_lock (not locked yet)\n";

        lock.lock();
        assert(lock.owns_lock());
        value = 75;
        std::cout << "  ✓ Manually locked, value: " << value << "\n";
    }

    // Try to lock
    {
        std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
        if (lock.owns_lock()) {
            value = 99;
            std::cout << "  ✓ unique_lock with try_to_lock succeeded, value: " << value << "\n";
        }
    }

    // Adopt lock
    mtx.lock();
    {
        std::unique_lock<std::mutex> lock(mtx, std::adopt_lock);
        assert(lock.owns_lock());
        value = 200;
        std::cout << "  ✓ unique_lock with adopt_lock, value: " << value << "\n";
    }

    // unlock and lock methods
    {
        std::unique_lock<std::mutex> lock(mtx);
        lock.unlock();
        assert(!lock.owns_lock());
        std::cout << "  ✓ unique_lock.unlock() successful\n";

        lock.lock();
        assert(lock.owns_lock());
        std::cout << "  ✓ unique_lock.lock() successful\n";
    }
}


// Test call_once
void test_call_once() {
    std::cout << "\n=== Testing std::call_once ===\n";

    std::once_flag flag;
    int counter = 0;

    auto init_func = [&counter]() {
        counter++;
        std::cout << "  ✓ Initialization function called\n";
    };

    // Call multiple times - should only execute once
    std::call_once(flag, init_func);
    std::call_once(flag, init_func);
    std::call_once(flag, init_func);

    assert(counter == 1);
    std::cout << "  ✓ Function executed exactly once, counter: " << counter << "\n";
}

// Test lock and try_lock algorithms
void test_lock_algorithms() {
    std::cout << "\n=== Testing lock/try_lock algorithms ===\n";

    std::mutex mtx1, mtx2, mtx3;

    // std::lock - locks all mutexes in deadlock-free manner
    std::lock(mtx1, mtx2, mtx3);
    std::cout << "  ✓ std::lock acquired all 3 mutexes\n";
    mtx1.unlock();
    mtx2.unlock();
    mtx3.unlock();

    // std::try_lock - tries to lock all mutexes
    int result = std::try_lock(mtx1, mtx2, mtx3);
    assert(result == -1);  // -1 means all locks acquired
    std::cout << "  ✓ std::try_lock acquired all 3 mutexes, result: " << result << "\n";
    mtx1.unlock();
    mtx2.unlock();
    mtx3.unlock();
}

// Test multithreaded scenario
void test_multithreaded() {
    std::cout << "\n=== Testing multithreaded scenario ===\n";

    std::mutex mtx;
    int shared_counter = 0;
    const int num_threads = 10;
    const int increments_per_thread = 100;

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                std::lock_guard<std::mutex> lock(mtx);
                shared_counter++;
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    int expected = num_threads * increments_per_thread;
    assert(shared_counter == expected);
    std::cout << "  ✓ Multithreaded increment: " << shared_counter
              << " (expected: " << expected << ")\n";
}

// Test lock tag constants
void test_lock_tags() {
    std::cout << "\n=== Testing lock tag constants ===\n";

    std::mutex mtx;

    // Test that tag constants exist and can be used
    std::unique_lock<std::mutex> lock1(mtx, std::defer_lock);
    std::cout << "  ✓ std::defer_lock tag available\n";

    lock1.lock();
    lock1.unlock();

    std::unique_lock<std::mutex> lock2(mtx, std::try_to_lock);
    if (lock2.owns_lock()) {
        std::cout << "  ✓ std::try_to_lock tag available\n";
        lock2.unlock();
    }

    mtx.lock();
    std::unique_lock<std::mutex> lock3(mtx, std::adopt_lock);
    std::cout << "  ✓ std::adopt_lock tag available\n";
}

int main() {
    std::cout << "Testing std_module.mutex\n";
    std::cout << "========================================\n";

    try {
        test_basic_mutex();
        test_recursive_mutex();
        test_timed_mutex();
        test_recursive_timed_mutex();
        test_lock_guard();
        test_scoped_lock();
        test_unique_lock();
        test_call_once();
        test_lock_algorithms();
        test_multithreaded();
        test_lock_tags();

        std::cout << "\n========================================\n";
        std::cout << "All mutex tests passed! ✓\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
