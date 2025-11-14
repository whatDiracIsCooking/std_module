/**
 * @file test_iosfwd.cpp
 * @brief Comprehensive tests for std_module.iosfwd
 *
 * Tests all forward-declared types from <iosfwd> header.
 * Since iosfwd only provides forward declarations, we test type availability,
 * pointer/reference declarations, and basic type traits.
 */

import std_module.iosfwd;
#include <iostream>
#include <cassert>
#include <type_traits>
#include <memory>

// Helper to print test results
#define TEST_SECTION(name) std::cout << "\n" << name << ":\n"
#define TEST_PASS(desc) std::cout << "  ✓ " << desc << "\n"

// Test that a type exists and can be used in declarations
template<typename T>
void test_type_exists(const char* name) {
    // Test that we can declare pointers and references
    T* ptr = nullptr;
    (void)ptr;
    TEST_PASS(std::string(name) + " - pointer declaration works");
}

// Test basic stream buffer types
void test_streambuf_types() {
    TEST_SECTION("Stream Buffer Types");

    test_type_exists<std::basic_streambuf<char>>("basic_streambuf<char>");
    test_type_exists<std::streambuf>("streambuf");
    test_type_exists<std::wstreambuf>("wstreambuf");

    // Verify type aliases are correct
    static_assert(std::is_same_v<std::streambuf, std::basic_streambuf<char>>,
        "streambuf should be basic_streambuf<char>");
    static_assert(std::is_same_v<std::wstreambuf, std::basic_streambuf<wchar_t>>,
        "wstreambuf should be basic_streambuf<wchar_t>");
    TEST_PASS("Type aliases verified");
}

// Test basic_ios types
void test_basic_ios_types() {
    TEST_SECTION("Basic IOS Types");

    test_type_exists<std::basic_ios<char>>("basic_ios<char>");
    test_type_exists<std::ios>("ios");
    test_type_exists<std::wios>("wios");

    static_assert(std::is_same_v<std::ios, std::basic_ios<char>>,
        "ios should be basic_ios<char>");
    static_assert(std::is_same_v<std::wios, std::basic_ios<wchar_t>>,
        "wios should be basic_ios<wchar_t>");
    TEST_PASS("Type aliases verified");
}

// Test input stream types
void test_istream_types() {
    TEST_SECTION("Input Stream Types");

    test_type_exists<std::basic_istream<char>>("basic_istream<char>");
    test_type_exists<std::istream>("istream");
    test_type_exists<std::wistream>("wistream");

    static_assert(std::is_same_v<std::istream, std::basic_istream<char>>,
        "istream should be basic_istream<char>");
    static_assert(std::is_same_v<std::wistream, std::basic_istream<wchar_t>>,
        "wistream should be basic_istream<wchar_t>");
    TEST_PASS("Type aliases verified");
}

// Test output stream types
void test_ostream_types() {
    TEST_SECTION("Output Stream Types");

    test_type_exists<std::basic_ostream<char>>("basic_ostream<char>");
    test_type_exists<std::ostream>("ostream");
    test_type_exists<std::wostream>("wostream");

    static_assert(std::is_same_v<std::ostream, std::basic_ostream<char>>,
        "ostream should be basic_ostream<char>");
    static_assert(std::is_same_v<std::wostream, std::basic_ostream<wchar_t>>,
        "wostream should be basic_ostream<wchar_t>");
    TEST_PASS("Type aliases verified");
}

// Test iostream types
void test_iostream_types() {
    TEST_SECTION("Input/Output Stream Types");

    test_type_exists<std::basic_iostream<char>>("basic_iostream<char>");
    test_type_exists<std::iostream>("iostream");
    test_type_exists<std::wiostream>("wiostream");

    static_assert(std::is_same_v<std::iostream, std::basic_iostream<char>>,
        "iostream should be basic_iostream<char>");
    static_assert(std::is_same_v<std::wiostream, std::basic_iostream<wchar_t>>,
        "wiostream should be basic_iostream<wchar_t>");
    TEST_PASS("Type aliases verified");
}

// Test file stream types
void test_file_stream_types() {
    TEST_SECTION("File Stream Types");

    // Input file streams
    test_type_exists<std::basic_ifstream<char>>("basic_ifstream<char>");
    test_type_exists<std::ifstream>("ifstream");
    test_type_exists<std::wifstream>("wifstream");

    // Output file streams
    test_type_exists<std::basic_ofstream<char>>("basic_ofstream<char>");
    test_type_exists<std::ofstream>("ofstream");
    test_type_exists<std::wofstream>("wofstream");

    // Bidirectional file streams
    test_type_exists<std::basic_fstream<char>>("basic_fstream<char>");
    test_type_exists<std::fstream>("fstream");
    test_type_exists<std::wfstream>("wfstream");

    // Verify type aliases
    static_assert(std::is_same_v<std::ifstream, std::basic_ifstream<char>>);
    static_assert(std::is_same_v<std::ofstream, std::basic_ofstream<char>>);
    static_assert(std::is_same_v<std::fstream, std::basic_fstream<char>>);
    TEST_PASS("All file stream type aliases verified");
}

// Test string stream types
void test_string_stream_types() {
    TEST_SECTION("String Stream Types");

    // Input string streams
    test_type_exists<std::basic_istringstream<char>>("basic_istringstream<char>");
    test_type_exists<std::istringstream>("istringstream");
    test_type_exists<std::wistringstream>("wistringstream");

    // Output string streams
    test_type_exists<std::basic_ostringstream<char>>("basic_ostringstream<char>");
    test_type_exists<std::ostringstream>("ostringstream");
    test_type_exists<std::wostringstream>("wostringstream");

    // Bidirectional string streams
    test_type_exists<std::basic_stringstream<char>>("basic_stringstream<char>");
    test_type_exists<std::stringstream>("stringstream");
    test_type_exists<std::wstringstream>("wstringstream");

    // Verify type aliases
    static_assert(std::is_same_v<std::istringstream, std::basic_istringstream<char>>);
    static_assert(std::is_same_v<std::ostringstream, std::basic_ostringstream<char>>);
    static_assert(std::is_same_v<std::stringstream, std::basic_stringstream<char>>);
    TEST_PASS("All string stream type aliases verified");
}

// Test file buffer types
void test_filebuf_types() {
    TEST_SECTION("File Buffer Types");

    test_type_exists<std::basic_filebuf<char>>("basic_filebuf<char>");
    test_type_exists<std::filebuf>("filebuf");
    test_type_exists<std::wfilebuf>("wfilebuf");

    static_assert(std::is_same_v<std::filebuf, std::basic_filebuf<char>>);
    static_assert(std::is_same_v<std::wfilebuf, std::basic_filebuf<wchar_t>>);
    TEST_PASS("Type aliases verified");
}

// Test string buffer types
void test_stringbuf_types() {
    TEST_SECTION("String Buffer Types");

    test_type_exists<std::basic_stringbuf<char>>("basic_stringbuf<char>");
    test_type_exists<std::stringbuf>("stringbuf");
    test_type_exists<std::wstringbuf>("wstringbuf");

    static_assert(std::is_same_v<std::stringbuf, std::basic_stringbuf<char>>);
    static_assert(std::is_same_v<std::wstringbuf, std::basic_stringbuf<wchar_t>>);
    TEST_PASS("Type aliases verified");
}

// Test synchronized output types (C++20)
void test_syncbuf_types() {
    TEST_SECTION("Synchronized Buffer Types (C++20)");

    test_type_exists<std::basic_syncbuf<char>>("basic_syncbuf<char>");
    test_type_exists<std::syncbuf>("syncbuf");
    test_type_exists<std::wsyncbuf>("wsyncbuf");

    test_type_exists<std::basic_osyncstream<char>>("basic_osyncstream<char>");
    test_type_exists<std::osyncstream>("osyncstream");
    test_type_exists<std::wosyncstream>("wosyncstream");

    static_assert(std::is_same_v<std::syncbuf, std::basic_syncbuf<char>>);
    static_assert(std::is_same_v<std::osyncstream, std::basic_osyncstream<char>>);
    TEST_PASS("Type aliases verified");
}

// Test stream position types
void test_position_types() {
    TEST_SECTION("Stream Position Types");

    test_type_exists<std::fpos<std::char_traits<char>::state_type>>("fpos");
    test_type_exists<std::streampos>("streampos");
    test_type_exists<std::wstreampos>("wstreampos");
    test_type_exists<std::u8streampos>("u8streampos");
    test_type_exists<std::u16streampos>("u16streampos");
    test_type_exists<std::u32streampos>("u32streampos");

    TEST_PASS("All position types available");
}

// Test char_traits forward declaration
void test_char_traits() {
    TEST_SECTION("Character Traits");

    test_type_exists<std::char_traits<char>>("char_traits<char>");
    test_type_exists<std::char_traits<wchar_t>>("char_traits<wchar_t>");
    test_type_exists<std::char_traits<char8_t>>("char_traits<char8_t>");
    test_type_exists<std::char_traits<char16_t>>("char_traits<char16_t>");
    test_type_exists<std::char_traits<char32_t>>("char_traits<char32_t>");

    TEST_PASS("All char_traits specializations available");
}

// Test that forward declarations work for function parameters
void accept_istream_ptr(std::istream* is) {
    (void)is;
}

void accept_ostream_ref(std::ostream& os) {
    (void)os;
}

void test_forward_declaration_usage() {
    TEST_SECTION("Forward Declaration Usage");

    // Test that we can pass nullptr to functions expecting pointers
    accept_istream_ptr(nullptr);
    TEST_PASS("Function with istream* parameter compiles");

    // Test that we can declare arrays of pointers
    std::ostream* stream_array[10] = {};
    (void)stream_array;
    TEST_PASS("Array of stream pointers compiles");

    // Test that we can use these types in templates
    using StreamPtr = std::unique_ptr<std::iostream>;
    StreamPtr ptr;
    (void)ptr;
    TEST_PASS("Template with forward-declared type compiles");
}

// Test wide character streams
void test_wide_char_streams() {
    TEST_SECTION("Wide Character Streams");

    // Test all wide character variants
    test_type_exists<std::wstreambuf>("wstreambuf");
    test_type_exists<std::wios>("wios");
    test_type_exists<std::wistream>("wistream");
    test_type_exists<std::wostream>("wostream");
    test_type_exists<std::wiostream>("wiostream");
    test_type_exists<std::wifstream>("wifstream");
    test_type_exists<std::wofstream>("wofstream");
    test_type_exists<std::wfstream>("wfstream");
    test_type_exists<std::wistringstream>("wistringstream");
    test_type_exists<std::wostringstream>("wostringstream");
    test_type_exists<std::wstringstream>("wstringstream");
    test_type_exists<std::wfilebuf>("wfilebuf");
    test_type_exists<std::wstringbuf>("wstringbuf");
    test_type_exists<std::wsyncbuf>("wsyncbuf");
    test_type_exists<std::wosyncstream>("wosyncstream");

    TEST_PASS("All wide character stream types available");
}

int main() {
    std::cout << "Testing std_module.iosfwd\n";
    std::cout << "========================================\n";

    try {
        test_streambuf_types();
        test_basic_ios_types();
        test_istream_types();
        test_ostream_types();
        test_iostream_types();
        test_file_stream_types();
        test_string_stream_types();
        test_filebuf_types();
        test_stringbuf_types();
        test_syncbuf_types();
        test_position_types();
        test_char_traits();
        test_forward_declaration_usage();
        test_wide_char_streams();

        std::cout << "\n========================================\n";
        std::cout << "All tests passed! ✓\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\nTest failed with exception: " << e.what() << "\n";
        return 1;
    }
}
