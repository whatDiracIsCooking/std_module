/**
 * @file test_vector.cpp
 * @brief Comprehensive test for std_module.vector (C++20)
 */

import std_module.vector;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules

// FIXME: The following #includes should be replaced with imports when modules are available:
// #include <string>     -> import std_module.string;
// #include <algorithm>  -> import std_module.algorithm;

void test_basic_construction() {
    std::cout << "Testing basic construction...\n";

    // Default constructor
    std::vector<int> v1;
    assert(v1.empty());
    std::cout << "  ✓ Default constructor: size=" << v1.size() << "\n";

    // Size constructor
    std::vector<int> v2(5);
    assert(v2.size() == 5);
    std::cout << "  ✓ Size constructor: size=" << v2.size() << "\n";

    // Size + value constructor
    std::vector<int> v3(3, 42);
    assert(v3.size() == 3 && v3[0] == 42 && v3[1] == 42 && v3[2] == 42);
    std::cout << "  ✓ Size + value constructor: " << v3[0] << ", " << v3[1] << ", " << v3[2] << "\n";

    // Initializer list
    std::vector<int> v4 = {1, 2, 3, 4, 5};
    assert(v4.size() == 5 && v4[0] == 1 && v4[4] == 5);
    std::cout << "  ✓ Initializer list: size=" << v4.size() << "\n";
}

void test_copy_and_move() {
    std::cout << "\nTesting copy and move operations...\n";

    std::vector<int> v1 = {1, 2, 3};

    // Copy constructor
    std::vector<int> v2(v1);
    assert(v2.size() == 3 && v2[0] == 1);
    std::cout << "  ✓ Copy constructor: size=" << v2.size() << "\n";

    // Copy assignment
    std::vector<int> v3;
    v3 = v1;
    assert(v3.size() == 3 && v3[1] == 2);
    std::cout << "  ✓ Copy assignment: size=" << v3.size() << "\n";

    // Move constructor
    std::vector<int> v4(std::move(v3));
    assert(v4.size() == 3 && v4[2] == 3);
    std::cout << "  ✓ Move constructor: size=" << v4.size() << "\n";

    // Move assignment
    std::vector<int> v5;
    v5 = std::move(v4);
    assert(v5.size() == 3);
    std::cout << "  ✓ Move assignment: size=" << v5.size() << "\n";
}

void test_element_access() {
    std::cout << "\nTesting element access...\n";

    std::vector<int> v = {10, 20, 30, 40, 50};

    // operator[]
    assert(v[0] == 10 && v[4] == 50);
    std::cout << "  ✓ operator[]: v[0]=" << v[0] << ", v[4]=" << v[4] << "\n";

    // at()
    assert(v.at(2) == 30);
    std::cout << "  ✓ at(): v.at(2)=" << v.at(2) << "\n";

    // front() and back()
    assert(v.front() == 10 && v.back() == 50);
    std::cout << "  ✓ front/back: front=" << v.front() << ", back=" << v.back() << "\n";

    // data()
    int* ptr = v.data();
    assert(ptr[0] == 10);
    std::cout << "  ✓ data(): *data()=" << *ptr << "\n";
}

void test_capacity() {
    std::cout << "\nTesting capacity operations...\n";

    std::vector<int> v;

    // empty()
    assert(v.empty());
    std::cout << "  ✓ empty(): " << v.empty() << "\n";

    // size() and max_size()
    v = {1, 2, 3};
    assert(v.size() == 3);
    assert(v.max_size() > 0);
    std::cout << "  ✓ size(): " << v.size() << ", max_size(): " << v.max_size() << "\n";

    // reserve()
    v.reserve(100);
    assert(v.capacity() >= 100);
    std::cout << "  ✓ reserve(100): capacity=" << v.capacity() << "\n";

    // shrink_to_fit()
    v.shrink_to_fit();
    std::cout << "  ✓ shrink_to_fit(): capacity=" << v.capacity() << "\n";
}

void test_modifiers() {
    std::cout << "\nTesting modifiers...\n";

    std::vector<int> v;

    // push_back
    v.push_back(10);
    v.push_back(20);
    assert(v.size() == 2 && v[0] == 10);
    std::cout << "  ✓ push_back: size=" << v.size() << "\n";

    // emplace_back
    v.emplace_back(30);
    assert(v.size() == 3 && v[2] == 30);
    std::cout << "  ✓ emplace_back: size=" << v.size() << "\n";

    // pop_back
    v.pop_back();
    assert(v.size() == 2);
    std::cout << "  ✓ pop_back: size=" << v.size() << "\n";

    // insert
    auto it = v.insert(v.begin() + 1, 15);
    assert(v.size() == 3 && v[1] == 15 && *it == 15);
    std::cout << "  ✓ insert: v[1]=" << v[1] << "\n";

    // emplace
    v.emplace(v.begin(), 5);
    assert(v.size() == 4 && v[0] == 5);
    std::cout << "  ✓ emplace: v[0]=" << v[0] << "\n";

    // erase
    v.erase(v.begin());
    assert(v.size() == 3 && v[0] == 10);
    std::cout << "  ✓ erase: v[0]=" << v[0] << "\n";

    // clear
    v.clear();
    assert(v.empty());
    std::cout << "  ✓ clear: size=" << v.size() << "\n";

    // assign
    v.assign(5, 100);
    assert(v.size() == 5 && v[0] == 100);
    std::cout << "  ✓ assign: size=" << v.size() << ", v[0]=" << v[0] << "\n";

    // resize
    v.resize(3);
    assert(v.size() == 3);
    std::cout << "  ✓ resize(3): size=" << v.size() << "\n";

    v.resize(6, 200);
    assert(v.size() == 6 && v[5] == 200);
    std::cout << "  ✓ resize(6, 200): size=" << v.size() << ", v[5]=" << v[5] << "\n";
}

void test_iterators() {
    std::cout << "\nTesting iterators...\n";

    std::vector<int> v = {1, 2, 3, 4, 5};

    // begin() / end()
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    assert(sum == 15);
    std::cout << "  ✓ begin/end iteration: sum=" << sum << "\n";

    // Range-based for
    sum = 0;
    for (int val : v) {
        sum += val;
    }
    assert(sum == 15);
    std::cout << "  ✓ Range-based for: sum=" << sum << "\n";

    // rbegin() / rend()
    std::vector<int> reversed;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        reversed.push_back(*it);
    }
    assert(reversed[0] == 5 && reversed[4] == 1);
    std::cout << "  ✓ rbegin/rend: reversed[0]=" << reversed[0] << "\n";

    // const iterators
    const std::vector<int>& cv = v;
    sum = 0;
    for (auto it = cv.cbegin(); it != cv.cend(); ++it) {
        sum += *it;
    }
    assert(sum == 15);
    std::cout << "  ✓ const iterators: sum=" << sum << "\n";
}

// FIXME: Commented out - requires import std_module.string
// void test_with_strings() {
//     std::cout << "\nTesting with strings...\n";
//
//     std::vector<std::string> words = {"hello", "world", "C++20", "modules"};
//     assert(words.size() == 4);
//     std::cout << "  ✓ String vector: " << words[0] << " " << words[1] << "\n";
//
//     words.push_back("test");
//     assert(words.size() == 5 && words.back() == "test");
//     std::cout << "  ✓ Push string: back=" << words.back() << "\n";
//
//     words.emplace_back("emplace");
//     assert(words.back() == "emplace");
//     std::cout << "  ✓ Emplace string: back=" << words.back() << "\n";
// }

void test_bool_specialization() {
    std::cout << "\nTesting bool specialization...\n";

    std::vector<bool> flags = {true, false, true, true, false};
    assert(flags.size() == 5);
    assert(flags[0] == true && flags[1] == false);
    std::cout << "  ✓ Bool vector: flags[0]=" << flags[0] << ", flags[1]=" << flags[1] << "\n";

    flags.push_back(true);
    assert(flags.size() == 6);
    std::cout << "  ✓ Push bool: size=" << flags.size() << "\n";

    // flip() - specific to vector<bool>
    flags.flip();
    assert(flags[0] == false && flags[1] == true);
    std::cout << "  ✓ flip(): flags[0]=" << flags[0] << ", flags[1]=" << flags[1] << "\n";
}

// FIXME: Commented out - requires import std_module.algorithm for std::equal
// void test_comparison_operators() {
//     std::cout << "\nTesting comparison operators...\n";
//
//     std::vector<int> v1 = {1, 2, 3};
//     std::vector<int> v2 = {1, 2, 3};
//     std::vector<int> v3 = {1, 2, 4};
//
//     // Note: Comparison operators for containers have known issues with C++20 modules
//     // due to how non-member template operators are exported. For full comparison
//     // operator support, you may need to #include <vector> directly.
//     // This is a known limitation of the current C++20 module implementation.
//
//     // Manual comparison as workaround
//     bool equal = (v1.size() == v2.size()) && std::equal(v1.begin(), v1.end(), v2.begin());
//     bool not_equal = !((v1.size() == v3.size()) && std::equal(v1.begin(), v1.end(), v3.begin()));
//
//     assert(equal);
//     assert(not_equal);
//     std::cout << "  ✓ Vector comparison works (using manual comparison)\n";
//     std::cout << "  ℹ Note: Native comparison operators (==, !=, <, <=, >, >=) may\n";
//     std::cout << "    require #include <vector> when using modules\n";
// }

void test_erase_if() {
    std::cout << "\nTesting std::erase and std::erase_if (C++20)...\n";

    std::vector<int> v = {1, 2, 3, 2, 4, 2, 5};

    // std::erase - remove all occurrences of a value
    auto removed = std::erase(v, 2);
    assert(v.size() == 4 && removed == 3);
    std::cout << "  ✓ std::erase(v, 2): removed " << removed << " elements, size=" << v.size() << "\n";

    // std::erase_if - remove elements matching predicate
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    removed = std::erase_if(v, [](int x) { return x % 2 == 0; });
    assert(v.size() == 5 && removed == 4);
    std::cout << "  ✓ std::erase_if(even): removed " << removed << " elements, size=" << v.size() << "\n";

    // Verify remaining elements are odd
    for (int val : v) {
        assert(val % 2 == 1);
    }
    std::cout << "  ✓ Remaining elements: ";
    for (int val : v) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void test_nested_vectors() {
    std::cout << "\nTesting nested vectors...\n";

    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    assert(matrix.size() == 3);
    assert(matrix[0].size() == 3);
    assert(matrix[1][1] == 5);
    std::cout << "  ✓ 2D vector: matrix[1][1]=" << matrix[1][1] << "\n";

    matrix.push_back({10, 11, 12});
    assert(matrix.size() == 4 && matrix[3][0] == 10);
    std::cout << "  ✓ Push row: matrix[3][0]=" << matrix[3][0] << "\n";
}

void test_swap() {
    std::cout << "\nTesting swap...\n";

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6, 7};

    v1.swap(v2);
    assert(v1.size() == 4 && v1[0] == 4);
    assert(v2.size() == 3 && v2[0] == 1);
    std::cout << "  ✓ Member swap: v1.size()=" << v1.size() << ", v2.size()=" << v2.size() << "\n";

    std::swap(v1, v2);
    assert(v1.size() == 3 && v1[0] == 1);
    assert(v2.size() == 4 && v2[0] == 4);
    std::cout << "  ✓ std::swap: v1.size()=" << v1.size() << ", v2.size()=" << v2.size() << "\n";
}

// FIXME: Commented out - requires import std_module.string and import std_module.algorithm
// struct CustomType {
//     int value;
//     std::string name;
//
//     CustomType(int v, std::string n) : value(v), name(std::move(n)) {}
//
//     bool operator==(const CustomType& other) const {
//         return value == other.value && name == other.name;
//     }
// };
//
// void test_custom_types() {
//     std::cout << "\nTesting with custom types...\n";
//
//     std::vector<CustomType> objects;
//     objects.emplace_back(1, "first");
//     objects.emplace_back(2, "second");
//     objects.push_back(CustomType{3, "third"});
//
//     assert(objects.size() == 3);
//     assert(objects[0].value == 1 && objects[0].name == "first");
//     std::cout << "  ✓ Custom type: objects[0]={" << objects[0].value << ", \"" << objects[0].name << "\"}\n";
//
//     CustomType target{2, "second"};
//     auto it = std::find(objects.begin(), objects.end(), target);
//     assert(it != objects.end() && it->value == 2);
//     std::cout << "  ✓ Find custom type: found at position " << (it - objects.begin()) << "\n";
// }

int main()
{
    std::cout << "=== C++20 std::vector Comprehensive Tests ===\n";
    std::cout << "Note: Some tests commented out pending additional module implementations\n\n";

    try {
        test_basic_construction();
        test_copy_and_move();
        test_element_access();
        test_capacity();
        test_modifiers();
        test_iterators();
        // test_with_strings();           // FIXME: requires import std_module.string
        test_bool_specialization();
        // test_comparison_operators();   // FIXME: requires import std_module.algorithm
        test_erase_if();
        test_nested_vectors();
        test_swap();
        // test_custom_types();           // FIXME: requires import std_module.string and std_module.algorithm

        std::cout << "\n=== All tests passed! ===\n";
        std::cout << "(Note: 3 tests disabled pending module implementations)\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n!!! Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
