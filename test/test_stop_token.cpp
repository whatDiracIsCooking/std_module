/**
 * @file test_stop_token.cpp
 * @brief Tests for the C++20 stop_token module wrapper
 */

import std_module.stop_token;

#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

void test_basic_stop_token()
{
    std::cout << "\n=== Testing Basic Stop Token ===" << std::endl;

    // Create a stop_source
    std::stop_source source;
    assert(source.stop_possible());
    assert(!source.stop_requested());
    std::cout << "  ✓ Created stop_source" << std::endl;

    // Get a stop_token from the source
    std::stop_token token = source.get_token();
    assert(token.stop_possible());
    assert(!token.stop_requested());
    std::cout << "  ✓ Obtained stop_token from source" << std::endl;

    // Request stop
    source.request_stop();
    assert(source.stop_requested());
    assert(token.stop_requested());
    std::cout << "  ✓ Requested stop and verified state" << std::endl;
}

void test_stop_token_copy()
{
    std::cout << "\n=== Testing Stop Token Copy ===" << std::endl;

    std::stop_source source;
    std::stop_token token1 = source.get_token();
    std::stop_token token2 = token1;  // Copy
    std::stop_token token3 = source.get_token();  // Another token from same source

    assert(!token1.stop_requested());
    assert(!token2.stop_requested());
    assert(!token3.stop_requested());
    std::cout << "  ✓ Created multiple tokens from same source" << std::endl;

    source.request_stop();
    assert(token1.stop_requested());
    assert(token2.stop_requested());
    assert(token3.stop_requested());
    std::cout << "  ✓ All tokens reflect stop request" << std::endl;
}

void test_stop_callback()
{
    std::cout << "\n=== Testing Stop Callback ===" << std::endl;

    std::atomic<bool> callback_invoked{false};
    std::stop_source source;
    std::stop_token token = source.get_token();

    // Register a callback
    std::stop_callback callback(token, [&callback_invoked]() {
        callback_invoked = true;
    });

    assert(!callback_invoked);
    std::cout << "  ✓ Registered stop_callback" << std::endl;

    // Request stop - should invoke the callback
    source.request_stop();
    assert(callback_invoked);
    std::cout << "  ✓ Callback invoked on stop request" << std::endl;
}

void test_stop_callback_already_stopped()
{
    std::cout << "\n=== Testing Stop Callback with Already Stopped Token ===" << std::endl;

    std::atomic<bool> callback_invoked{false};
    std::stop_source source;
    std::stop_token token = source.get_token();

    // Request stop first
    source.request_stop();
    std::cout << "  ✓ Requested stop before registering callback" << std::endl;

    // Register callback - should be invoked immediately
    std::stop_callback callback(token, [&callback_invoked]() {
        callback_invoked = true;
    });

    assert(callback_invoked);
    std::cout << "  ✓ Callback invoked immediately for already-stopped token" << std::endl;
}

void test_nostopstate()
{
    std::cout << "\n=== Testing No-Stop-State Source ===" << std::endl;

    // Create a stop_source with no associated state
    std::stop_source source{std::nostopstate};
    assert(!source.stop_possible());
    assert(!source.stop_requested());
    std::cout << "  ✓ Created stop_source with nostopstate" << std::endl;

    // Token from no-state source also has no state
    std::stop_token token = source.get_token();
    assert(!token.stop_possible());
    assert(!token.stop_requested());
    std::cout << "  ✓ Token from no-state source has no state" << std::endl;

    // Default-constructed stop_token also has no state
    std::stop_token default_token;
    assert(!default_token.stop_possible());
    assert(!default_token.stop_requested());
    std::cout << "  ✓ Default-constructed stop_token has no state" << std::endl;
}

void test_multiple_callbacks()
{
    std::cout << "\n=== Testing Multiple Callbacks ===" << std::endl;

    std::atomic<int> count{0};
    std::stop_source source;
    std::stop_token token = source.get_token();

    // Register multiple callbacks
    std::stop_callback cb1(token, [&count]() { count++; });
    std::stop_callback cb2(token, [&count]() { count++; });
    std::stop_callback cb3(token, [&count]() { count++; });

    assert(count == 0);
    std::cout << "  ✓ Registered 3 callbacks" << std::endl;

    // Request stop - all callbacks should be invoked
    source.request_stop();
    assert(count == 3);
    std::cout << "  ✓ All 3 callbacks invoked on stop request" << std::endl;
}

void test_stop_source_move()
{
    std::cout << "\n=== Testing Stop Source Move ===" << std::endl;

    std::stop_source source1;
    std::stop_token token = source1.get_token();

    // Move the source
    std::stop_source source2 = std::move(source1);

    assert(!source1.stop_possible());  // Moved-from source has no state
    assert(source2.stop_possible());
    std::cout << "  ✓ Moved stop_source" << std::endl;

    // Token should still work with moved-to source
    source2.request_stop();
    assert(token.stop_requested());
    std::cout << "  ✓ Token still valid after source move" << std::endl;
}

void test_stop_token_comparison()
{
    std::cout << "\n=== Testing Stop Token Comparison ===" << std::endl;

    std::stop_source source1;
    std::stop_source source2;

    std::stop_token token1a = source1.get_token();
    std::stop_token token1b = source1.get_token();
    std::stop_token token2 = source2.get_token();

    // Tokens from same source should compare equal
    assert(token1a == token1b);
    std::cout << "  ✓ Tokens from same source are equal" << std::endl;

    // Tokens from different sources should not compare equal
    assert(token1a != token2);
    std::cout << "  ✓ Tokens from different sources are not equal" << std::endl;

    // No-state tokens should compare equal
    std::stop_token no_state1;
    std::stop_token no_state2;
    assert(no_state1 == no_state2);
    std::cout << "  ✓ No-state tokens are equal" << std::endl;
}

void test_stop_possible()
{
    std::cout << "\n=== Testing Stop Possible States ===" << std::endl;

    // Source with stop capability
    std::stop_source source;
    std::stop_token token = source.get_token();
    assert(token.stop_possible());
    std::cout << "  ✓ Token from source is stop-possible" << std::endl;

    // No-state token
    std::stop_token no_state_token;
    assert(!no_state_token.stop_possible());
    std::cout << "  ✓ No-state token is not stop-possible" << std::endl;

    // No-state source
    std::stop_source no_state_source{std::nostopstate};
    std::stop_token token_from_no_state = no_state_source.get_token();
    assert(!token_from_no_state.stop_possible());
    std::cout << "  ✓ Token from no-state source is not stop-possible" << std::endl;
}

int main()
{
    std::cout << "Running stop_token module tests..." << std::endl;

    test_basic_stop_token();
    test_stop_token_copy();
    test_stop_callback();
    test_stop_callback_already_stopped();
    test_nostopstate();
    test_multiple_callbacks();
    test_stop_source_move();
    test_stop_token_comparison();
    test_stop_possible();

    std::cout << "\n✅ All stop_token tests passed!" << std::endl;
    return 0;
}
