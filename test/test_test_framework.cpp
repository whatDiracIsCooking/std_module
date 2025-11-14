/**
 * @file test_test_framework.cpp
 * @brief Comprehensive test demonstrating all test framework features
 *
 * This test validates the test_framework module and serves as a usage guide.
 * Note: This test uses ONLY module imports - no #include directives!
 */

import std_module.test_framework;

// ============================================================================
// Test: Assertion Functions
// ============================================================================

void test_assertions() {
    test::section("Testing assertion functions");

    // Test assert_true
    test::assert_true(true, "assert_true with true condition");
    test::success("assert_true works");

    // Test assert_equal
    test::assert_equal(42, 42, "assert_equal with equal values");
    test::success("assert_equal works with integers");

    test::assert_equal(3.14, 3.14, "assert_equal with doubles");
    test::success("assert_equal works with doubles");

    // Test assert_not_equal
    test::assert_not_equal(42, 43, "assert_not_equal with different values");
    test::success("assert_not_equal works");

    // Test assert_that (convenience function)
    test::assert_that(5 > 3);
    test::success("assert_that works");
}

// ============================================================================
// Test: I/O Utilities
// ============================================================================

void test_io_utilities() {
    test::section("Testing I/O utilities");

    // Test cout
    test::cout << "  Testing cout: ";
    test::cout << "Hello from test framework!" << test::endl;
    test::success("cout works");

    // Test stringstream
    test::ostringstream oss;
    oss << "Value: " << 42;
    test::assert_equal(oss.str(), "Value: 42", "ostringstream formatting");
    test::success("ostringstream works");

    test::istringstream iss("123 456");
    int a, b;
    iss >> a >> b;
    test::assert_equal(a, 123, "istringstream first value");
    test::assert_equal(b, 456, "istringstream second value");
    test::success("istringstream works");

    // Test stringstream (bidirectional)
    test::stringstream ss;
    ss << "Test " << 789;
    test::assert_true(ss.str().find("789") != test::string::npos, "stringstream write");
    test::success("stringstream works");
}

// ============================================================================
// Test: Formatting Helpers
// ============================================================================

void test_formatting_helpers() {
    test::section("Testing formatting helpers");

    // Test symbols
    test::cout << "  Checkmark: " << test::checkmark() << test::endl;
    test::assert_true(test::checkmark() != nullptr, "checkmark returns non-null");
    test::success("checkmark() works");

    test::cout << "  Crossmark: " << test::crossmark() << test::endl;
    test::assert_true(test::crossmark() != nullptr, "crossmark returns non-null");
    test::success("crossmark() works");

    test::cout << "  Warning: " << test::warning_symbol() << test::endl;
    test::assert_true(test::warning_symbol() != nullptr, "warning_symbol returns non-null");
    test::success("warning_symbol() works");

    // Test convenience functions
    test::success("Testing success() function");
    test::warning("Testing warning() function");
    test::failure("Testing failure() function (this is NOT an actual failure)");
}

// ============================================================================
// Test: Stream Operators (ADL Validation)
// ============================================================================

void test_stream_operators() {
    test::section("Testing stream operators (ADL)");

    // Test operator<< with various types
    test::ostringstream oss;
    oss << "String: " << "hello";
    oss << ", Int: " << 42;
    oss << ", Double: " << 3.14;
    oss << ", Bool: " << true;

    test::assert_true(oss.str().find("hello") != test::string::npos, "String output");
    test::assert_true(oss.str().find("42") != test::string::npos, "Int output");
    test::assert_true(oss.str().find("3.14") != test::string::npos, "Double output");
    test::success("operator<< works for multiple types");

    // Test operator>> with various types
    test::istringstream iss("42 3.14 hello");
    int i;
    double d;
    test::stringstream::char_type s[10];

    iss >> i >> d;
    test::assert_equal(i, 42, "operator>> for int");
    test::assert_equal(d, 3.14, "operator>> for double");
    test::success("operator>> works for multiple types");
}

// ============================================================================
// Test: Exception Support Detection
// ============================================================================

void test_exception_support() {
    test::section("Testing exception support detection");

    bool has_exceptions = test::has_exception_support();
    if (has_exceptions) {
        test::success("Exception support detected");
    } else {
        test::warning("Exception support not detected");
    }

    test::cout << "  Exception support: " << (has_exceptions ? "enabled" : "disabled") << test::endl;
}

// ============================================================================
// Test: Real-World Test Pattern
// ============================================================================

void test_realistic_example() {
    test::section("Testing realistic test pattern");

    // This demonstrates how a typical module test would use the framework
    test::cout << "  Simulating a real module test...\n";

    // Construction test
    test::ostringstream result;
    result << "Value: " << 42;
    test::assert_equal(result.str(), "Value: 42", "Construction and formatting");
    test::success("Construction works");

    // Operation test
    int x = 10;
    int y = 20;
    int sum = x + y;
    test::assert_equal(sum, 30, "Addition operation");
    test::success("Operations work");

    // Edge case test
    test::assert_not_equal(x, y, "Values are different");
    test::success("Edge cases handled");

    test::cout << "  " << test::checkmark() << " Real-world pattern validated\n";
}

// ============================================================================
// Test: Pure Module Import Validation
// ============================================================================

void test_pure_module_import() {
    test::section("Testing pure module import (no #include)");

    // This test validates that we can use the test framework
    // WITHOUT any #include directives whatsoever!

    test::cout << "  This file uses ONLY: import std_module.test_framework;\n";
    test::cout << "  No #include <iostream> - using test::cout\n";
    test::cout << "  No #include <cassert> - using test::assert_*\n";
    test::cout << "  No #include <sstream> - using test::stringstream\n";

    test::success("Pure module import validated");
    test::success("Zero #include directives needed for testing!");
}

// ============================================================================
// Main Test Entry Point
// ============================================================================

int main() {
    test::test_header("std_module.test_framework");

    try {
        test_assertions();
        test_io_utilities();
        test_formatting_helpers();
        test_stream_operators();
        test_exception_support();
        test_realistic_example();
        test_pure_module_import();

        test::test_footer();
        return 0;

    } catch (...) {
        test::cerr << "\n❌ TEST FAILED: Unexpected exception caught\n";
        return 1;
    }
}
