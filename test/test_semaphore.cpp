/**
 * @file test_semaphore.cpp
 * @brief Tests for std_module.semaphore
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.semaphore;
import std_module.chrono;  // For milliseconds, steady_clock
import std_module.test_framework;

int main() {
    test::test_header("std_module.semaphore");

    test::section("Testing symbol accessibility");

    // Test binary_semaphore
    std::binary_semaphore sem0(0);
    test::success("binary_semaphore construction (0)");

    std::binary_semaphore sem1(1);
    test::success("binary_semaphore construction (1)");

    // Test counting_semaphore
    std::counting_semaphore<10> csem(5);
    test::success("counting_semaphore construction");

    // Test acquire/release
    sem1.acquire();
    test::success("acquire");

    sem1.release();
    test::success("release");

    // Test try_acquire
    test::assert_true(sem1.try_acquire(), "try_acquire (should succeed)");
    test::assert_true(!sem1.try_acquire(), "try_acquire (should fail)");

    sem1.release();

    // Test try_acquire_for
    test::assert_true(sem1.try_acquire_for(std::chrono::milliseconds(10)), "try_acquire_for");

    sem1.release();

    // Test try_acquire_until
    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
    test::assert_true(sem1.try_acquire_until(deadline), "try_acquire_until");

    sem1.release();

    // Test counting_semaphore with multiple permits
    csem.acquire();
    csem.acquire();
    test::success("multiple acquires");

    csem.release();
    csem.release();
    test::success("multiple releases");

    // Test release with count
    csem.release(3);
    test::success("release(n)");

    csem.acquire();
    csem.acquire();
    csem.acquire();

    test::test_footer();
    return 0;
}
