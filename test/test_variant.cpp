/**
 * @file test_variant.cpp
 * @brief Comprehensive test for std_module.variant (C++20)
 */

import std_module.variant;

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

void test_basic_variant() {
    std::cout << "Testing basic variant...\n";

    // Test variant construction with first type
    std::variant<int, double, std::string> v1 = 42;
    assert(std::holds_alternative<int>(v1));
    assert(std::get<int>(v1) == 42);
    assert(std::get<0>(v1) == 42);
    std::cout << "  ✓ variant with int: " << std::get<int>(v1) << "\n";

    // Test variant with second type
    std::variant<int, double, std::string> v2 = 3.14;
    assert(std::holds_alternative<double>(v2));
    assert(std::get<double>(v2) == 3.14);
    assert(std::get<1>(v2) == 3.14);
    std::cout << "  ✓ variant with double: " << std::get<double>(v2) << "\n";

    // Test variant with third type
    std::variant<int, double, std::string> v3 = std::string("Hello");
    assert(std::holds_alternative<std::string>(v3));
    assert(std::get<std::string>(v3) == "Hello");
    assert(std::get<2>(v3) == "Hello");
    std::cout << "  ✓ variant with string: " << std::get<std::string>(v3) << "\n";

    // Test index()
    assert(v1.index() == 0);
    assert(v2.index() == 1);
    assert(v3.index() == 2);
    std::cout << "  ✓ index(): " << v1.index() << ", " << v2.index() << ", " << v3.index() << "\n";
}

void test_variant_assignment() {
    std::cout << "\nTesting variant assignment...\n";

    std::variant<int, std::string> v = 10;
    assert(std::holds_alternative<int>(v));
    assert(std::get<int>(v) == 10);
    std::cout << "  ✓ initial value: " << std::get<int>(v) << "\n";

    // Assign different type
    v = std::string("Changed");
    assert(std::holds_alternative<std::string>(v));
    assert(std::get<std::string>(v) == "Changed");
    std::cout << "  ✓ changed to string: " << std::get<std::string>(v) << "\n";

    // Assign same type, different value
    v = std::string("Another");
    assert(std::get<std::string>(v) == "Another");
    std::cout << "  ✓ updated string: " << std::get<std::string>(v) << "\n";

    // Assign back to first type
    v = 99;
    assert(std::holds_alternative<int>(v));
    assert(std::get<int>(v) == 99);
    std::cout << "  ✓ back to int: " << std::get<int>(v) << "\n";
}

void test_variant_emplace() {
    std::cout << "\nTesting variant emplace...\n";

    std::variant<int, std::string, std::vector<int>> v;

    // Emplace by type
    v.emplace<std::string>("Emplaced");
    assert(std::holds_alternative<std::string>(v));
    assert(std::get<std::string>(v) == "Emplaced");
    std::cout << "  ✓ emplace<string>: " << std::get<std::string>(v) << "\n";

    // Emplace by index
    v.emplace<2>(std::vector<int>{1, 2, 3, 4, 5});
    assert(std::holds_alternative<std::vector<int>>(v));
    assert(std::get<std::vector<int>>(v).size() == 5);
    std::cout << "  ✓ emplace<2>(vector): size = " << std::get<std::vector<int>>(v).size() << "\n";

    // Emplace with constructor arguments
    v.emplace<std::string>(10, 'X');  // Creates string "XXXXXXXXXX"
    assert(std::get<std::string>(v) == "XXXXXXXXXX");
    std::cout << "  ✓ emplace with args: " << std::get<std::string>(v) << "\n";
}

void test_get_if() {
    std::cout << "\nTesting get_if...\n";

    std::variant<int, std::string> v = 42;

    // get_if with correct type
    int* ptr1 = std::get_if<int>(&v);
    assert(ptr1 != nullptr);
    assert(*ptr1 == 42);
    std::cout << "  ✓ get_if<int> success: " << *ptr1 << "\n";

    // get_if with wrong type
    std::string* ptr2 = std::get_if<std::string>(&v);
    assert(ptr2 == nullptr);
    std::cout << "  ✓ get_if<string> returns nullptr\n";

    // get_if by index
    int* ptr3 = std::get_if<0>(&v);
    assert(ptr3 != nullptr);
    assert(*ptr3 == 42);
    std::cout << "  ✓ get_if<0> success: " << *ptr3 << "\n";

    std::string* ptr4 = std::get_if<1>(&v);
    assert(ptr4 == nullptr);
    std::cout << "  ✓ get_if<1> (string) returns nullptr\n";
}

void test_visit() {
    std::cout << "\nTesting visit...\n";

    std::variant<int, double, std::string> v1 = 42;
    std::variant<int, double, std::string> v2 = 3.14;
    std::variant<int, double, std::string> v3 = std::string("Hello");

    // Simple visitor
    auto visitor = [](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            return "int";
        } else if constexpr (std::is_same_v<T, double>) {
            return "double";
        } else if constexpr (std::is_same_v<T, std::string>) {
            return "string";
        }
    };

    auto result1 = std::visit(visitor, v1);
    assert(std::string(result1) == "int");
    std::cout << "  ✓ visit variant<int>: " << result1 << "\n";

    auto result2 = std::visit(visitor, v2);
    assert(std::string(result2) == "double");
    std::cout << "  ✓ visit variant<double>: " << result2 << "\n";

    auto result3 = std::visit(visitor, v3);
    assert(std::string(result3) == "string");
    std::cout << "  ✓ visit variant<string>: " << result3 << "\n";

    // Visitor that modifies the variant
    auto incrementer = [](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            arg++;
        } else if constexpr (std::is_same_v<T, double>) {
            arg += 0.5;
        }
    };

    std::visit(incrementer, v1);
    assert(std::get<int>(v1) == 43);
    std::cout << "  ✓ visit with modification: " << std::get<int>(v1) << "\n";
}

void test_monostate() {
    std::cout << "\nTesting monostate...\n";

    // monostate allows default construction of variants
    std::variant<std::monostate, int, std::string> v1;
    assert(std::holds_alternative<std::monostate>(v1));
    assert(v1.index() == 0);
    std::cout << "  ✓ default constructed variant holds monostate\n";

    // Assign a value
    v1 = 42;
    assert(std::holds_alternative<int>(v1));
    assert(std::get<int>(v1) == 42);
    std::cout << "  ✓ assigned int: " << std::get<int>(v1) << "\n";

    // Back to monostate
    v1 = std::monostate{};
    assert(std::holds_alternative<std::monostate>(v1));
    std::cout << "  ✓ back to monostate\n";
}

void test_bad_variant_access() {
    std::cout << "\nTesting bad_variant_access exception...\n";

    std::variant<int, std::string> v = 42;

    try {
        // Try to access wrong type
        std::string& s = std::get<std::string>(v);
        (void)s;
        assert(false && "Should have thrown");
    } catch (const std::bad_variant_access& e) {
        std::cout << "  ✓ bad_variant_access caught: " << e.what() << "\n";
    }

    try {
        // Try to access wrong index
        std::string& s = std::get<1>(v);
        (void)s;
        assert(false && "Should have thrown");
    } catch (const std::bad_variant_access& e) {
        std::cout << "  ✓ bad_variant_access by index caught: " << e.what() << "\n";
    }
}

void test_variant_size_and_alternative() {
    std::cout << "\nTesting variant_size and variant_alternative...\n";

    using MyVariant = std::variant<int, double, std::string, bool>;

    // Test variant_size
    constexpr size_t size = std::variant_size_v<MyVariant>;
    assert(size == 4);
    std::cout << "  ✓ variant_size: " << size << "\n";

    // Test variant_alternative
    using FirstType = std::variant_alternative_t<0, MyVariant>;
    using SecondType = std::variant_alternative_t<1, MyVariant>;
    using ThirdType = std::variant_alternative_t<2, MyVariant>;
    using FourthType = std::variant_alternative_t<3, MyVariant>;

    assert((std::is_same_v<FirstType, int>));
    assert((std::is_same_v<SecondType, double>));
    assert((std::is_same_v<ThirdType, std::string>));
    assert((std::is_same_v<FourthType, bool>));
    std::cout << "  ✓ variant_alternative types correct\n";
}

void test_variant_swap() {
    std::cout << "\nTesting variant swap...\n";

    std::variant<int, std::string> v1 = 42;
    std::variant<int, std::string> v2 = std::string("Hello");

    v1.swap(v2);

    assert(std::holds_alternative<std::string>(v1));
    assert(std::get<std::string>(v1) == "Hello");
    assert(std::holds_alternative<int>(v2));
    assert(std::get<int>(v2) == 42);

    std::cout << "  ✓ swap: " << std::get<std::string>(v1) << ", " << std::get<int>(v2) << "\n";
}

// Custom type for testing
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

void test_variant_custom_type() {
    std::cout << "\nTesting variant with custom type...\n";

    std::variant<int, Point, std::string> v;

    v.emplace<Point>(10, 20);
    assert(std::holds_alternative<Point>(v));
    assert(std::get<Point>(v).x == 10);
    assert(std::get<Point>(v).y == 20);
    std::cout << "  ✓ variant<Point>: (" << std::get<Point>(v).x << ", " << std::get<Point>(v).y << ")\n";

    // Visit custom type
    auto visitor = [](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Point>) {
            return arg.x + arg.y;
        } else {
            return 0;
        }
    };

    int sum = std::visit(visitor, v);
    assert(sum == 30);
    std::cout << "  ✓ visit Point, sum: " << sum << "\n";
}

void test_variant_multi_visit() {
    std::cout << "\nTesting multi-variant visit...\n";

    std::variant<int, double> v1 = 5;
    std::variant<int, double> v2 = 3.5;

    // Visitor must return consistent type
    auto adder = [](auto&& a, auto&& b) -> double {
        return a + b;
    };

    auto result = std::visit(adder, v1, v2);
    // 5 + 3.5 = 8.5 (double)
    assert(result == 8.5);
    std::cout << "  ✓ multi-visit result: " << result << "\n";

    v1 = 10;
    v2 = 20;
    result = std::visit(adder, v1, v2);
    assert(result == 30.0);
    std::cout << "  ✓ multi-visit int + int: " << result << "\n";
}

void test_variant_valueless() {
    std::cout << "\nTesting valueless_by_exception...\n";

    std::variant<int, std::string> v = 42;
    assert(!v.valueless_by_exception());
    std::cout << "  ✓ normal variant is not valueless\n";

    // Note: It's hard to create a valueless variant in practice without
    // throwing exceptions during assignment. The valueless state is rare.
}

int main() {
    std::cout << "=== Testing std_module.variant ===\n\n";

    test_basic_variant();
    test_variant_assignment();
    test_variant_emplace();
    test_get_if();
    test_visit();
    test_monostate();
    test_bad_variant_access();
    test_variant_size_and_alternative();
    test_variant_swap();
    test_variant_custom_type();
    test_variant_multi_visit();
    test_variant_valueless();

    std::cout << "\n=== All variant tests passed! ===\n";
    return 0;
}
