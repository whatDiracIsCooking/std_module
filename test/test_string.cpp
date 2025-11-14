/**
 * @file test_string.cpp
 * @brief Comprehensive test for std_module.string (C++20)
 */

import std_module.string;

#include <iostream>  // For std::cout
#include <cassert>   // For assertions
#include <sstream>   // For std::istringstream (getline test)

void test_basic_construction() {
    std::cout << "Testing basic construction...\n";

    // Default constructor
    std::string s1;
    assert(s1.empty());
    std::cout << "  ✓ Default constructor: empty=" << s1.empty() << "\n";

    // From C string
    std::string s2("Hello");
    assert(s2 == "Hello" && s2.size() == 5);
    std::cout << "  ✓ C string constructor: \"" << s2 << "\"\n";

    // From C string with count
    std::string s3("Hello, World!", 5);
    assert(s3 == "Hello");
    std::cout << "  ✓ C string with count: \"" << s3 << "\"\n";

    // Fill constructor
    std::string s4(5, 'a');
    assert(s4 == "aaaaa" && s4.size() == 5);
    std::cout << "  ✓ Fill constructor: \"" << s4 << "\"\n";

    // Copy constructor
    std::string s5(s2);
    assert(s5 == "Hello");
    std::cout << "  ✓ Copy constructor: \"" << s5 << "\"\n";

    // Substring constructor
    std::string s6(s2, 1, 3);  // "ell"
    assert(s6 == "ell");
    std::cout << "  ✓ Substring constructor: \"" << s6 << "\"\n";
}

void test_string_literals() {
    std::cout << "\nTesting string literals...\n";

    using namespace std::literals::string_literals;

    auto s1 = "Hello"s;
    assert(s1 == "Hello");
    std::cout << "  ✓ String literal: \"" << s1 << "\"\n";

    auto s2 = "World\0Hidden"s;  // Can contain null characters
    assert(s2.size() == 12);
    std::cout << "  ✓ String literal with null: size=" << s2.size() << "\n";
}

void test_assignment() {
    std::cout << "\nTesting assignment operations...\n";

    std::string s1;

    // Copy assignment
    s1 = "Hello";
    assert(s1 == "Hello");
    std::cout << "  ✓ Copy assignment from C string: \"" << s1 << "\"\n";

    // Character assignment
    s1 = 'X';
    assert(s1 == "X" && s1.size() == 1);
    std::cout << "  ✓ Character assignment: \"" << s1 << "\"\n";

    // String assignment
    std::string s2("World");
    s1 = s2;
    assert(s1 == "World");
    std::cout << "  ✓ String assignment: \"" << s1 << "\"\n";

    // Move assignment
    std::string s3("Move");
    s1 = std::move(s3);
    assert(s1 == "Move");
    std::cout << "  ✓ Move assignment: \"" << s1 << "\"\n";
}

void test_element_access() {
    std::cout << "\nTesting element access...\n";

    std::string s = "Hello";

    // operator[]
    assert(s[0] == 'H' && s[4] == 'o');
    std::cout << "  ✓ operator[]: s[0]='" << s[0] << "', s[4]='" << s[4] << "'\n";

    // at()
    assert(s.at(1) == 'e');
    std::cout << "  ✓ at(): s.at(1)='" << s.at(1) << "'\n";

    // front() and back()
    assert(s.front() == 'H' && s.back() == 'o');
    std::cout << "  ✓ front/back: front='" << s.front() << "', back='" << s.back() << "'\n";

    // data() and c_str()
    const char* cstr = s.c_str();
    const char* data = s.data();
    assert(cstr[0] == 'H' && data[0] == 'H');
    std::cout << "  ✓ c_str/data: c_str()=\"" << cstr << "\"\n";

    // Bounds checking with at()
    try {
        char c = s.at(100);  // Out of bounds
        (void)c;
        assert(false);  // Should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "  ✓ at() bounds checking: exception thrown\n";
    }
}

void test_capacity() {
    std::cout << "\nTesting capacity operations...\n";

    std::string s;

    // empty()
    assert(s.empty());
    std::cout << "  ✓ empty(): " << s.empty() << "\n";

    // size() and length()
    s = "Hello";
    assert(s.size() == 5 && s.length() == 5);
    std::cout << "  ✓ size/length: " << s.size() << "\n";

    // max_size()
    std::cout << "  ✓ max_size: " << s.max_size() << "\n";

    // reserve()
    std::size_t old_cap = s.capacity();
    s.reserve(100);
    assert(s.capacity() >= 100);
    std::cout << "  ✓ reserve: capacity " << old_cap << " -> " << s.capacity() << "\n";

    // shrink_to_fit()
    s.shrink_to_fit();
    std::cout << "  ✓ shrink_to_fit: capacity=" << s.capacity() << "\n";

    // clear()
    s.clear();
    assert(s.empty() && s.size() == 0);
    std::cout << "  ✓ clear: empty=" << s.empty() << "\n";
}

void test_modifiers() {
    std::cout << "\nTesting modifier operations...\n";

    std::string s = "Hello";

    // push_back()
    s.push_back('!');
    assert(s == "Hello!");
    std::cout << "  ✓ push_back: \"" << s << "\"\n";

    // pop_back()
    s.pop_back();
    assert(s == "Hello");
    std::cout << "  ✓ pop_back: \"" << s << "\"\n";

    // append()
    s.append(" World");
    assert(s == "Hello World");
    std::cout << "  ✓ append: \"" << s << "\"\n";

    // operator+=
    s += "!";
    assert(s == "Hello World!");
    std::cout << "  ✓ operator+=: \"" << s << "\"\n";

    // insert()
    s = "Hello";
    s.insert(5, " World");
    assert(s == "Hello World");
    std::cout << "  ✓ insert: \"" << s << "\"\n";

    // erase()
    s.erase(5, 6);  // Remove " World"
    assert(s == "Hello");
    std::cout << "  ✓ erase: \"" << s << "\"\n";

    // replace()
    s.replace(0, 5, "Goodbye");
    assert(s == "Goodbye");
    std::cout << "  ✓ replace: \"" << s << "\"\n";

    // resize()
    s.resize(3);
    assert(s == "Goo");
    std::cout << "  ✓ resize (shrink): \"" << s << "\"\n";

    s.resize(6, '!');
    assert(s == "Goo!!!");
    std::cout << "  ✓ resize (grow): \"" << s << "\"\n";

    // swap()
    std::string s2 = "Swap";
    s.swap(s2);
    assert(s == "Swap" && s2 == "Goo!!!");
    std::cout << "  ✓ swap: \"" << s << "\" <-> \"" << s2 << "\"\n";
}

void test_string_operations() {
    std::cout << "\nTesting string operations...\n";

    std::string s = "Hello World";

    // substr()
    std::string sub = s.substr(0, 5);
    assert(sub == "Hello");
    std::cout << "  ✓ substr: \"" << sub << "\"\n";

    // compare()
    assert(s.compare("Hello World") == 0);
    assert(s.compare("Hello") > 0);
    assert(s.compare("Zebra") < 0);
    std::cout << "  ✓ compare: comparisons work correctly\n";

    // starts_with() (C++20)
    assert(s.starts_with("Hello"));
    assert(!s.starts_with("World"));
    std::cout << "  ✓ starts_with: \"Hello\"=" << s.starts_with("Hello") << "\n";

    // ends_with() (C++20)
    assert(s.ends_with("World"));
    assert(!s.ends_with("Hello"));
    std::cout << "  ✓ ends_with: \"World\"=" << s.ends_with("World") << "\n";

    // contains() (C++23, might not be available)
#if __cpp_lib_string_contains >= 202011L
    assert(s.contains("lo Wo"));
    assert(!s.contains("xyz"));
    std::cout << "  ✓ contains: \"lo Wo\"=" << s.contains("lo Wo") << "\n";
#else
    std::cout << "  - contains: not available (C++23)\n";
#endif

    // copy()
    char buffer[20];
    std::size_t copied = s.copy(buffer, 5, 0);
    buffer[copied] = '\0';
    assert(copied == 5 && std::string(buffer) == "Hello");
    std::cout << "  ✓ copy: \"" << buffer << "\"\n";
}

void test_search() {
    std::cout << "\nTesting search operations...\n";

    std::string s = "Hello World Hello";

    // find()
    std::size_t pos = s.find("World");
    assert(pos == 6);
    std::cout << "  ✓ find: \"World\" at position " << pos << "\n";

    // find() not found
    pos = s.find("xyz");
    assert(pos == std::string::npos);
    std::cout << "  ✓ find (not found): npos\n";

    // rfind()
    pos = s.rfind("Hello");
    assert(pos == 12);
    std::cout << "  ✓ rfind: \"Hello\" at position " << pos << "\n";

    // find_first_of()
    pos = s.find_first_of("Wo");
    assert(pos == 4);  // First 'o' in "Hello"
    std::cout << "  ✓ find_first_of: \"Wo\" at position " << pos << "\n";

    // find_last_of()
    pos = s.find_last_of("lo");
    assert(pos == 16);  // Last 'o'
    std::cout << "  ✓ find_last_of: \"lo\" at position " << pos << "\n";

    // find_first_not_of()
    pos = s.find_first_not_of("Helo ");
    assert(pos == 6);  // 'W'
    std::cout << "  ✓ find_first_not_of: \"Helo \" at position " << pos << "\n";

    // find_last_not_of()
    pos = s.find_last_not_of("Helo ");
    assert(pos == 10);  // 'r'
    std::cout << "  ✓ find_last_not_of: \"Helo \" at position " << pos << "\n";
}

void test_conversions() {
    std::cout << "\nTesting numeric conversions...\n";

    // to_string()
    std::string s1 = std::to_string(42);
    assert(s1 == "42");
    std::cout << "  ✓ to_string(int): \"" << s1 << "\"\n";

    std::string s2 = std::to_string(3.14159);
    std::cout << "  ✓ to_string(double): \"" << s2 << "\"\n";

    // stoi()
    int i = std::stoi("42");
    assert(i == 42);
    std::cout << "  ✓ stoi: " << i << "\n";

    // stol()
    long l = std::stol("123456");
    assert(l == 123456);
    std::cout << "  ✓ stol: " << l << "\n";

    // stoll()
    long long ll = std::stoll("9876543210");
    assert(ll == 9876543210LL);
    std::cout << "  ✓ stoll: " << ll << "\n";

    // stoul()
    unsigned long ul = std::stoul("42");
    assert(ul == 42UL);
    std::cout << "  ✓ stoul: " << ul << "\n";

    // stoull()
    unsigned long long ull = std::stoull("9876543210");
    assert(ull == 9876543210ULL);
    std::cout << "  ✓ stoull: " << ull << "\n";

    // stof()
    float f = std::stof("3.14");
    assert(f > 3.13f && f < 3.15f);
    std::cout << "  ✓ stof: " << f << "\n";

    // stod()
    double d = std::stod("3.14159");
    assert(d > 3.14 && d < 3.15);
    std::cout << "  ✓ stod: " << d << "\n";

    // stold()
    long double ld = std::stold("3.14159265358979");
    assert(ld > 3.14L && ld < 3.15L);
    std::cout << "  ✓ stold: " << ld << "\n";

    // Error handling
    try {
        int bad = std::stoi("not a number");
        (void)bad;
        assert(false);  // Should not reach
    } catch (const std::invalid_argument&) {
        std::cout << "  ✓ stoi error handling: invalid_argument thrown\n";
    }

    try {
        int overflow = std::stoi("999999999999999999999");
        (void)overflow;
        assert(false);  // Should not reach
    } catch (const std::out_of_range&) {
        std::cout << "  ✓ stoi error handling: out_of_range thrown\n";
    }
}

void test_comparison_operators() {
    std::cout << "\nTesting comparison operators...\n";

    std::string s1 = "apple";
    std::string s2 = "banana";
    std::string s3 = "apple";

    // operator==
    assert(s1 == s3 && !(s1 == s2));
    std::cout << "  ✓ operator==: \"apple\" == \"apple\"\n";

    // operator!=
    assert(s1 != s2 && !(s1 != s3));
    std::cout << "  ✓ operator!=: \"apple\" != \"banana\"\n";

    // operator<
    assert(s1 < s2);
    std::cout << "  ✓ operator<: \"apple\" < \"banana\"\n";

    // operator<=
    assert(s1 <= s2 && s1 <= s3);
    std::cout << "  ✓ operator<=: works correctly\n";

    // operator>
    assert(s2 > s1);
    std::cout << "  ✓ operator>: \"banana\" > \"apple\"\n";

    // operator>=
    assert(s2 >= s1 && s1 >= s3);
    std::cout << "  ✓ operator>=: works correctly\n";
}

void test_concatenation() {
    std::cout << "\nTesting string concatenation...\n";

    std::string s1 = "Hello";
    std::string s2 = "World";

    // operator+ (string + string)
    std::string s3 = s1 + " " + s2;
    assert(s3 == "Hello World");
    std::cout << "  ✓ operator+ (string + string): \"" << s3 << "\"\n";

    // operator+ (string + const char*)
    std::string s4 = s1 + " there";
    assert(s4 == "Hello there");
    std::cout << "  ✓ operator+ (string + const char*): \"" << s4 << "\"\n";

    // operator+ (const char* + string)
    std::string s5 = "Hi " + s2;
    assert(s5 == "Hi World");
    std::cout << "  ✓ operator+ (const char* + string): \"" << s5 << "\"\n";

    // operator+ (string + char)
    std::string s6 = s1 + '!';
    assert(s6 == "Hello!");
    std::cout << "  ✓ operator+ (string + char): \"" << s6 << "\"\n";
}

void test_getline() {
    std::cout << "\nTesting getline...\n";

    std::istringstream iss("Line1\nLine2\nLine3");
    std::string line;

    // getline with newline delimiter (default)
    std::getline(iss, line);
    assert(line == "Line1");
    std::cout << "  ✓ getline (default): \"" << line << "\"\n";

    std::getline(iss, line);
    assert(line == "Line2");
    std::cout << "  ✓ getline: \"" << line << "\"\n";

    // getline with custom delimiter
    std::istringstream iss2("a,b,c");
    std::getline(iss2, line, ',');
    assert(line == "a");
    std::cout << "  ✓ getline (custom delim): \"" << line << "\"\n";
}

void test_iterators() {
    std::cout << "\nTesting iterators...\n";

    std::string s = "Hello";

    // begin/end
    std::string result;
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += *it;
    }
    assert(result == "Hello");
    std::cout << "  ✓ begin/end: \"" << result << "\"\n";

    // Range-based for loop
    result.clear();
    for (char c : s) {
        result += c;
    }
    assert(result == "Hello");
    std::cout << "  ✓ range-based for: \"" << result << "\"\n";

    // rbegin/rend (reverse)
    result.clear();
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        result += *it;
    }
    assert(result == "olleH");
    std::cout << "  ✓ rbegin/rend: \"" << result << "\"\n";
}

void test_hash() {
    std::cout << "\nTesting hash support...\n";

    std::string s1 = "Hello";
    std::string s2 = "Hello";
    std::string s3 = "World";

    std::hash<std::string> hasher;
    std::size_t h1 = hasher(s1);
    std::size_t h2 = hasher(s2);
    std::size_t h3 = hasher(s3);

    assert(h1 == h2);
    assert(h1 != h3);  // Very likely different
    std::cout << "  ✓ hash: equal strings have equal hashes\n";
    std::cout << "  ✓ hash(\"Hello\")=" << h1 << "\n";
}

void test_wide_strings() {
    std::cout << "\nTesting wide string types...\n";

    std::wstring ws = L"Wide";
    assert(ws.size() == 4);
    std::wcout << L"  ✓ wstring: size=" << ws.size() << L"\n";

    std::u16string u16s = u"UTF-16";
    assert(u16s.size() == 6);
    std::cout << "  ✓ u16string: size=" << u16s.size() << "\n";

    std::u32string u32s = U"UTF-32";
    assert(u32s.size() == 6);
    std::cout << "  ✓ u32string: size=" << u32s.size() << "\n";

    std::u8string u8s = u8"UTF-8";
    assert(u8s.size() == 5);
    std::cout << "  ✓ u8string: size=" << u8s.size() << "\n";
}

int main() {
    std::cout << "=== Testing std_module.string ===\n\n";

    try {
        test_basic_construction();
        test_string_literals();
        test_assignment();
        test_element_access();
        test_capacity();
        test_modifiers();
        test_string_operations();
        test_search();
        test_conversions();
        test_comparison_operators();
        test_concatenation();
        test_getline();
        test_iterators();
        test_hash();
        test_wide_strings();

        std::cout << "\n=== All tests passed! ===\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n!!! Test failed with exception: " << e.what() << " !!!\n";
        return 1;
    }
}
