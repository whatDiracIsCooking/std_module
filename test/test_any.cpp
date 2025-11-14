/**
 * @file test_any.cpp
 * @brief Comprehensive test for std_module.any (C++20)
 */

import std_module.any;

#include <iostream>  // For output
#include <cassert>   // For assertions
#include <string>    // For std::string tests
#include <vector>    // For std::vector tests

void test_basic_construction() {
    std::cout << "Testing basic construction and assignment...\n";

    // Default construction
    std::any a1;
    assert(!a1.has_value());
    std::cout << "  ✓ Default constructed any has no value\n";

    // Construction with value
    std::any a2 = 42;
    assert(a2.has_value());
    assert(std::any_cast<int>(a2) == 42);
    std::cout << "  ✓ Constructed with int: " << std::any_cast<int>(a2) << "\n";

    // Construction with string
    std::any a3 = std::string("Hello");
    assert(a3.has_value());
    assert(std::any_cast<std::string>(a3) == "Hello");
    std::cout << "  ✓ Constructed with string: " << std::any_cast<std::string>(a3) << "\n";

    // Copy construction
    std::any a4 = a2;
    assert(a4.has_value());
    assert(std::any_cast<int>(a4) == 42);
    std::cout << "  ✓ Copy constructed: " << std::any_cast<int>(a4) << "\n";

    // Move construction
    std::any a5 = std::move(a3);
    assert(a5.has_value());
    assert(std::any_cast<std::string>(a5) == "Hello");
    std::cout << "  ✓ Move constructed: " << std::any_cast<std::string>(a5) << "\n";
}

void test_assignment() {
    std::cout << "\nTesting assignment...\n";

    std::any a;

    // Assign int
    a = 100;
    assert(a.has_value());
    assert(std::any_cast<int>(a) == 100);
    std::cout << "  ✓ Assigned int: " << std::any_cast<int>(a) << "\n";

    // Assign string
    a = std::string("World");
    assert(a.has_value());
    assert(std::any_cast<std::string>(a) == "World");
    std::cout << "  ✓ Assigned string: " << std::any_cast<std::string>(a) << "\n";

    // Assign double
    a = 3.14159;
    assert(a.has_value());
    assert(std::any_cast<double>(a) == 3.14159);
    std::cout << "  ✓ Assigned double: " << std::any_cast<double>(a) << "\n";
}

void test_any_cast() {
    std::cout << "\nTesting any_cast...\n";

    std::any a = 42;

    // any_cast with value
    int value = std::any_cast<int>(a);
    assert(value == 42);
    std::cout << "  ✓ any_cast<int> by value: " << value << "\n";

    // any_cast with reference
    int& ref = std::any_cast<int&>(a);
    assert(ref == 42);
    ref = 100;
    assert(std::any_cast<int>(a) == 100);
    std::cout << "  ✓ any_cast<int&> by reference, modified to: " << std::any_cast<int>(a) << "\n";

    // any_cast with const reference
    const std::any& const_a = a;
    const int& const_ref = std::any_cast<const int&>(const_a);
    assert(const_ref == 100);
    std::cout << "  ✓ any_cast<const int&> by const reference: " << const_ref << "\n";

    // any_cast with pointer
    int* ptr = std::any_cast<int>(&a);
    assert(ptr != nullptr);
    assert(*ptr == 100);
    std::cout << "  ✓ any_cast<int> by pointer: " << *ptr << "\n";

    // any_cast with wrong type returns nullptr
    double* wrong_ptr = std::any_cast<double>(&a);
    assert(wrong_ptr == nullptr);
    std::cout << "  ✓ any_cast with wrong type returns nullptr\n";
}

void test_bad_any_cast_exception() {
    std::cout << "\nTesting bad_any_cast exception...\n";

    std::any a = 42;

    try {
        // This should throw bad_any_cast
        std::string s = std::any_cast<std::string>(a);
        assert(false);  // Should not reach here
    } catch (const std::bad_any_cast& e) {
        std::cout << "  ✓ Caught expected bad_any_cast: " << e.what() << "\n";
    }

    try {
        // This should also throw
        std::any_cast<double>(a);
        assert(false);  // Should not reach here
    } catch (const std::bad_any_cast& e) {
        std::cout << "  ✓ Caught expected bad_any_cast for double\n";
    }
}

void test_type_checking() {
    std::cout << "\nTesting type checking...\n";

    std::any a;
    assert(!a.has_value());
    std::cout << "  ✓ Empty any has no value\n";

    a = 42;
    assert(a.has_value());
    assert(a.type() == typeid(int));
    std::cout << "  ✓ any with int has correct type: " << a.type().name() << "\n";

    a = std::string("test");
    assert(a.has_value());
    assert(a.type() == typeid(std::string));
    std::cout << "  ✓ any with string has correct type: " << a.type().name() << "\n";

    a = 3.14;
    assert(a.has_value());
    assert(a.type() == typeid(double));
    std::cout << "  ✓ any with double has correct type: " << a.type().name() << "\n";
}

void test_reset() {
    std::cout << "\nTesting reset...\n";

    std::any a = 42;
    assert(a.has_value());
    std::cout << "  ✓ any has value before reset\n";

    a.reset();
    assert(!a.has_value());
    std::cout << "  ✓ any has no value after reset\n";
}

void test_emplace() {
    std::cout << "\nTesting emplace...\n";

    std::any a;

    // Emplace int
    a.emplace<int>(42);
    assert(a.has_value());
    assert(std::any_cast<int>(a) == 42);
    std::cout << "  ✓ Emplaced int: " << std::any_cast<int>(a) << "\n";

    // Emplace string
    a.emplace<std::string>("Hello, emplace!");
    assert(a.has_value());
    assert(std::any_cast<std::string>(a) == "Hello, emplace!");
    std::cout << "  ✓ Emplaced string: " << std::any_cast<std::string>(a) << "\n";

    // Emplace vector
    a.emplace<std::vector<int>>(3, 100);
    assert(a.has_value());
    auto vec = std::any_cast<std::vector<int>>(a);
    assert(vec.size() == 3);
    assert(vec[0] == 100);
    std::cout << "  ✓ Emplaced vector<int> with 3 elements of value 100\n";
}

void test_make_any() {
    std::cout << "\nTesting make_any...\n";

    // make_any with int
    auto a1 = std::make_any<int>(42);
    assert(a1.has_value());
    assert(std::any_cast<int>(a1) == 42);
    std::cout << "  ✓ make_any<int>(42): " << std::any_cast<int>(a1) << "\n";

    // make_any with string
    auto a2 = std::make_any<std::string>("Hello");
    assert(a2.has_value());
    assert(std::any_cast<std::string>(a2) == "Hello");
    std::cout << "  ✓ make_any<std::string>(\"Hello\"): " << std::any_cast<std::string>(a2) << "\n";

    // make_any with vector
    auto a3 = std::make_any<std::vector<int>>(5, 10);
    assert(a3.has_value());
    auto vec = std::any_cast<std::vector<int>>(a3);
    assert(vec.size() == 5);
    assert(vec[0] == 10);
    std::cout << "  ✓ make_any<vector<int>>(5, 10): vector with " << vec.size() << " elements\n";
}

void test_swap() {
    std::cout << "\nTesting swap...\n";

    std::any a1 = 42;
    std::any a2 = std::string("Hello");

    assert(std::any_cast<int>(a1) == 42);
    assert(std::any_cast<std::string>(a2) == "Hello");

    // Swap using member function
    a1.swap(a2);
    assert(std::any_cast<std::string>(a1) == "Hello");
    assert(std::any_cast<int>(a2) == 42);
    std::cout << "  ✓ Member swap: a1 now contains string, a2 contains int\n";

    // Swap using std::swap
    std::swap(a1, a2);
    assert(std::any_cast<int>(a1) == 42);
    assert(std::any_cast<std::string>(a2) == "Hello");
    std::cout << "  ✓ std::swap: a1 back to int, a2 back to string\n";
}

void test_complex_types() {
    std::cout << "\nTesting complex types...\n";

    // Vector
    std::any a1 = std::vector<int>{1, 2, 3, 4, 5};
    auto vec = std::any_cast<std::vector<int>>(a1);
    assert(vec.size() == 5);
    assert(vec[2] == 3);
    std::cout << "  ✓ any with vector<int>, size: " << vec.size() << "\n";

    // Nested any - explicitly construct any<any>
    std::any inner_any = std::make_any<int>(42);
    std::any a2 = std::make_any<std::any>(inner_any);
    assert(a2.has_value());
    auto inner = std::any_cast<std::any>(a2);
    assert(inner.has_value());
    assert(std::any_cast<int>(inner) == 42);
    std::cout << "  ✓ Nested any works correctly\n";
}

int main() {
    std::cout << "=== std_module.any Comprehensive Test Suite ===\n\n";

    test_basic_construction();
    test_assignment();
    test_any_cast();
    test_bad_any_cast_exception();
    test_type_checking();
    test_reset();
    test_emplace();
    test_make_any();
    test_swap();
    test_complex_types();

    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}
