/**
 * @file test_exception.cpp
 * @brief Tests for std_module.exception
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.exception;
import std_module.test_framework;

// FUTURE: When std_module.stdexcept is available, remove this include
#include <stdexcept>

int main() {
    test::test_header("std_module.exception");

    test::section("Testing basic exception types");

    // Test std::exception
    try {
        throw std::exception();
    } catch (const std::exception& e) {
        [[maybe_unused]] auto msg = e.what();
        test::success("exception class and what()");
    }

    // Test std::bad_exception
    try {
        throw std::bad_exception();
    } catch (const std::bad_exception&) {
        test::success("bad_exception");
    }

    test::section("Testing exception_ptr");

    // Test current_exception and rethrow_exception
    std::exception_ptr eptr;
    try {
        throw std::runtime_error("test");
    } catch (...) {
        eptr = std::current_exception();
    }
    test::assert_true(eptr != nullptr, "current_exception()");

    try {
        std::rethrow_exception(eptr);
    } catch (const std::runtime_error&) {
        test::success("rethrow_exception()");
    }

    // Test make_exception_ptr
    auto eptr2 = std::make_exception_ptr(std::runtime_error("made"));
    test::assert_true(eptr2 != nullptr, "make_exception_ptr()");

    test::section("Testing nested exceptions");

    // Test throw_with_nested
    try {
        try {
            throw std::runtime_error("inner");
        } catch (...) {
            std::throw_with_nested(std::runtime_error("outer"));
        }
    } catch (const std::runtime_error&) {
        test::success("throw_with_nested()");
    }

    // Test rethrow_if_nested
    try {
        try {
            throw std::runtime_error("inner");
        } catch (...) {
            std::throw_with_nested(std::runtime_error("outer"));
        }
    } catch (const std::runtime_error& e) {
        try {
            std::rethrow_if_nested(e);
        } catch (...) {
            test::success("rethrow_if_nested()");
        }
    }

    // Test nested_exception class
    std::nested_exception ne;
    test::success("nested_exception class");

    test::section("Testing uncaught_exceptions");

    int count = std::uncaught_exceptions();
    test::assert_equal(count, 0, "uncaught_exceptions()");

    test::section("Testing terminate handlers");

    // Test get_terminate/set_terminate (don't actually call terminate!)
    auto old_handler = std::get_terminate();
    test::assert_true(old_handler != nullptr, "get_terminate()");

    std::set_terminate(old_handler);
    test::success("set_terminate()");

    test::test_footer();
    return 0;
}
