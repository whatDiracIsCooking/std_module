/**
 * @file test_string_view.cpp
 * @brief Tests for std_module.string_view
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.string_view;
import std_module.test_framework;
#include <cstddef>  // for size_t

int main() {
    test::test_header("std_module.string_view");

    test::section("Testing symbol accessibility");

    // Basic construction
    std::string_view sv1;
    std::string_view sv2 = "hello";
    test::assert_true(sv2.size() > 0, "string_view construction");

    // String view literals
    using namespace std::literals::string_view_literals;
    auto lit = "test"sv;
    test::assert_true(lit.length() > 0, "string_view literals");

    // Element access
    test::assert_true(sv2[0] == 'h', "operator[]");
    test::assert_true(sv2.at(0) == 'h', "at");
    test::assert_true(sv2.front() == 'h', "front");
    test::assert_true(sv2.back() == 'o', "back");
    test::assert_true(sv2.data() != nullptr, "data");

    // Capacity
    test::assert_true(sv2.size() == 5, "size");
    test::assert_true(sv2.length() == 5, "length");
    test::assert_false(sv2.empty(), "empty");

    // Modifiers
    std::string_view sv3 = "hello world";
    sv3.remove_prefix(6);
    test::assert_equal(sv3.compare("world"), 0, "remove_prefix");
    sv3.remove_suffix(2);
    test::assert_true(sv3.size() < 5, "remove_suffix");

    // Operations
    std::string_view sv4 = "hello world";
    test::assert_equal(sv4.substr(0, 5).compare("hello"), 0, "substr");
    test::assert_true(sv4.starts_with("hello"), "starts_with");
    test::assert_true(sv4.ends_with("world"), "ends_with");

    // Search operations
    test::assert_true(sv4.find("world") != std::string_view::npos, "find");
    test::assert_true(sv4.rfind("o") != std::string_view::npos, "rfind");

    // Wide string_view
    std::wstring_view wsv = L"wide";
    test::assert_true(wsv.size() > 0, "wstring_view");

    // Hash support
    std::hash<std::string_view> hasher;
    test::assert_true(hasher("test") == hasher("test"), "hash");

    // npos constant
    test::assert_true(std::string_view::npos == static_cast<size_t>(-1), "npos");

    test::test_footer();
    return 0;
}
