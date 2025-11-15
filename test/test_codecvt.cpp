/**
 * @file test_codecvt.cpp
 * @brief Tests for std_module.codecvt
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 * @note <codecvt> is deprecated in C++17, but still part of the standard library
 */

import std_module.codecvt;
import std_module.test_framework;

#include <string>    // TEMP: For wstring_convert
#include <locale>    // TEMP: For wstring_convert

int main() {
    test::test_header("std_module.codecvt");

    test::section("Testing codecvt_utf8");

    // Test that codecvt_utf8 is constructible and callable with different char types
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv_wchar;
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> conv_char16;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv_char32;

    // Test from_bytes and to_bytes are callable
    std::string test_str = "Test";
    auto wide = conv_wchar.from_bytes(test_str);
    auto back = conv_wchar.to_bytes(wide);
    test::assert_true(!back.empty(), "codecvt_utf8 conversions");

    test::section("Testing codecvt_utf16");

    // Test that codecvt_utf16 is constructible and callable
    std::wstring_convert<std::codecvt_utf16<wchar_t>, wchar_t> conv_utf16_wchar;
    std::wstring_convert<std::codecvt_utf16<char16_t>, char16_t> conv_utf16_char16;
    std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> conv_utf16_char32;

    // Test conversions are callable
    std::wstring wide_str = L"Test";
    auto bytes = conv_utf16_wchar.to_bytes(wide_str);
    auto back_wide = conv_utf16_wchar.from_bytes(bytes);
    test::assert_true(!bytes.empty(), "codecvt_utf16 conversions");

    test::section("Testing codecvt_utf8_utf16");

    // Test that codecvt_utf8_utf16 is constructible and callable
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv_utf8_utf16_16;
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>, char32_t> conv_utf8_utf16_32;

    auto u16 = conv_utf8_utf16_16.from_bytes(test_str);
    auto utf8 = conv_utf8_utf16_16.to_bytes(u16);
    test::assert_true(!utf8.empty(), "codecvt_utf8_utf16 conversions");

    test::section("Testing codecvt_mode enum");

    // Test that codecvt_mode enum values are accessible
    [[maybe_unused]] std::codecvt_mode mode1 = std::consume_header;
    [[maybe_unused]] std::codecvt_mode mode2 = std::generate_header;
    [[maybe_unused]] std::codecvt_mode mode3 = std::little_endian;
    test::success("codecvt_mode enum accessible");

    test::section("Testing codecvt with modes");

    // Test that codecvt with mode parameters is constructible
    std::wstring_convert<std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>> conv_bom;
    std::wstring_convert<std::codecvt_utf16<char16_t, 0x10ffff, std::little_endian>, char16_t> conv_le;

    // Test conversions with modes are callable
    auto with_bom = conv_bom.to_bytes(L"Test");
    auto le_bytes = conv_le.to_bytes(u"Test");
    test::assert_true(!with_bom.empty(), "codecvt with modes");

    test::test_footer();
    return 0;
}
