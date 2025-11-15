/**
 * @file test_any.cpp
 * @brief Tests for std_module.any
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.any;
import std_module.test_framework;

int main() {
    test::test_header("std_module.any");

    test::section("Testing basic construction and type checking");

    // Sanity check each operation is callable (not testing correctness)
    std::any a1;
    test::assert_false(a1.has_value(), "default construction");

    std::any a2 = 42;
    test::assert_true(a2.has_value(), "value construction");

    std::any a3 = a2;
    test::assert_true(a3.has_value(), "copy construction");

    test::section("Testing any_cast");

    int val = std::any_cast<int>(a3);
    test::assert_true(val == 42, "any_cast value");

    int& ref = std::any_cast<int&>(a3);
    ref = 100;
    test::assert_true(std::any_cast<int>(a3) == 100, "any_cast reference");

    int* ptr = std::any_cast<int>(&a3);
    test::assert_true(ptr != nullptr, "any_cast pointer (valid)");

    double* bad_ptr = std::any_cast<double>(&a3);
    test::assert_true(bad_ptr == nullptr, "any_cast pointer (invalid)");

    test::section("Testing bad_any_cast exception");

    try {
        std::any_cast<double>(a3);
        test::failure("bad_any_cast should throw");
    } catch (const std::bad_any_cast&) {
        test::success("bad_any_cast exception");
    }

    test::section("Testing operations");

    a1.emplace<int>(42);
    test::assert_true(a1.has_value(), "emplace");

    a1.reset();
    test::assert_false(a1.has_value(), "reset");

    auto a5 = std::make_any<int>(42);
    test::assert_true(a5.has_value(), "make_any");

    std::any a6 = 10;
    std::any a7 = 20;
    a6.swap(a7);
    test::assert_true(std::any_cast<int>(a6) == 20, "swap");

    test::test_footer();
    return 0;
}
