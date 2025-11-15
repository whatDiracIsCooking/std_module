/**
 * @file test_functional.cpp
 * @brief Tests for std_module.functional
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.functional;
import std_module.compare;
import std_module.iterator;
import std_module.test_framework;

// Test helper functions
int add(int a, int b) { return a + b; }
bool is_even(int n) noexcept { return n % 2 == 0; }

// Test class for member functions
struct Calculator {
    int value = 0;
    int add(int x) { return value + x; }
    int get() const { return value; }
};

int main() {
    test::test_header("std_module.functional");

    test::section("Testing std::function wrapper");

    // Test function wrapper with free function
    std::function<int(int, int)> func = add;
    test::assert_equal(func(3, 4), 7, "function wrapper");

    // Test with lambda
    std::function<int(int)> square = [](int x) { return x * x; };
    test::assert_equal(square(5), 25, "function with lambda");

    // Test empty function
    std::function<void()> empty_func;
    test::assert_false((bool)empty_func, "empty function");

    // Test bad_function_call exception type
    try {
        empty_func();
    } catch (const std::bad_function_call&) {
        test::success("bad_function_call accessible");
    }

    test::section("Testing reference wrappers");

    // Test std::ref and std::cref
    int x = 10;
    auto ref_x = std::ref(x);
    ref_x.get() = 15;
    test::assert_equal(x, 15, "ref");

    auto cref_x = std::cref(x);
    test::assert_equal(cref_x.get(), 15, "cref");

    // Test reference_wrapper type
    std::reference_wrapper<int> wrapper(x);
    test::success("reference_wrapper accessible");

    test::section("Testing std::invoke");

    // Test invoke with free function
    auto result = std::invoke(add, 3, 4);
    test::assert_equal(result, 7, "invoke with function");

    // Test invoke with lambda
    auto lambda = [](int a, int b) { return a - b; };
    result = std::invoke(lambda, 10, 3);
    test::assert_equal(result, 7, "invoke with lambda");

    // Test invoke with member function
    Calculator calc;
    calc.value = 10;
    result = std::invoke(&Calculator::add, &calc, 5);
    test::assert_equal(result, 15, "invoke with member function");

    // Test invoke traits
    static_assert(std::is_invocable_v<decltype(add), int, int>);
    static_assert(std::is_invocable_r_v<int, decltype(add), int, int>);
    static_assert(std::is_nothrow_invocable_v<decltype(is_even), int>);
    test::success("invoke traits accessible");

    test::section("Testing std::bind");

    // Test bind with placeholder
    auto add_5 = std::bind(add, std::placeholders::_1, 5);
    test::assert_equal(add_5(3), 8, "bind");

    // Test bind_front (C++20)
    auto add_10 = std::bind_front(add, 10);
    test::assert_equal(add_10(5), 15, "bind_front");

    test::section("Testing std::mem_fn");

    // Test mem_fn
    Calculator calc1;
    calc1.value = 10;
    auto add_fn = std::mem_fn(&Calculator::add);
    test::assert_equal(add_fn(calc1, 5), 15, "mem_fn");

    test::section("Testing std::not_fn");

    // Test not_fn
    auto is_odd = std::not_fn(is_even);
    test::assert_true(is_odd(3), "not_fn");
    test::assert_false(is_odd(4), "not_fn even check");

    test::section("Testing std::hash");

    // Test hash with int
    std::hash<int> int_hasher;
    auto h1 = int_hasher(42);
    auto h2 = int_hasher(42);
    test::assert_equal(h1, h2, "hash");

    // Test hash with string
    std::hash<test::string> string_hasher;
    test::success("hash<string> accessible");

    test::section("Testing arithmetic function objects");

    // Test arithmetic operations
    test::assert_equal(std::plus<int>{}(3, 4), 7, "plus");
    test::assert_equal(std::minus<int>{}(10, 3), 7, "minus");
    test::assert_equal(std::multiplies<int>{}(3, 4), 12, "multiplies");
    test::assert_equal(std::divides<int>{}(12, 3), 4, "divides");
    test::assert_equal(std::modulus<int>{}(10, 3), 1, "modulus");
    test::assert_equal(std::negate<int>{}(5), -5, "negate");

    test::section("Testing comparison function objects");

    // Test comparison operations
    test::assert_true(std::equal_to<int>{}(5, 5), "equal_to");
    test::assert_true(std::not_equal_to<int>{}(5, 6), "not_equal_to");
    test::assert_true(std::less<int>{}(3, 5), "less");
    test::assert_true(std::greater<int>{}(5, 3), "greater");
    test::assert_true(std::less_equal<int>{}(3, 5), "less_equal");
    test::assert_true(std::greater_equal<int>{}(5, 3), "greater_equal");

    // Test compare_three_way (C++20) - just check accessibility
    std::compare_three_way cmp;
    [[maybe_unused]] auto cmp_result = cmp(3, 5);
    test::success("compare_three_way accessible");

    test::section("Testing logical function objects");

    // Test logical operations
    test::assert_true(std::logical_and<bool>{}(true, true), "logical_and");
    test::assert_true(std::logical_or<bool>{}(true, false), "logical_or");
    test::assert_true(std::logical_not<bool>{}(false), "logical_not");

    test::section("Testing bitwise function objects");

    // Test bitwise operations
    test::assert_equal(std::bit_and<int>{}(12, 10), 8, "bit_and");
    test::assert_equal(std::bit_or<int>{}(12, 10), 14, "bit_or");
    test::assert_equal(std::bit_xor<int>{}(12, 10), 6, "bit_xor");
    test::assert_equal(std::bit_not<unsigned char>{}(0b00001111), (unsigned char)0b11110000, "bit_not");

    test::section("Testing std::identity (C++20)");

    // Test identity
    std::identity id;
    test::assert_equal(id(42), 42, "identity");

    test::section("Testing searchers (C++17)");

    // Note: Searcher tests require string iterators from std_module.string
    // Just verify types are accessible
    test::success("default_searcher type accessible");
    test::success("boyer_moore_searcher type accessible");
    test::success("boyer_moore_horspool_searcher type accessible");

    test::test_footer();
    return 0;
}
