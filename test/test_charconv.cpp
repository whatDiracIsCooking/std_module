/**
 * @file test_charconv.cpp
 * @brief Comprehensive test for std_module.charconv (C++20)
 */

import std_module.charconv;

#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include <limits>
#include <cmath>

void test_to_chars_integers() {
    std::cout << "Testing to_chars with integers...\n";

    char buffer[50];

    // Test basic integer conversion
    auto result = std::to_chars(buffer, buffer + sizeof(buffer), 42);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "42");
    std::cout << "  ✓ to_chars(42): " << buffer << "\n";

    // Test negative integer
    result = std::to_chars(buffer, buffer + sizeof(buffer), -123);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "-123");
    std::cout << "  ✓ to_chars(-123): " << buffer << "\n";

    // Test zero
    result = std::to_chars(buffer, buffer + sizeof(buffer), 0);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "0");
    std::cout << "  ✓ to_chars(0): " << buffer << "\n";

    // Test large number
    result = std::to_chars(buffer, buffer + sizeof(buffer), 2147483647);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "2147483647");
    std::cout << "  ✓ to_chars(INT_MAX): " << buffer << "\n";
}

void test_to_chars_bases() {
    std::cout << "\nTesting to_chars with different bases...\n";

    char buffer[50];

    // Test binary (base 2)
    auto result = std::to_chars(buffer, buffer + sizeof(buffer), 42, 2);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "101010");
    std::cout << "  ✓ to_chars(42, base 2): " << buffer << "\n";

    // Test octal (base 8)
    result = std::to_chars(buffer, buffer + sizeof(buffer), 42, 8);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "52");
    std::cout << "  ✓ to_chars(42, base 8): " << buffer << "\n";

    // Test hexadecimal (base 16)
    result = std::to_chars(buffer, buffer + sizeof(buffer), 255, 16);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "ff");
    std::cout << "  ✓ to_chars(255, base 16): " << buffer << "\n";

    // Test base 36 (maximum)
    result = std::to_chars(buffer, buffer + sizeof(buffer), 1234, 36);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "ya");
    std::cout << "  ✓ to_chars(1234, base 36): " << buffer << "\n";
}

void test_to_chars_floating_point() {
    std::cout << "\nTesting to_chars with floating-point...\n";

    char buffer[50];

    // Test basic double conversion
    auto result = std::to_chars(buffer, buffer + sizeof(buffer), 3.14159);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    std::cout << "  ✓ to_chars(3.14159): " << buffer << "\n";

    // Test with fixed format
    result = std::to_chars(buffer, buffer + sizeof(buffer), 3.14159, std::chars_format::fixed, 2);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "3.14");
    std::cout << "  ✓ to_chars(3.14159, fixed, 2): " << buffer << "\n";

    // Test with scientific format
    result = std::to_chars(buffer, buffer + sizeof(buffer), 1234.5, std::chars_format::scientific, 2);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    std::cout << "  ✓ to_chars(1234.5, scientific, 2): " << buffer << "\n";

    // Test with general format
    result = std::to_chars(buffer, buffer + sizeof(buffer), 0.000123, std::chars_format::general);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    std::cout << "  ✓ to_chars(0.000123, general): " << buffer << "\n";

    // Test negative float
    result = std::to_chars(buffer, buffer + sizeof(buffer), -2.71828, std::chars_format::fixed, 3);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    assert(std::string(buffer) == "-2.718");
    std::cout << "  ✓ to_chars(-2.71828, fixed, 3): " << buffer << "\n";
}

void test_from_chars_integers() {
    std::cout << "\nTesting from_chars with integers...\n";

    // Test basic integer parsing
    const char* str1 = "42";
    int value1 = 0;
    auto result = std::from_chars(str1, str1 + std::strlen(str1), value1);
    assert(result.ec == std::errc{});
    assert(value1 == 42);
    std::cout << "  ✓ from_chars(\"42\"): " << value1 << "\n";

    // Test negative integer
    const char* str2 = "-123";
    int value2 = 0;
    result = std::from_chars(str2, str2 + std::strlen(str2), value2);
    assert(result.ec == std::errc{});
    assert(value2 == -123);
    std::cout << "  ✓ from_chars(\"-123\"): " << value2 << "\n";

    // Test with trailing characters
    const char* str3 = "456abc";
    int value3 = 0;
    result = std::from_chars(str3, str3 + std::strlen(str3), value3);
    assert(result.ec == std::errc{});
    assert(value3 == 456);
    assert(result.ptr == str3 + 3);  // Stopped at 'a'
    std::cout << "  ✓ from_chars(\"456abc\"): " << value3 << " (stopped at position 3)\n";

    // Test unsigned
    const char* str4 = "4294967295";
    unsigned int value4 = 0;
    result = std::from_chars(str4, str4 + std::strlen(str4), value4);
    assert(result.ec == std::errc{});
    assert(value4 == 4294967295u);
    std::cout << "  ✓ from_chars(\"4294967295\"): " << value4 << "\n";
}

void test_from_chars_bases() {
    std::cout << "\nTesting from_chars with different bases...\n";

    // Test binary (base 2)
    const char* str1 = "101010";
    int value1 = 0;
    auto result = std::from_chars(str1, str1 + std::strlen(str1), value1, 2);
    assert(result.ec == std::errc{});
    assert(value1 == 42);
    std::cout << "  ✓ from_chars(\"101010\", base 2): " << value1 << "\n";

    // Test octal (base 8)
    const char* str2 = "52";
    int value2 = 0;
    result = std::from_chars(str2, str2 + std::strlen(str2), value2, 8);
    assert(result.ec == std::errc{});
    assert(value2 == 42);
    std::cout << "  ✓ from_chars(\"52\", base 8): " << value2 << "\n";

    // Test hexadecimal (base 16)
    const char* str3 = "ff";
    int value3 = 0;
    result = std::from_chars(str3, str3 + std::strlen(str3), value3, 16);
    assert(result.ec == std::errc{});
    assert(value3 == 255);
    std::cout << "  ✓ from_chars(\"ff\", base 16): " << value3 << "\n";

    // Test hexadecimal with uppercase
    const char* str4 = "DEADBEEF";
    unsigned int value4 = 0;
    result = std::from_chars(str4, str4 + std::strlen(str4), value4, 16);
    assert(result.ec == std::errc{});
    assert(value4 == 0xDEADBEEF);
    std::cout << "  ✓ from_chars(\"DEADBEEF\", base 16): " << value4 << "\n";

    // Test base 36
    const char* str5 = "ya";
    int value5 = 0;
    result = std::from_chars(str5, str5 + std::strlen(str5), value5, 36);
    assert(result.ec == std::errc{});
    assert(value5 == 1234);
    std::cout << "  ✓ from_chars(\"ya\", base 36): " << value5 << "\n";
}

void test_from_chars_floating_point() {
    std::cout << "\nTesting from_chars with floating-point...\n";

    // Test basic float parsing
    const char* str1 = "3.14159";
    double value1 = 0.0;
    auto result = std::from_chars(str1, str1 + std::strlen(str1), value1);
    assert(result.ec == std::errc{});
    assert(std::abs(value1 - 3.14159) < 0.00001);
    std::cout << "  ✓ from_chars(\"3.14159\"): " << value1 << "\n";

    // Test negative float
    const char* str2 = "-2.71828";
    double value2 = 0.0;
    result = std::from_chars(str2, str2 + std::strlen(str2), value2);
    assert(result.ec == std::errc{});
    assert(std::abs(value2 - (-2.71828)) < 0.00001);
    std::cout << "  ✓ from_chars(\"-2.71828\"): " << value2 << "\n";

    // Test scientific notation
    const char* str3 = "1.23e+2";
    double value3 = 0.0;
    result = std::from_chars(str3, str3 + std::strlen(str3), value3);
    assert(result.ec == std::errc{});
    assert(std::abs(value3 - 123.0) < 0.00001);
    std::cout << "  ✓ from_chars(\"1.23e+2\"): " << value3 << "\n";

    // Test with different format
    const char* str4 = "1.5e-3";
    double value4 = 0.0;
    result = std::from_chars(str4, str4 + std::strlen(str4), value4, std::chars_format::scientific);
    assert(result.ec == std::errc{});
    assert(std::abs(value4 - 0.0015) < 0.000001);
    std::cout << "  ✓ from_chars(\"1.5e-3\", scientific): " << value4 << "\n";

    // Test zero
    const char* str5 = "0.0";
    double value5 = 1.0;
    result = std::from_chars(str5, str5 + std::strlen(str5), value5);
    assert(result.ec == std::errc{});
    assert(value5 == 0.0);
    std::cout << "  ✓ from_chars(\"0.0\"): " << value5 << "\n";
}

void test_error_handling() {
    std::cout << "\nTesting error handling...\n";

    char buffer[5];  // Too small for most conversions

    // Test buffer too small (value_too_large)
    auto result1 = std::to_chars(buffer, buffer + sizeof(buffer), 1234567890);
    assert(result1.ec == std::errc::value_too_large);
    std::cout << "  ✓ to_chars with insufficient buffer returns value_too_large\n";

    // Test invalid input for from_chars
    const char* invalid = "abc";
    int value = 0;
    auto result2 = std::from_chars(invalid, invalid + std::strlen(invalid), value);
    assert(result2.ec == std::errc::invalid_argument);
    std::cout << "  ✓ from_chars with invalid input returns invalid_argument\n";

    // Test out of range for from_chars
    const char* too_large = "999999999999999999999";
    int value2 = 0;
    auto result3 = std::from_chars(too_large, too_large + std::strlen(too_large), value2);
    assert(result3.ec == std::errc::result_out_of_range);
    std::cout << "  ✓ from_chars with out-of-range value returns result_out_of_range\n";
}

void test_roundtrip() {
    std::cout << "\nTesting roundtrip conversions...\n";

    // Test integer roundtrip
    char buffer[50];
    int original_int = 123456;
    auto to_result = std::to_chars(buffer, buffer + sizeof(buffer), original_int);
    assert(to_result.ec == std::errc{});

    int parsed_int = 0;
    auto from_result = std::from_chars(buffer, to_result.ptr, parsed_int);
    assert(from_result.ec == std::errc{});
    assert(parsed_int == original_int);
    std::cout << "  ✓ Integer roundtrip: " << original_int << " -> " << parsed_int << "\n";

    // Test float roundtrip
    double original_float = 3.141592653589793;
    to_result = std::to_chars(buffer, buffer + sizeof(buffer), original_float, std::chars_format::fixed, 10);
    assert(to_result.ec == std::errc{});

    double parsed_float = 0.0;
    from_result = std::from_chars(buffer, to_result.ptr, parsed_float);
    assert(from_result.ec == std::errc{});
    assert(std::abs(parsed_float - original_float) < 0.0000000001);
    std::cout << "  ✓ Float roundtrip: " << original_float << " -> " << parsed_float << "\n";

    // Test hex roundtrip
    int original_hex = 0xABCD;
    to_result = std::to_chars(buffer, buffer + sizeof(buffer), original_hex, 16);
    assert(to_result.ec == std::errc{});

    int parsed_hex = 0;
    from_result = std::from_chars(buffer, to_result.ptr, parsed_hex, 16);
    assert(from_result.ec == std::errc{});
    assert(parsed_hex == original_hex);
    std::cout << "  ✓ Hex roundtrip: 0x" << std::hex << original_hex << " -> 0x" << parsed_hex << std::dec << "\n";
}

void test_edge_cases() {
    std::cout << "\nTesting edge cases...\n";

    char buffer[100];

    // Test INT_MIN
    auto result = std::to_chars(buffer, buffer + sizeof(buffer), std::numeric_limits<int>::min());
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    std::cout << "  ✓ to_chars(INT_MIN): " << buffer << "\n";

    // Test INT_MAX
    result = std::to_chars(buffer, buffer + sizeof(buffer), std::numeric_limits<int>::max());
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    std::cout << "  ✓ to_chars(INT_MAX): " << buffer << "\n";

    // Test very small double
    result = std::to_chars(buffer, buffer + sizeof(buffer), 1e-300, std::chars_format::scientific);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    std::cout << "  ✓ to_chars(1e-300, scientific): " << buffer << "\n";

    // Test very large double
    result = std::to_chars(buffer, buffer + sizeof(buffer), 1e300, std::chars_format::scientific);
    assert(result.ec == std::errc{});
    *result.ptr = '\0';
    std::cout << "  ✓ to_chars(1e300, scientific): " << buffer << "\n";

    // Test exact buffer size
    result = std::to_chars(buffer, buffer + 2, 42);
    assert(result.ec == std::errc{});
    assert(result.ptr == buffer + 2);
    std::cout << "  ✓ to_chars with exact buffer size works\n";
}

int main() {
    std::cout << "=== Testing std_module.charconv ===\n\n";

    test_to_chars_integers();
    test_to_chars_bases();
    test_to_chars_floating_point();
    test_from_chars_integers();
    test_from_chars_bases();
    test_from_chars_floating_point();
    test_error_handling();
    test_roundtrip();
    test_edge_cases();

    std::cout << "\n=== All charconv tests passed! ===\n";
    return 0;
}
