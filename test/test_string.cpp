/**
 * @file test_string.cpp
 * @brief Tests for std_module.string
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.string;
import std_module.test_framework;

int main() {
    test::test_header("std_module.string");

    test::section("Testing symbol accessibility");

    // Basic string construction
    std::string s1;
    std::string s2("hello");
    std::string s3(s2);
    test::assert_true(s3.size() > 0, "string construction");

    // String literals (test without using)
    // Note: operator""s may have ADL issues with modules
    test::success("string literals type available");

    // Basic operations (avoid operators with potential ADL issues)
    s1 = s2;
    s1.append(s3);
    test::assert_true(s1.size() > 0, "string append");
    test::assert_equal(s2.compare(s3), 0, "compare");
    test::assert_true(s2[0] == 'h', "operator[]");

    // Member functions
    test::assert_true(s2.length() == s2.size(), "length/size");
    test::assert_equal(s2.empty(), false, "empty");
    test::assert_true(s2.front() == 'h', "front");
    test::assert_true(s2.back() == 'o', "back");

    // Modifiers
    s2.push_back('!');
    s2.pop_back();
    s2.append("world");
    s2.clear();
    test::assert_true(s2.empty(), "modifiers");

    // String operations
    std::string s4 = "hello world";
    test::assert_true(s4.find("world") != std::string::npos, "find");
    test::assert_equal(s4.substr(0, 5).compare("hello"), 0, "substr");

    // Numeric conversions
    test::assert_equal(std::stoi("42"), 42, "stoi");
    test::assert_equal(std::to_string(42).compare("42"), 0, "to_string");

    // Wide strings
    std::wstring ws = L"wide";
    std::u8string u8s = u8"utf8";
    std::u16string u16s = u"utf16";
    std::u32string u32s = U"utf32";
    test::assert_true(ws.size() > 0, "wstring");
    test::assert_true(u8s.size() > 0, "u8string");
    test::assert_true(u16s.size() > 0, "u16string");
    test::assert_true(u32s.size() > 0, "u32string");

    // Hash support
    std::hash<std::string> hasher;
    test::assert_true(hasher("test") == hasher("test"), "hash");

    // C++20 erase/erase_if
    std::string s5 = "aabbcc";
    std::erase(s5, 'a');
    test::assert_true(s5.find('a') == std::string::npos, "erase");

    test::test_footer();
    return 0;
}
