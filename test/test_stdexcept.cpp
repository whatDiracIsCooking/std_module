/**
 * @file test_stdexcept.cpp
 * @brief Tests for std_module.stdexcept
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.stdexcept;
import std_module.test_framework;

int main() {
    test::test_header("std_module.stdexcept");

    test::section("Testing exception accessibility");

    // Test that exception types are constructible and catchable
    try {
        throw std::logic_error("test");
    } catch (const std::logic_error& e) {
        test::success("logic_error");
    }

    try {
        throw std::domain_error("test");
    } catch (const std::domain_error& e) {
        test::success("domain_error");
    }

    try {
        throw std::invalid_argument("test");
    } catch (const std::invalid_argument& e) {
        test::success("invalid_argument");
    }

    try {
        throw std::length_error("test");
    } catch (const std::length_error& e) {
        test::success("length_error");
    }

    try {
        throw std::out_of_range("test");
    } catch (const std::out_of_range& e) {
        test::success("out_of_range");
    }

    try {
        throw std::runtime_error("test");
    } catch (const std::runtime_error& e) {
        test::success("runtime_error");
    }

    try {
        throw std::range_error("test");
    } catch (const std::range_error& e) {
        test::success("range_error");
    }

    try {
        throw std::overflow_error("test");
    } catch (const std::overflow_error& e) {
        test::success("overflow_error");
    }

    try {
        throw std::underflow_error("test");
    } catch (const std::underflow_error& e) {
        test::success("underflow_error");
    }

    test::test_footer();
    return 0;
}
