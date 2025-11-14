/**
 * @file test_complex.cpp
 * @brief Tests for std_module.complex
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.complex;
import std_module.test_framework;

#include <cmath>  // For M_PI

int main() {
    test::test_header("std_module.complex");

    test::section("Testing complex construction");

    // Test that complex types are constructible
    std::complex<double> c1;
    std::complex<double> c2(3.0);
    std::complex<double> c3(3.0, 4.0);
    std::complex<float> cf(1.5f, 2.5f);
    test::success("complex types constructible");

    test::section("Testing real/imag accessors");

    // Test that real() and imag() are callable
    auto r = std::real(c3);
    auto i = std::imag(c3);
    test::assert_true(r > 0, "real/imag functions");

    test::section("Testing basic complex functions");

    // Test that basic functions are callable
    auto magnitude = std::abs(c3);
    auto phase = std::arg(c3);
    auto norm_val = std::norm(c3);
    auto conj_val = std::conj(c3);
    auto proj_val = std::proj(c3);
    test::assert_true(magnitude > 0, "abs/arg/norm/conj/proj");

    test::section("Testing polar form");

    // Test that polar() is callable
    auto polar_c = std::polar(5.0, M_PI / 4);
    test::assert_true(std::abs(polar_c) > 0, "polar");

    test::section("Testing exponential functions");

    // Test that exp, log, log10 are callable
    std::complex<double> c(1.0, 0.0);
    auto exp_c = std::exp(c);
    auto log_c = std::log(c);
    auto log10_c = std::log10(c);
    test::assert_true(std::abs(exp_c) > 0, "exp/log/log10");

    test::section("Testing power functions");

    // Test that pow, sqrt are callable
    auto pow_c = std::pow(c3, 2);
    auto sqrt_c = std::sqrt(c3);
    test::assert_true(std::abs(pow_c) > 0, "pow/sqrt");

    test::section("Testing trigonometric functions");

    // Test that sin, cos, tan are callable
    auto sin_c = std::sin(c3);
    auto cos_c = std::cos(c3);
    auto tan_c = std::tan(c3);
    test::assert_true(std::abs(sin_c) >= 0, "sin/cos/tan");

    // Test that asin, acos, atan are callable
    std::complex<double> c_small(0.5, 0.0);
    auto asin_c = std::asin(c_small);
    auto acos_c = std::acos(c_small);
    auto atan_c = std::atan(c_small);
    test::assert_true(std::abs(asin_c) >= 0, "asin/acos/atan");

    test::section("Testing hyperbolic functions");

    // Test that sinh, cosh, tanh are callable
    auto sinh_c = std::sinh(c3);
    auto cosh_c = std::cosh(c3);
    auto tanh_c = std::tanh(c3);
    test::assert_true(std::abs(sinh_c) > 0, "sinh/cosh/tanh");

    // Test that asinh, acosh, atanh are callable
    auto asinh_c = std::asinh(c_small);
    std::complex<double> c_gt1(2.0, 0.0);
    auto acosh_c = std::acosh(c_gt1);
    auto atanh_c = std::atanh(c_small);
    test::assert_true(std::abs(asinh_c) >= 0, "asinh/acosh/atanh");

    test::section("Testing complex literals");

    using namespace std::literals::complex_literals;

    // Test that imaginary unit literals are accessible
    auto i_d = 1.0i;
    auto i_f = 1.0if;
    auto i_l = 1.0il;
    test::assert_true(std::abs(std::imag(i_d)) > 0, "complex literals");

    test::test_footer();
    return 0;
}
