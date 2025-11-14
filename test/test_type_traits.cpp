/**
 * @file test_type_traits.cpp
 * @brief Comprehensive tests for std_module.type_traits
 *
 * Tests type traits, type transformations, and compile-time type queries
 * exported by the type_traits module.
 */

import std_module.type_traits;

#include <iostream>
#include <cassert>

// Helper classes for testing
class Base {};
class Derived : public Base {};
class Abstract { virtual void f() = 0; };
class Polymorphic { virtual ~Polymorphic() {} };
class Final final {};
class Empty {};
enum Color { RED, GREEN, BLUE };
enum class StrongColor { RED, GREEN, BLUE };

// Test primary type categories
void test_primary_categories() {
    std::cout << "\n=== Testing primary type categories ===\n";

    // Void
    static_assert(std::is_void_v<void>);
    static_assert(!std::is_void_v<int>);
    std::cout << "  ✓ is_void works\n";

    // Null pointer
    static_assert(std::is_null_pointer_v<std::nullptr_t>);
    static_assert(!std::is_null_pointer_v<int*>);
    std::cout << "  ✓ is_null_pointer works\n";

    // Integral
    static_assert(std::is_integral_v<int>);
    static_assert(std::is_integral_v<bool>);
    static_assert(!std::is_integral_v<float>);
    std::cout << "  ✓ is_integral works\n";

    // Floating point
    static_assert(std::is_floating_point_v<float>);
    static_assert(std::is_floating_point_v<double>);
    static_assert(!std::is_floating_point_v<int>);
    std::cout << "  ✓ is_floating_point works\n";

    // Array
    static_assert(std::is_array_v<int[]>);
    static_assert(std::is_array_v<int[5]>);
    static_assert(!std::is_array_v<int*>);
    std::cout << "  ✓ is_array works\n";

    // Enum
    static_assert(std::is_enum_v<Color>);
    static_assert(std::is_enum_v<StrongColor>);
    static_assert(!std::is_enum_v<int>);
    std::cout << "  ✓ is_enum works\n";

    // Class
    static_assert(std::is_class_v<Base>);
    static_assert(!std::is_class_v<int>);
    std::cout << "  ✓ is_class works\n";

    // Pointer
    static_assert(std::is_pointer_v<int*>);
    static_assert(!std::is_pointer_v<int>);
    std::cout << "  ✓ is_pointer works\n";

    // References
    static_assert(std::is_lvalue_reference_v<int&>);
    static_assert(!std::is_lvalue_reference_v<int>);
    static_assert(std::is_rvalue_reference_v<int&&>);
    static_assert(!std::is_rvalue_reference_v<int&>);
    std::cout << "  ✓ is_lvalue_reference and is_rvalue_reference work\n";
}

// Test composite type categories
void test_composite_categories() {
    std::cout << "\n=== Testing composite type categories ===\n";

    static_assert(std::is_fundamental_v<int>);
    static_assert(std::is_fundamental_v<float>);
    static_assert(!std::is_fundamental_v<Base>);
    std::cout << "  ✓ is_fundamental works\n";

    static_assert(std::is_arithmetic_v<int>);
    static_assert(std::is_arithmetic_v<double>);
    static_assert(!std::is_arithmetic_v<void*>);
    std::cout << "  ✓ is_arithmetic works\n";

    static_assert(std::is_scalar_v<int>);
    static_assert(std::is_scalar_v<int*>);
    static_assert(!std::is_scalar_v<Base>);
    std::cout << "  ✓ is_scalar works\n";

    static_assert(std::is_object_v<int>);
    static_assert(std::is_object_v<Base>);
    static_assert(!std::is_object_v<void>);
    std::cout << "  ✓ is_object works\n";

    static_assert(std::is_compound_v<Base>);
    static_assert(std::is_compound_v<int*>);
    static_assert(!std::is_compound_v<int>);
    std::cout << "  ✓ is_compound works\n";

    static_assert(std::is_reference_v<int&>);
    static_assert(std::is_reference_v<int&&>);
    static_assert(!std::is_reference_v<int>);
    std::cout << "  ✓ is_reference works\n";
}

// Test type properties
void test_type_properties() {
    std::cout << "\n=== Testing type properties ===\n";

    static_assert(std::is_const_v<const int>);
    static_assert(!std::is_const_v<int>);
    std::cout << "  ✓ is_const works\n";

    static_assert(std::is_volatile_v<volatile int>);
    static_assert(!std::is_volatile_v<int>);
    std::cout << "  ✓ is_volatile works\n";

    static_assert(std::is_trivial_v<int>);
    static_assert(std::is_trivially_copyable_v<int>);
    std::cout << "  ✓ is_trivial and is_trivially_copyable work\n";

    static_assert(std::is_empty_v<Empty>);
    static_assert(!std::is_empty_v<int>);
    std::cout << "  ✓ is_empty works\n";

    static_assert(std::is_polymorphic_v<Polymorphic>);
    static_assert(!std::is_polymorphic_v<Base>);
    std::cout << "  ✓ is_polymorphic works\n";

    static_assert(std::is_abstract_v<Abstract>);
    static_assert(!std::is_abstract_v<Base>);
    std::cout << "  ✓ is_abstract works\n";

    static_assert(std::is_final_v<Final>);
    static_assert(!std::is_final_v<Base>);
    std::cout << "  ✓ is_final works\n";

    static_assert(std::is_signed_v<int>);
    static_assert(!std::is_signed_v<unsigned int>);
    std::cout << "  ✓ is_signed works\n";

    static_assert(std::is_unsigned_v<unsigned int>);
    static_assert(!std::is_unsigned_v<int>);
    std::cout << "  ✓ is_unsigned works\n";

    static_assert(std::is_bounded_array_v<int[5]>);
    static_assert(!std::is_bounded_array_v<int[]>);
    std::cout << "  ✓ is_bounded_array works\n";

    static_assert(std::is_unbounded_array_v<int[]>);
    static_assert(!std::is_unbounded_array_v<int[5]>);
    std::cout << "  ✓ is_unbounded_array works\n";
}

// Test constructibility traits
void test_constructibility() {
    std::cout << "\n=== Testing constructibility traits ===\n";

    static_assert(std::is_default_constructible_v<int>);
    static_assert(std::is_default_constructible_v<Base>);
    std::cout << "  ✓ is_default_constructible works\n";

    static_assert(std::is_copy_constructible_v<int>);
    static_assert(std::is_copy_constructible_v<Base>);
    std::cout << "  ✓ is_copy_constructible works\n";

    static_assert(std::is_move_constructible_v<int>);
    static_assert(std::is_move_constructible_v<Base>);
    std::cout << "  ✓ is_move_constructible works\n";

    static_assert(std::is_constructible_v<int, int>);
    static_assert(std::is_constructible_v<Base>);
    std::cout << "  ✓ is_constructible works\n";

    static_assert(std::is_trivially_default_constructible_v<int>);
    std::cout << "  ✓ is_trivially_default_constructible works\n";

    static_assert(std::is_nothrow_default_constructible_v<int>);
    std::cout << "  ✓ is_nothrow_default_constructible works\n";
}

// Test assignability traits
void test_assignability() {
    std::cout << "\n=== Testing assignability traits ===\n";

    static_assert(std::is_copy_assignable_v<int>);
    static_assert(std::is_copy_assignable_v<Base>);
    std::cout << "  ✓ is_copy_assignable works\n";

    static_assert(std::is_move_assignable_v<int>);
    static_assert(std::is_move_assignable_v<Base>);
    std::cout << "  ✓ is_move_assignable works\n";

    static_assert(std::is_assignable_v<int&, int>);
    std::cout << "  ✓ is_assignable works\n";

    static_assert(std::is_trivially_copy_assignable_v<int>);
    std::cout << "  ✓ is_trivially_copy_assignable works\n";

    static_assert(std::is_nothrow_copy_assignable_v<int>);
    std::cout << "  ✓ is_nothrow_copy_assignable works\n";
}

// Test destructibility traits
void test_destructibility() {
    std::cout << "\n=== Testing destructibility traits ===\n";

    static_assert(std::is_destructible_v<int>);
    static_assert(std::is_destructible_v<Base>);
    std::cout << "  ✓ is_destructible works\n";

    static_assert(std::is_trivially_destructible_v<int>);
    std::cout << "  ✓ is_trivially_destructible works\n";

    static_assert(std::is_nothrow_destructible_v<int>);
    std::cout << "  ✓ is_nothrow_destructible works\n";

    static_assert(std::has_virtual_destructor_v<Polymorphic>);
    static_assert(!std::has_virtual_destructor_v<Base>);
    std::cout << "  ✓ has_virtual_destructor works\n";
}

// Test property queries
void test_property_queries() {
    std::cout << "\n=== Testing property queries ===\n";

    static_assert(std::alignment_of_v<int> >= 1);
    std::cout << "  ✓ alignment_of works: " << std::alignment_of_v<int> << "\n";

    static_assert(std::rank_v<int[5][10]> == 2);
    static_assert(std::rank_v<int> == 0);
    std::cout << "  ✓ rank works\n";

    static_assert(std::extent_v<int[5]> == 5);
    static_assert(std::extent_v<int[5][10], 1> == 10);
    std::cout << "  ✓ extent works\n";
}

// Test type relationships
void test_type_relationships() {
    std::cout << "\n=== Testing type relationships ===\n";

    static_assert(std::is_same_v<int, int>);
    static_assert(!std::is_same_v<int, float>);
    std::cout << "  ✓ is_same works\n";

    static_assert(std::is_base_of_v<Base, Derived>);
    static_assert(!std::is_base_of_v<Derived, Base>);
    std::cout << "  ✓ is_base_of works\n";

    static_assert(std::is_convertible_v<int, float>);
    static_assert(std::is_convertible_v<Derived*, Base*>);
    std::cout << "  ✓ is_convertible works\n";

    static_assert(std::is_invocable_v<int(*)()>);
    std::cout << "  ✓ is_invocable works\n";
}

// Test type transformations - const/volatile
void test_cv_transformations() {
    std::cout << "\n=== Testing const/volatile transformations ===\n";

    static_assert(std::is_same_v<std::remove_cv_t<const volatile int>, int>);
    std::cout << "  ✓ remove_cv works\n";

    static_assert(std::is_same_v<std::remove_const_t<const int>, int>);
    std::cout << "  ✓ remove_const works\n";

    static_assert(std::is_same_v<std::remove_volatile_t<volatile int>, int>);
    std::cout << "  ✓ remove_volatile works\n";

    static_assert(std::is_same_v<std::add_const_t<int>, const int>);
    std::cout << "  ✓ add_const works\n";

    static_assert(std::is_same_v<std::add_volatile_t<int>, volatile int>);
    std::cout << "  ✓ add_volatile works\n";
}

// Test reference transformations
void test_reference_transformations() {
    std::cout << "\n=== Testing reference transformations ===\n";

    static_assert(std::is_same_v<std::remove_reference_t<int&>, int>);
    static_assert(std::is_same_v<std::remove_reference_t<int&&>, int>);
    std::cout << "  ✓ remove_reference works\n";

    static_assert(std::is_same_v<std::add_lvalue_reference_t<int>, int&>);
    std::cout << "  ✓ add_lvalue_reference works\n";

    static_assert(std::is_same_v<std::add_rvalue_reference_t<int>, int&&>);
    std::cout << "  ✓ add_rvalue_reference works\n";
}

// Test pointer transformations
void test_pointer_transformations() {
    std::cout << "\n=== Testing pointer transformations ===\n";

    static_assert(std::is_same_v<std::remove_pointer_t<int*>, int>);
    std::cout << "  ✓ remove_pointer works\n";

    static_assert(std::is_same_v<std::add_pointer_t<int>, int*>);
    std::cout << "  ✓ add_pointer works\n";
}

// Test sign modifiers
void test_sign_modifiers() {
    std::cout << "\n=== Testing sign modifiers ===\n";

    static_assert(std::is_same_v<std::make_signed_t<unsigned int>, int>);
    std::cout << "  ✓ make_signed works\n";

    static_assert(std::is_same_v<std::make_unsigned_t<int>, unsigned int>);
    std::cout << "  ✓ make_unsigned works\n";
}

// Test array transformations
void test_array_transformations() {
    std::cout << "\n=== Testing array transformations ===\n";

    static_assert(std::is_same_v<std::remove_extent_t<int[5]>, int>);
    static_assert(std::is_same_v<std::remove_extent_t<int[5][10]>, int[10]>);
    std::cout << "  ✓ remove_extent works\n";

    static_assert(std::is_same_v<std::remove_all_extents_t<int[5][10]>, int>);
    std::cout << "  ✓ remove_all_extents works\n";
}

// Test miscellaneous transformations
void test_misc_transformations() {
    std::cout << "\n=== Testing miscellaneous transformations ===\n";

    static_assert(std::is_same_v<std::decay_t<int&>, int>);
    static_assert(std::is_same_v<std::decay_t<int[]>, int*>);
    std::cout << "  ✓ decay works\n";

    static_assert(std::is_same_v<std::remove_cvref_t<const int&>, int>);
    std::cout << "  ✓ remove_cvref works\n";

    using EnabledType = std::enable_if_t<true, int>;
    static_assert(std::is_same_v<EnabledType, int>);
    std::cout << "  ✓ enable_if works\n";

    static_assert(std::is_same_v<std::conditional_t<true, int, float>, int>);
    static_assert(std::is_same_v<std::conditional_t<false, int, float>, float>);
    std::cout << "  ✓ conditional works\n";

    static_assert(std::is_same_v<std::common_type_t<int, float>, float>);
    std::cout << "  ✓ common_type works\n";

    static_assert(std::is_same_v<std::type_identity_t<int>, int>);
    std::cout << "  ✓ type_identity works\n";
}

// Test logical operators
void test_logical_operators() {
    std::cout << "\n=== Testing logical operator traits ===\n";

    static_assert(std::conjunction_v<std::true_type, std::true_type>);
    static_assert(!std::conjunction_v<std::true_type, std::false_type>);
    std::cout << "  ✓ conjunction works\n";

    static_assert(std::disjunction_v<std::true_type, std::false_type>);
    static_assert(!std::disjunction_v<std::false_type, std::false_type>);
    std::cout << "  ✓ disjunction works\n";

    static_assert(std::negation_v<std::false_type>);
    static_assert(!std::negation_v<std::true_type>);
    std::cout << "  ✓ negation works\n";
}

// Test helper constants
void test_helper_constants() {
    std::cout << "\n=== Testing helper constants ===\n";

    static_assert(std::true_type::value);
    static_assert(!std::false_type::value);
    std::cout << "  ✓ true_type and false_type work\n";

    using ten = std::integral_constant<int, 10>;
    static_assert(ten::value == 10);
    std::cout << "  ✓ integral_constant works\n";

    static_assert(std::bool_constant<true>::value);
    std::cout << "  ✓ bool_constant works\n";
}


int main() {
    std::cout << "Testing std_module.type_traits\n";
    std::cout << "========================================\n";

    try {
        test_primary_categories();
        test_composite_categories();
        test_type_properties();
        test_constructibility();
        test_assignability();
        test_destructibility();
        test_property_queries();
        test_type_relationships();
        test_cv_transformations();
        test_reference_transformations();
        test_pointer_transformations();
        test_sign_modifiers();
        test_array_transformations();
        test_misc_transformations();
        test_logical_operators();
        test_helper_constants();

        std::cout << "\n========================================\n";
        std::cout << "All type_traits tests passed! ✓\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
