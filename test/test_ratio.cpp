/**
 * @file test_ratio.cpp
 * @brief Tests for std_module.ratio
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.ratio;
import std_module.test_framework;

int main() {
    test::test_header("std_module.ratio");

    test::section("Testing symbol accessibility");

    // Test basic ratio template
    using half = std::ratio<1, 2>;
    test::assert_equal(half::num, 1, "ratio::num");
    test::assert_equal(half::den, 2, "ratio::den");

    // Test SI unit typedefs
    test::assert_equal(std::atto::num, 1, "atto");
    test::assert_equal(std::femto::num, 1, "femto");
    test::assert_equal(std::pico::num, 1, "pico");
    test::assert_equal(std::nano::num, 1, "nano");
    test::assert_equal(std::micro::num, 1, "micro");
    test::assert_equal(std::milli::num, 1, "milli");
    test::assert_equal(std::centi::num, 1, "centi");
    test::assert_equal(std::deci::num, 1, "deci");
    test::assert_equal(std::deca::num, 10, "deca");
    test::assert_equal(std::hecto::num, 100, "hecto");
    test::assert_equal(std::kilo::num, 1000, "kilo");
    test::assert_equal(std::mega::num, 1000000, "mega");
    test::assert_equal(std::giga::num, 1000000000, "giga");
    test::assert_true(std::tera::num > 0, "tera");
    test::assert_true(std::peta::num > 0, "peta");
    test::assert_true(std::exa::num > 0, "exa");

    // Test ratio arithmetic
    using one_third = std::ratio<1, 3>;
    using sum = std::ratio_add<half, one_third>;
    test::assert_equal(sum::num, 5, "ratio_add");
    test::assert_equal(sum::den, 6, "ratio_add");

    using diff = std::ratio_subtract<half, one_third>;
    test::success("ratio_subtract");

    using prod = std::ratio_multiply<half, one_third>;
    test::success("ratio_multiply");

    using quot = std::ratio_divide<half, one_third>;
    test::success("ratio_divide");

    // Test ratio comparison
    static_assert(std::ratio_equal<half, std::ratio<2, 4>>::value);
    test::success("ratio_equal");

    static_assert(std::ratio_not_equal<half, one_third>::value);
    test::success("ratio_not_equal");

    static_assert(std::ratio_less<one_third, half>::value);
    test::success("ratio_less");

    static_assert(std::ratio_less_equal<half, half>::value);
    test::success("ratio_less_equal");

    static_assert(std::ratio_greater<half, one_third>::value);
    test::success("ratio_greater");

    static_assert(std::ratio_greater_equal<half, half>::value);
    test::success("ratio_greater_equal");

    // Test _v helpers (C++17)
    static_assert(std::ratio_equal_v<half, half>);
    test::success("ratio comparison _v helpers");

    test::test_footer();
    return 0;
}
