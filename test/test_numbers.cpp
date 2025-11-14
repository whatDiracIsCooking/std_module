/**
 * @file test_numbers.cpp
 * @brief Tests for std_module.numbers
 *
 * Comprehensive test suite for C++20 <numbers> functionality through modules.
 */

import std_module.numbers;

#include <iostream>
#include <cassert>
#include <cmath>
#include <type_traits>

// Test mathematical constants
void test_constants()
{
    std::cout << "\nTesting mathematical constants:\n";

    // e (Euler's number)
    assert(std::numbers::e > 2.718 && std::numbers::e < 2.719);
    std::cout << "  ✓ e = " << std::numbers::e << "\n";

    // pi
    assert(std::numbers::pi > 3.141 && std::numbers::pi < 3.142);
    std::cout << "  ✓ pi = " << std::numbers::pi << "\n";

    // sqrt(2)
    assert(std::numbers::sqrt2 > 1.414 && std::numbers::sqrt2 < 1.415);
    std::cout << "  ✓ sqrt2 = " << std::numbers::sqrt2 << "\n";

    // sqrt(3)
    assert(std::numbers::sqrt3 > 1.732 && std::numbers::sqrt3 < 1.733);
    std::cout << "  ✓ sqrt3 = " << std::numbers::sqrt3 << "\n";

    // Golden ratio (phi)
    assert(std::numbers::phi > 1.618 && std::numbers::phi < 1.619);
    std::cout << "  ✓ phi = " << std::numbers::phi << "\n";
}

// Test logarithmic constants
void test_logarithmic_constants()
{
    std::cout << "\nTesting logarithmic constants:\n";

    // log2(e)
    assert(std::numbers::log2e > 1.442 && std::numbers::log2e < 1.443);
    std::cout << "  ✓ log2e = " << std::numbers::log2e << "\n";

    // log10(e)
    assert(std::numbers::log10e > 0.434 && std::numbers::log10e < 0.435);
    std::cout << "  ✓ log10e = " << std::numbers::log10e << "\n";

    // ln(2)
    assert(std::numbers::ln2 > 0.693 && std::numbers::ln2 < 0.694);
    std::cout << "  ✓ ln2 = " << std::numbers::ln2 << "\n";

    // ln(10)
    assert(std::numbers::ln10 > 2.302 && std::numbers::ln10 < 2.303);
    std::cout << "  ✓ ln10 = " << std::numbers::ln10 << "\n";
}

// Test inverse constants
void test_inverse_constants()
{
    std::cout << "\nTesting inverse constants:\n";

    // 1/pi
    assert(std::numbers::inv_pi > 0.318 && std::numbers::inv_pi < 0.319);
    std::cout << "  ✓ inv_pi = " << std::numbers::inv_pi << "\n";

    // 1/sqrt(pi)
    assert(std::numbers::inv_sqrtpi > 0.564 && std::numbers::inv_sqrtpi < 0.565);
    std::cout << "  ✓ inv_sqrtpi = " << std::numbers::inv_sqrtpi << "\n";

    // 1/sqrt(3)
    assert(std::numbers::inv_sqrt3 > 0.577 && std::numbers::inv_sqrt3 < 0.578);
    std::cout << "  ✓ inv_sqrt3 = " << std::numbers::inv_sqrt3 << "\n";
}

// Test Euler-Mascheroni constant
void test_egamma()
{
    std::cout << "\nTesting Euler-Mascheroni constant:\n";

    assert(std::numbers::egamma > 0.577 && std::numbers::egamma < 0.578);
    std::cout << "  ✓ egamma = " << std::numbers::egamma << "\n";
}

// Test template versions
void test_template_constants()
{
    std::cout << "\nTesting template constant versions:\n";

    // Test float precision
    static_assert(std::is_same_v<decltype(std::numbers::pi_v<float>), const float>);
    assert(std::numbers::pi_v<float> > 3.14f && std::numbers::pi_v<float> < 3.15f);
    std::cout << "  ✓ pi_v<float> = " << std::numbers::pi_v<float> << "\n";

    // Test double precision
    static_assert(std::is_same_v<decltype(std::numbers::pi_v<double>), const double>);
    assert(std::numbers::pi_v<double> > 3.141 && std::numbers::pi_v<double> < 3.142);
    std::cout << "  ✓ pi_v<double> = " << std::numbers::pi_v<double> << "\n";

    // Test long double precision
    static_assert(std::is_same_v<decltype(std::numbers::pi_v<long double>), const long double>);
    std::cout << "  ✓ pi_v<long double> = " << std::numbers::pi_v<long double> << "\n";

    // Test e_v
    assert(std::numbers::e_v<float> > 2.71f && std::numbers::e_v<float> < 2.72f);
    std::cout << "  ✓ e_v<float> = " << std::numbers::e_v<float> << "\n";

    // Test sqrt2_v
    assert(std::numbers::sqrt2_v<double> > 1.414 && std::numbers::sqrt2_v<double> < 1.415);
    std::cout << "  ✓ sqrt2_v<double> = " << std::numbers::sqrt2_v<double> << "\n";
}

// Test mathematical relationships
void test_relationships()
{
    std::cout << "\nTesting mathematical relationships:\n";

    // pi * inv_pi should be approximately 1
    double product = std::numbers::pi * std::numbers::inv_pi;
    assert(std::abs(product - 1.0) < 0.0001);
    std::cout << "  ✓ pi * inv_pi ≈ 1.0 (actual: " << product << ")\n";

    // sqrt(2)^2 should be approximately 2
    double square = std::numbers::sqrt2 * std::numbers::sqrt2;
    assert(std::abs(square - 2.0) < 0.0001);
    std::cout << "  ✓ sqrt2 * sqrt2 ≈ 2.0 (actual: " << square << ")\n";

    // sqrt(3) * inv_sqrt(3) should be approximately 1
    product = std::numbers::sqrt3 * std::numbers::inv_sqrt3;
    assert(std::abs(product - 1.0) < 0.0001);
    std::cout << "  ✓ sqrt3 * inv_sqrt3 ≈ 1.0 (actual: " << product << ")\n";

    // e^(ln(2)) should be approximately 2
    double result = std::exp(std::numbers::ln2);
    assert(std::abs(result - 2.0) < 0.0001);
    std::cout << "  ✓ e^(ln2) ≈ 2.0 (actual: " << result << ")\n";
}

int main()
{
    std::cout << "=================================\n";
    std::cout << "Testing std_module.numbers\n";
    std::cout << "=================================\n";

    try
    {
        test_constants();
        test_logarithmic_constants();
        test_inverse_constants();
        test_egamma();
        test_template_constants();
        test_relationships();

        std::cout << "\n=================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "=================================\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
