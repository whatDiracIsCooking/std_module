/**
 * @file test_deque.cpp
 * @brief Comprehensive test for std_module.deque (C++20)
 */

import std_module.deque;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string when available
#include <algorithm> // FIXME: Should be import std_module.algorithm when available (for std::equal)

void test_basic_construction() {
    std::cout << "Testing basic construction...\n";

    // Default construction
    std::deque<int> d1;
    assert(d1.empty());
    assert(d1.size() == 0);
    std::cout << "  ✓ Default construction: empty deque\n";

    // Construction with size
    std::deque<int> d2(5);
    assert(d2.size() == 5);
    for (const auto& val : d2) {
        assert(val == 0);
    }
    std::cout << "  ✓ Construction with size: " << d2.size() << " elements\n";

    // Construction with size and value
    std::deque<int> d3(5, 42);
    assert(d3.size() == 5);
    for (const auto& val : d3) {
        assert(val == 42);
    }
    std::cout << "  ✓ Construction with size and value: 5 elements of value 42\n";

    // Initializer list construction
    std::deque<int> d4{1, 2, 3, 4, 5};
    assert(d4.size() == 5);
    assert(d4[0] == 1 && d4[4] == 5);
    std::cout << "  ✓ Initializer list construction: {1, 2, 3, 4, 5}\n";

    // Copy construction
    std::deque<int> d5(d4);
    assert(d5.size() == d4.size());
    assert(d5 == d4);
    std::cout << "  ✓ Copy construction\n";

    // Move construction
    std::deque<int> d6(std::move(d5));
    assert(d6.size() == 5);
    assert(d6 == d4);
    std::cout << "  ✓ Move construction\n";
}

void test_push_pop_operations() {
    std::cout << "\nTesting push/pop operations...\n";

    std::deque<int> d;

    // push_back
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    assert(d.size() == 3);
    assert(d.back() == 3);
    std::cout << "  ✓ push_back: [1, 2, 3]\n";

    // push_front
    d.push_front(0);
    d.push_front(-1);
    assert(d.size() == 5);
    assert(d.front() == -1);
    assert(d.back() == 3);
    std::cout << "  ✓ push_front: [-1, 0, 1, 2, 3]\n";

    // pop_back
    d.pop_back();
    assert(d.size() == 4);
    assert(d.back() == 2);
    std::cout << "  ✓ pop_back: [-1, 0, 1, 2]\n";

    // pop_front
    d.pop_front();
    assert(d.size() == 3);
    assert(d.front() == 0);
    std::cout << "  ✓ pop_front: [0, 1, 2]\n";

    // emplace_back
    d.emplace_back(100);
    assert(d.back() == 100);
    assert(d.size() == 4);
    std::cout << "  ✓ emplace_back: [0, 1, 2, 100]\n";

    // emplace_front
    d.emplace_front(-100);
    assert(d.front() == -100);
    assert(d.size() == 5);
    std::cout << "  ✓ emplace_front: [-100, 0, 1, 2, 100]\n";
}

void test_element_access() {
    std::cout << "\nTesting element access...\n";

    std::deque<int> d{10, 20, 30, 40, 50};

    // operator[]
    assert(d[0] == 10);
    assert(d[2] == 30);
    assert(d[4] == 50);
    std::cout << "  ✓ operator[]: d[0]=" << d[0] << ", d[2]=" << d[2] << ", d[4]=" << d[4] << "\n";

    // at()
    assert(d.at(0) == 10);
    assert(d.at(2) == 30);
    assert(d.at(4) == 50);
    std::cout << "  ✓ at(): d.at(0)=" << d.at(0) << ", d.at(2)=" << d.at(2) << "\n";

    // front() and back()
    assert(d.front() == 10);
    assert(d.back() == 50);
    std::cout << "  ✓ front() and back(): " << d.front() << ", " << d.back() << "\n";

    // Modify via reference
    d[2] = 300;
    assert(d[2] == 300);
    d.front() = 100;
    assert(d[0] == 100);
    std::cout << "  ✓ Modification via reference\n";

    // Test bounds checking with at()
    bool caught_exception = false;
    try {
        d.at(100);
    } catch (const std::out_of_range&) {
        caught_exception = true;
    }
    assert(caught_exception);
    std::cout << "  ✓ at() throws out_of_range for invalid index\n";
}

void test_iterators() {
    std::cout << "\nTesting iterators...\n";

    std::deque<int> d{1, 2, 3, 4, 5};

    // Forward iteration
    int sum = 0;
    for (auto it = d.begin(); it != d.end(); ++it) {
        sum += *it;
    }
    assert(sum == 15);
    std::cout << "  ✓ Forward iteration: sum = " << sum << "\n";

    // Range-based for loop
    sum = 0;
    for (const auto& val : d) {
        sum += val;
    }
    assert(sum == 15);
    std::cout << "  ✓ Range-based for loop: sum = " << sum << "\n";

    // Reverse iteration
    std::deque<int> reversed;
    for (auto it = d.rbegin(); it != d.rend(); ++it) {
        reversed.push_back(*it);
    }
    assert(reversed[0] == 5 && reversed[4] == 1);
    std::cout << "  ✓ Reverse iteration: [5, 4, 3, 2, 1]\n";

    // Const iterators
    const std::deque<int>& const_d = d;
    sum = 0;
    for (auto it = const_d.cbegin(); it != const_d.cend(); ++it) {
        sum += *it;
    }
    assert(sum == 15);
    std::cout << "  ✓ Const iterators: sum = " << sum << "\n";

    // Iterator modification
    for (auto& val : d) {
        val *= 2;
    }
    assert(d[0] == 2 && d[4] == 10);
    std::cout << "  ✓ Iterator modification: [2, 4, 6, 8, 10]\n";
}

void test_capacity() {
    std::cout << "\nTesting capacity operations...\n";

    std::deque<int> d;

    // empty()
    assert(d.empty());
    std::cout << "  ✓ empty() on new deque: true\n";

    d.push_back(1);
    assert(!d.empty());
    assert(d.size() == 1);
    std::cout << "  ✓ After push_back: size = " << d.size() << ", empty = false\n";

    // size()
    for (int i = 2; i <= 10; ++i) {
        d.push_back(i);
    }
    assert(d.size() == 10);
    std::cout << "  ✓ size() after 10 push_back: " << d.size() << "\n";

    // max_size()
    assert(d.max_size() > 0);
    std::cout << "  ✓ max_size(): " << d.max_size() << "\n";

    // shrink_to_fit()
    d.shrink_to_fit();
    assert(d.size() == 10);
    std::cout << "  ✓ shrink_to_fit(): size still " << d.size() << "\n";
}

void test_modifiers() {
    std::cout << "\nTesting modifier operations...\n";

    std::deque<int> d{1, 2, 3, 4, 5};

    // insert() single element
    auto it = d.begin() + 2;
    d.insert(it, 99);
    assert(d.size() == 6);
    assert(d[2] == 99);
    std::cout << "  ✓ insert() single element: [1, 2, 99, 3, 4, 5]\n";

    // insert() multiple elements
    it = d.begin() + 1;
    d.insert(it, 3, 77);
    assert(d.size() == 9);
    assert(d[1] == 77 && d[2] == 77 && d[3] == 77);
    std::cout << "  ✓ insert() 3 copies of 77 at position 1\n";

    // erase() single element
    d.clear();
    d = {1, 2, 3, 4, 5};
    it = d.begin() + 2;
    d.erase(it);
    assert(d.size() == 4);
    assert(d[2] == 4);
    std::cout << "  ✓ erase() element at position 2: [1, 2, 4, 5]\n";

    // erase() range
    it = d.begin() + 1;
    auto it2 = it + 2;
    d.erase(it, it2);
    assert(d.size() == 2);
    assert(d[0] == 1 && d[1] == 5);
    std::cout << "  ✓ erase() range: [1, 5]\n";

    // clear()
    d.clear();
    assert(d.empty());
    assert(d.size() == 0);
    std::cout << "  ✓ clear(): size = 0, empty = true\n";

    // resize()
    d.resize(5);
    assert(d.size() == 5);
    std::cout << "  ✓ resize(5): size = " << d.size() << "\n";

    d.resize(10, 42);
    assert(d.size() == 10);
    assert(d[9] == 42);
    std::cout << "  ✓ resize(10, 42): size = " << d.size() << ", last element = 42\n";

    // swap()
    std::deque<int> d2{100, 200, 300};
    d.swap(d2);
    assert(d.size() == 3);
    assert(d[0] == 100);
    assert(d2.size() == 10);
    std::cout << "  ✓ swap(): sizes swapped\n";
}

void test_comparison_operators() {
    std::cout << "\nTesting comparison operators...\n";

    std::deque<int> d1{1, 2, 3};
    std::deque<int> d2{1, 2, 3};
    std::deque<int> d3{1, 2, 4};
    std::deque<int> d4{1, 2};

    // operator==
    assert(d1 == d2);
    assert(!(d1 == d3));
    std::cout << "  ✓ operator==: [1,2,3] == [1,2,3]\n";

    // operator!=
    assert(d1 != d3);
    assert(!(d1 != d2));
    std::cout << "  ✓ operator!=: [1,2,3] != [1,2,4]\n";

    // operator<
    assert(d1 < d3);
    assert(d4 < d1);
    assert(!(d1 < d2));
    std::cout << "  ✓ operator<: [1,2,3] < [1,2,4]\n";

    // operator<=
    assert(d1 <= d2);
    assert(d1 <= d3);
    std::cout << "  ✓ operator<=\n";

    // operator>
    assert(d3 > d1);
    assert(!(d1 > d2));
    std::cout << "  ✓ operator>: [1,2,4] > [1,2,3]\n";

    // operator>=
    assert(d1 >= d2);
    assert(d3 >= d1);
    std::cout << "  ✓ operator>=\n";
}

void test_with_strings() {
    std::cout << "\nTesting deque with std::string...\n";

    std::deque<std::string> d;
    d.push_back("hello");
    d.push_back("world");
    d.push_front("C++");

    assert(d.size() == 3);
    assert(d[0] == "C++");
    assert(d[1] == "hello");
    assert(d[2] == "world");
    std::cout << "  ✓ String deque: [" << d[0] << ", " << d[1] << ", " << d[2] << "]\n";

    d.emplace_back("modules");
    assert(d.back() == "modules");
    std::cout << "  ✓ emplace_back with string: back = " << d.back() << "\n";

    d.pop_front();
    assert(d.front() == "hello");
    std::cout << "  ✓ After pop_front: front = " << d.front() << "\n";
}

void test_assign() {
    std::cout << "\nTesting assign operations...\n";

    std::deque<int> d;

    // assign with count and value
    d.assign(5, 100);
    assert(d.size() == 5);
    assert(d[0] == 100 && d[4] == 100);
    std::cout << "  ✓ assign(5, 100): 5 elements of value 100\n";

    // assign with iterators
    std::deque<int> source{1, 2, 3, 4, 5};
    d.assign(source.begin(), source.end());
    assert(d.size() == 5);
    assert(d == source);
    std::cout << "  ✓ assign with iterators: [1, 2, 3, 4, 5]\n";

    // assign with initializer list
    d.assign({10, 20, 30});
    assert(d.size() == 3);
    assert(d[0] == 10 && d[1] == 20 && d[2] == 30);
    std::cout << "  ✓ assign with initializer list: [10, 20, 30]\n";
}

void test_emplace() {
    std::cout << "\nTesting emplace operations...\n";

    std::deque<std::string> d{"first", "last"};

    // emplace in the middle
    auto it = d.begin() + 1;
    d.emplace(it, "middle");
    assert(d.size() == 3);
    assert(d[0] == "first");
    assert(d[1] == "middle");
    assert(d[2] == "last");
    std::cout << "  ✓ emplace(): [first, middle, last]\n";

    // emplace with construction arguments
    d.emplace(d.begin(), 5, 'x');
    assert(d.front() == "xxxxx");
    std::cout << "  ✓ emplace with args: front = " << d.front() << "\n";
}

int main() {
    std::cout << "==============================================\n";
    std::cout << "  std_module.deque Comprehensive Test Suite\n";
    std::cout << "==============================================\n\n";

    try {
        test_basic_construction();
        test_push_pop_operations();
        test_element_access();
        test_iterators();
        test_capacity();
        test_modifiers();
        test_comparison_operators();
        test_with_strings();
        test_assign();
        test_emplace();

        std::cout << "\n==============================================\n";
        std::cout << "  ✓ All tests passed successfully!\n";
        std::cout << "==============================================\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\n✗ Test failed with unknown exception\n";
        return 1;
    }
}
