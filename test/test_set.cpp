/**
 * @file test_set.cpp
 * @brief Comprehensive tests for std_module.set
 *
 * Tests all exported functionality from <set> including:
 * - std::set operations
 * - std::multiset operations
 * - Custom comparators
 * - All member functions and iterators
 */

import std_module.set;

#include <cassert>
#include <iostream>
#include <string>
#include <functional>

// Custom type for testing
struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Custom comparator for testing
struct GreaterInt {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

void test_basic_set_operations() {
    std::cout << "\nTesting basic set operations...\n";

    // Construction and insertion
    std::set<int> s;
    assert(s.empty());
    assert(s.size() == 0);
    std::cout << "  ✓ Empty set construction\n";

    // Insert elements
    auto [it1, inserted1] = s.insert(42);
    assert(inserted1);
    assert(*it1 == 42);
    assert(s.size() == 1);
    std::cout << "  ✓ Single element insertion\n";

    // Try to insert duplicate
    auto [it2, inserted2] = s.insert(42);
    assert(!inserted2);
    assert(s.size() == 1);
    std::cout << "  ✓ Duplicate rejection (set property)\n";

    // Insert multiple elements
    s.insert(10);
    s.insert(30);
    s.insert(20);
    assert(s.size() == 4);
    std::cout << "  ✓ Multiple element insertion\n";

    // Check ordering (should be 10, 20, 30, 42)
    auto it = s.begin();
    assert(*it == 10); ++it;
    assert(*it == 20); ++it;
    assert(*it == 30); ++it;
    assert(*it == 42);
    std::cout << "  ✓ Automatic ordering\n";
}

void test_set_lookup() {
    std::cout << "\nTesting set lookup operations...\n";

    std::set<int> s = {10, 20, 30, 40, 50};

    // find()
    auto it = s.find(30);
    assert(it != s.end());
    assert(*it == 30);
    std::cout << "  ✓ find() existing element\n";

    it = s.find(99);
    assert(it == s.end());
    std::cout << "  ✓ find() non-existing element\n";

    // count()
    assert(s.count(30) == 1);
    assert(s.count(99) == 0);
    std::cout << "  ✓ count() operation\n";

    // contains() (C++20)
    assert(s.contains(30));
    assert(!s.contains(99));
    std::cout << "  ✓ contains() operation\n";

    // lower_bound()
    it = s.lower_bound(25);
    assert(it != s.end());
    assert(*it == 30);
    std::cout << "  ✓ lower_bound() operation\n";

    // upper_bound()
    it = s.upper_bound(30);
    assert(it != s.end());
    assert(*it == 40);
    std::cout << "  ✓ upper_bound() operation\n";
}

void test_set_modification() {
    std::cout << "\nTesting set modification operations...\n";

    std::set<int> s = {10, 20, 30, 40, 50};

    // erase by value
    size_t erased = s.erase(30);
    assert(erased == 1);
    assert(s.size() == 4);
    assert(s.count(30) == 0);
    std::cout << "  ✓ erase() by value\n";

    // erase by iterator
    auto it = s.find(20);
    assert(it != s.end());
    it = s.erase(it);
    assert(s.size() == 3);
    assert(*it == 40);
    std::cout << "  ✓ erase() by iterator\n";

    // clear()
    s.clear();
    assert(s.empty());
    assert(s.size() == 0);
    std::cout << "  ✓ clear() operation\n";
}

void test_set_emplace() {
    std::cout << "\nTesting set emplace operations...\n";

    std::set<std::string> s;

    // emplace
    auto [it1, inserted1] = s.emplace("hello");
    assert(inserted1);
    assert(*it1 == "hello");
    std::cout << "  ✓ emplace() new element\n";

    auto [it2, inserted2] = s.emplace("hello");
    assert(!inserted2);
    std::cout << "  ✓ emplace() duplicate rejection\n";

    // emplace_hint
    auto hint = s.begin();
    auto it3 = s.emplace_hint(hint, "world");
    assert(*it3 == "world");
    assert(s.size() == 2);
    std::cout << "  ✓ emplace_hint() operation\n";
}

void test_set_iterators() {
    std::cout << "\nTesting set iterators...\n";

    std::set<int> s = {1, 2, 3, 4, 5};

    // Forward iteration
    int sum = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        sum += *it;
    }
    assert(sum == 15);
    std::cout << "  ✓ Forward iteration with begin()/end()\n";

    // Range-based for loop
    sum = 0;
    for (int val : s) {
        sum += val;
    }
    assert(sum == 15);
    std::cout << "  ✓ Range-based for loop\n";

    // Reverse iteration
    sum = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        sum += *it;
    }
    assert(sum == 15);
    std::cout << "  ✓ Reverse iteration with rbegin()/rend()\n";

    // Const iterators
    const std::set<int>& cs = s;
    sum = 0;
    for (auto it = cs.cbegin(); it != cs.cend(); ++it) {
        sum += *it;
    }
    assert(sum == 15);
    std::cout << "  ✓ Const iterators cbegin()/cend()\n";
}

void test_set_comparison() {
    std::cout << "\nTesting set comparison operators...\n";

    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {1, 2, 3};
    std::set<int> s3 = {1, 2, 4};
    std::set<int> s4 = {1, 2};

    // Equality
    assert(s1 == s2);
    assert(!(s1 == s3));
    std::cout << "  ✓ Equality comparison\n";

    // Inequality
    assert(s1 != s3);
    assert(!(s1 != s2));
    std::cout << "  ✓ Inequality comparison\n";

    // Less than
    assert(s1 < s3);
    assert(s4 < s1);
    std::cout << "  ✓ Less-than comparison\n";

    // Less than or equal
    assert(s1 <= s2);
    assert(s1 <= s3);
    std::cout << "  ✓ Less-than-or-equal comparison\n";

    // Greater than
    assert(s3 > s1);
    assert(s1 > s4);
    std::cout << "  ✓ Greater-than comparison\n";

    // Greater than or equal
    assert(s1 >= s2);
    assert(s3 >= s1);
    std::cout << "  ✓ Greater-than-or-equal comparison\n";
}

void test_set_with_custom_comparator() {
    std::cout << "\nTesting set with custom comparator...\n";

    // Set with greater<int> comparator (descending order)
    std::set<int, std::greater<int>> s = {10, 20, 30, 40};

    auto it = s.begin();
    assert(*it == 40); ++it;
    assert(*it == 30); ++it;
    assert(*it == 20); ++it;
    assert(*it == 10);
    std::cout << "  ✓ Set with std::greater<int> comparator\n";

    // Set with custom comparator struct
    std::set<int, GreaterInt> s2;
    s2.insert(10);
    s2.insert(30);
    s2.insert(20);

    auto it2 = s2.begin();
    assert(*it2 == 30); ++it2;
    assert(*it2 == 20); ++it2;
    assert(*it2 == 10);
    std::cout << "  ✓ Set with custom comparator struct\n";
}

void test_set_with_custom_type() {
    std::cout << "\nTesting set with custom type...\n";

    std::set<Point> s;

    s.insert({1, 2});
    s.insert({3, 4});
    s.insert({1, 5});

    assert(s.size() == 3);

    auto it = s.find({3, 4});
    assert(it != s.end());
    assert(it->x == 3 && it->y == 4);
    std::cout << "  ✓ Set with custom Point type\n";

    // Check ordering
    it = s.begin();
    assert(it->x == 1 && it->y == 2); ++it;
    assert(it->x == 1 && it->y == 5); ++it;
    assert(it->x == 3 && it->y == 4);
    std::cout << "  ✓ Custom type ordering\n";
}

void test_multiset_operations() {
    std::cout << "\nTesting multiset operations...\n";

    std::multiset<int> ms;

    // Insert duplicates
    ms.insert(42);
    ms.insert(42);
    ms.insert(42);
    assert(ms.size() == 3);
    assert(ms.count(42) == 3);
    std::cout << "  ✓ multiset allows duplicates\n";

    // Insert more elements
    ms.insert(10);
    ms.insert(10);
    ms.insert(30);
    assert(ms.size() == 6);
    assert(ms.count(10) == 2);
    assert(ms.count(30) == 1);
    std::cout << "  ✓ multiset insertion\n";

    // Check ordering (duplicates together)
    auto it = ms.begin();
    assert(*it == 10); ++it;
    assert(*it == 10); ++it;
    assert(*it == 30); ++it;
    assert(*it == 42); ++it;
    assert(*it == 42); ++it;
    assert(*it == 42);
    std::cout << "  ✓ multiset ordering with duplicates\n";

    // erase one occurrence
    it = ms.find(42);
    ms.erase(it);
    assert(ms.count(42) == 2);
    std::cout << "  ✓ erase single occurrence by iterator\n";

    // erase all occurrences
    size_t erased = ms.erase(42);
    assert(erased == 2);
    assert(ms.count(42) == 0);
    std::cout << "  ✓ erase all occurrences by value\n";
}

void test_multiset_equal_range() {
    std::cout << "\nTesting multiset equal_range...\n";

    std::multiset<int> ms = {10, 20, 20, 20, 30, 40};

    auto [first, last] = ms.equal_range(20);

    size_t count = 0;
    for (auto it = first; it != last; ++it) {
        assert(*it == 20);
        ++count;
    }
    assert(count == 3);
    std::cout << "  ✓ equal_range() finds all duplicates\n";

    auto [first2, last2] = ms.equal_range(99);
    assert(first2 == last2);
    std::cout << "  ✓ equal_range() for non-existing element\n";
}

void test_set_initialization() {
    std::cout << "\nTesting set initialization methods...\n";

    // Initializer list
    std::set<int> s1 = {5, 3, 1, 4, 2};
    assert(s1.size() == 5);
    assert(*s1.begin() == 1);
    std::cout << "  ✓ Initializer list construction\n";

    // Copy constructor
    std::set<int> s2(s1);
    assert(s2 == s1);
    assert(s2.size() == 5);
    std::cout << "  ✓ Copy constructor\n";

    // Range constructor
    int arr[] = {10, 20, 30, 40};
    std::set<int> s3(arr, arr + 4);
    assert(s3.size() == 4);
    assert(s3.contains(20));
    std::cout << "  ✓ Range constructor\n";

    // Assignment
    std::set<int> s4;
    s4 = s1;
    assert(s4 == s1);
    std::cout << "  ✓ Copy assignment\n";
}

void test_set_swap() {
    std::cout << "\nTesting set swap...\n";

    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {10, 20, 30, 40};

    s1.swap(s2);

    assert(s1.size() == 4);
    assert(s2.size() == 3);
    assert(s1.contains(10));
    assert(s2.contains(1));
    std::cout << "  ✓ swap() member function\n";

    std::swap(s1, s2);
    assert(s1.size() == 3);
    assert(s2.size() == 4);
    std::cout << "  ✓ std::swap() function\n";
}

void test_set_extract_and_merge() {
    std::cout << "\nTesting set extract and merge (C++17)...\n";

    std::set<int> s1 = {1, 2, 3, 4, 5};

    // Extract node
    auto node = s1.extract(3);
    assert(s1.size() == 4);
    assert(!s1.contains(3));
    assert(node.value() == 3);
    std::cout << "  ✓ extract() node\n";

    // Modify and reinsert
    node.value() = 30;
    s1.insert(std::move(node));
    assert(s1.size() == 5);
    assert(s1.contains(30));
    std::cout << "  ✓ modify and reinsert node\n";

    // Merge sets
    std::set<int> s2 = {6, 7, 8, 1};  // 1 is duplicate
    s1.merge(s2);
    assert(s1.size() == 8);  // 7 new unique elements
    assert(s2.size() == 1);   // 1 remains in s2 (duplicate)
    assert(s2.contains(1));
    std::cout << "  ✓ merge() operation\n";
}

int main() {
    std::cout << "==================================\n";
    std::cout << "Testing std_module.set\n";
    std::cout << "==================================\n";

    try {
        test_basic_set_operations();
        test_set_lookup();
        test_set_modification();
        test_set_emplace();
        test_set_iterators();
        test_set_comparison();
        test_set_with_custom_comparator();
        test_set_with_custom_type();
        test_multiset_operations();
        test_multiset_equal_range();
        test_set_initialization();
        test_set_swap();
        test_set_extract_and_merge();

        std::cout << "\n==================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "==================================\n";
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
