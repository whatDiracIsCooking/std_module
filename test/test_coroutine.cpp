/**
 * @file test_coroutine.cpp
 * @brief Tests for std_module.coroutine
 *
 * Comprehensive test suite for C++20 <coroutine> functionality through modules.
 */

import std_module.coroutine;

#include <iostream>
#include <cassert>

// Test coroutine_handle
void test_coroutine_handle()
{
    std::cout << "\nTesting coroutine_handle:\n";

    // Test default construction
    std::coroutine_handle<> handle;
    assert(!handle);
    assert(handle.address() == nullptr);
    std::cout << "  ✓ Default constructed coroutine_handle is null\n";

    // Test from_address
    void* addr = nullptr;
    auto handle2 = std::coroutine_handle<>::from_address(addr);
    assert(!handle2);
    std::cout << "  ✓ coroutine_handle::from_address works\n";
}

// Test suspend_always and suspend_never
void test_trivial_awaitables()
{
    std::cout << "\nTesting trivial awaitables:\n";

    std::suspend_always always;
    std::suspend_never never;

    assert(always.await_ready() == false);
    assert(never.await_ready() == true);
    std::cout << "  ✓ suspend_always::await_ready() returns false\n";
    std::cout << "  ✓ suspend_never::await_ready() returns true\n";

    // Test await_suspend and await_resume (they're no-ops)
    std::coroutine_handle<> handle;
    always.await_suspend(handle);
    never.await_suspend(handle);
    always.await_resume();
    never.await_resume();
    std::cout << "  ✓ await_suspend and await_resume work\n";
}

// Test noop_coroutine
void test_noop_coroutine()
{
    std::cout << "\nTesting noop_coroutine:\n";

    auto noop = std::noop_coroutine();
    assert(noop);
    assert(!noop.done());
    std::cout << "  ✓ noop_coroutine is valid and not done\n";

    // Resume should be safe to call
    noop.resume();
    std::cout << "  ✓ noop_coroutine can be resumed\n";

    // Get address
    [[maybe_unused]] void* addr = noop.address();
    std::cout << "  ✓ noop_coroutine address can be obtained\n";
}

// Simple generator coroutine example
struct Generator
{
    struct promise_type
    {
        int current_value;

        Generator get_return_object()
        {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }

        std::suspend_always yield_value(int value)
        {
            current_value = value;
            return {};
        }
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator()
    {
        if (handle)
            handle.destroy();
    }

    bool next()
    {
        handle.resume();
        return !handle.done();
    }

    int value() const { return handle.promise().current_value; }
};

Generator counter()
{
    for (int i = 0; i < 3; ++i)
    {
        co_yield i;
    }
}

// Test a simple coroutine
void test_simple_coroutine()
{
    std::cout << "\nTesting simple coroutine:\n";

    auto gen = counter();

    assert(gen.next());
    assert(gen.value() == 0);
    std::cout << "  ✓ First yield: " << gen.value() << "\n";

    assert(gen.next());
    assert(gen.value() == 1);
    std::cout << "  ✓ Second yield: " << gen.value() << "\n";

    assert(gen.next());
    assert(gen.value() == 2);
    std::cout << "  ✓ Third yield: " << gen.value() << "\n";

    assert(!gen.next());
    std::cout << "  ✓ Coroutine completes correctly\n";
}

int main()
{
    std::cout << "=================================\n";
    std::cout << "Testing std_module.coroutine\n";
    std::cout << "=================================\n";

    try
    {
        test_coroutine_handle();
        test_trivial_awaitables();
        test_noop_coroutine();
        test_simple_coroutine();

        std::cout << "\n=================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "=================================\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
