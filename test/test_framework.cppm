/**
 * @file test_framework.cppm
 * @brief C++20 test framework module for std_module tests
 *
 * Provides testing utilities to avoid #include directives in tests:
 * - Custom assert functions (no <cassert> needed)
 * - I/O utilities (cout, cerr, stringstreams)
 * - Test formatting helpers (checkmarks, sections, headers)
 */

module;
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>   // for std::abort
#include <cstddef>   // for size_t
#include <stdexcept> // for exception types (out_of_range, etc.)
#include <any>       // for bad_any_cast

export module std_module.test_framework;

// Re-export std types in std namespace (required for ADL to work correctly)
export namespace std {
    // Common types
    using std::size_t;

    // I/O Streams
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::flush;

    // I/O manipulators
    using std::hex;
    using std::dec;
    using std::oct;
    using std::setw;
    using std::setfill;
    using std::setprecision;

    // String streams
    using std::ostringstream;
    using std::istringstream;
    using std::stringstream;

    // String support
    using std::string;

    // Exception types (for testing exception handling)
    using std::exception;
    using std::logic_error;
    using std::runtime_error;
    using std::out_of_range;
    using std::invalid_argument;
    using std::bad_any_cast;

    // Stream operators (CRITICAL: must be in std namespace for ADL)
    using std::operator<<;
    using std::operator>>;
}

export namespace test {
    // Re-export std:: utilities for convenience
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::flush;
    using std::hex;
    using std::dec;
    using std::oct;
    using std::setw;
    using std::setfill;
    using std::setprecision;
    using std::ostringstream;
    using std::istringstream;
    using std::stringstream;
    using std::string;

    // ========================================
    // Assertion Functions
    // ========================================

    /**
     * Assert that a condition is true, abort with message if false
     * @param condition The boolean condition to test
     * @param message Error message to display on failure
     */
    inline void assert_true(bool condition, const char* message = "Assertion failed") {
        if (!condition) {
            cerr << "❌ ASSERTION FAILED: " << message << endl;
            std::abort();
        }
    }

    /**
     * Assert that a condition is false, abort with message if true
     * @param condition The boolean condition to test (should be false)
     * @param message Error message to display on failure
     */
    inline void assert_false(bool condition, const char* message = "Assertion failed (expected false)") {
        if (condition) {
            cerr << "❌ ASSERTION FAILED: " << message << endl;
            std::abort();
        }
    }

    /**
     * Assert that two values are equal using operator==
     * @param actual The actual value from the test
     * @param expected The expected value
     * @param message Error message to display on failure
     */
    template<typename T, typename U>
    inline void assert_equal(const T& actual, const U& expected, const char* message = "Values not equal") {
        if (!(actual == expected)) {
            cerr << "❌ ASSERTION FAILED: " << message << endl;
            cerr << "   Expected: " << expected << endl;
            cerr << "   Actual:   " << actual << endl;
            std::abort();
        }
    }

    /**
     * Assert that two values are NOT equal using operator==
     * @param actual The actual value from the test
     * @param unexpected The value that should NOT match
     * @param message Error message to display on failure
     */
    template<typename T, typename U>
    inline void assert_not_equal(const T& actual, const U& unexpected, const char* message = "Values should not be equal") {
        if (actual == unexpected) {
            cerr << "❌ ASSERTION FAILED: " << message << endl;
            cerr << "   Unexpected value: " << unexpected << endl;
            cerr << "   Actual value:     " << actual << endl;
            std::abort();
        }
    }

    /**
     * Convenience macro-like function for simple assertions
     * Usage: test::assert_that(x > 5);
     */
    inline void assert_that(bool condition) {
        assert_true(condition, "Assertion failed");
    }

    // ========================================
    // Test Formatting Helpers
    // ========================================

    /**
     * Returns the checkmark symbol for successful tests
     */
    inline const char* checkmark() { return "✓"; }

    /**
     * Returns the cross mark symbol for failed tests
     */
    inline const char* crossmark() { return "✗"; }

    /**
     * Returns the warning symbol for warnings
     */
    inline const char* warning_symbol() { return "⚠"; }

    /**
     * Print a test section header
     * @param name The name of the test section
     */
    inline void section(const char* name) {
        cout << "\n" << name << "...\n";
    }

    /**
     * Print a test module header
     * @param module_name The name of the module being tested (e.g., "std_module.format")
     */
    inline void test_header(const char* module_name) {
        cout << "=== Testing " << module_name << " ===\n";
    }

    /**
     * Print a test footer indicating success
     */
    inline void test_footer() {
        cout << "\n=== All tests passed! ===\n";
    }

    /**
     * Print a success message with checkmark
     * @param description Description of what succeeded
     */
    inline void success(const char* description) {
        cout << "  " << checkmark() << " " << description << "\n";
    }

    /**
     * Print a warning message with warning symbol
     * @param description Description of the warning
     */
    inline void warning(const char* description) {
        cout << "  " << warning_symbol() << " " << description << "\n";
    }

    /**
     * Print a failure message with cross mark (does NOT abort)
     * @param description Description of what failed
     */
    inline void failure(const char* description) {
        cout << "  " << crossmark() << " " << description << "\n";
    }

    // ========================================
    // Exception Testing Helpers
    // ========================================

    /**
     * Returns true if the standard exception type is available
     * Useful for checking if exception handling is available in the current module
     */
    inline bool has_exception_support() {
        #if __cpp_exceptions
        return true;
        #else
        return false;
        #endif
    }
}
