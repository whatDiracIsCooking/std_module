/**
 * @file test_concepts.cpp
 * @brief Tests for std_module.concepts
 *
 * Tests the C++20 concepts library.
 */

import std_module.concepts;
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

// Test same_as concept
void test_same_as() {
    std::cout << "Testing same_as concept...\n";

    static_assert(std::same_as<int, int>);
    static_assert(!std::same_as<int, float>);
    static_assert(std::same_as<const int, const int>);
    static_assert(!std::same_as<int, const int>);

    std::cout << "  ✓ same_as works correctly\n";
}

// Test integral concepts
void test_integral_concepts() {
    std::cout << "\nTesting integral concepts...\n";

    static_assert(std::integral<int>);
    static_assert(std::integral<char>);
    static_assert(std::integral<bool>);
    static_assert(!std::integral<float>);
    static_assert(!std::integral<double>);

    static_assert(std::signed_integral<int>);
    static_assert(!std::signed_integral<unsigned int>);
    static_assert(std::unsigned_integral<unsigned int>);
    static_assert(!std::unsigned_integral<int>);

    std::cout << "  ✓ integral, signed_integral, unsigned_integral work correctly\n";
}

// Test floating_point concept
void test_floating_point() {
    std::cout << "\nTesting floating_point concept...\n";

    static_assert(std::floating_point<float>);
    static_assert(std::floating_point<double>);
    static_assert(std::floating_point<long double>);
    static_assert(!std::floating_point<int>);
    static_assert(!std::floating_point<bool>);

    std::cout << "  ✓ floating_point works correctly\n";
}

// Test derived_from concept
void test_derived_from() {
    std::cout << "\nTesting derived_from concept...\n";

    class Base {};
    class Derived : public Base {};
    class NotDerived {};

    static_assert(std::derived_from<Derived, Base>);
    static_assert(!std::derived_from<NotDerived, Base>);
    static_assert(std::derived_from<Base, Base>); // A class is derived from itself

    std::cout << "  ✓ derived_from works correctly\n";
}

// Test convertible_to concept
void test_convertible_to() {
    std::cout << "\nTesting convertible_to concept...\n";

    static_assert(std::convertible_to<int, double>);
    static_assert(std::convertible_to<float, double>);
    static_assert(std::convertible_to<int, long>);
    static_assert(!std::convertible_to<int*, double*>);

    std::cout << "  ✓ convertible_to works correctly\n";
}

// Test constructible_from and related concepts
void test_constructible_concepts() {
    std::cout << "\nTesting constructible concepts...\n";

    static_assert(std::constructible_from<std::string, const char*>);
    static_assert(std::default_initializable<int>);
    static_assert(std::default_initializable<std::string>);
    static_assert(std::move_constructible<std::string>);
    static_assert(std::copy_constructible<std::string>);

    std::cout << "  ✓ constructible_from, default_initializable, move_constructible, copy_constructible work correctly\n";
}

// Test destructible concept
void test_destructible() {
    std::cout << "\nTesting destructible concept...\n";

    static_assert(std::destructible<int>);
    static_assert(std::destructible<std::string>);
    static_assert(std::destructible<std::vector<int>>);

    std::cout << "  ✓ destructible works correctly\n";
}

// Test assignable_from concept
void test_assignable_from() {
    std::cout << "\nTesting assignable_from concept...\n";

    static_assert(std::assignable_from<int&, int>);
    static_assert(std::assignable_from<std::string&, std::string>);
    static_assert(!std::assignable_from<const int&, int>);

    std::cout << "  ✓ assignable_from works correctly\n";
}

// Test swappable concepts
void test_swappable_concepts() {
    std::cout << "\nTesting swappable concepts...\n";

    static_assert(std::swappable<int>);
    static_assert(std::swappable<std::string>);
    static_assert(std::swappable_with<int&, int&>);
    static_assert(std::swappable_with<std::string&, std::string&>);

    std::cout << "  ✓ swappable, swappable_with work correctly\n";
}

// Test comparison concepts
void test_comparison_concepts() {
    std::cout << "\nTesting comparison concepts...\n";

    static_assert(std::equality_comparable<int>);
    static_assert(std::equality_comparable<std::string>);
    static_assert(std::equality_comparable_with<int, int>);
    static_assert(std::equality_comparable_with<int, long>);

    static_assert(std::totally_ordered<int>);
    static_assert(std::totally_ordered<double>);
    static_assert(std::totally_ordered_with<int, int>);
    static_assert(std::totally_ordered_with<int, long>);

    std::cout << "  ✓ equality_comparable, totally_ordered and _with variants work correctly\n";
}

// Test object concepts
void test_object_concepts() {
    std::cout << "\nTesting object concepts...\n";

    static_assert(std::movable<std::string>);
    static_assert(std::copyable<std::string>);
    static_assert(std::semiregular<int>);
    static_assert(std::semiregular<std::string>);
    static_assert(std::regular<int>);
    static_assert(std::regular<std::string>);

    std::cout << "  ✓ movable, copyable, semiregular, regular work correctly\n";
}

// Test callable concepts
void test_callable_concepts() {
    std::cout << "\nTesting callable concepts...\n";

    auto lambda = [](int x) { return x > 0; };
    auto binary_lambda = [](int x, int y) { return x < y; };

    static_assert(std::invocable<decltype(lambda), int>);
    static_assert(std::regular_invocable<decltype(lambda), int>);
    static_assert(std::predicate<decltype(lambda), int>);
    static_assert(std::relation<decltype(binary_lambda), int, int>);
    static_assert(std::equivalence_relation<decltype(binary_lambda), int, int>);
    static_assert(std::strict_weak_order<decltype(binary_lambda), int, int>);

    std::cout << "  ✓ invocable, regular_invocable, predicate, relation, equivalence_relation, strict_weak_order work correctly\n";
}

// Test concepts with template functions
template<std::integral T>
T add_integral(T a, T b) {
    return a + b;
}

template<std::floating_point T>
T add_floating(T a, T b) {
    return a + b;
}

void test_constrained_templates() {
    std::cout << "\nTesting concept-constrained templates...\n";

    auto result_int = add_integral(5, 3);
    assert(result_int == 8);
    std::cout << "  ✓ Integral-constrained template: " << result_int << "\n";

    auto result_float = add_floating(5.5, 3.2);
    assert(result_float > 8.6 && result_float < 8.8);
    std::cout << "  ✓ Floating-point-constrained template: " << result_float << "\n";
}

// Test concepts with requires clauses
template<typename T>
    requires std::regular<T> && std::totally_ordered<T>
T max_value(T a, T b) {
    return (a > b) ? a : b;
}

void test_requires_clauses() {
    std::cout << "\nTesting requires clauses...\n";

    auto result_int = max_value(10, 20);
    assert(result_int == 20);
    std::cout << "  ✓ Requires clause with int: " << result_int << "\n";

    auto result_double = max_value(10.5, 20.3);
    assert(result_double > 20.2 && result_double < 20.4);
    std::cout << "  ✓ Requires clause with double: " << result_double << "\n";

    std::string s1 = "apple";
    std::string s2 = "banana";
    auto result_str = max_value(s1, s2);
    assert(result_str == "banana");
    std::cout << "  ✓ Requires clause with string: " << result_str << "\n";
}

int main() {
    std::cout << "=== Testing std_module.concepts ===\n\n";

    try {
        test_same_as();
        test_integral_concepts();
        test_floating_point();
        test_derived_from();
        test_convertible_to();
        test_constructible_concepts();
        test_destructible();
        test_assignable_from();
        test_swappable_concepts();
        test_comparison_concepts();
        test_object_concepts();
        test_callable_concepts();
        test_constrained_templates();
        test_requires_clauses();

        std::cout << "\n=== All concepts tests passed! ===\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\n!!! Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
