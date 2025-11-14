/**
 * @file test_ratio.cpp
 * @brief Comprehensive tests for std_module.ratio
 *
 * Tests all exported symbols from <ratio> including:
 * - std::ratio template
 * - SI unit typedefs (atto through exa)
 * - Ratio arithmetic (add, subtract, multiply, divide)
 * - Ratio comparison (equal, not_equal, less, etc.)
 */

import std_module.ratio;

#include <iostream>
#include <cassert>
#include <type_traits>

// Test basic ratio template
void test_basic_ratio()
{
    std::cout << "\n=== Testing Basic Ratio Template ===\n";

    // Create a ratio of 1/2
    using half = std::ratio<1, 2>;
    assert(half::num == 1);
    assert(half::den == 2);
    std::cout << "  ✓ std::ratio<1, 2>: " << half::num << "/" << half::den << "\n";

    // Create a ratio of 2/4 (should reduce to 1/2)
    using quarter_times_two = std::ratio<2, 4>;
    assert(quarter_times_two::num == 1);
    assert(quarter_times_two::den == 2);
    std::cout << "  ✓ std::ratio<2, 4> reduces to: " << quarter_times_two::num << "/" << quarter_times_two::den << "\n";

    // Negative ratios
    using neg_half = std::ratio<-1, 2>;
    assert(neg_half::num == -1);
    assert(neg_half::den == 2);
    std::cout << "  ✓ std::ratio<-1, 2>: " << neg_half::num << "/" << neg_half::den << "\n";
}

// Test SI unit typedefs
void test_si_units()
{
    std::cout << "\n=== Testing SI Unit Typedefs ===\n";

    // Test all SI prefixes
    assert(std::atto::num == 1 && std::atto::den == 1000000000000000000LL);
    std::cout << "  ✓ atto: 10^-18\n";

    assert(std::femto::num == 1 && std::femto::den == 1000000000000000LL);
    std::cout << "  ✓ femto: 10^-15\n";

    assert(std::pico::num == 1 && std::pico::den == 1000000000000LL);
    std::cout << "  ✓ pico: 10^-12\n";

    assert(std::nano::num == 1 && std::nano::den == 1000000000);
    std::cout << "  ✓ nano: 10^-9\n";

    assert(std::micro::num == 1 && std::micro::den == 1000000);
    std::cout << "  ✓ micro: 10^-6\n";

    assert(std::milli::num == 1 && std::milli::den == 1000);
    std::cout << "  ✓ milli: 10^-3\n";

    assert(std::centi::num == 1 && std::centi::den == 100);
    std::cout << "  ✓ centi: 10^-2\n";

    assert(std::deci::num == 1 && std::deci::den == 10);
    std::cout << "  ✓ deci: 10^-1\n";

    assert(std::deca::num == 10 && std::deca::den == 1);
    std::cout << "  ✓ deca: 10^1\n";

    assert(std::hecto::num == 100 && std::hecto::den == 1);
    std::cout << "  ✓ hecto: 10^2\n";

    assert(std::kilo::num == 1000 && std::kilo::den == 1);
    std::cout << "  ✓ kilo: 10^3\n";

    assert(std::mega::num == 1000000 && std::mega::den == 1);
    std::cout << "  ✓ mega: 10^6\n";

    assert(std::giga::num == 1000000000 && std::giga::den == 1);
    std::cout << "  ✓ giga: 10^9\n";

    assert(std::tera::num == 1000000000000LL && std::tera::den == 1);
    std::cout << "  ✓ tera: 10^12\n";

    assert(std::peta::num == 1000000000000000LL && std::peta::den == 1);
    std::cout << "  ✓ peta: 10^15\n";

    assert(std::exa::num == 1000000000000000000LL && std::exa::den == 1);
    std::cout << "  ✓ exa: 10^18\n";
}

// Test ratio arithmetic
void test_ratio_arithmetic()
{
    std::cout << "\n=== Testing Ratio Arithmetic ===\n";

    using one_half = std::ratio<1, 2>;
    using one_third = std::ratio<1, 3>;
    using two_thirds = std::ratio<2, 3>;

    // Addition: 1/2 + 1/3 = 5/6
    using sum = std::ratio_add<one_half, one_third>;
    assert(sum::num == 5 && sum::den == 6);
    std::cout << "  ✓ ratio_add<1/2, 1/3> = " << sum::num << "/" << sum::den << "\n";

    // Subtraction: 2/3 - 1/3 = 1/3
    using diff = std::ratio_subtract<two_thirds, one_third>;
    assert(diff::num == 1 && diff::den == 3);
    std::cout << "  ✓ ratio_subtract<2/3, 1/3> = " << diff::num << "/" << diff::den << "\n";

    // Multiplication: 1/2 * 2/3 = 1/3
    using prod = std::ratio_multiply<one_half, two_thirds>;
    assert(prod::num == 1 && prod::den == 3);
    std::cout << "  ✓ ratio_multiply<1/2, 2/3> = " << prod::num << "/" << prod::den << "\n";

    // Division: 1/2 / 1/3 = 3/2
    using quot = std::ratio_divide<one_half, one_third>;
    assert(quot::num == 3 && quot::den == 2);
    std::cout << "  ✓ ratio_divide<1/2, 1/3> = " << quot::num << "/" << quot::den << "\n";
}

// Test ratio comparison
void test_ratio_comparison()
{
    std::cout << "\n=== Testing Ratio Comparison ===\n";

    using one_half = std::ratio<1, 2>;
    using two_fourths = std::ratio<2, 4>;  // Equal to 1/2
    using one_third = std::ratio<1, 3>;

    // Equality
    assert((std::ratio_equal<one_half, two_fourths>::value == true));
    std::cout << "  ✓ ratio_equal<1/2, 2/4> = true\n";

    assert((std::ratio_not_equal<one_half, one_third>::value == true));
    std::cout << "  ✓ ratio_not_equal<1/2, 1/3> = true\n";

    // Ordering
    assert((std::ratio_less<one_third, one_half>::value == true));
    std::cout << "  ✓ ratio_less<1/3, 1/2> = true\n";

    assert((std::ratio_less_equal<one_half, two_fourths>::value == true));
    std::cout << "  ✓ ratio_less_equal<1/2, 2/4> = true\n";

    assert((std::ratio_greater<one_half, one_third>::value == true));
    std::cout << "  ✓ ratio_greater<1/2, 1/3> = true\n";

    assert((std::ratio_greater_equal<one_half, one_half>::value == true));
    std::cout << "  ✓ ratio_greater_equal<1/2, 1/2> = true\n";
}

// Test ratio comparison helper variables (C++17)
void test_ratio_comparison_v()
{
    std::cout << "\n=== Testing Ratio Comparison _v Helpers ===\n";

    using one_half = std::ratio<1, 2>;
    using two_fourths = std::ratio<2, 4>;
    using one_third = std::ratio<1, 3>;

    // Using _v suffix for constexpr bool values
    static_assert(std::ratio_equal_v<one_half, two_fourths>);
    std::cout << "  ✓ ratio_equal_v<1/2, 2/4> = true\n";

    static_assert(std::ratio_not_equal_v<one_half, one_third>);
    std::cout << "  ✓ ratio_not_equal_v<1/2, 1/3> = true\n";

    static_assert(std::ratio_less_v<one_third, one_half>);
    std::cout << "  ✓ ratio_less_v<1/3, 1/2> = true\n";

    static_assert(std::ratio_less_equal_v<one_half, two_fourths>);
    std::cout << "  ✓ ratio_less_equal_v<1/2, 2/4> = true\n";

    static_assert(std::ratio_greater_v<one_half, one_third>);
    std::cout << "  ✓ ratio_greater_v<1/2, 1/3> = true\n";

    static_assert(std::ratio_greater_equal_v<one_half, one_half>);
    std::cout << "  ✓ ratio_greater_equal_v<1/2, 1/2> = true\n";
}

// Test practical use case: time conversions
void test_time_conversions()
{
    std::cout << "\n=== Testing Practical Use Case: Time Conversions ===\n";

    // seconds to milliseconds: multiply by 1000
    using seconds_to_ms = std::ratio_multiply<std::ratio<1>, std::kilo>;
    assert(seconds_to_ms::num == 1000 && seconds_to_ms::den == 1);
    std::cout << "  ✓ 1 second = " << seconds_to_ms::num << " milliseconds\n";

    // nanoseconds to seconds: divide by 1 billion
    using ns_to_s = std::ratio_divide<std::nano, std::ratio<1>>;
    assert(ns_to_s::num == 1 && ns_to_s::den == 1000000000);
    std::cout << "  ✓ 1 nanosecond = 1/" << ns_to_s::den << " seconds\n";

    // millisecond is 1/1000 of a second
    assert((std::ratio_equal_v<std::milli, std::ratio<1, 1000>>));
    std::cout << "  ✓ milli == 1/1000\n";
}

// Test edge cases
void test_edge_cases()
{
    std::cout << "\n=== Testing Edge Cases ===\n";

    // Zero ratio
    using zero = std::ratio<0, 1>;
    assert(zero::num == 0);
    std::cout << "  ✓ std::ratio<0, 1>: " << zero::num << "/" << zero::den << "\n";

    // Large numerator and denominator
    using large_ratio = std::ratio<1000000, 2000000>;  // Should reduce to 1/2
    assert(large_ratio::num == 1 && large_ratio::den == 2);
    std::cout << "  ✓ std::ratio<1000000, 2000000> reduces to: " << large_ratio::num << "/" << large_ratio::den << "\n";

    // Negative ratio normalization
    using neg1 = std::ratio<-1, -2>;  // Should normalize to 1/2
    assert(neg1::num == 1 && neg1::den == 2);
    std::cout << "  ✓ std::ratio<-1, -2> normalizes to: " << neg1::num << "/" << neg1::den << "\n";

    using neg2 = std::ratio<1, -2>;  // Should normalize to -1/2
    assert(neg2::num == -1 && neg2::den == 2);
    std::cout << "  ✓ std::ratio<1, -2> normalizes to: " << neg2::num << "/" << neg2::den << "\n";
}

int main()
{
    std::cout << "Testing std_module.ratio\n";
    std::cout << "========================\n";

    test_basic_ratio();
    test_si_units();
    test_ratio_arithmetic();
    test_ratio_comparison();
    test_ratio_comparison_v();
    test_time_conversions();
    test_edge_cases();

    std::cout << "\n✓ All ratio tests passed!\n";
    return 0;
}
