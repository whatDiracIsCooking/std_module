/**
 * @file test_locale.cpp
 * @brief Tests for std_module.locale
 *
 * Comprehensive test suite covering all locale functionality including:
 * - Locale construction and naming
 * - Character classification functions
 * - Character conversion functions
 * - Facet access and usage
 * - Locale comparison and operations
 */

import std_module.locale;

#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

// ==============================================================================
// Test: Basic Locale Construction and Naming
// ==============================================================================

void test_locale_construction() {
    std::cout << "Testing locale construction and naming...\n";

    // Default locale
    std::locale default_loc;
    std::cout << "  ✓ Default locale created\n";

    // Classic "C" locale
    std::locale classic = std::locale::classic();
    std::cout << "  ✓ Classic locale: " << classic.name() << "\n";

    // Global locale
    std::locale global = std::locale::global(std::locale::classic());
    std::cout << "  ✓ Global locale set\n";

    // Named locale (C)
    try {
        std::locale c_locale("C");
        std::cout << "  ✓ Named locale \"C\": " << c_locale.name() << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "  ! Could not create C locale: " << e.what() << "\n";
    }

    std::cout << "\n";
}

// ==============================================================================
// Test: Character Classification Functions
// ==============================================================================

void test_character_classification() {
    std::cout << "Testing character classification functions...\n";

    std::locale loc = std::locale::classic();

    // Test isspace
    assert(std::isspace(' ', loc));
    assert(std::isspace('\t', loc));
    assert(std::isspace('\n', loc));
    assert(!std::isspace('a', loc));
    std::cout << "  ✓ isspace works correctly\n";

    // Test isblank
    assert(std::isblank(' ', loc));
    assert(std::isblank('\t', loc));
    assert(!std::isblank('\n', loc));
    assert(!std::isblank('a', loc));
    std::cout << "  ✓ isblank works correctly\n";

    // Test iscntrl
    assert(std::iscntrl('\n', loc));
    assert(std::iscntrl('\t', loc));
    assert(!std::iscntrl('a', loc));
    std::cout << "  ✓ iscntrl works correctly\n";

    // Test isupper/islower
    assert(std::isupper('A', loc));
    assert(!std::isupper('a', loc));
    assert(std::islower('a', loc));
    assert(!std::islower('A', loc));
    std::cout << "  ✓ isupper/islower work correctly\n";

    // Test isalpha
    assert(std::isalpha('a', loc));
    assert(std::isalpha('Z', loc));
    assert(!std::isalpha('1', loc));
    assert(!std::isalpha(' ', loc));
    std::cout << "  ✓ isalpha works correctly\n";

    // Test isdigit
    assert(std::isdigit('0', loc));
    assert(std::isdigit('9', loc));
    assert(!std::isdigit('a', loc));
    std::cout << "  ✓ isdigit works correctly\n";

    // Test isxdigit
    assert(std::isxdigit('0', loc));
    assert(std::isxdigit('9', loc));
    assert(std::isxdigit('a', loc));
    assert(std::isxdigit('F', loc));
    assert(!std::isxdigit('g', loc));
    std::cout << "  ✓ isxdigit works correctly\n";

    // Test isalnum
    assert(std::isalnum('a', loc));
    assert(std::isalnum('Z', loc));
    assert(std::isalnum('0', loc));
    assert(!std::isalnum(' ', loc));
    std::cout << "  ✓ isalnum works correctly\n";

    // Test ispunct
    assert(std::ispunct('.', loc));
    assert(std::ispunct('!', loc));
    assert(std::ispunct(',', loc));
    assert(!std::ispunct('a', loc));
    assert(!std::ispunct('1', loc));
    std::cout << "  ✓ ispunct works correctly\n";

    // Test isprint
    assert(std::isprint('a', loc));
    assert(std::isprint(' ', loc));
    assert(!std::isprint('\n', loc));
    std::cout << "  ✓ isprint works correctly\n";

    // Test isgraph
    assert(std::isgraph('a', loc));
    assert(std::isgraph('!', loc));
    assert(!std::isgraph(' ', loc));
    assert(!std::isgraph('\n', loc));
    std::cout << "  ✓ isgraph works correctly\n";

    std::cout << "\n";
}

// ==============================================================================
// Test: Character Conversion Functions
// ==============================================================================

void test_character_conversion() {
    std::cout << "Testing character conversion functions...\n";

    std::locale loc = std::locale::classic();

    // Test toupper
    assert(std::toupper('a', loc) == 'A');
    assert(std::toupper('z', loc) == 'Z');
    assert(std::toupper('A', loc) == 'A');
    assert(std::toupper('1', loc) == '1');
    std::cout << "  ✓ toupper works correctly\n";

    // Test tolower
    assert(std::tolower('A', loc) == 'a');
    assert(std::tolower('Z', loc) == 'z');
    assert(std::tolower('a', loc) == 'a');
    assert(std::tolower('1', loc) == '1');
    std::cout << "  ✓ tolower works correctly\n";

    std::cout << "\n";
}

// ==============================================================================
// Test: Facet Access
// ==============================================================================

void test_facet_access() {
    std::cout << "Testing facet access...\n";

    std::locale loc = std::locale::classic();

    // Test has_facet for ctype
    assert(std::has_facet<std::ctype<char>>(loc));
    std::cout << "  ✓ has_facet<ctype<char>> returns true\n";

    // Test use_facet for ctype
    const std::ctype<char>& ct = std::use_facet<std::ctype<char>>(loc);
    assert(ct.is(std::ctype_base::alpha, 'a'));
    assert(ct.is(std::ctype_base::digit, '5'));
    assert(ct.is(std::ctype_base::space, ' '));
    std::cout << "  ✓ use_facet<ctype<char>> works correctly\n";

    // Test has_facet for numpunct
    assert(std::has_facet<std::numpunct<char>>(loc));
    std::cout << "  ✓ has_facet<numpunct<char>> returns true\n";

    // Test use_facet for numpunct
    const std::numpunct<char>& np = std::use_facet<std::numpunct<char>>(loc);
    char decimal_point = np.decimal_point();
    char thousands_sep = np.thousands_sep();
    std::cout << "  ✓ use_facet<numpunct<char>> decimal_point: '" << decimal_point << "'\n";
    std::cout << "  ✓ use_facet<numpunct<char>> thousands_sep: '" << thousands_sep << "'\n";

    // Test has_facet for collate
    assert(std::has_facet<std::collate<char>>(loc));
    std::cout << "  ✓ has_facet<collate<char>> returns true\n";

    std::cout << "\n";
}

// ==============================================================================
// Test: Locale Categories
// ==============================================================================

void test_locale_categories() {
    std::cout << "Testing locale categories...\n";

    std::locale c_loc = std::locale::classic();

    // Create locale with specific category (numeric)
    try {
        std::locale numeric_loc(c_loc, "C", std::locale::numeric);
        std::cout << "  ✓ Created locale with numeric category\n";
    } catch (const std::runtime_error& e) {
        std::cout << "  ! Could not create numeric locale: " << e.what() << "\n";
    }

    // Create locale with specific category (ctype)
    try {
        std::locale ctype_loc(c_loc, "C", std::locale::ctype);
        std::cout << "  ✓ Created locale with ctype category\n";
    } catch (const std::runtime_error& e) {
        std::cout << "  ! Could not create ctype locale: " << e.what() << "\n";
    }

    // Test locale::all category
    try {
        std::locale all_loc(c_loc, "C", std::locale::all);
        std::cout << "  ✓ Created locale with all categories\n";
    } catch (const std::runtime_error& e) {
        std::cout << "  ! Could not create all-category locale: " << e.what() << "\n";
    }

    std::cout << "\n";
}

// ==============================================================================
// Test: Locale Comparison
// ==============================================================================

void test_locale_comparison() {
    std::cout << "Testing locale comparison...\n";

    std::locale loc1 = std::locale::classic();
    std::locale loc2 = std::locale::classic();

    // Test equality
    assert(loc1 == loc2);
    std::cout << "  ✓ Locale equality comparison works\n";

    // Test inequality
    assert(!(loc1 != loc2));
    std::cout << "  ✓ Locale inequality comparison works\n";

    std::cout << "\n";
}

// ==============================================================================
// Test: Ctype Facet Character Classification
// ==============================================================================

void test_ctype_facet() {
    std::cout << "Testing ctype facet character classification...\n";

    std::locale loc = std::locale::classic();
    const std::ctype<char>& ct = std::use_facet<std::ctype<char>>(loc);

    // Test is() with individual character
    assert(ct.is(std::ctype_base::alpha, 'a'));
    assert(ct.is(std::ctype_base::digit, '5'));
    assert(ct.is(std::ctype_base::space, ' '));
    assert(ct.is(std::ctype_base::upper, 'A'));
    assert(ct.is(std::ctype_base::lower, 'a'));
    assert(ct.is(std::ctype_base::punct, '.'));
    std::cout << "  ✓ ctype::is() works for individual characters\n";

    // Test toupper and tolower via facet
    assert(ct.toupper('a') == 'A');
    assert(ct.tolower('A') == 'a');
    std::cout << "  ✓ ctype::toupper() and tolower() work\n";

    // Test scan_is
    const char* str = "hello123";
    const char* result = ct.scan_is(std::ctype_base::digit, str, str + 8);
    assert(result != str + 8);  // Found a digit
    assert(*result == '1');
    std::cout << "  ✓ ctype::scan_is() works\n";

    // Test scan_not
    const char* result2 = ct.scan_not(std::ctype_base::alpha, str, str + 8);
    assert(result2 != str + 8);  // Found a non-alpha
    assert(*result2 == '1');
    std::cout << "  ✓ ctype::scan_not() works\n";

    std::cout << "\n";
}

// ==============================================================================
// Test: Collate Facet
// ==============================================================================

void test_collate_facet() {
    std::cout << "Testing collate facet...\n";

    std::locale loc = std::locale::classic();
    const std::collate<char>& col = std::use_facet<std::collate<char>>(loc);

    // Test compare
    std::string s1 = "apple";
    std::string s2 = "banana";
    int cmp = col.compare(s1.data(), s1.data() + s1.size(),
                          s2.data(), s2.data() + s2.size());
    assert(cmp < 0);  // "apple" < "banana"
    std::cout << "  ✓ collate::compare() works\n";

    // Test transform
    std::string trans1 = col.transform(s1.data(), s1.data() + s1.size());
    std::string trans2 = col.transform(s2.data(), s2.data() + s2.size());
    assert(trans1 < trans2);  // Transformed "apple" < transformed "banana"
    std::cout << "  ✓ collate::transform() works\n";

    // Test hash
    long hash_val = col.hash(s1.data(), s1.data() + s1.size());
    std::cout << "  ✓ collate::hash() returns: " << hash_val << "\n";

    std::cout << "\n";
}

// ==============================================================================
// Test: Wide Character Support
// ==============================================================================

void test_wide_character_support() {
    std::cout << "Testing wide character support...\n";

    std::locale loc = std::locale::classic();

    // Test wide character classification
    assert(std::isspace(L' ', loc));
    assert(std::isalpha(L'a', loc));
    assert(std::isdigit(L'5', loc));
    std::cout << "  ✓ Wide character classification works\n";

    // Test wide character conversion
    assert(std::toupper(L'a', loc) == L'A');
    assert(std::tolower(L'Z', loc) == L'z');
    std::cout << "  ✓ Wide character conversion works\n";

    // Test has_facet for wide ctype
    assert(std::has_facet<std::ctype<wchar_t>>(loc));
    std::cout << "  ✓ has_facet<ctype<wchar_t>> returns true\n";

    // Test use_facet for wide ctype
    const std::ctype<wchar_t>& wct = std::use_facet<std::ctype<wchar_t>>(loc);
    assert(wct.is(std::ctype_base::alpha, L'a'));
    std::cout << "  ✓ use_facet<ctype<wchar_t>> works\n";

    std::cout << "\n";
}

// ==============================================================================
// Main Test Runner
// ==============================================================================

int main() {
    std::cout << "=================================================\n";
    std::cout << "Running std_module.locale tests\n";
    std::cout << "=================================================\n\n";

    try {
        test_locale_construction();
        test_character_classification();
        test_character_conversion();
        test_facet_access();
        test_locale_categories();
        test_locale_comparison();
        test_ctype_facet();
        test_collate_facet();
        test_wide_character_support();

        std::cout << "=================================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "=================================================\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n=================================================\n";
        std::cerr << "Test failed with exception: " << e.what() << "\n";
        std::cerr << "=================================================\n";
        return 1;
    }
}
