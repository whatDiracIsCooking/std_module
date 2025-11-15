/**
 * @file test_limits.cpp
 * @brief Tests for std_module.limits
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that numeric_limits types are accessible through the module.
 */

import std_module.limits;
import std_module.test_framework;

int main() {
    test::test_header("std_module.limits");

    test::section("Testing symbol accessibility");

    // Test integer limits are accessible
    test::assert_true(std::numeric_limits<int>::is_specialized, "numeric_limits<int>");
    test::assert_true(std::numeric_limits<int>::min() < 0, "int::min");
    test::assert_true(std::numeric_limits<int>::max() > 0, "int::max");
    test::assert_true(std::numeric_limits<int>::is_integer, "int::is_integer");
    test::assert_true(std::numeric_limits<int>::is_signed, "int::is_signed");

    // Test unsigned limits
    test::assert_true(std::numeric_limits<unsigned>::is_specialized, "numeric_limits<unsigned>");
    test::assert_true(!std::numeric_limits<unsigned>::is_signed, "unsigned::is_signed");

    // Test floating-point limits
    test::assert_true(std::numeric_limits<float>::is_specialized, "numeric_limits<float>");
    test::assert_true(std::numeric_limits<float>::min() > 0, "float::min");
    test::assert_true(std::numeric_limits<float>::max() > 0, "float::max");
    test::assert_true(std::numeric_limits<float>::epsilon() > 0, "float::epsilon");
    test::assert_true(!std::numeric_limits<float>::is_integer, "float::is_integer");

    // Test double limits
    test::assert_true(std::numeric_limits<double>::is_specialized, "numeric_limits<double>");
    test::assert_true(std::numeric_limits<double>::epsilon() > 0, "double::epsilon");

    // Test special floating-point values
    if (std::numeric_limits<double>::has_infinity) {
        auto inf = std::numeric_limits<double>::infinity();
        test::assert_true(inf > 0, "infinity");
    }
    if (std::numeric_limits<double>::has_quiet_NaN) {
        auto qnan = std::numeric_limits<double>::quiet_NaN();
        test::assert_true(qnan != qnan, "quiet_NaN (NaN != NaN)");
    }

    // Test numeric properties
    test::assert_true(std::numeric_limits<int>::radix == 2, "radix");
    test::assert_true(std::numeric_limits<int>::is_bounded, "is_bounded");
    test::assert_true(std::numeric_limits<int>::is_exact, "is_exact");
    test::assert_true(!std::numeric_limits<float>::is_exact, "float not is_exact");

    // Test bool limits
    test::assert_true(std::numeric_limits<bool>::is_specialized, "numeric_limits<bool>");
    test::assert_true(std::numeric_limits<bool>::min() == false, "bool::min");
    test::assert_true(std::numeric_limits<bool>::max() == true, "bool::max");

    // Test rounding and denorm styles
    auto float_round = std::numeric_limits<float>::round_style;
    auto int_round = std::numeric_limits<int>::round_style;
    test::assert_true(int_round == std::float_round_style::round_toward_zero, "round_style");

    auto float_denorm = std::numeric_limits<float>::has_denorm;
    auto int_denorm = std::numeric_limits<int>::has_denorm;
    test::assert_true(int_denorm == std::float_denorm_style::denorm_absent, "has_denorm");

    test::test_footer();
    return 0;
}
