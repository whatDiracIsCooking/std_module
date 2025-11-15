/**
 * @file test_variant.cpp
 * @brief Tests for std_module.variant
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.variant;
import std_module.test_framework;

int main() {
    test::test_header("std_module.variant");

    test::section("Testing symbol accessibility");

    // Basic variant
    std::variant<int, double> v1 = 42;
    test::assert_true(std::holds_alternative<int>(v1), "holds_alternative");
    test::assert_equal(std::get<int>(v1), 42, "get<Type>");
    test::assert_equal(std::get<0>(v1), 42, "get<N>");

    // index()
    test::assert_equal(v1.index(), 0ull, "index");

    // Assignment
    v1 = 3.14;
    test::assert_true(std::holds_alternative<double>(v1), "assignment");

    // emplace
    v1.emplace<int>(99);
    test::assert_equal(std::get<int>(v1), 99, "emplace");

    // get_if
    int* ptr = std::get_if<int>(&v1);
    test::assert_true(ptr != nullptr, "get_if");

    // visit (simplified - just test it's callable)
    auto visitor = [](auto&& arg) -> int {
        return 1;
    };
    int result = std::visit(visitor, v1);
    test::assert_equal(result, 1, "visit");

    // monostate
    std::variant<std::monostate, int> v2;
    test::assert_true(std::holds_alternative<std::monostate>(v2), "monostate");

    // bad_variant_access exception
    bool caught = false;
    try {
        [[maybe_unused]] double d = std::get<double>(v1);
    } catch (const std::bad_variant_access&) {
        caught = true;
    }
    test::assert_true(caught, "bad_variant_access");

    // variant_size and variant_alternative
    using V = std::variant<int, double, char>;
    static_assert(std::variant_size_v<V> == 3);
    test::success("variant_size and variant_alternative");

    // swap
    std::variant<int, double> v3 = 10;
    std::variant<int, double> v4 = 20.0;
    v3.swap(v4);
    test::assert_true(std::holds_alternative<double>(v3), "swap");

    // valueless_by_exception
    test::assert_false(v1.valueless_by_exception(), "valueless_by_exception");

    test::test_footer();
    return 0;
}
