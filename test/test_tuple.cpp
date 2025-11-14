/**
 * @file test_tuple.cpp
 * @brief Comprehensive tests for std_module.tuple
 */

import std_module.tuple;
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

// Test basic tuple creation and access
void test_tuple_basics() {
    std::cout << "\n=== Testing tuple basics ===\n";

    // Create tuple
    std::tuple<int, double, std::string> t1(42, 3.14, "hello");

    // Access elements with get
    assert(std::get<0>(t1) == 42);
    assert(std::get<1>(t1) == 3.14);
    assert(std::get<2>(t1) == "hello");
    std::cout << "  ✓ Tuple creation and get<N>: ("
              << std::get<0>(t1) << ", "
              << std::get<1>(t1) << ", "
              << std::get<2>(t1) << ")\n";

    // Get by type (when unique)
    assert(std::get<int>(t1) == 42);
    assert(std::get<double>(t1) == 3.14);
    assert(std::get<std::string>(t1) == "hello");
    std::cout << "  ✓ get<Type> works for unique types\n";

    // Modify through get
    std::get<0>(t1) = 100;
    assert(std::get<0>(t1) == 100);
    std::cout << "  ✓ Modification through get: " << std::get<0>(t1) << "\n";
}

// Test make_tuple
void test_make_tuple() {
    std::cout << "\n=== Testing make_tuple ===\n";

    // make_tuple with automatic type deduction
    auto t1 = std::make_tuple(1, 2.5, "test");
    assert(std::get<0>(t1) == 1);
    assert(std::get<1>(t1) == 2.5);
    assert(std::get<2>(t1) == std::string("test"));
    std::cout << "  ✓ make_tuple with type deduction\n";

    // make_tuple with references (copies by default)
    int x = 10;
    auto t2 = std::make_tuple(x, 20);
    x = 99; // Change original
    assert(std::get<0>(t2) == 10); // Tuple has copy
    std::cout << "  ✓ make_tuple creates copies\n";

    // Empty tuple
    auto t3 = std::make_tuple();
    assert(std::tuple_size<decltype(t3)>::value == 0);
    std::cout << "  ✓ Empty tuple works\n";
}

// Test tie
void test_tie() {
    std::cout << "\n=== Testing tie ===\n";

    // Unpack tuple with tie
    std::tuple<int, double, std::string> t(42, 3.14, "world");
    int i;
    double d;
    std::string s;

    std::tie(i, d, s) = t;
    assert(i == 42);
    assert(d == 3.14);
    assert(s == "world");
    std::cout << "  ✓ tie unpacks tuple: i=" << i << ", d=" << d << ", s=" << s << "\n";

    // Use std::ignore to skip elements
    std::tie(i, std::ignore, s) = t;
    assert(i == 42);
    assert(s == "world");
    std::cout << "  ✓ std::ignore skips elements\n";

    // tie creates references to existing variables
    auto ref_tuple = std::tie(i, d, s);
    std::get<0>(ref_tuple) = 100;
    assert(i == 100); // Original variable modified
    std::cout << "  ✓ tie creates reference tuple\n";
}

// Test structured bindings (C++17)
void test_structured_bindings() {
    std::cout << "\n=== Testing structured bindings ===\n";

    std::tuple<int, double, std::string> t(42, 3.14, "test");

    // Structured binding declaration
    auto [i, d, s] = t;
    assert(i == 42);
    assert(d == 3.14);
    assert(s == "test");
    std::cout << "  ✓ Structured bindings: [" << i << ", " << d << ", " << s << "]\n";

    // Reference binding
    auto& [ri, rd, rs] = t;
    ri = 100;
    assert(std::get<0>(t) == 100);
    std::cout << "  ✓ Reference structured bindings modify original\n";
}

// Test tuple_cat
void test_tuple_cat() {
    std::cout << "\n=== Testing tuple_cat ===\n";

    std::tuple<int, double> t1(1, 2.5);
    std::tuple<std::string, char> t2("hello", 'x');

    // Concatenate tuples
    auto combined = std::tuple_cat(t1, t2);
    assert(std::get<0>(combined) == 1);
    assert(std::get<1>(combined) == 2.5);
    assert(std::get<2>(combined) == "hello");
    assert(std::get<3>(combined) == 'x');
    assert(std::tuple_size<decltype(combined)>::value == 4);
    std::cout << "  ✓ tuple_cat combines tuples (size="
              << std::tuple_size<decltype(combined)>::value << ")\n";

    // Concatenate multiple tuples
    std::tuple<bool> t3(true);
    auto triple = std::tuple_cat(t1, t2, t3);
    assert(std::tuple_size<decltype(triple)>::value == 5);
    assert(std::get<4>(triple) == true);
    std::cout << "  ✓ tuple_cat with multiple tuples (size="
              << std::tuple_size<decltype(triple)>::value << ")\n";
}

// Test forward_as_tuple
void test_forward_as_tuple() {
    std::cout << "\n=== Testing forward_as_tuple ===\n";

    int x = 10;
    double y = 2.5;

    // forward_as_tuple creates a tuple of references
    auto refs = std::forward_as_tuple(x, y);
    std::get<0>(refs) = 20;
    assert(x == 20); // Original modified
    std::cout << "  ✓ forward_as_tuple creates references: x=" << x << "\n";

    // Works with temporaries (creates rvalue references)
    auto temp_refs = std::forward_as_tuple(42, 3.14);
    assert(std::get<0>(temp_refs) == 42);
    std::cout << "  ✓ forward_as_tuple with temporaries\n";
}

// Test tuple comparison
void test_tuple_comparison() {
    std::cout << "\n=== Testing tuple comparison ===\n";

    std::tuple<int, double> t1(1, 2.5);
    std::tuple<int, double> t2(1, 2.5);
    std::tuple<int, double> t3(1, 3.0);
    std::tuple<int, double> t4(2, 2.5);

    // Equality
    assert(t1 == t2);
    assert(!(t1 == t3));
    std::cout << "  ✓ Tuple equality works\n";

    // Inequality
    assert(t1 != t3);
    assert(!(t1 != t2));
    std::cout << "  ✓ Tuple inequality works\n";

    // Lexicographic comparison
    assert(t1 < t3);  // 2.5 < 3.0
    assert(t1 < t4);  // 1 < 2
    assert(!(t3 < t1));
    std::cout << "  ✓ Tuple less-than comparison works\n";

    assert(t3 > t1);
    assert(t1 <= t2);
    assert(t3 >= t1);
    std::cout << "  ✓ Tuple comparison operators work\n";
}

// Test tuple_size and tuple_element
void test_tuple_traits() {
    std::cout << "\n=== Testing tuple traits ===\n";

    using MyTuple = std::tuple<int, double, std::string, char>;

    // tuple_size
    constexpr size_t size = std::tuple_size<MyTuple>::value;
    assert(size == 4);
    std::cout << "  ✓ tuple_size: " << size << "\n";

    // tuple_element
    using Type0 = std::tuple_element<0, MyTuple>::type;
    using Type1 = std::tuple_element<1, MyTuple>::type;
    using Type2 = std::tuple_element<2, MyTuple>::type;
    using Type3 = std::tuple_element<3, MyTuple>::type;

    static_assert(std::is_same<Type0, int>::value, "Type0 should be int");
    static_assert(std::is_same<Type1, double>::value, "Type1 should be double");
    static_assert(std::is_same<Type2, std::string>::value, "Type2 should be std::string");
    static_assert(std::is_same<Type3, char>::value, "Type3 should be char");
    std::cout << "  ✓ tuple_element works\n";

    // tuple_element_t (C++14 alias)
    using TypeT0 = std::tuple_element_t<0, MyTuple>;
    static_assert(std::is_same<TypeT0, int>::value, "TypeT0 should be int");
    std::cout << "  ✓ tuple_element_t works\n";
}

// Test swap
void test_swap() {
    std::cout << "\n=== Testing swap ===\n";

    std::tuple<int, std::string> t1(1, "one");
    std::tuple<int, std::string> t2(2, "two");

    // Swap tuples
    std::swap(t1, t2);
    assert(std::get<0>(t1) == 2);
    assert(std::get<1>(t1) == "two");
    assert(std::get<0>(t2) == 1);
    assert(std::get<1>(t2) == "one");
    std::cout << "  ✓ swap works: t1=(" << std::get<0>(t1) << "," << std::get<1>(t1)
              << "), t2=(" << std::get<0>(t2) << "," << std::get<1>(t2) << ")\n";

    // Member swap
    t1.swap(t2);
    assert(std::get<0>(t1) == 1);
    assert(std::get<1>(t1) == "one");
    std::cout << "  ✓ Member swap works\n";
}

// Test apply (C++17)
void test_apply() {
    std::cout << "\n=== Testing apply ===\n";

    // Apply function to tuple elements
    auto sum = [](int a, int b, int c) { return a + b + c; };
    std::tuple<int, int, int> t(10, 20, 30);

    int result = std::apply(sum, t);
    assert(result == 60);
    std::cout << "  ✓ apply with lambda: " << result << "\n";

    // Apply with different function
    auto print_info = [](const std::string& name, int age, double height) {
        return name + " is " + std::to_string(age) + " years old";
    };
    std::tuple<std::string, int, double> person("Alice", 25, 1.65);
    std::string info = std::apply(print_info, person);
    assert(info == "Alice is 25 years old");
    std::cout << "  ✓ apply with complex types: " << info << "\n";
}

// Test make_from_tuple (C++17)
void test_make_from_tuple() {
    std::cout << "\n=== Testing make_from_tuple ===\n";

    // Simple struct
    struct Point {
        int x, y, z;
        Point(int x, int y, int z) : x(x), y(y), z(z) {}
    };

    std::tuple<int, int, int> coords(10, 20, 30);
    Point p = std::make_from_tuple<Point>(coords);
    assert(p.x == 10);
    assert(p.y == 20);
    assert(p.z == 30);
    std::cout << "  ✓ make_from_tuple constructs Point: ("
              << p.x << ", " << p.y << ", " << p.z << ")\n";

    // With std::string
    struct Person {
        std::string name;
        int age;
        Person(std::string n, int a) : name(n), age(a) {}
    };

    std::tuple<std::string, int> data("Bob", 30);
    Person person = std::make_from_tuple<Person>(data);
    assert(person.name == "Bob");
    assert(person.age == 30);
    std::cout << "  ✓ make_from_tuple with string: "
              << person.name << ", " << person.age << "\n";
}

// Test with complex types
void test_complex_types() {
    std::cout << "\n=== Testing complex types ===\n";

    // Tuple of vectors
    std::tuple<std::vector<int>, std::vector<std::string>> t;
    std::get<0>(t).push_back(1);
    std::get<0>(t).push_back(2);
    std::get<1>(t).push_back("a");
    std::get<1>(t).push_back("b");

    assert(std::get<0>(t).size() == 2);
    assert(std::get<1>(t).size() == 2);
    std::cout << "  ✓ Tuple of vectors works\n";

    // Nested tuples
    std::tuple<int, std::tuple<double, std::string>> nested(
        42, std::make_tuple(3.14, "nested")
    );
    assert(std::get<0>(nested) == 42);
    assert(std::get<0>(std::get<1>(nested)) == 3.14);
    assert(std::get<1>(std::get<1>(nested)) == "nested");
    std::cout << "  ✓ Nested tuples work\n";
}

int main() {
    std::cout << "Testing std_module.tuple\n";
    std::cout << "========================\n";

    try {
        test_tuple_basics();
        test_make_tuple();
        test_tie();
        test_structured_bindings();
        test_tuple_cat();
        test_forward_as_tuple();
        test_tuple_comparison();
        test_tuple_traits();
        test_swap();
        test_apply();
        test_make_from_tuple();
        test_complex_types();

        std::cout << "\n✅ All tuple tests passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
