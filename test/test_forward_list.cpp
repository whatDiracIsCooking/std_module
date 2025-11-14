/**
 * @file test_forward_list.cpp
 * @brief Comprehensive tests for std_module.forward_list
 */

import std_module.forward_list;
#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

// ==============================================================================
// Test 1: Basic construction and element access
// ==============================================================================

void test_basic_construction() {
    std::cout << "\n[Test 1] Basic construction and element access\n";

    // Default construction
    std::forward_list<int> list1;
    assert(list1.empty());
    std::cout << "  ✓ Default construction creates empty forward_list\n";

    // Construction with values
    std::forward_list<int> list2{1, 2, 3, 4, 5};
    assert(!list2.empty());
    assert(list2.front() == 1);
    std::cout << "  ✓ Initializer list construction: front = " << list2.front() << "\n";

    // Construction with count and value
    std::forward_list<int> list3(5, 42);
    assert(list3.front() == 42);
    std::cout << "  ✓ Construction with count and value\n";
}

// ==============================================================================
// Test 2: Iterators
// ==============================================================================

void test_iterators() {
    std::cout << "\n[Test 2] Iterators\n";

    std::forward_list<int> list{10, 20, 30, 40, 50};

    // Test begin/end
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    assert(sum == 150);
    std::cout << "  ✓ begin()/end() iteration: sum = " << sum << "\n";

    // Test range-based for loop
    sum = 0;
    for (int val : list) {
        sum += val;
    }
    assert(sum == 150);
    std::cout << "  ✓ Range-based for loop works correctly\n";

    // Test before_begin
    auto it = list.before_begin();
    ++it;
    assert(*it == 10);
    std::cout << "  ✓ before_begin() points before first element\n";
}

// ==============================================================================
// Test 3: Capacity operations
// ==============================================================================

void test_capacity() {
    std::cout << "\n[Test 3] Capacity operations\n";

    std::forward_list<int> list;
    assert(list.empty());
    std::cout << "  ✓ empty() returns true for default-constructed list\n";

    list.push_front(42);
    assert(!list.empty());
    std::cout << "  ✓ empty() returns false after push_front()\n";

    auto max = list.max_size();
    assert(max > 0);
    std::cout << "  ✓ max_size() = " << max << "\n";
}

// ==============================================================================
// Test 4: Modifiers - push_front, pop_front
// ==============================================================================

void test_push_pop() {
    std::cout << "\n[Test 4] push_front() and pop_front()\n";

    std::forward_list<int> list;

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    assert(list.front() == 1);
    std::cout << "  ✓ push_front(): front = " << list.front() << "\n";

    list.pop_front();
    assert(list.front() == 2);
    std::cout << "  ✓ pop_front(): new front = " << list.front() << "\n";

    list.pop_front();
    assert(list.front() == 3);
    list.pop_front();
    assert(list.empty());
    std::cout << "  ✓ All elements removed with pop_front()\n";
}

// ==============================================================================
// Test 5: insert_after and erase_after
// ==============================================================================

void test_insert_erase_after() {
    std::cout << "\n[Test 5] insert_after() and erase_after()\n";

    std::forward_list<int> list{1, 2, 4, 5};

    // Insert after first element
    auto it = list.begin();
    list.insert_after(it, 99);

    // Check sequence: 1, 99, 2, 4, 5
    it = list.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 99);
    std::cout << "  ✓ insert_after() inserts element correctly\n";

    // Erase the 99
    it = list.begin();
    list.erase_after(it);

    // Check sequence: 1, 2, 4, 5
    it = list.begin();
    ++it;
    assert(*it == 2);
    std::cout << "  ✓ erase_after() removes element correctly\n";

    // Insert multiple elements
    it = list.begin();
    ++it;  // Point to 2
    list.insert_after(it, {10, 11, 12});

    // Sequence: 1, 2, 10, 11, 12, 4, 5
    int count = 0;
    for (auto val : list) {
        count++;
    }
    assert(count == 7);
    std::cout << "  ✓ insert_after() with initializer_list: size = " << count << "\n";
}

// ==============================================================================
// Test 6: clear and resize
// ==============================================================================

void test_clear_resize() {
    std::cout << "\n[Test 6] clear() and resize()\n";

    std::forward_list<int> list{1, 2, 3, 4, 5};

    list.clear();
    assert(list.empty());
    std::cout << "  ✓ clear() empties the list\n";

    list = {1, 2, 3};
    list.resize(5);  // Resize larger

    int count = 0;
    for (auto val : list) {
        count++;
    }
    assert(count == 5);
    std::cout << "  ✓ resize() larger: new size = " << count << "\n";

    list.resize(2);  // Resize smaller
    count = 0;
    for (auto val : list) {
        count++;
    }
    assert(count == 2);
    std::cout << "  ✓ resize() smaller: new size = " << count << "\n";
}

// ==============================================================================
// Test 7: Operations - sort, reverse
// ==============================================================================

void test_sort_reverse() {
    std::cout << "\n[Test 7] sort() and reverse()\n";

    std::forward_list<int> list{5, 2, 8, 1, 9};

    list.sort();
    auto it = list.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    std::cout << "  ✓ sort() orders elements correctly\n";

    list.reverse();
    it = list.begin();
    assert(*it == 9);
    ++it;
    assert(*it == 8);
    std::cout << "  ✓ reverse() reverses element order\n";
}

// ==============================================================================
// Test 8: Operations - unique and remove
// ==============================================================================

void test_unique_remove() {
    std::cout << "\n[Test 8] unique() and remove()\n";

    std::forward_list<int> list{1, 1, 2, 3, 3, 3, 4, 5, 5};

    list.unique();

    int count = 0;
    for (auto val : list) {
        count++;
    }
    assert(count == 5);  // 1, 2, 3, 4, 5
    std::cout << "  ✓ unique() removes consecutive duplicates: size = " << count << "\n";

    list.remove(3);
    count = 0;
    for (auto val : list) {
        count++;
        assert(val != 3);
    }
    assert(count == 4);
    std::cout << "  ✓ remove() removes all instances of value: size = " << count << "\n";
}

// ==============================================================================
// Test 9: remove_if
// ==============================================================================

void test_remove_if() {
    std::cout << "\n[Test 9] remove_if()\n";

    std::forward_list<int> list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Remove even numbers
    list.remove_if([](int n) { return n % 2 == 0; });

    int count = 0;
    for (auto val : list) {
        assert(val % 2 == 1);  // All should be odd
        count++;
    }
    assert(count == 5);
    std::cout << "  ✓ remove_if() removes even numbers: " << count << " odd numbers remain\n";
}

// ==============================================================================
// Test 10: merge
// ==============================================================================

void test_merge() {
    std::cout << "\n[Test 10] merge()\n";

    std::forward_list<int> list1{1, 3, 5, 7};
    std::forward_list<int> list2{2, 4, 6, 8};

    list1.merge(list2);

    assert(list2.empty());
    std::cout << "  ✓ merge() empties source list\n";

    auto it = list1.begin();
    int prev = *it;
    ++it;
    while (it != list1.end()) {
        assert(*it >= prev);  // Should be sorted
        prev = *it;
        ++it;
    }
    std::cout << "  ✓ merge() produces sorted merged list\n";
}

// ==============================================================================
// Test 11: splice_after
// ==============================================================================

void test_splice_after() {
    std::cout << "\n[Test 11] splice_after()\n";

    std::forward_list<int> list1{1, 2, 3};
    std::forward_list<int> list2{10, 20, 30};

    // Splice entire list2 after first element of list1
    auto it = list1.begin();
    list1.splice_after(it, list2);

    assert(list2.empty());
    std::cout << "  ✓ splice_after() empties source list\n";

    // Check sequence: 1, 10, 20, 30, 2, 3
    it = list1.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 10);
    ++it;
    assert(*it == 20);
    std::cout << "  ✓ splice_after() inserts elements correctly\n";
}

// ==============================================================================
// Test 12: Comparison operators
// ==============================================================================

void test_comparison_operators() {
    std::cout << "\n[Test 12] Comparison operators\n";

    std::forward_list<int> list1{1, 2, 3};
    std::forward_list<int> list2{1, 2, 3};
    std::forward_list<int> list3{1, 2, 4};

    assert(list1 == list2);
    std::cout << "  ✓ operator==() works correctly\n";

    assert(list1 != list3);
    std::cout << "  ✓ operator!=() works correctly\n";

    assert(list1 < list3);
    std::cout << "  ✓ operator<() works correctly\n";

    assert(list3 > list1);
    std::cout << "  ✓ operator>() works correctly\n";

    assert(list1 <= list2);
    assert(list1 <= list3);
    std::cout << "  ✓ operator<=() works correctly\n";

    assert(list2 >= list1);
    assert(list3 >= list1);
    std::cout << "  ✓ operator>=() works correctly\n";
}

// ==============================================================================
// Test 13: swap
// ==============================================================================

void test_swap() {
    std::cout << "\n[Test 13] swap()\n";

    std::forward_list<int> list1{1, 2, 3};
    std::forward_list<int> list2{10, 20};

    list1.swap(list2);

    assert(list1.front() == 10);
    assert(list2.front() == 1);
    std::cout << "  ✓ Member swap() exchanges contents\n";

    std::swap(list1, list2);
    assert(list1.front() == 1);
    assert(list2.front() == 10);
    std::cout << "  ✓ std::swap() exchanges contents\n";
}

// ==============================================================================
// Test 14: erase and erase_if (C++20)
// ==============================================================================

void test_erase_functions() {
    std::cout << "\n[Test 14] erase() and erase_if() functions\n";

    std::forward_list<int> list{1, 2, 3, 2, 4, 2, 5};

    auto removed = std::erase(list, 2);
    assert(removed == 3);

    int count = 0;
    for (auto val : list) {
        assert(val != 2);
        count++;
    }
    assert(count == 4);
    std::cout << "  ✓ std::erase() removed " << removed << " elements\n";

    list = {1, 2, 3, 4, 5, 6, 7, 8};
    removed = std::erase_if(list, [](int n) { return n % 2 == 0; });
    assert(removed == 4);
    std::cout << "  ✓ std::erase_if() removed " << removed << " even numbers\n";
}

// ==============================================================================
// Test 15: String forward_list
// ==============================================================================

void test_string_forward_list() {
    std::cout << "\n[Test 15] forward_list with strings\n";

    std::forward_list<std::string> list{"hello", "world", "cpp", "modules"};

    assert(list.front() == "hello");
    std::cout << "  ✓ forward_list<string>: front = \"" << list.front() << "\"\n";

    list.sort();
    assert(list.front() == "cpp");
    std::cout << "  ✓ sort() on strings: front = \"" << list.front() << "\"\n";

    list.remove("world");
    bool found_world = false;
    for (const auto& s : list) {
        if (s == "world") found_world = true;
    }
    assert(!found_world);
    std::cout << "  ✓ remove() works with strings\n";
}

// ==============================================================================
// Main Test Runner
// ==============================================================================

int main() {
    std::cout << "==============================================\n";
    std::cout << "Testing std_module.forward_list\n";
    std::cout << "==============================================\n";

    try {
        test_basic_construction();
        test_iterators();
        test_capacity();
        test_push_pop();
        test_insert_erase_after();
        test_clear_resize();
        test_sort_reverse();
        test_unique_remove();
        test_remove_if();
        test_merge();
        test_splice_after();
        test_comparison_operators();
        test_swap();
        test_erase_functions();
        test_string_forward_list();

        std::cout << "\n==============================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "==============================================\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
