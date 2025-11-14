/**
 * @file test_initializer_list.cpp
 * @brief Comprehensive tests for std_module.initializer_list
 */

import std_module.initializer_list;
#include <iostream>
#include <cassert>
#include <vector>
#include <string>

// ==============================================================================
// Test 1: Basic initializer_list construction
// ==============================================================================

void test_basic_construction() {
    std::cout << "\n[Test 1] Basic initializer_list construction\n";

    std::initializer_list<int> list = {1, 2, 3, 4, 5};

    assert(list.size() == 5);
    std::cout << "  ✓ initializer_list size: " << list.size() << "\n";

    assert(*list.begin() == 1);
    std::cout << "  ✓ First element: " << *list.begin() << "\n";
}

// ==============================================================================
// Test 2: Iterating over initializer_list
// ==============================================================================

void test_iteration() {
    std::cout << "\n[Test 2] Iterating over initializer_list\n";

    std::initializer_list<int> list = {10, 20, 30, 40, 50};

    int sum = 0;
    for (auto val : list) {
        sum += val;
    }

    assert(sum == 150);
    std::cout << "  ✓ Sum of elements: " << sum << "\n";

    // Test begin/end
    sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    assert(sum == 150);
    std::cout << "  ✓ Sum using iterators: " << sum << "\n";
}

// ==============================================================================
// Test 3: std::begin and std::end
// ==============================================================================

void test_std_begin_end() {
    std::cout << "\n[Test 3] std::begin and std::end\n";

    std::initializer_list<int> list = {1, 2, 3};

    auto it_begin = std::begin(list);
    auto it_end = std::end(list);

    assert(*it_begin == 1);
    std::cout << "  ✓ std::begin() points to first element\n";

    int count = 0;
    for (auto it = it_begin; it != it_end; ++it) {
        count++;
    }
    assert(count == 3);
    std::cout << "  ✓ std::end() correctly marks end: " << count << " elements\n";
}

// ==============================================================================
// Test 4: Empty initializer_list
// ==============================================================================

void test_empty_list() {
    std::cout << "\n[Test 4] Empty initializer_list\n";

    std::initializer_list<int> list;

    assert(list.size() == 0);
    assert(list.begin() == list.end());
    std::cout << "  ✓ Empty initializer_list has size 0\n";
}

// ==============================================================================
// Test 5: initializer_list with strings
// ==============================================================================

void test_string_initializer_list() {
    std::cout << "\n[Test 5] initializer_list with strings\n";

    std::initializer_list<std::string> list = {"hello", "world", "cpp"};

    assert(list.size() == 3);
    assert(*list.begin() == "hello");
    std::cout << "  ✓ String initializer_list: size = " << list.size() << ", first = \"" << *list.begin() << "\"\n";
}

// ==============================================================================
// Test 6: Passing initializer_list to function
// ==============================================================================

int sum_values(std::initializer_list<int> list) {
    int sum = 0;
    for (auto val : list) {
        sum += val;
    }
    return sum;
}

void test_function_parameter() {
    std::cout << "\n[Test 6] Passing initializer_list to function\n";

    int result = sum_values({1, 2, 3, 4, 5});
    assert(result == 15);
    std::cout << "  ✓ Function with initializer_list parameter: sum = " << result << "\n";

    result = sum_values({10, 20});
    assert(result == 30);
    std::cout << "  ✓ Different initializer_list: sum = " << result << "\n";
}

// ==============================================================================
// Test 7: Using initializer_list with containers
// ==============================================================================

void test_container_construction() {
    std::cout << "\n[Test 7] Using initializer_list with containers\n";

    std::vector<int> vec = {1, 2, 3, 4, 5};
    assert(vec.size() == 5);
    assert(vec[0] == 1);
    std::cout << "  ✓ Vector constructed from initializer_list: size = " << vec.size() << "\n";

    std::vector<std::string> str_vec = {"alpha", "beta", "gamma"};
    assert(str_vec.size() == 3);
    assert(str_vec[1] == "beta");
    std::cout << "  ✓ String vector from initializer_list: size = " << str_vec.size() << "\n";
}

// ==============================================================================
// Test 8: Nested initializer_lists
// ==============================================================================

void test_nested_lists() {
    std::cout << "\n[Test 8] Nested initializer_lists\n";

    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    assert(matrix.size() == 3);
    assert(matrix[0].size() == 3);
    assert(matrix[1][1] == 5);
    std::cout << "  ✓ Nested initializer_lists create 3x3 matrix\n";
    std::cout << "  ✓ Matrix[1][1] = " << matrix[1][1] << "\n";
}

// ==============================================================================
// Test 9: initializer_list size() method
// ==============================================================================

void test_size_method() {
    std::cout << "\n[Test 9] initializer_list size() method\n";

    auto list1 = {1};
    assert(list1.size() == 1);
    std::cout << "  ✓ Single element list: size = " << list1.size() << "\n";

    auto list2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(list2.size() == 10);
    std::cout << "  ✓ Ten element list: size = " << list2.size() << "\n";

    std::initializer_list<int> list3;
    assert(list3.size() == 0);
    std::cout << "  ✓ Empty list: size = " << list3.size() << "\n";
}

// ==============================================================================
// Test 10: Const-correctness
// ==============================================================================

void test_const_correctness() {
    std::cout << "\n[Test 10] Const-correctness\n";

    const std::initializer_list<int> list = {5, 10, 15};

    assert(list.size() == 3);

    int sum = 0;
    for (auto val : list) {
        sum += val;
    }
    assert(sum == 30);
    std::cout << "  ✓ Const initializer_list works correctly: sum = " << sum << "\n";
}

// ==============================================================================
// Test 11: Copy semantics
// ==============================================================================

void test_copy_semantics() {
    std::cout << "\n[Test 11] Copy semantics\n";

    std::initializer_list<int> list1 = {1, 2, 3};
    std::initializer_list<int> list2 = list1;

    assert(list1.size() == list2.size());
    assert(list1.begin() == list2.begin());  // Shallow copy
    std::cout << "  ✓ Copied initializer_list has same size and elements\n";
}

// ==============================================================================
// Test 12: Using with auto
// ==============================================================================

void test_auto_deduction() {
    std::cout << "\n[Test 12] Using with auto\n";

    auto list = {1, 2, 3, 4, 5};
    // Type is std::initializer_list<int>

    assert(list.size() == 5);
    int sum = 0;
    for (auto val : list) {
        sum += val;
    }
    assert(sum == 15);
    std::cout << "  ✓ Auto-deduced initializer_list: size = " << list.size() << ", sum = " << sum << "\n";
}

// ==============================================================================
// Test 13: Range-for loop
// ==============================================================================

void test_range_for() {
    std::cout << "\n[Test 13] Range-for loop\n";

    std::initializer_list<double> list = {1.5, 2.5, 3.5, 4.5};

    double sum = 0.0;
    for (double val : list) {
        sum += val;
    }

    assert(sum == 12.0);
    std::cout << "  ✓ Range-for with doubles: sum = " << sum << "\n";
}

// ==============================================================================
// Main Test Runner
// ==============================================================================

int main() {
    std::cout << "==============================================\n";
    std::cout << "Testing std_module.initializer_list\n";
    std::cout << "==============================================\n";

    try {
        test_basic_construction();
        test_iteration();
        test_std_begin_end();
        test_empty_list();
        test_string_initializer_list();
        test_function_parameter();
        test_container_construction();
        test_nested_lists();
        test_size_method();
        test_const_correctness();
        test_copy_semantics();
        test_auto_deduction();
        test_range_for();

        std::cout << "\n==============================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "==============================================\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
