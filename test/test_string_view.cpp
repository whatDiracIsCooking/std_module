/**
 * @file test_string_view.cpp
 * @brief Comprehensive test for std_module.string_view (C++20)
 */

import std_module.string_view;

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

void test_basic_construction() {
    std::cout << "Testing basic construction...\n";

    // Default construction
    std::string_view sv1;
    assert(sv1.empty());
    assert(sv1.size() == 0);
    std::cout << "  ✓ Default construction: empty string_view\n";

    // From string literal
    std::string_view sv2 = "Hello, World!";
    assert(sv2.size() == 13);
    assert(sv2 == "Hello, World!");
    std::cout << "  ✓ From string literal: " << sv2 << "\n";

    // From std::string
    std::string str = "C++ Modules";
    std::string_view sv3 = str;
    assert(sv3.size() == 11);
    assert(sv3 == "C++ Modules");
    std::cout << "  ✓ From std::string: " << sv3 << "\n";

    // From pointer and length
    const char* cstr = "Test String";
    std::string_view sv4(cstr, 4);
    assert(sv4.size() == 4);
    assert(sv4 == "Test");
    std::cout << "  ✓ From pointer and length: " << sv4 << "\n";

    // Copy construction
    std::string_view sv5 = sv2;
    assert(sv5 == sv2);
    std::cout << "  ✓ Copy construction works\n";
}

void test_string_view_literals() {
    std::cout << "\nTesting string_view literals...\n";

    using namespace std::literals::string_view_literals;

    auto sv = "Hello"sv;
    assert(sv.size() == 5);
    assert(sv == "Hello");
    std::cout << "  ✓ sv literal: " << sv << "\n";

    // Literal with embedded null
    auto sv_with_null = "Hello\0World"sv;
    assert(sv_with_null.size() == 11);  // includes the null character
    std::cout << "  ✓ sv literal with embedded null (size: " << sv_with_null.size() << ")\n";
}

void test_element_access() {
    std::cout << "\nTesting element access...\n";

    std::string_view sv = "Hello, World!";

    // operator[]
    assert(sv[0] == 'H');
    assert(sv[7] == 'W');
    std::cout << "  ✓ operator[]: sv[0] = " << sv[0] << ", sv[7] = " << sv[7] << "\n";

    // at()
    assert(sv.at(0) == 'H');
    assert(sv.at(12) == '!');
    std::cout << "  ✓ at(): sv.at(0) = " << sv.at(0) << ", sv.at(12) = " << sv.at(12) << "\n";

    // front() and back()
    assert(sv.front() == 'H');
    assert(sv.back() == '!');
    std::cout << "  ✓ front() = " << sv.front() << ", back() = " << sv.back() << "\n";

    // data()
    assert(sv.data() != nullptr);
    std::cout << "  ✓ data() returns valid pointer\n";

    // Test at() exception
    try {
        sv.at(100);  // Out of bounds
        std::cout << "  ✗ at() should have thrown exception\n";
    } catch (const std::out_of_range& e) {
        std::cout << "  ✓ at() throws out_of_range for invalid index\n";
    }
}

void test_iterators() {
    std::cout << "\nTesting iterators...\n";

    std::string_view sv = "Hello";

    // Range-based for loop
    std::string result;
    for (char c : sv) {
        result += c;
    }
    assert(result == "Hello");
    std::cout << "  ✓ Range-based for loop: " << result << "\n";

    // begin() and end()
    assert(std::distance(sv.begin(), sv.end()) == 5);
    std::cout << "  ✓ begin()/end() distance: " << std::distance(sv.begin(), sv.end()) << "\n";

    // rbegin() and rend() for reverse iteration
    std::string reversed;
    for (auto it = sv.rbegin(); it != sv.rend(); ++it) {
        reversed += *it;
    }
    assert(reversed == "olleH");
    std::cout << "  ✓ Reverse iteration: " << reversed << "\n";

    // Algorithm usage
    assert(std::count(sv.begin(), sv.end(), 'l') == 2);
    std::cout << "  ✓ Algorithm (count 'l'): " << std::count(sv.begin(), sv.end(), 'l') << "\n";
}

void test_capacity() {
    std::cout << "\nTesting capacity...\n";

    std::string_view sv1 = "Hello";
    assert(sv1.size() == 5);
    assert(sv1.length() == 5);
    assert(!sv1.empty());
    std::cout << "  ✓ size() = " << sv1.size() << ", length() = " << sv1.length() << "\n";

    std::string_view sv2;
    assert(sv2.empty());
    assert(sv2.size() == 0);
    std::cout << "  ✓ empty() returns true for default-constructed string_view\n";

    // max_size()
    assert(sv1.max_size() > 0);
    std::cout << "  ✓ max_size() = " << sv1.max_size() << "\n";
}

void test_modifiers() {
    std::cout << "\nTesting modifiers...\n";

    std::string_view sv = "Hello, World!";

    // remove_prefix
    sv.remove_prefix(7);
    assert(sv == "World!");
    std::cout << "  ✓ remove_prefix(7): " << sv << "\n";

    // remove_suffix
    sv.remove_suffix(1);
    assert(sv == "World");
    std::cout << "  ✓ remove_suffix(1): " << sv << "\n";

    // swap
    std::string_view sv1 = "First";
    std::string_view sv2 = "Second";
    sv1.swap(sv2);
    assert(sv1 == "Second");
    assert(sv2 == "First");
    std::cout << "  ✓ swap: sv1 = " << sv1 << ", sv2 = " << sv2 << "\n";
}

void test_operations() {
    std::cout << "\nTesting operations...\n";

    std::string_view sv = "Hello, World!";

    // copy
    char buffer[10];
    size_t copied = sv.copy(buffer, 5, 0);
    assert(copied == 5);
    assert(std::string_view(buffer, 5) == "Hello");
    std::cout << "  ✓ copy: " << std::string_view(buffer, copied) << "\n";

    // substr
    auto sub = sv.substr(7, 5);
    assert(sub == "World");
    std::cout << "  ✓ substr(7, 5): " << sub << "\n";

    auto sub2 = sv.substr(7);
    assert(sub2 == "World!");
    std::cout << "  ✓ substr(7): " << sub2 << "\n";

    // compare
    assert(sv.compare("Hello, World!") == 0);
    assert(sv.compare("Hello") > 0);
    assert(sv.compare("Zebra") < 0);
    std::cout << "  ✓ compare works correctly\n";

    // starts_with (C++20)
    assert(sv.starts_with("Hello"));
    assert(!sv.starts_with("World"));
    assert(sv.starts_with('H'));
    std::cout << "  ✓ starts_with: \"Hello\" = true, \"World\" = false\n";

    // ends_with (C++20)
    assert(sv.ends_with("World!"));
    assert(!sv.ends_with("Hello"));
    assert(sv.ends_with('!'));
    std::cout << "  ✓ ends_with: \"World!\" = true, \"Hello\" = false\n";

    // contains (C++23 if available, skip if not)
    #if __cpp_lib_string_contains >= 202011L
    assert(sv.contains("World"));
    assert(!sv.contains("xyz"));
    assert(sv.contains(','));
    std::cout << "  ✓ contains: \"World\" = true, \"xyz\" = false\n";
    #else
    std::cout << "  ~ contains: not available (C++23 feature)\n";
    #endif
}

void test_search() {
    std::cout << "\nTesting search operations...\n";

    std::string_view sv = "Hello, World! Hello!";

    // find
    assert(sv.find("World") == 7);
    assert(sv.find("xyz") == std::string_view::npos);
    assert(sv.find('o') == 4);
    std::cout << "  ✓ find: \"World\" at " << sv.find("World") << ", 'o' at " << sv.find('o') << "\n";

    // rfind
    assert(sv.rfind("Hello") == 14);
    assert(sv.rfind('o') == 18);
    std::cout << "  ✓ rfind: \"Hello\" at " << sv.rfind("Hello") << ", 'o' at " << sv.rfind('o') << "\n";

    // find_first_of
    assert(sv.find_first_of("aeiou") == 1);  // 'e' in "Hello"
    std::cout << "  ✓ find_first_of: vowel at " << sv.find_first_of("aeiou") << "\n";

    // find_last_of
    assert(sv.find_last_of("aeiou") == 18);  // 'o' in last "Hello"
    std::cout << "  ✓ find_last_of: vowel at " << sv.find_last_of("aeiou") << "\n";

    // find_first_not_of
    assert(sv.find_first_not_of("He") == 2);  // 'l' in "Hello"
    std::cout << "  ✓ find_first_not_of: at " << sv.find_first_not_of("He") << "\n";

    // find_last_not_of
    assert(sv.find_last_not_of("!") == 18);  // 'o' before '!'
    std::cout << "  ✓ find_last_not_of: at " << sv.find_last_not_of("!") << "\n";
}

void test_comparison_operators() {
    std::cout << "\nTesting comparison operators...\n";

    std::string_view sv1 = "apple";
    std::string_view sv2 = "banana";
    std::string_view sv3 = "apple";

    assert(sv1 == sv3);
    assert(sv1 != sv2);
    assert(sv1 < sv2);
    assert(sv2 > sv1);
    assert(sv1 <= sv3);
    assert(sv1 >= sv3);
    std::cout << "  ✓ All comparison operators work correctly\n";

    // Compare with string literal
    assert(sv1 == "apple");
    assert("apple" == sv1);
    std::cout << "  ✓ Comparison with string literals works\n";
}

void test_wide_string_view() {
    std::cout << "\nTesting wide string_view...\n";

    std::wstring_view wsv = L"Wide String";
    assert(wsv.size() == 11);
    assert(wsv == L"Wide String");
    std::wcout << L"  ✓ wstring_view: " << wsv << L"\n";

    using namespace std::literals::string_view_literals;
    auto wsv2 = L"Wide Literal"sv;
    assert(wsv2.size() == 12);
    std::wcout << L"  ✓ wstring_view literal: " << wsv2 << L"\n";
}

void test_different_char_types() {
    std::cout << "\nTesting different character types...\n";

    // u8string_view (UTF-8)
    std::u8string_view u8sv = u8"UTF-8 String";
    assert(u8sv.size() == 12);
    std::cout << "  ✓ u8string_view size: " << u8sv.size() << "\n";

    // u16string_view (UTF-16)
    std::u16string_view u16sv = u"UTF-16 String";
    assert(u16sv.size() == 13);
    std::cout << "  ✓ u16string_view size: " << u16sv.size() << "\n";

    // u32string_view (UTF-32)
    std::u32string_view u32sv = U"UTF-32 String";
    assert(u32sv.size() == 13);
    std::cout << "  ✓ u32string_view size: " << u32sv.size() << "\n";
}

void test_hash() {
    std::cout << "\nTesting hash support...\n";

    std::string_view sv1 = "test";
    std::string_view sv2 = "test";
    std::string_view sv3 = "different";

    std::hash<std::string_view> hasher;
    assert(hasher(sv1) == hasher(sv2));
    assert(hasher(sv1) != hasher(sv3));
    std::cout << "  ✓ Hash for \"test\": " << hasher(sv1) << "\n";
    std::cout << "  ✓ Hash for \"different\": " << hasher(sv3) << "\n";
    std::cout << "  ✓ Equal string_views have equal hashes\n";
}

void test_conversion_to_string() {
    std::cout << "\nTesting conversion to std::string...\n";

    std::string_view sv = "Convert Me";
    std::string str(sv);
    assert(str == "Convert Me");
    std::cout << "  ✓ Explicit conversion to std::string: " << str << "\n";

    // Using string constructor with iterators
    std::string str2(sv.begin(), sv.end());
    assert(str2 == "Convert Me");
    std::cout << "  ✓ Construction from iterators: " << str2 << "\n";
}

void test_npos() {
    std::cout << "\nTesting npos constant...\n";

    std::string_view sv = "test";
    auto pos = sv.find("notfound");
    assert(pos == std::string_view::npos);
    std::cout << "  ✓ npos returned for not found: " << pos << " == " << std::string_view::npos << "\n";
}

int main()
{
    std::cout << "=== C++20 std::string_view Comprehensive Tests ===\n\n";

    try {
        test_basic_construction();
        test_string_view_literals();
        test_element_access();
        test_iterators();
        test_capacity();
        test_modifiers();
        test_operations();
        test_search();
        test_comparison_operators();
        test_wide_string_view();
        test_different_char_types();
        test_hash();
        test_conversion_to_string();
        test_npos();

        std::cout << "\n=== All tests passed! ===\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n!!! Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
