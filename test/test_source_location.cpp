/**
 * @file test_source_location.cpp
 * @brief Tests for std_module.source_location
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.source_location;
import std_module.test_framework;

int main() {
    test::test_header("std_module.source_location");

    test::section("Testing symbol accessibility");

    // Test source_location::current()
    auto loc = std::source_location::current();
    test::success("source_location::current()");

    // Test member functions
    test::assert_true(loc.line() > 0, "line()");

    [[maybe_unused]] auto col = loc.column();
    test::success("column()");

    const char* file = loc.file_name();
    test::assert_true(file != nullptr, "file_name()");

    const char* func = loc.function_name();
    test::assert_true(func != nullptr, "function_name()");

    // Test copyability
    auto loc2 = loc;
    test::assert_equal(loc.line(), loc2.line(), "copy construction");

    // Test in default parameter context
    auto test_func = [](const std::source_location& sl = std::source_location::current()) {
        return sl.line() > 0;
    };
    test::assert_true(test_func(), "default parameter capture");

    test::test_footer();
    return 0;
}
