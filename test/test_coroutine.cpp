/**
 * @file test_coroutine.cpp
 * @brief Tests for std_module.coroutine
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.coroutine;
import std_module.test_framework;

int main() {
    test::test_header("std_module.coroutine");

    test::section("Testing coroutine_handle symbols");

    // Test default construction and basic operations
    std::coroutine_handle<> handle;
    test::assert_true(!handle, "default coroutine_handle is null");
    test::assert_true(handle.address() == nullptr, "address() is nullptr");

    auto handle2 = std::coroutine_handle<>::from_address(nullptr);
    test::assert_true(!handle2, "from_address works");

    test::section("Testing trivial awaitables");

    // Test suspend_always
    std::suspend_always always;
    test::assert_true(always.await_ready() == false, "suspend_always::await_ready");
    always.await_suspend(handle);
    always.await_resume();
    test::success("suspend_always methods callable");

    // Test suspend_never
    std::suspend_never never;
    test::assert_true(never.await_ready() == true, "suspend_never::await_ready");
    never.await_suspend(handle);
    never.await_resume();
    test::success("suspend_never methods callable");

    test::section("Testing noop_coroutine");

    auto noop = std::noop_coroutine();
    test::assert_true(static_cast<bool>(noop), "noop_coroutine is valid");
    test::assert_true(!noop.done(), "noop_coroutine not done");
    noop.resume();
    [[maybe_unused]] void* addr = noop.address();
    test::success("noop_coroutine methods callable");

    test::test_footer();
    return 0;
}
