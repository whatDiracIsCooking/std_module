/**
 * @file test_string.cpp
 * @brief Comprehensive test for std_module.string (C++20)
 */

import std_module.string;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <sstream>   // For testing getline

void test_basic_construction() {
    std::cout << "Testing basic string construction...\n";

    // Default constructor
    std::string s1;
    assert(s1.empty());
    std::cout << "  ✓ Default constructor: empty string\n";

    // C-string constructor
    std::string s2("Hello");
    assert(s2 == "Hello");
    std::cout << "  ✓ C-string constructor: " << s2 << "\n";

    // Copy constructor
    std::string s3(s2);
    assert(s3 == "Hello");
    std::cout << "  ✓ Copy constructor: " << s3 << "\n";

    // Fill constructor
    std::string s4(5, 'A');
    assert(s4 == "AAAAA");
    std::cout << "  ✓ Fill constructor: " << s4 << "\n";

    // Substring constructor
    std::string s5("Hello World", 5);
    assert(s5 == "Hello");
    std::cout << "  ✓ Substring constructor: " << s5 << "\n";
}

void test_string_literals() {
    std::cout << "\nTesting string literals...\n";

    using namespace std::literals::string_literals;

    auto s1 = "Hello"s;
    assert(s1 == "Hello");
    std::cout << "  ✓ String literal operator\"\"s: " << s1 << "\n";

    auto s2 = "World"s;
    auto s3 = s1 + " " + s2;
    assert(s3 == "Hello World");
    std::cout << "  ✓ Concatenation with literals: " << s3 << "\n";
}

void test_assignment_and_concatenation() {
    std::cout << "\nTesting assignment and concatenation...\n";

    std::string s1 = "Hello";
    std::string s2 = " World";
    std::string s3 = s1 + s2;
    assert(s3 == "Hello World");
    std::cout << "  ✓ String concatenation: " << s3 << "\n";

    s1 += s2;
    assert(s1 == "Hello World");
    std::cout << "  ✓ Compound assignment (+=): " << s1 << "\n";

    s1 = "Reset";
    assert(s1 == "Reset");
    std::cout << "  ✓ Assignment operator: " << s1 << "\n";
}

void test_comparison() {
    std::cout << "\nTesting string comparison...\n";

    std::string s1 = "apple";
    std::string s2 = "banana";
    std::string s3 = "apple";

    assert(s1 == s3);
    std::cout << "  ✓ Equality comparison (==): " << s1 << " == " << s3 << "\n";

    assert(s1 != s2);
    std::cout << "  ✓ Inequality comparison (!=): " << s1 << " != " << s2 << "\n";

    assert(s1 < s2);
    std::cout << "  ✓ Less-than comparison (<): " << s1 << " < " << s2 << "\n";

    assert(s2 > s1);
    std::cout << "  ✓ Greater-than comparison (>): " << s2 << " > " << s1 << "\n";
}

void test_access_and_iteration() {
    std::cout << "\nTesting string access and iteration...\n";

    std::string s = "Hello";

    assert(s[0] == 'H');
    assert(s[4] == 'o');
    std::cout << "  ✓ Subscript operator: s[0] = " << s[0] << ", s[4] = " << s[4] << "\n";

    assert(s.at(2) == 'l');
    std::cout << "  ✓ at() method: s.at(2) = " << s.at(2) << "\n";

    assert(s.front() == 'H');
    assert(s.back() == 'o');
    std::cout << "  ✓ front() and back(): '" << s.front() << "' and '" << s.back() << "'\n";

    // Test iteration
    std::string result;
    for (char c : s) {
        result += c;
    }
    assert(result == s);
    std::cout << "  ✓ Range-based for loop: " << result << "\n";
}

void test_capacity_and_size() {
    std::cout << "\nTesting capacity and size operations...\n";

    std::string s = "Hello";

    assert(s.size() == 5);
    assert(s.length() == 5);
    std::cout << "  ✓ size() and length(): " << s.size() << "\n";

    assert(!s.empty());
    std::cout << "  ✓ empty() on non-empty string: false\n";

    std::string empty;
    assert(empty.empty());
    std::cout << "  ✓ empty() on empty string: true\n";

    s.clear();
    assert(s.empty());
    std::cout << "  ✓ clear(): string is now empty\n";
}

void test_modifiers() {
    std::cout << "\nTesting string modifiers...\n";

    std::string s = "Hello";

    s.push_back('!');
    assert(s == "Hello!");
    std::cout << "  ✓ push_back(): " << s << "\n";

    s.pop_back();
    assert(s == "Hello");
    std::cout << "  ✓ pop_back(): " << s << "\n";

    s.append(" World");
    assert(s == "Hello World");
    std::cout << "  ✓ append(): " << s << "\n";

    s.insert(5, ",");
    assert(s == "Hello, World");
    std::cout << "  ✓ insert(): " << s << "\n";

    s.erase(5, 1);  // Remove the comma
    assert(s == "Hello World");
    std::cout << "  ✓ erase(): " << s << "\n";

    s.replace(6, 5, "C++");
    assert(s == "Hello C++");
    std::cout << "  ✓ replace(): " << s << "\n";
}

void test_string_operations() {
    std::cout << "\nTesting string operations...\n";

    std::string s = "Hello World Hello";

    // substr
    std::string sub = s.substr(0, 5);
    assert(sub == "Hello");
    std::cout << "  ✓ substr(0, 5): " << sub << "\n";

    // find
    size_t pos = s.find("World");
    assert(pos == 6);
    std::cout << "  ✓ find(\"World\"): position " << pos << "\n";

    // rfind (find from the end)
    pos = s.rfind("Hello");
    assert(pos == 12);
    std::cout << "  ✓ rfind(\"Hello\"): position " << pos << "\n";

    // find_first_of
    pos = s.find_first_of("aeiou");
    assert(pos == 1);  // 'e' in "Hello"
    std::cout << "  ✓ find_first_of(\"aeiou\"): position " << pos << "\n";

    // find_last_of
    pos = s.find_last_of("aeiou");
    assert(pos == 16);  // 'o' at end of second "Hello"
    std::cout << "  ✓ find_last_of(\"aeiou\"): position " << pos << "\n";
}

void test_c_string_interface() {
    std::cout << "\nTesting C-string interface...\n";

    std::string s = "Hello";

    const char* cstr = s.c_str();
    assert(std::string(cstr) == "Hello");
    std::cout << "  ✓ c_str(): " << cstr << "\n";

    const char* data = s.data();
    assert(std::string(data) == "Hello");
    std::cout << "  ✓ data(): " << data << "\n";
}

void test_numeric_conversions() {
    std::cout << "\nTesting numeric conversions...\n";

    // String to numeric
    assert(std::stoi("42") == 42);
    std::cout << "  ✓ stoi(\"42\"): " << std::stoi("42") << "\n";

    assert(std::stol("1234567890") == 1234567890L);
    std::cout << "  ✓ stol(\"1234567890\"): " << std::stol("1234567890") << "\n";

    assert(std::stoll("9876543210") == 9876543210LL);
    std::cout << "  ✓ stoll(\"9876543210\"): " << std::stoll("9876543210") << "\n";

    assert(std::stoul("12345") == 12345UL);
    std::cout << "  ✓ stoul(\"12345\"): " << std::stoul("12345") << "\n";

    assert(std::stoull("98765") == 98765ULL);
    std::cout << "  ✓ stoull(\"98765\"): " << std::stoull("98765") << "\n";

    assert(std::stof("3.14") > 3.13f && std::stof("3.14") < 3.15f);
    std::cout << "  ✓ stof(\"3.14\"): " << std::stof("3.14") << "\n";

    assert(std::stod("2.71828") > 2.71 && std::stod("2.71828") < 2.72);
    std::cout << "  ✓ stod(\"2.71828\"): " << std::stod("2.71828") << "\n";

    assert(std::stold("1.414") > 1.41L && std::stold("1.414") < 1.42L);
    std::cout << "  ✓ stold(\"1.414\"): " << std::stold("1.414") << "\n";

    // Numeric to string
    assert(std::to_string(42) == "42");
    std::cout << "  ✓ to_string(42): " << std::to_string(42) << "\n";

    assert(std::to_string(3.14) == "3.140000");
    std::cout << "  ✓ to_string(3.14): " << std::to_string(3.14) << "\n";

    assert(std::to_string(-100) == "-100");
    std::cout << "  ✓ to_string(-100): " << std::to_string(-100) << "\n";
}

void test_getline() {
    std::cout << "\nTesting getline...\n";

    std::istringstream iss("Line1\nLine2\nLine3");
    std::string line;

    std::getline(iss, line);
    assert(line == "Line1");
    std::cout << "  ✓ getline() first line: " << line << "\n";

    std::getline(iss, line);
    assert(line == "Line2");
    std::cout << "  ✓ getline() second line: " << line << "\n";

    // Test getline with custom delimiter
    std::istringstream iss2("A,B,C");
    std::getline(iss2, line, ',');
    assert(line == "A");
    std::cout << "  ✓ getline() with delimiter ',': " << line << "\n";
}

void test_erase_erase_if() {
    std::cout << "\nTesting C++20 erase/erase_if...\n";

    // Test erase
    std::string s1 = "Hello World Hello";
    auto count = std::erase(s1, 'l');
    assert(s1 == "Heo Word Heo");
    std::cout << "  ✓ erase(s, 'l'): " << s1 << " (removed " << count << " characters)\n";

    // Test erase_if
    std::string s2 = "Hello123World456";
    auto count2 = std::erase_if(s2, [](char c) { return c >= '0' && c <= '9'; });
    assert(s2 == "HelloWorld");
    std::cout << "  ✓ erase_if(s, is_digit): " << s2 << " (removed " << count2 << " digits)\n";
}

void test_wide_strings() {
    std::cout << "\nTesting wide string types...\n";

    std::wstring ws = L"Wide String";
    assert(ws.length() == 11);
    std::wcout << L"  ✓ wstring: " << ws << L"\n";

    std::u16string u16s = u"UTF-16 String";
    assert(u16s.length() == 13);
    std::cout << "  ✓ u16string length: " << u16s.length() << "\n";

    std::u32string u32s = U"UTF-32 String";
    assert(u32s.length() == 13);
    std::cout << "  ✓ u32string length: " << u32s.length() << "\n";

    std::u8string u8s = u8"UTF-8 String";
    assert(u8s.length() == 12);
    std::cout << "  ✓ u8string length: " << u8s.length() << "\n";
}

void test_exception_handling() {
    std::cout << "\nTesting exception handling...\n";

    // Test at() throws on out of range
    try {
        std::string s = "Hello";
        char c = s.at(100);  // Should throw
        (void)c;
        assert(false);  // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "  ✓ at() throws out_of_range: " << e.what() << "\n";
    }

    // Test stoi throws on invalid input
    try {
        int n = std::stoi("not a number");
        (void)n;
        assert(false);  // Should not reach here
    } catch (const std::invalid_argument& e) {
        std::cout << "  ✓ stoi() throws invalid_argument: " << e.what() << "\n";
    }

    // Test stoi throws on out of range
    try {
        int n = std::stoi("999999999999999999999999");
        (void)n;
        assert(false);  // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "  ✓ stoi() throws out_of_range: " << e.what() << "\n";
    }
}

void test_hash_support() {
    std::cout << "\nTesting hash support...\n";

    std::string s1 = "Hello";
    std::string s2 = "Hello";
    std::string s3 = "World";

    std::hash<std::string> hasher;

    assert(hasher(s1) == hasher(s2));
    std::cout << "  ✓ hash(\"Hello\") == hash(\"Hello\"): " << hasher(s1) << "\n";

    assert(hasher(s1) != hasher(s3));
    std::cout << "  ✓ hash(\"Hello\") != hash(\"World\")\n";
}

int main() {
    std::cout << "=== Testing std_module.string ===\n\n";

    test_basic_construction();
    test_string_literals();
    test_assignment_and_concatenation();
    test_comparison();
    test_access_and_iteration();
    test_capacity_and_size();
    test_modifiers();
    test_string_operations();
    test_c_string_interface();
    test_numeric_conversions();
    test_getline();
    test_erase_erase_if();
    test_wide_strings();
    test_exception_handling();
    test_hash_support();

    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}
