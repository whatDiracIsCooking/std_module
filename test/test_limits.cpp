/**
 * @file test_limits.cpp
 * @brief Comprehensive test for std_module.limits (C++20)
 */

import std_module.limits;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules

void test_integer_limits() {
    std::cout << "Testing integer type limits...\n";

    // Test int limits
    assert(std::numeric_limits<int>::is_specialized);
    assert(std::numeric_limits<int>::is_integer);
    assert(std::numeric_limits<int>::is_signed);
    std::cout << "  ✓ int is_specialized: " << std::numeric_limits<int>::is_specialized << "\n";
    std::cout << "  ✓ int min: " << std::numeric_limits<int>::min() << "\n";
    std::cout << "  ✓ int max: " << std::numeric_limits<int>::max() << "\n";
    std::cout << "  ✓ int lowest: " << std::numeric_limits<int>::lowest() << "\n";
    std::cout << "  ✓ int digits: " << std::numeric_limits<int>::digits << "\n";

    // Test unsigned int limits
    assert(std::numeric_limits<unsigned int>::is_specialized);
    assert(std::numeric_limits<unsigned int>::is_integer);
    assert(!std::numeric_limits<unsigned int>::is_signed);
    std::cout << "  ✓ unsigned int is_signed: " << std::numeric_limits<unsigned int>::is_signed << "\n";
    std::cout << "  ✓ unsigned int min: " << std::numeric_limits<unsigned int>::min() << "\n";
    std::cout << "  ✓ unsigned int max: " << std::numeric_limits<unsigned int>::max() << "\n";

    // Test char limits
    assert(std::numeric_limits<char>::is_specialized);
    assert(std::numeric_limits<char>::is_integer);
    std::cout << "  ✓ char min: " << static_cast<int>(std::numeric_limits<char>::min()) << "\n";
    std::cout << "  ✓ char max: " << static_cast<int>(std::numeric_limits<char>::max()) << "\n";
}

void test_floating_point_limits() {
    std::cout << "\nTesting floating-point type limits...\n";

    // Test float limits
    assert(std::numeric_limits<float>::is_specialized);
    assert(!std::numeric_limits<float>::is_integer);
    assert(std::numeric_limits<float>::is_signed);
    std::cout << "  ✓ float is_specialized: " << std::numeric_limits<float>::is_specialized << "\n";
    std::cout << "  ✓ float min: " << std::numeric_limits<float>::min() << "\n";
    std::cout << "  ✓ float max: " << std::numeric_limits<float>::max() << "\n";
    std::cout << "  ✓ float lowest: " << std::numeric_limits<float>::lowest() << "\n";
    std::cout << "  ✓ float epsilon: " << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << "  ✓ float digits: " << std::numeric_limits<float>::digits << "\n";
    std::cout << "  ✓ float digits10: " << std::numeric_limits<float>::digits10 << "\n";

    // Test double limits
    assert(std::numeric_limits<double>::is_specialized);
    assert(!std::numeric_limits<double>::is_integer);
    assert(std::numeric_limits<double>::is_signed);
    std::cout << "  ✓ double min: " << std::numeric_limits<double>::min() << "\n";
    std::cout << "  ✓ double max: " << std::numeric_limits<double>::max() << "\n";
    std::cout << "  ✓ double epsilon: " << std::numeric_limits<double>::epsilon() << "\n";

    // Test long double limits
    assert(std::numeric_limits<long double>::is_specialized);
    std::cout << "  ✓ long double min: " << std::numeric_limits<long double>::min() << "\n";
    std::cout << "  ✓ long double max: " << std::numeric_limits<long double>::max() << "\n";
}

void test_special_float_values() {
    std::cout << "\nTesting special floating-point values...\n";

    // Test infinity
    if (std::numeric_limits<double>::has_infinity) {
        auto inf = std::numeric_limits<double>::infinity();
        assert(inf > 0);
        std::cout << "  ✓ double has_infinity: " << std::numeric_limits<double>::has_infinity << "\n";
        std::cout << "  ✓ double infinity: " << inf << "\n";
    }

    // Test quiet NaN
    if (std::numeric_limits<double>::has_quiet_NaN) {
        auto qnan = std::numeric_limits<double>::quiet_NaN();
        assert(qnan != qnan);  // NaN is not equal to itself
        std::cout << "  ✓ double has_quiet_NaN: " << std::numeric_limits<double>::has_quiet_NaN << "\n";
        std::cout << "  ✓ double quiet_NaN: " << qnan << "\n";
    }

    // Test signaling NaN
    if (std::numeric_limits<double>::has_signaling_NaN) {
        auto snan = std::numeric_limits<double>::signaling_NaN();
        std::cout << "  ✓ double has_signaling_NaN: " << std::numeric_limits<double>::has_signaling_NaN << "\n";
        std::cout << "  ✓ double signaling_NaN: " << snan << "\n";
    }

    // Test denorm_min
    if (std::numeric_limits<double>::has_denorm != std::float_denorm_style::denorm_absent) {
        auto denorm = std::numeric_limits<double>::denorm_min();
        assert(denorm > 0);
        assert(denorm < std::numeric_limits<double>::min());
        std::cout << "  ✓ double denorm_min: " << denorm << "\n";
    }
}

void test_numeric_properties() {
    std::cout << "\nTesting numeric properties...\n";

    // Test radix
    std::cout << "  ✓ int radix: " << std::numeric_limits<int>::radix << "\n";
    std::cout << "  ✓ float radix: " << std::numeric_limits<float>::radix << "\n";
    assert(std::numeric_limits<int>::radix == 2);
    assert(std::numeric_limits<float>::radix == 2);

    // Test min/max exponent
    std::cout << "  ✓ float min_exponent: " << std::numeric_limits<float>::min_exponent << "\n";
    std::cout << "  ✓ float max_exponent: " << std::numeric_limits<float>::max_exponent << "\n";
    std::cout << "  ✓ float min_exponent10: " << std::numeric_limits<float>::min_exponent10 << "\n";
    std::cout << "  ✓ float max_exponent10: " << std::numeric_limits<float>::max_exponent10 << "\n";

    // Test max_digits10
    std::cout << "  ✓ double max_digits10: " << std::numeric_limits<double>::max_digits10 << "\n";
}

void test_type_traits() {
    std::cout << "\nTesting type traits...\n";

    // Test is_bounded
    assert(std::numeric_limits<int>::is_bounded);
    assert(std::numeric_limits<float>::is_bounded);
    std::cout << "  ✓ int is_bounded: " << std::numeric_limits<int>::is_bounded << "\n";
    std::cout << "  ✓ float is_bounded: " << std::numeric_limits<float>::is_bounded << "\n";

    // Test is_modulo
    std::cout << "  ✓ unsigned int is_modulo: " << std::numeric_limits<unsigned int>::is_modulo << "\n";
    std::cout << "  ✓ int is_modulo: " << std::numeric_limits<int>::is_modulo << "\n";

    // Test is_exact
    assert(std::numeric_limits<int>::is_exact);
    assert(!std::numeric_limits<float>::is_exact);
    std::cout << "  ✓ int is_exact: " << std::numeric_limits<int>::is_exact << "\n";
    std::cout << "  ✓ float is_exact: " << std::numeric_limits<float>::is_exact << "\n";

    // Test is_iec559
    std::cout << "  ✓ float is_iec559: " << std::numeric_limits<float>::is_iec559 << "\n";
    std::cout << "  ✓ double is_iec559: " << std::numeric_limits<double>::is_iec559 << "\n";

    // Test traps
    std::cout << "  ✓ int traps: " << std::numeric_limits<int>::traps << "\n";
    std::cout << "  ✓ float traps: " << std::numeric_limits<float>::traps << "\n";

    // Test tinyness_before
    std::cout << "  ✓ float tinyness_before: " << std::numeric_limits<float>::tinyness_before << "\n";
}

void test_rounding_and_denorm_styles() {
    std::cout << "\nTesting rounding and denormalization styles...\n";

    // Test round_style
    auto float_round = std::numeric_limits<float>::round_style;
    std::cout << "  ✓ float round_style: " << static_cast<int>(float_round) << "\n";

    auto int_round = std::numeric_limits<int>::round_style;
    std::cout << "  ✓ int round_style: " << static_cast<int>(int_round) << "\n";
    assert(int_round == std::float_round_style::round_toward_zero);

    // Test has_denorm
    auto float_denorm = std::numeric_limits<float>::has_denorm;
    std::cout << "  ✓ float has_denorm: " << static_cast<int>(float_denorm) << "\n";

    auto int_denorm = std::numeric_limits<int>::has_denorm;
    std::cout << "  ✓ int has_denorm: " << static_cast<int>(int_denorm) << "\n";
    assert(int_denorm == std::float_denorm_style::denorm_absent);

    // Test has_denorm_loss
    std::cout << "  ✓ float has_denorm_loss: " << std::numeric_limits<float>::has_denorm_loss << "\n";
}

void test_long_long_limits() {
    std::cout << "\nTesting long long type limits...\n";

    // Test long long limits
    assert(std::numeric_limits<long long>::is_specialized);
    assert(std::numeric_limits<long long>::is_integer);
    assert(std::numeric_limits<long long>::is_signed);
    std::cout << "  ✓ long long min: " << std::numeric_limits<long long>::min() << "\n";
    std::cout << "  ✓ long long max: " << std::numeric_limits<long long>::max() << "\n";

    // Test unsigned long long limits
    assert(std::numeric_limits<unsigned long long>::is_specialized);
    assert(!std::numeric_limits<unsigned long long>::is_signed);
    std::cout << "  ✓ unsigned long long min: " << std::numeric_limits<unsigned long long>::min() << "\n";
    std::cout << "  ✓ unsigned long long max: " << std::numeric_limits<unsigned long long>::max() << "\n";
}

void test_bool_limits() {
    std::cout << "\nTesting bool type limits...\n";

    assert(std::numeric_limits<bool>::is_specialized);
    assert(std::numeric_limits<bool>::is_integer);
    assert(!std::numeric_limits<bool>::is_signed);
    assert(std::numeric_limits<bool>::min() == false);
    assert(std::numeric_limits<bool>::max() == true);
    std::cout << "  ✓ bool is_specialized: " << std::numeric_limits<bool>::is_specialized << "\n";
    std::cout << "  ✓ bool min: " << std::numeric_limits<bool>::min() << "\n";
    std::cout << "  ✓ bool max: " << std::numeric_limits<bool>::max() << "\n";
    std::cout << "  ✓ bool digits: " << std::numeric_limits<bool>::digits << "\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "std_module.limits - Comprehensive Tests\n";
    std::cout << "========================================\n\n";

    try {
        test_integer_limits();
        test_floating_point_limits();
        test_special_float_values();
        test_numeric_properties();
        test_type_traits();
        test_rounding_and_denorm_styles();
        test_long_long_limits();
        test_bool_limits();

        std::cout << "\n========================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "========================================\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
