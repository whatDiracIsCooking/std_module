/**
 * @file test_functional.cpp
 * @brief Comprehensive test for std_module.functional (C++20)
 */

import std_module.functional;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string when available
#include <vector>    // FIXME: Should be import std_module.vector (but we have it!)
#include <algorithm> // FIXME: Should be import std_module.algorithm (but we have it!)
#include <compare>   // FIXME: Should be import std_module.compare when available

// Test helper functions
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }
bool is_even(int n) noexcept { return n % 2 == 0; }
bool is_positive(int n) { return n > 0; }

// Test class for member functions
class Calculator {
public:
    int value = 0;

    int add(int x) { return value + x; }
    int multiply(int x) const { return value * x; }
    void set(int x) { value = x; }
    int get() const { return value; }
};

void test_function_wrapper() {
    std::cout << "Testing std::function...\n";

    // Basic function wrapper
    std::function<int(int, int)> func = add;
    assert(func(3, 4) == 7);
    std::cout << "  ✓ Function wrapper with free function: " << func(3, 4) << "\n";

    // Lambda
    std::function<int(int)> square = [](int x) { return x * x; };
    assert(square(5) == 25);
    std::cout << "  ✓ Function wrapper with lambda: " << square(5) << "\n";

    // Change function
    func = multiply;
    assert(func(3, 4) == 12);
    std::cout << "  ✓ Reassigned function wrapper: " << func(3, 4) << "\n";

    // Empty function
    std::function<void()> empty_func;
    assert(!empty_func);
    std::cout << "  ✓ Empty function evaluates to false\n";

    // Bad function call test
    try {
        empty_func();
        assert(false && "Should have thrown bad_function_call");
    } catch (const std::bad_function_call&) {
        std::cout << "  ✓ Empty function throws bad_function_call\n";
    }
}

void test_reference_wrappers() {
    std::cout << "\nTesting reference wrappers (ref, cref)...\n";

    int x = 10;
    int y = 20;

    // std::ref
    auto ref_x = std::ref(x);
    ref_x.get() = 15;
    assert(x == 15);
    std::cout << "  ✓ std::ref modifies original: " << x << "\n";

    // std::cref
    auto cref_y = std::cref(y);
    assert(cref_y.get() == 20);
    std::cout << "  ✓ std::cref reads original: " << cref_y.get() << "\n";

    // std::reference_wrapper
    std::reference_wrapper<int> wrapper(x);
    wrapper.get() = 25;
    assert(x == 25);
    std::cout << "  ✓ reference_wrapper modifies original: " << x << "\n";

    // Use in container
    std::vector<std::reference_wrapper<int>> vec;
    vec.push_back(std::ref(x));
    vec.push_back(std::ref(y));
    vec[0].get() = 100;
    assert(x == 100);
    std::cout << "  ✓ reference_wrapper in container: x=" << x << ", y=" << y << "\n";
}

void test_invoke() {
    std::cout << "\nTesting std::invoke...\n";

    // Invoke free function
    auto result = std::invoke(add, 3, 4);
    assert(result == 7);
    std::cout << "  ✓ invoke with free function: " << result << "\n";

    // Invoke lambda
    auto lambda = [](int x, int y) { return x - y; };
    result = std::invoke(lambda, 10, 3);
    assert(result == 7);
    std::cout << "  ✓ invoke with lambda: " << result << "\n";

    // Invoke member function
    Calculator calc;
    calc.value = 10;
    result = std::invoke(&Calculator::add, &calc, 5);
    assert(result == 15);
    std::cout << "  ✓ invoke with member function: " << result << "\n";

    // Invoke member function (const)
    result = std::invoke(&Calculator::multiply, calc, 3);
    assert(result == 30);
    std::cout << "  ✓ invoke with const member function: " << result << "\n";

    // Invoke member variable
    result = std::invoke(&Calculator::value, calc);
    assert(result == 10);
    std::cout << "  ✓ invoke with member variable: " << result << "\n";

    // Test invoke traits
    static_assert(std::is_invocable_v<decltype(add), int, int>);
    static_assert(std::is_invocable_r_v<int, decltype(add), int, int>);
    static_assert(std::is_nothrow_invocable_v<decltype(is_even), int>);
    std::cout << "  ✓ invoke traits work correctly\n";
}

void test_bind() {
    std::cout << "\nTesting std::bind and bind_front...\n";

    // Basic bind
    auto add_5 = std::bind(add, std::placeholders::_1, 5);
    assert(add_5(3) == 8);
    std::cout << "  ✓ bind with placeholder: " << add_5(3) << "\n";

    // Bind with reordered arguments
    auto subtract = [](int a, int b) { return a - b; };
    auto reverse_subtract = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);
    assert(reverse_subtract(3, 10) == 7);  // 10 - 3
    std::cout << "  ✓ bind with reordered placeholders: " << reverse_subtract(3, 10) << "\n";

    // Bind member function
    Calculator calc;
    calc.value = 10;
    auto calc_add = std::bind(&Calculator::add, &calc, std::placeholders::_1);
    assert(calc_add(5) == 15);
    std::cout << "  ✓ bind with member function: " << calc_add(5) << "\n";

    // bind_front (C++20)
    auto add_10 = std::bind_front(add, 10);
    assert(add_10(5) == 15);
    std::cout << "  ✓ bind_front: " << add_10(5) << "\n";

    // bind_front with lambda
    auto multiply_by = [](int a, int b) { return a * b; };
    auto multiply_by_3 = std::bind_front(multiply_by, 3);
    assert(multiply_by_3(4) == 12);
    std::cout << "  ✓ bind_front with lambda: " << multiply_by_3(4) << "\n";
}

void test_mem_fn() {
    std::cout << "\nTesting std::mem_fn...\n";

    Calculator calc1, calc2;
    calc1.value = 10;
    calc2.value = 20;

    // mem_fn with member function
    auto add_fn = std::mem_fn(&Calculator::add);
    assert(add_fn(calc1, 5) == 15);
    std::cout << "  ✓ mem_fn with member function: " << add_fn(calc1, 5) << "\n";

    // mem_fn with const member function
    auto multiply_fn = std::mem_fn(&Calculator::multiply);
    assert(multiply_fn(calc2, 3) == 60);
    std::cout << "  ✓ mem_fn with const member function: " << multiply_fn(calc2, 3) << "\n";

    // mem_fn with getter
    auto get_fn = std::mem_fn(&Calculator::get);
    assert(get_fn(calc1) == 10);
    assert(get_fn(calc2) == 20);
    std::cout << "  ✓ mem_fn with getter: calc1=" << get_fn(calc1)
              << ", calc2=" << get_fn(calc2) << "\n";
}

void test_not_fn() {
    std::cout << "\nTesting std::not_fn...\n";

    // Negate predicate
    auto is_odd = std::not_fn(is_even);
    assert(is_odd(3) == true);
    assert(is_odd(4) == false);
    std::cout << "  ✓ not_fn with predicate: is_odd(3)=" << is_odd(3)
              << ", is_odd(4)=" << is_odd(4) << "\n";

    // Negate lambda
    auto less_than_10 = [](int x) { return x < 10; };
    auto greater_equal_10 = std::not_fn(less_than_10);
    assert(greater_equal_10(15) == true);
    assert(greater_equal_10(5) == false);
    std::cout << "  ✓ not_fn with lambda: >=10(15)=" << greater_equal_10(15)
              << ", >=10(5)=" << greater_equal_10(5) << "\n";
}

void test_hash() {
    std::cout << "\nTesting std::hash...\n";

    // Hash integers
    std::hash<int> int_hasher;
    auto h1 = int_hasher(42);
    auto h2 = int_hasher(42);
    auto h3 = int_hasher(43);
    assert(h1 == h2);
    assert(h1 != h3);
    std::cout << "  ✓ hash<int>: hash(42)=" << h1 << ", hash(43)=" << h3 << "\n";

    // Hash strings
    std::hash<std::string> string_hasher;
    auto hs1 = string_hasher("hello");
    auto hs2 = string_hasher("hello");
    auto hs3 = string_hasher("world");
    assert(hs1 == hs2);
    assert(hs1 != hs3);
    std::cout << "  ✓ hash<string>: hash('hello')=" << hs1 << ", hash('world')=" << hs3 << "\n";

    // Hash double
    std::hash<double> double_hasher;
    auto hd = double_hasher(3.14);
    std::cout << "  ✓ hash<double>: hash(3.14)=" << hd << "\n";
}

void test_arithmetic_operations() {
    std::cout << "\nTesting arithmetic operations...\n";

    // plus
    std::plus<int> add_op;
    assert(add_op(3, 4) == 7);
    std::cout << "  ✓ plus: 3 + 4 = " << add_op(3, 4) << "\n";

    // minus
    std::minus<int> sub_op;
    assert(sub_op(10, 3) == 7);
    std::cout << "  ✓ minus: 10 - 3 = " << sub_op(10, 3) << "\n";

    // multiplies
    std::multiplies<int> mul_op;
    assert(mul_op(3, 4) == 12);
    std::cout << "  ✓ multiplies: 3 * 4 = " << mul_op(3, 4) << "\n";

    // divides
    std::divides<int> div_op;
    assert(div_op(12, 3) == 4);
    std::cout << "  ✓ divides: 12 / 3 = " << div_op(12, 3) << "\n";

    // modulus
    std::modulus<int> mod_op;
    assert(mod_op(10, 3) == 1);
    std::cout << "  ✓ modulus: 10 % 3 = " << mod_op(10, 3) << "\n";

    // negate
    std::negate<int> neg_op;
    assert(neg_op(5) == -5);
    assert(neg_op(-3) == 3);
    std::cout << "  ✓ negate: -5 = " << neg_op(5) << ", -(-3) = " << neg_op(-3) << "\n";
}

void test_comparisons() {
    std::cout << "\nTesting comparison operations...\n";

    // equal_to
    std::equal_to<int> eq;
    assert(eq(5, 5) == true);
    assert(eq(5, 6) == false);
    std::cout << "  ✓ equal_to: 5==5=" << eq(5, 5) << ", 5==6=" << eq(5, 6) << "\n";

    // not_equal_to
    std::not_equal_to<int> neq;
    assert(neq(5, 6) == true);
    assert(neq(5, 5) == false);
    std::cout << "  ✓ not_equal_to: 5!=6=" << neq(5, 6) << ", 5!=5=" << neq(5, 5) << "\n";

    // less
    std::less<int> lt;
    assert(lt(3, 5) == true);
    assert(lt(5, 3) == false);
    std::cout << "  ✓ less: 3<5=" << lt(3, 5) << ", 5<3=" << lt(5, 3) << "\n";

    // greater
    std::greater<int> gt;
    assert(gt(5, 3) == true);
    assert(gt(3, 5) == false);
    std::cout << "  ✓ greater: 5>3=" << gt(5, 3) << ", 3>5=" << gt(3, 5) << "\n";

    // less_equal
    std::less_equal<int> le;
    assert(le(3, 5) == true);
    assert(le(5, 5) == true);
    assert(le(5, 3) == false);
    std::cout << "  ✓ less_equal: 3<=5=" << le(3, 5) << ", 5<=5=" << le(5, 5) << "\n";

    // greater_equal
    std::greater_equal<int> ge;
    assert(ge(5, 3) == true);
    assert(ge(5, 5) == true);
    assert(ge(3, 5) == false);
    std::cout << "  ✓ greater_equal: 5>=3=" << ge(5, 3) << ", 5>=5=" << ge(5, 5) << "\n";

    // compare_three_way (C++20)
    std::compare_three_way cmp;
    assert(cmp(3, 5) == std::strong_ordering::less);
    assert(cmp(5, 3) == std::strong_ordering::greater);
    assert(cmp(5, 5) == std::strong_ordering::equal);
    std::cout << "  ✓ compare_three_way: works correctly\n";
}

void test_logical_operations() {
    std::cout << "\nTesting logical operations...\n";

    // logical_and
    std::logical_and<bool> and_op;
    assert(and_op(true, true) == true);
    assert(and_op(true, false) == false);
    std::cout << "  ✓ logical_and: true&&true=" << and_op(true, true)
              << ", true&&false=" << and_op(true, false) << "\n";

    // logical_or
    std::logical_or<bool> or_op;
    assert(or_op(true, false) == true);
    assert(or_op(false, false) == false);
    std::cout << "  ✓ logical_or: true||false=" << or_op(true, false)
              << ", false||false=" << or_op(false, false) << "\n";

    // logical_not
    std::logical_not<bool> not_op;
    assert(not_op(true) == false);
    assert(not_op(false) == true);
    std::cout << "  ✓ logical_not: !true=" << not_op(true)
              << ", !false=" << not_op(false) << "\n";
}

void test_bitwise_operations() {
    std::cout << "\nTesting bitwise operations...\n";

    // bit_and
    std::bit_and<int> and_op;
    assert(and_op(0b1100, 0b1010) == 0b1000);
    std::cout << "  ✓ bit_and: 12 & 10 = " << and_op(12, 10) << "\n";

    // bit_or
    std::bit_or<int> or_op;
    assert(or_op(0b1100, 0b1010) == 0b1110);
    std::cout << "  ✓ bit_or: 12 | 10 = " << or_op(12, 10) << "\n";

    // bit_xor
    std::bit_xor<int> xor_op;
    assert(xor_op(0b1100, 0b1010) == 0b0110);
    std::cout << "  ✓ bit_xor: 12 ^ 10 = " << xor_op(12, 10) << "\n";

    // bit_not
    std::bit_not<unsigned char> not_op;
    assert(not_op(0b00001111) == 0b11110000);
    std::cout << "  ✓ bit_not: ~15 = " << static_cast<int>(not_op(15)) << "\n";
}

void test_identity() {
    std::cout << "\nTesting std::identity (C++20)...\n";

    // Basic identity
    std::identity id;
    assert(id(42) == 42);
    std::cout << "  ✓ identity(42) = " << id(42) << "\n";

    // Identity with string
    std::string str = "hello";
    assert(id(str) == "hello");
    std::cout << "  ✓ identity(\"hello\") = " << id(str) << "\n";

    // Identity preserves type
    int x = 10;
    int& ref = id(x);
    ref = 20;
    assert(x == 20);
    std::cout << "  ✓ identity preserves references: x = " << x << "\n";
}

void test_searchers() {
    std::cout << "\nTesting searchers (C++17)...\n";

    std::string haystack = "hello world, hello universe";
    std::string needle = "hello";

    // default_searcher
    std::default_searcher searcher(needle.begin(), needle.end());
    auto it = searcher(haystack.begin(), haystack.end()).first;
    assert(it == haystack.begin());
    std::cout << "  ✓ default_searcher found at position: "
              << (it - haystack.begin()) << "\n";

    // boyer_moore_searcher
    std::boyer_moore_searcher bm_searcher(needle.begin(), needle.end());
    auto it2 = bm_searcher(haystack.begin(), haystack.end()).first;
    assert(it2 == haystack.begin());
    std::cout << "  ✓ boyer_moore_searcher found at position: "
              << (it2 - haystack.begin()) << "\n";

    // boyer_moore_horspool_searcher
    std::boyer_moore_horspool_searcher bmh_searcher(needle.begin(), needle.end());
    auto it3 = bmh_searcher(haystack.begin(), haystack.end()).first;
    assert(it3 == haystack.begin());
    std::cout << "  ✓ boyer_moore_horspool_searcher found at position: "
              << (it3 - haystack.begin()) << "\n";
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "std_module.functional - Comprehensive Tests\n";
    std::cout << "===========================================\n\n";

    test_function_wrapper();
    test_reference_wrappers();
    test_invoke();
    test_bind();
    test_mem_fn();
    test_not_fn();
    test_hash();
    test_arithmetic_operations();
    test_comparisons();
    test_logical_operations();
    test_bitwise_operations();
    test_identity();
    test_searchers();

    std::cout << "\n===========================================\n";
    std::cout << "All tests passed! ✓\n";
    std::cout << "===========================================\n";

    return 0;
}
