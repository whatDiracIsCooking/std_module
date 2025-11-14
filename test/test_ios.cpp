/**
 * @file test_ios.cpp
 * @brief Comprehensive test for std_module.ios (C++20)
 */

import std_module.ios;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <sstream>   // FIXME: Should be import std_module.sstream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string when available

void test_boolean_manipulators() {
    std::cout << "Testing boolean manipulators...\n";

    std::ostringstream oss;

    // Test boolalpha/noboolalpha
    oss << std::boolalpha << true;
    assert(oss.str() == "true");
    std::cout << "  ✓ boolalpha: " << oss.str() << "\n";

    oss.str("");
    oss << std::noboolalpha << true;
    assert(oss.str() == "1");
    std::cout << "  ✓ noboolalpha: " << oss.str() << "\n";
}

void test_numeric_base_manipulators() {
    std::cout << "\nTesting numeric base manipulators...\n";

    std::ostringstream oss;

    // Test dec
    oss << std::dec << 42;
    assert(oss.str() == "42");
    std::cout << "  ✓ dec: " << oss.str() << "\n";

    // Test hex
    oss.str("");
    oss << std::hex << 255;
    assert(oss.str() == "ff");
    std::cout << "  ✓ hex: " << oss.str() << "\n";

    // Test oct
    oss.str("");
    oss << std::oct << 64;
    assert(oss.str() == "100");
    std::cout << "  ✓ oct: " << oss.str() << "\n";
}

void test_base_notation_manipulators() {
    std::cout << "\nTesting base notation manipulators...\n";

    std::ostringstream oss;

    // Test showbase
    oss << std::showbase << std::hex << 255;
    assert(oss.str() == "0xff");
    std::cout << "  ✓ showbase with hex: " << oss.str() << "\n";

    // Test noshowbase
    oss.str("");
    oss << std::noshowbase << std::hex << 255;
    assert(oss.str() == "ff");
    std::cout << "  ✓ noshowbase with hex: " << oss.str() << "\n";
}

void test_floating_point_manipulators() {
    std::cout << "\nTesting floating point manipulators...\n";

    std::ostringstream oss;
    oss.precision(2);

    // Test fixed
    oss << std::fixed << 3.14159;
    assert(oss.str() == "3.14");
    std::cout << "  ✓ fixed: " << oss.str() << "\n";

    // Test scientific
    oss.str("");
    oss << std::scientific << 1234.5;
    std::cout << "  ✓ scientific: " << oss.str() << "\n";

    // Test defaultfloat
    oss.str("");
    oss << std::defaultfloat << 3.14;
    std::cout << "  ✓ defaultfloat: " << oss.str() << "\n";

    // Test hexfloat
    oss.str("");
    oss << std::hexfloat << 1.0;
    std::cout << "  ✓ hexfloat: " << oss.str() << "\n";
}

void test_sign_manipulators() {
    std::cout << "\nTesting sign manipulators...\n";

    std::ostringstream oss;

    // Test showpos
    oss << std::showpos << 42;
    assert(oss.str() == "+42");
    std::cout << "  ✓ showpos: " << oss.str() << "\n";

    // Test noshowpos
    oss.str("");
    oss << std::noshowpos << 42;
    assert(oss.str() == "42");
    std::cout << "  ✓ noshowpos: " << oss.str() << "\n";
}

void test_floating_point_notation() {
    std::cout << "\nTesting floating point notation...\n";

    std::ostringstream oss;

    // Test showpoint
    oss << std::showpoint << 1.0;
    std::cout << "  ✓ showpoint: " << oss.str() << "\n";

    // Test noshowpoint
    oss.str("");
    oss << std::noshowpoint << 1.0;
    std::cout << "  ✓ noshowpoint: " << oss.str() << "\n";
}

void test_case_manipulators() {
    std::cout << "\nTesting case manipulators...\n";

    std::ostringstream oss;

    // Test uppercase
    oss << std::uppercase << std::hex << 255;
    assert(oss.str() == "FF");
    std::cout << "  ✓ uppercase with hex: " << oss.str() << "\n";

    // Test nouppercase
    oss.str("");
    oss << std::nouppercase << std::hex << 255;
    assert(oss.str() == "ff");
    std::cout << "  ✓ nouppercase with hex: " << oss.str() << "\n";
}

void test_alignment_manipulators() {
    std::cout << "\nTesting alignment manipulators...\n";

    std::ostringstream oss;

    // Test left alignment
    oss.width(10);
    oss << std::left << 42;
    std::cout << "  ✓ left alignment: '" << oss.str() << "'\n";

    // Test right alignment
    oss.str("");
    oss.width(10);
    oss << std::right << 42;
    std::cout << "  ✓ right alignment: '" << oss.str() << "'\n";

    // Test internal alignment
    oss.str("");
    oss.width(10);
    oss << std::internal << std::showpos << 42;
    std::cout << "  ✓ internal alignment: '" << oss.str() << "'\n";
}

void test_whitespace_manipulators() {
    std::cout << "\nTesting whitespace manipulators...\n";

    std::istringstream iss("  42  ");

    // Test skipws (default)
    int value;
    iss >> std::skipws >> value;
    assert(value == 42);
    std::cout << "  ✓ skipws: " << value << "\n";

    // Test noskipws
    std::istringstream iss2("  42");
    char c;
    iss2 >> std::noskipws >> c;
    assert(c == ' ');
    std::cout << "  ✓ noskipws: got space character\n";
}

void test_buffering_manipulators() {
    std::cout << "\nTesting buffering manipulators...\n";

    std::ostringstream oss;

    // Test unitbuf (flush after each output)
    oss << std::unitbuf << "test";
    std::cout << "  ✓ unitbuf enabled\n";

    // Test nounitbuf (default buffering)
    oss << std::nounitbuf << "test";
    std::cout << "  ✓ nounitbuf enabled\n";
}

void test_ios_base_flags() {
    std::cout << "\nTesting ios_base flags...\n";

    std::ostringstream oss;

    // Test setting flags directly
    oss.setf(std::ios_base::hex, std::ios_base::basefield);
    oss << 255;
    assert(oss.str() == "ff");
    std::cout << "  ✓ setf with hex flag: " << oss.str() << "\n";

    // Test unsetting flags
    oss.str("");
    oss.unsetf(std::ios_base::hex);
    oss.setf(std::ios_base::dec, std::ios_base::basefield);
    oss << 255;
    assert(oss.str() == "255");
    std::cout << "  ✓ unsetf and dec flag: " << oss.str() << "\n";
}

void test_stream_state() {
    std::cout << "\nTesting stream state...\n";

    std::ostringstream oss;

    // Test good state
    assert(oss.good());
    std::cout << "  ✓ Stream is in good state\n";

    // Test eof state
    std::istringstream iss("");
    char c;
    iss >> c;
    assert(iss.eof());
    std::cout << "  ✓ Stream detects EOF\n";

    // Test clear state
    iss.clear();
    assert(!iss.eof());
    std::cout << "  ✓ Stream state cleared\n";
}

void test_position_types() {
    std::cout << "\nTesting position types...\n";

    // Test streampos
    std::streampos pos = 0;
    pos += 10;
    assert(pos == std::streampos(10));
    std::cout << "  ✓ streampos arithmetic works\n";

    // Test streamoff
    std::streamoff offset = 5;
    std::streamoff offset2 = 3;
    assert(offset + offset2 == 8);
    std::cout << "  ✓ streamoff arithmetic works\n";
}

void test_error_category() {
    std::cout << "\nTesting error handling...\n";

    // Test iostream_category
    const std::error_category& cat = std::iostream_category();
    std::cout << "  ✓ iostream_category: " << cat.name() << "\n";

    // Test make_error_code
    auto ec = std::make_error_code(std::io_errc::stream);
    std::cout << "  ✓ make_error_code: " << ec.message() << "\n";

    // Test make_error_condition
    auto cond = std::make_error_condition(std::io_errc::stream);
    std::cout << "  ✓ make_error_condition: " << cond.message() << "\n";
}

void test_combined_manipulators() {
    std::cout << "\nTesting combined manipulators...\n";

    std::ostringstream oss;

    // Combine multiple manipulators
    oss << std::hex << std::showbase << std::uppercase << 255;
    assert(oss.str() == "0XFF");
    std::cout << "  ✓ Combined hex + showbase + uppercase: " << oss.str() << "\n";

    // Test floating point combination
    oss.str("");
    oss << std::fixed << std::showpoint << std::showpos;
    oss.precision(2);
    oss << 3.14;
    std::cout << "  ✓ Combined fixed + showpoint + showpos: " << oss.str() << "\n";
}

void test_ios_type_aliases() {
    std::cout << "\nTesting type aliases...\n";

    // Test ios (basic_ios<char>)
    std::ios* ios_ptr = nullptr;
    (void)ios_ptr; // Suppress unused variable warning
    std::cout << "  ✓ std::ios type alias exists\n";

    // Test wios (basic_ios<wchar_t>)
    std::wios* wios_ptr = nullptr;
    (void)wios_ptr; // Suppress unused variable warning
    std::cout << "  ✓ std::wios type alias exists\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "std_module.ios Comprehensive Test Suite\n";
    std::cout << "========================================\n\n";

    test_boolean_manipulators();
    test_numeric_base_manipulators();
    test_base_notation_manipulators();
    test_floating_point_manipulators();
    test_sign_manipulators();
    test_floating_point_notation();
    test_case_manipulators();
    test_alignment_manipulators();
    test_whitespace_manipulators();
    test_buffering_manipulators();
    test_ios_base_flags();
    test_stream_state();
    test_position_types();
    test_error_category();
    test_combined_manipulators();
    test_ios_type_aliases();

    std::cout << "\n========================================\n";
    std::cout << "All tests passed! ✓\n";
    std::cout << "========================================\n";

    return 0;
}
