/**
 * @file test_stop_token.cpp
 * @brief Tests for std_module.stop_token
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.stop_token;
import std_module.test_framework;

int main() {
    test::test_header("std_module.stop_token");

    test::section("Testing symbol accessibility");

    // Test stop_source
    std::stop_source source;
    test::assert_true(source.stop_possible(), "stop_source.stop_possible");
    test::assert_true(!source.stop_requested(), "stop_source.stop_requested (initially false)");

    // Test stop_token
    std::stop_token token = source.get_token();
    test::assert_true(token.stop_possible(), "stop_token.stop_possible");

    // Test request_stop
    test::assert_true(source.request_stop(), "stop_source.request_stop");
    test::assert_true(token.stop_requested(), "stop_token.stop_requested (after request)");

    // Test stop_callback
    bool callback_called = false;
    {
        std::stop_callback cb(token, [&callback_called]() { callback_called = true; });
        // Callback should be called immediately since stop already requested
    }
    test::assert_true(callback_called, "stop_callback");

    // Test nostopstate
    std::stop_source no_state_source{std::nostopstate};
    test::assert_true(!no_state_source.stop_possible(), "nostopstate");

    // Test comparison
    std::stop_token token1 = source.get_token();
    std::stop_token token2 = source.get_token();
    test::assert_true(token1 == token2, "stop_token comparison");

    test::test_footer();
    return 0;
}
