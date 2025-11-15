/**
 * @file test_mutex.cpp
 * @brief Tests for std_module.mutex
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that mutex types and lock guards are accessible through the module.
 */

import std_module.mutex;
import std_module.test_framework;

#include <thread>

int main() {
    test::test_header("std_module.mutex");

    test::section("Testing symbol accessibility");

    // Test basic mutex
    std::mutex mtx;
    mtx.lock();
    mtx.unlock();
    test::success("mutex lock/unlock");

    bool locked = mtx.try_lock();
    test::assert_true(locked, "mutex::try_lock");
    mtx.unlock();

    // Test recursive_mutex
    std::recursive_mutex rmtx;
    rmtx.lock();
    rmtx.lock();  // Can lock multiple times
    rmtx.unlock();
    rmtx.unlock();
    test::success("recursive_mutex");

    // Test timed_mutex
    std::timed_mutex tmtx;
    locked = tmtx.try_lock_for(std::chrono::milliseconds(10));
    test::assert_true(locked, "timed_mutex::try_lock_for");
    tmtx.unlock();

    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
    locked = tmtx.try_lock_until(deadline);
    test::assert_true(locked, "timed_mutex::try_lock_until");
    tmtx.unlock();

    // Test recursive_timed_mutex
    std::recursive_timed_mutex rtmtx;
    locked = rtmtx.try_lock_for(std::chrono::milliseconds(10));
    test::assert_true(locked, "recursive_timed_mutex");
    rtmtx.unlock();

    // Test lock_guard
    {
        std::lock_guard<std::mutex> lock(mtx);
        test::success("lock_guard");
    }

    // Test scoped_lock
    std::mutex mtx1, mtx2;
    {
        std::scoped_lock lock(mtx1, mtx2);
        test::success("scoped_lock");
    }

    // Test unique_lock
    {
        std::unique_lock<std::mutex> lock(mtx);
        test::assert_true(lock.owns_lock(), "unique_lock::owns_lock");
        lock.unlock();
        test::assert_true(!lock.owns_lock(), "unique_lock::unlock");
        lock.lock();
        test::success("unique_lock");
    }

    // Test unique_lock with defer_lock
    {
        std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
        test::assert_true(!lock.owns_lock(), "defer_lock");
        lock.lock();
        test::success("unique_lock with defer_lock");
    }

    // Test call_once
    std::once_flag flag;
    int counter = 0;
    std::call_once(flag, [&]() { counter++; });
    std::call_once(flag, [&]() { counter++; });
    test::assert_true(counter == 1, "call_once");

    // Test lock algorithms
    std::mutex m1, m2, m3;
    std::lock(m1, m2, m3);
    test::success("std::lock");
    m1.unlock();
    m2.unlock();
    m3.unlock();

    int result = std::try_lock(m1, m2, m3);
    test::assert_true(result == -1, "std::try_lock");
    m1.unlock();
    m2.unlock();
    m3.unlock();

    // Test lock tag constants
    std::unique_lock<std::mutex> lock1(mtx, std::defer_lock);
    test::success("std::defer_lock tag");

    std::unique_lock<std::mutex> lock2(mtx, std::try_to_lock);
    test::success("std::try_to_lock tag");
    if (lock2.owns_lock()) lock2.unlock();

    mtx.lock();
    std::unique_lock<std::mutex> lock3(mtx, std::adopt_lock);
    test::success("std::adopt_lock tag");

    test::test_footer();
    return 0;
}
