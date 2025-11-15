/**
 * @file test_type_traits.cpp
 * @brief Tests for std_module.type_traits
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.type_traits;
import std_module.test_framework;

int main() {
    test::test_header("std_module.type_traits");

    test::section("Testing symbol accessibility");

    // Primary type categories
    static_assert(std::is_void_v<void>);
    static_assert(std::is_integral_v<int>);
    static_assert(std::is_floating_point_v<double>);
    static_assert(std::is_pointer_v<int*>);
    test::success("primary type categories");

    // Composite type categories
    static_assert(std::is_fundamental_v<int>);
    static_assert(std::is_arithmetic_v<double>);
    static_assert(std::is_reference_v<int&>);
    test::success("composite type categories");

    // Type properties
    static_assert(std::is_const_v<const int>);
    static_assert(std::is_volatile_v<volatile int>);
    static_assert(std::is_signed_v<int>);
    static_assert(std::is_unsigned_v<unsigned int>);
    test::success("type properties");

    // Constructibility
    static_assert(std::is_default_constructible_v<int>);
    static_assert(std::is_copy_constructible_v<int>);
    static_assert(std::is_move_constructible_v<int>);
    test::success("constructibility traits");

    // Assignability
    static_assert(std::is_copy_assignable_v<int>);
    static_assert(std::is_move_assignable_v<int>);
    test::success("assignability traits");

    // Destructibility
    static_assert(std::is_destructible_v<int>);
    test::success("destructibility traits");

    // Type relationships
    static_assert(std::is_same_v<int, int>);
    static_assert(!std::is_same_v<int, float>);
    test::success("is_same");

    // Type transformations
    static_assert(std::is_same_v<std::remove_const_t<const int>, int>);
    static_assert(std::is_same_v<std::remove_reference_t<int&>, int>);
    static_assert(std::is_same_v<std::add_pointer_t<int>, int*>);
    test::success("type transformations");

    // Const/volatile transformations
    static_assert(std::is_same_v<std::remove_cv_t<const volatile int>, int>);
    static_assert(std::is_same_v<std::add_const_t<int>, const int>);
    test::success("cv transformations");

    // Reference transformations
    static_assert(std::is_same_v<std::add_lvalue_reference_t<int>, int&>);
    static_assert(std::is_same_v<std::add_rvalue_reference_t<int>, int&&>);
    test::success("reference transformations");

    // Sign modifiers
    static_assert(std::is_same_v<std::make_signed_t<unsigned int>, int>);
    static_assert(std::is_same_v<std::make_unsigned_t<int>, unsigned int>);
    test::success("sign modifiers");

    // Other transformations
    static_assert(std::is_same_v<std::decay_t<int&>, int>);
    static_assert(std::is_same_v<std::remove_cvref_t<const int&>, int>);
    static_assert(std::is_same_v<std::conditional_t<true, int, float>, int>);
    test::success("misc transformations");

    // Logical operators
    static_assert(std::conjunction_v<std::true_type, std::true_type>);
    static_assert(std::disjunction_v<std::true_type, std::false_type>);
    static_assert(std::negation_v<std::false_type>);
    test::success("logical operators");

    // Helper constants
    static_assert(std::true_type::value);
    static_assert(!std::false_type::value);
    static_assert(std::integral_constant<int, 42>::value == 42);
    test::success("helper constants");

    test::test_footer();
    return 0;
}
