/**
 * @file test_concepts.cpp
 * @brief Tests for std_module.concepts
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.concepts;
import std_module.test_framework;

#include <string>
#include <vector>

// Test type hierarchy for derived_from concept
class Base {};
class Derived : public Base {};

// Concept-constrained function template
template<std::integral T>
T add_integral(T a, T b) {
    return a + b;
}

int main() {
    test::test_header("std_module.concepts");

    test::section("Testing core language concepts");

    // Test that core concepts are accessible (compile-time check)
    static_assert(std::same_as<int, int>);
    static_assert(!std::same_as<int, float>);
    test::success("same_as concept");

    test::section("Testing arithmetic concepts");

    static_assert(std::integral<int>);
    static_assert(std::signed_integral<int>);
    static_assert(std::unsigned_integral<unsigned int>);
    static_assert(std::floating_point<double>);
    test::success("integral/signed_integral/unsigned_integral/floating_point");

    test::section("Testing object concepts");

    static_assert(std::derived_from<Derived, Base>);
    static_assert(std::convertible_to<int, double>);
    static_assert(std::constructible_from<std::string, const char*>);
    static_assert(std::default_initializable<int>);
    static_assert(std::move_constructible<std::string>);
    static_assert(std::copy_constructible<std::string>);
    static_assert(std::destructible<std::string>);
    static_assert(std::assignable_from<int&, int>);
    test::success("derived_from/convertible_to/constructible/destructible/assignable");

    test::section("Testing swappable concepts");

    static_assert(std::swappable<int>);
    static_assert(std::swappable_with<int&, int&>);
    test::success("swappable concepts");

    test::section("Testing comparison concepts");

    static_assert(std::equality_comparable<int>);
    static_assert(std::equality_comparable_with<int, long>);
    static_assert(std::totally_ordered<int>);
    static_assert(std::totally_ordered_with<int, long>);
    test::success("equality_comparable/totally_ordered");

    test::section("Testing regular/semiregular concepts");

    static_assert(std::movable<std::string>);
    static_assert(std::copyable<std::string>);
    static_assert(std::semiregular<int>);
    static_assert(std::regular<std::string>);
    test::success("movable/copyable/semiregular/regular");

    test::section("Testing callable concepts");

    auto lambda = [](int x) { return x > 0; };
    auto binary_lambda = [](int x, int y) { return x < y; };

    static_assert(std::invocable<decltype(lambda), int>);
    static_assert(std::regular_invocable<decltype(lambda), int>);
    static_assert(std::predicate<decltype(lambda), int>);
    static_assert(std::relation<decltype(binary_lambda), int, int>);
    static_assert(std::equivalence_relation<decltype(binary_lambda), int, int>);
    static_assert(std::strict_weak_order<decltype(binary_lambda), int, int>);
    test::success("invocable/regular_invocable/predicate/relation");

    test::section("Testing concept-constrained templates");

    // Test that concept-constrained templates are callable
    auto result = add_integral(5, 3);
    test::assert_true(result > 0, "concept-constrained template");

    test::test_footer();
    return 0;
}
