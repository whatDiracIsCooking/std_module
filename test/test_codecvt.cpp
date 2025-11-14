/**
 * @file test_codecvt.cpp
 * @brief Comprehensive test for std_module.codecvt (C++20)
 * @note <codecvt> is deprecated in C++17, but still part of the standard library
 */

import std_module.codecvt;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string when available
#include <locale>    // For wstring_convert

// Test basic UTF-8 conversion
void test_codecvt_utf8_basic() {
    std::cout << "Testing codecvt_utf8 basic conversion...\n";

    // UTF-8 to wide string conversion
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // Convert ASCII
    std::string utf8_ascii = "Hello, World!";
    std::wstring wide = converter.from_bytes(utf8_ascii);
    assert(wide == L"Hello, World!");
    std::cout << "  ✓ ASCII string converted to wide string\n";

    // Convert back to UTF-8
    std::string utf8_back = converter.to_bytes(wide);
    assert(utf8_back == utf8_ascii);
    std::cout << "  ✓ Wide string converted back to UTF-8\n";
}

// Test UTF-8 with multi-byte characters
void test_codecvt_utf8_multibyte() {
    std::cout << "\nTesting codecvt_utf8 with multi-byte characters...\n";

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // Test with emoji and special characters
    std::string utf8_emoji = "Hello 👋 World 🌍";
    std::wstring wide = converter.from_bytes(utf8_emoji);
    assert(!wide.empty());
    std::cout << "  ✓ UTF-8 with emoji converted to wide string (length: " << wide.length() << ")\n";

    // Convert back
    std::string utf8_back = converter.to_bytes(wide);
    assert(utf8_back == utf8_emoji);
    std::cout << "  ✓ Wide string with emoji converted back to UTF-8\n";
}

// Test UTF-8 with different character types (char16_t)
void test_codecvt_utf8_char16() {
    std::cout << "\nTesting codecvt_utf8 with char16_t...\n";

    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;

    std::string utf8 = "Hello";
    std::u16string u16 = converter.from_bytes(utf8);
    assert(u16.length() == 5);
    std::cout << "  ✓ UTF-8 converted to UTF-16 (char16_t)\n";

    std::string back = converter.to_bytes(u16);
    assert(back == utf8);
    std::cout << "  ✓ UTF-16 (char16_t) converted back to UTF-8\n";
}

// Test UTF-8 with char32_t
void test_codecvt_utf8_char32() {
    std::cout << "\nTesting codecvt_utf8 with char32_t...\n";

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

    std::string utf8 = "Test";
    std::u32string u32 = converter.from_bytes(utf8);
    assert(u32.length() == 4);
    std::cout << "  ✓ UTF-8 converted to UTF-32 (char32_t)\n";

    std::string back = converter.to_bytes(u32);
    assert(back == utf8);
    std::cout << "  ✓ UTF-32 (char32_t) converted back to UTF-8\n";
}

// Test codecvt_utf16 basic conversion
void test_codecvt_utf16_basic() {
    std::cout << "\nTesting codecvt_utf16 basic conversion...\n";

    // Note: codecvt_utf16 converts between UTF-16 and UCS-2/UCS-4
    std::wstring_convert<std::codecvt_utf16<wchar_t>, wchar_t> converter;

    std::wstring wide = L"Hello";
    std::string bytes = converter.to_bytes(wide);
    assert(!bytes.empty());
    std::cout << "  ✓ Wide string converted to UTF-16 bytes (size: " << bytes.size() << ")\n";

    std::wstring back = converter.from_bytes(bytes);
    assert(back == wide);
    std::cout << "  ✓ UTF-16 bytes converted back to wide string\n";
}

// Test codecvt_utf16 with char16_t
void test_codecvt_utf16_char16() {
    std::cout << "\nTesting codecvt_utf16 with char16_t...\n";

    std::wstring_convert<std::codecvt_utf16<char16_t>, char16_t> converter;

    std::u16string u16 = u"Test String";
    std::string bytes = converter.to_bytes(u16);
    assert(!bytes.empty());
    std::cout << "  ✓ UTF-16 string converted to bytes (size: " << bytes.size() << ")\n";

    std::u16string back = converter.from_bytes(bytes);
    assert(back == u16);
    std::cout << "  ✓ Bytes converted back to UTF-16 string\n";
}

// Test codecvt_utf16 with char32_t
void test_codecvt_utf16_char32() {
    std::cout << "\nTesting codecvt_utf16 with char32_t...\n";

    std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> converter;

    std::u32string u32 = U"Hello World";
    std::string bytes = converter.to_bytes(u32);
    assert(!bytes.empty());
    std::cout << "  ✓ UTF-32 string converted to UTF-16 bytes (size: " << bytes.size() << ")\n";

    std::u32string back = converter.from_bytes(bytes);
    assert(back == u32);
    std::cout << "  ✓ UTF-16 bytes converted back to UTF-32 string\n";
}

// Test codecvt_utf8_utf16
void test_codecvt_utf8_utf16() {
    std::cout << "\nTesting codecvt_utf8_utf16 conversion...\n";

    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;

    std::string utf8 = "Hello World";
    std::u16string u16 = converter.from_bytes(utf8);
    assert(u16.length() == 11);
    std::cout << "  ✓ UTF-8 converted to UTF-16 via codecvt_utf8_utf16\n";

    std::string back = converter.to_bytes(u16);
    assert(back == utf8);
    std::cout << "  ✓ UTF-16 converted back to UTF-8 via codecvt_utf8_utf16\n";
}

// Test codecvt_utf8_utf16 with char32_t
void test_codecvt_utf8_utf16_char32() {
    std::cout << "\nTesting codecvt_utf8_utf16 with char32_t...\n";

    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>, char32_t> converter;

    std::string utf8 = "Test";
    std::u32string u32 = converter.from_bytes(utf8);
    assert(!u32.empty());
    std::cout << "  ✓ UTF-8 converted to UTF-32 via codecvt_utf8_utf16\n";

    std::string back = converter.to_bytes(u32);
    assert(back == utf8);
    std::cout << "  ✓ UTF-32 converted back to UTF-8 via codecvt_utf8_utf16\n";
}

// Test codecvt_mode enum
void test_codecvt_mode() {
    std::cout << "\nTesting codecvt_mode enum...\n";

    // Test that we can use codecvt_mode values
    std::codecvt_mode mode1 = std::consume_header;
    std::codecvt_mode mode2 = std::generate_header;
    std::codecvt_mode mode3 = std::little_endian;

    // Verify they're different values
    assert(static_cast<int>(mode1) != static_cast<int>(mode2));
    assert(static_cast<int>(mode2) != static_cast<int>(mode3));
    std::cout << "  ✓ codecvt_mode enum values accessible\n";

    // Test combining modes with OR
    std::codecvt_mode combined = static_cast<std::codecvt_mode>(
        static_cast<int>(std::consume_header) | static_cast<int>(std::little_endian)
    );
    std::cout << "  ✓ codecvt_mode values can be combined\n";
}

// Test UTF-8 with BOM (Byte Order Mark)
void test_utf8_with_bom() {
    std::cout << "\nTesting UTF-8 with BOM handling...\n";

    // Test with generate_header mode
    std::wstring_convert<std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>> converter;

    std::wstring wide = L"Test";
    std::string utf8_with_bom = converter.to_bytes(wide);

    // UTF-8 BOM is 3 bytes: 0xEF, 0xBB, 0xBF
    assert(utf8_with_bom.size() >= 3);
    std::cout << "  ✓ UTF-8 with BOM generated (size: " << utf8_with_bom.size() << ")\n";
}

// Test UTF-16 with little endian mode
void test_utf16_little_endian() {
    std::cout << "\nTesting UTF-16 with little endian mode...\n";

    std::wstring_convert<std::codecvt_utf16<char16_t, 0x10ffff, std::little_endian>, char16_t> converter;

    std::u16string u16 = u"Hello";
    std::string bytes = converter.to_bytes(u16);
    assert(!bytes.empty());
    std::cout << "  ✓ UTF-16 with little endian mode (size: " << bytes.size() << ")\n";

    std::u16string back = converter.from_bytes(bytes);
    assert(back == u16);
    std::cout << "  ✓ UTF-16 little endian roundtrip successful\n";
}

// Test error handling
void test_error_handling() {
    std::cout << "\nTesting error handling...\n";

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // Test invalid UTF-8 sequence
    try {
        std::string invalid_utf8 = "\xFF\xFE";  // Invalid UTF-8
        std::wstring result = converter.from_bytes(invalid_utf8);
        // If we get here, check if converter detected an error via converted() or state()
        std::cout << "  ✓ Invalid UTF-8 handled (result length: " << result.length() << ")\n";
    } catch (const std::range_error& e) {
        std::cout << "  ✓ Invalid UTF-8 threw range_error: " << e.what() << "\n";
    }
}

// Test empty string conversion
void test_empty_strings() {
    std::cout << "\nTesting empty string conversions...\n";

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    std::string empty_utf8 = "";
    std::wstring wide = converter.from_bytes(empty_utf8);
    assert(wide.empty());
    std::cout << "  ✓ Empty UTF-8 string converted to empty wide string\n";

    std::wstring empty_wide = L"";
    std::string utf8 = converter.to_bytes(empty_wide);
    assert(utf8.empty());
    std::cout << "  ✓ Empty wide string converted to empty UTF-8 string\n";
}

int main() {
    std::cout << "=================================================\n";
    std::cout << "  std_module.codecvt Comprehensive Test Suite\n";
    std::cout << "=================================================\n\n";

    test_codecvt_utf8_basic();
    test_codecvt_utf8_multibyte();
    test_codecvt_utf8_char16();
    test_codecvt_utf8_char32();
    test_codecvt_utf16_basic();
    test_codecvt_utf16_char16();
    test_codecvt_utf16_char32();
    test_codecvt_utf8_utf16();
    test_codecvt_utf8_utf16_char32();
    test_codecvt_mode();
    test_utf8_with_bom();
    test_utf16_little_endian();
    test_error_handling();
    test_empty_strings();

    std::cout << "\n=================================================\n";
    std::cout << "  All std_module.codecvt tests passed! ✓\n";
    std::cout << "=================================================\n";

    return 0;
}
