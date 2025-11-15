/**
 * @file test_optional.cpp
 * @brief Tests for std_module.optional
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.optional;
import std_module.test_framework;

int main() {
    test::test_header("std_module.optional");

    test::section("Testing symbol accessibility");

    // Test basic construction and access
    std::optional<int> opt1;
    test::assert_true(!opt1.has_value(), "empty optional");

    std::optional<int> opt2 = 42;
    test::assert_true(opt2.has_value(), "optional with value");
    test::assert_equal(*opt2, 42, "operator*");
    test::assert_equal(opt2.value(), 42, "value()");

    // Test nullopt
    std::optional<int> opt3 = std::nullopt;
    test::assert_true(!opt3.has_value(), "nullopt");

    // Test value_or
    test::assert_equal(opt1.value_or(100), 100, "value_or on empty");
    test::assert_equal(opt2.value_or(100), 42, "value_or on non-empty");

    // Test emplace, reset, swap
    opt1.emplace(99);
    test::assert_equal(*opt1, 99, "emplace");

    opt1.reset();
    test::assert_true(!opt1.has_value(), "reset");

    opt1 = 10;
    opt2 = 20;
    opt1.swap(opt2);
    test::assert_equal(*opt1, 20, "swap");

    // Test make_optional
    auto opt4 = std::make_optional(123);
    test::assert_equal(*opt4, 123, "make_optional");

    // Test bad_optional_access exception
    try {
        std::optional<int> empty;
        [[maybe_unused]] int val = empty.value();
        test::assert_true(false, "should have thrown");
    } catch (const std::bad_optional_access&) {
        test::success("bad_optional_access");
    }

    test::test_footer();
    return 0;
}
