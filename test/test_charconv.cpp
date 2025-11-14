/**
 * @file test_charconv.cpp
 * @brief Tests for std_module.charconv
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.charconv;
import std_module.test_framework;

int main() {
    test::test_header("std_module.charconv");

    test::section("Testing symbol accessibility");

    // Test that charconv functions and types are accessible (not testing correctness)
    char buffer[50];

    // to_chars variants - integers
    [[maybe_unused]] auto r1 = std::to_chars(buffer, buffer + sizeof(buffer), 42);
    [[maybe_unused]] auto r2 = std::to_chars(buffer, buffer + sizeof(buffer), 42, 16);
    test::success("to_chars (integer, with base)");

    // to_chars variants - floating point
    [[maybe_unused]] auto r3 = std::to_chars(buffer, buffer + sizeof(buffer), 3.14);
    [[maybe_unused]] auto r4 = std::to_chars(buffer, buffer + sizeof(buffer), 3.14, std::chars_format::fixed);
    [[maybe_unused]] auto r5 = std::to_chars(buffer, buffer + sizeof(buffer), 3.14, std::chars_format::scientific, 2);
    test::success("to_chars (floating-point, with format)");

    // from_chars variants - integers
    const char* str = "42";
    int value = 0;
    [[maybe_unused]] auto r6 = std::from_chars(str, str + 2, value);
    [[maybe_unused]] auto r7 = std::from_chars(str, str + 2, value, 10);
    test::success("from_chars (integer, with base)");

    // from_chars variants - floating point
    const char* fstr = "3.14";
    double dvalue = 0.0;
    [[maybe_unused]] auto r8 = std::from_chars(fstr, fstr + 4, dvalue);
    [[maybe_unused]] auto r9 = std::from_chars(fstr, fstr + 4, dvalue, std::chars_format::general);
    test::success("from_chars (floating-point, with format)");

    // chars_format enum
    [[maybe_unused]] auto fmt_sci = std::chars_format::scientific;
    [[maybe_unused]] auto fmt_fix = std::chars_format::fixed;
    [[maybe_unused]] auto fmt_hex = std::chars_format::hex;
    [[maybe_unused]] auto fmt_gen = std::chars_format::general;
    test::success("chars_format enum");

    // to_chars_result and from_chars_result structures
    auto result = std::to_chars(buffer, buffer + sizeof(buffer), 42);
    [[maybe_unused]] auto ptr = result.ptr;
    [[maybe_unused]] auto ec = result.ec;
    test::success("to_chars_result structure");

    test::test_footer();
    return 0;
}
