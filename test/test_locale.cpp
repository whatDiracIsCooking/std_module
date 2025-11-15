/**
 * @file test_locale.cpp
 * @brief Tests for std_module.locale
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that locale functionality is accessible through the module.
 */

import std_module.locale;
import std_module.test_framework;

#include <string>

int main() {
    test::test_header("std_module.locale");

    test::section("Testing symbol accessibility");

    // Test locale construction
    std::locale default_loc;
    std::locale classic = std::locale::classic();
    test::success("locale construction (default, classic)");

    // Test global locale
    std::locale global = std::locale::global(std::locale::classic());
    test::success("global locale");

    // Test character classification functions
    std::locale loc = std::locale::classic();
    test::assert_true(std::isspace(' ', loc), "isspace");
    test::assert_true(std::isalpha('a', loc), "isalpha");
    test::assert_true(std::isdigit('5', loc), "isdigit");
    test::assert_true(std::isupper('A', loc), "isupper");
    test::assert_true(std::islower('a', loc), "islower");
    test::assert_true(std::isalnum('a', loc), "isalnum");
    test::assert_true(std::ispunct('.', loc), "ispunct");
    test::assert_true(std::isprint('a', loc), "isprint");
    test::assert_true(std::isgraph('a', loc), "isgraph");

    // Test character conversion
    test::assert_true(std::toupper('a', loc) == 'A', "toupper");
    test::assert_true(std::tolower('A', loc) == 'a', "tolower");

    // Test facet access
    test::assert_true(std::has_facet<std::ctype<char>>(loc), "has_facet<ctype>");
    const std::ctype<char>& ct = std::use_facet<std::ctype<char>>(loc);
    test::assert_true(ct.is(std::ctype_base::alpha, 'a'), "use_facet<ctype>");

    test::assert_true(std::has_facet<std::numpunct<char>>(loc), "has_facet<numpunct>");
    const std::numpunct<char>& np = std::use_facet<std::numpunct<char>>(loc);
    char dp = np.decimal_point();
    test::assert_true(dp != 0, "use_facet<numpunct>");

    test::assert_true(std::has_facet<std::collate<char>>(loc), "has_facet<collate>");
    const std::collate<char>& col = std::use_facet<std::collate<char>>(loc);
    std::string s1 = "a", s2 = "b";
    int cmp = col.compare(s1.data(), s1.data() + 1, s2.data(), s2.data() + 1);
    test::assert_true(cmp < 0, "use_facet<collate>");

    // Test wide character support
    test::assert_true(std::isalpha(L'a', loc), "wide char isalpha");
    test::assert_true(std::toupper(L'a', loc) == L'A', "wide char toupper");

    test::test_footer();
    return 0;
}
