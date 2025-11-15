/**
 * @file test_numbers.cpp
 * @brief Tests for std_module.numbers
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.numbers;
import std_module.test_framework;

int main() {
    test::test_header("std_module.numbers");

    test::section("Testing symbol accessibility");

    // Test mathematical constants
    test::assert_true(std::numbers::e > 0, "e");
    test::assert_true(std::numbers::pi > 0, "pi");
    test::assert_true(std::numbers::sqrt2 > 0, "sqrt2");
    test::assert_true(std::numbers::sqrt3 > 0, "sqrt3");
    test::assert_true(std::numbers::phi > 0, "phi");

    // Test logarithmic constants
    test::assert_true(std::numbers::log2e > 0, "log2e");
    test::assert_true(std::numbers::log10e > 0, "log10e");
    test::assert_true(std::numbers::ln2 > 0, "ln2");
    test::assert_true(std::numbers::ln10 > 0, "ln10");

    // Test inverse constants
    test::assert_true(std::numbers::inv_pi > 0, "inv_pi");
    test::assert_true(std::numbers::inv_sqrtpi > 0, "inv_sqrtpi");
    test::assert_true(std::numbers::inv_sqrt3 > 0, "inv_sqrt3");

    // Test Euler-Mascheroni constant
    test::assert_true(std::numbers::egamma > 0, "egamma");

    // Test template versions (just verify they compile and are accessible)
    [[maybe_unused]] float pi_f = std::numbers::pi_v<float>;
    [[maybe_unused]] double pi_d = std::numbers::pi_v<double>;
    [[maybe_unused]] long double pi_ld = std::numbers::pi_v<long double>;
    test::success("template constant versions (pi_v, e_v, etc.)");

    test::test_footer();
    return 0;
}
