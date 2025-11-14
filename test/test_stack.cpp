/**
 * @file test_stack.cpp
 * @brief Comprehensive test for std_module.stack (C++20)
 */

import std_module.stack;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string when available
#include <vector>    // For testing stack with different underlying containers

void test_basic_construction() {
    std::cout << "Testing basic construction...\n";

    // Default construction
    std::stack<int> s1;
    assert(s1.empty());
    assert(s1.size() == 0);
    std::cout << "  ✓ Default construction: empty stack\n";

    // Construction with multiple elements
    std::stack<int> s2;
    s2.push(1);
    s2.push(2);
    s2.push(3);
    s2.push(4);
    s2.push(5);
    assert(s2.size() == 5);
    assert(s2.top() == 5);
    std::cout << "  ✓ Construction with elements: size = " << s2.size() << ", top = " << s2.top() << "\n";

    // Copy construction
    std::stack<int> s3(s2);
    assert(s3.size() == s2.size());
    assert(s3.top() == s2.top());
    std::cout << "  ✓ Copy construction\n";

    // Move construction
    std::stack<int> s4(std::move(s3));
    assert(s4.size() == 5);
    assert(s4.top() == 5);
    std::cout << "  ✓ Move construction\n";

    // Copy assignment
    std::stack<int> s5;
    s5 = s2;
    assert(s5.size() == s2.size());
    assert(s5.top() == s2.top());
    std::cout << "  ✓ Copy assignment\n";

    // Move assignment
    std::stack<int> s6;
    s6 = std::move(s4);
    assert(s6.size() == 5);
    assert(s6.top() == 5);
    std::cout << "  ✓ Move assignment\n";

    // Construction with underlying container (using vector)
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::stack<int, std::vector<int>> s7(vec);
    assert(s7.size() == 5);
    assert(s7.top() == 5);
    std::cout << "  ✓ Construction with underlying vector container: size = " << s7.size() << ", top = " << s7.top() << "\n";
}

void test_push_pop_operations() {
    std::cout << "\nTesting push/pop operations...\n";

    std::stack<int> s;

    // push
    s.push(1);
    assert(s.size() == 1);
    assert(s.top() == 1);
    std::cout << "  ✓ push(1): size = " << s.size() << ", top = " << s.top() << "\n";

    s.push(2);
    assert(s.size() == 2);
    assert(s.top() == 2);
    std::cout << "  ✓ push(2): size = " << s.size() << ", top = " << s.top() << "\n";

    s.push(3);
    assert(s.size() == 3);
    assert(s.top() == 3);
    std::cout << "  ✓ push(3): size = " << s.size() << ", top = " << s.top() << "\n";

    // pop
    s.pop();
    assert(s.size() == 2);
    assert(s.top() == 2);
    std::cout << "  ✓ pop(): size = " << s.size() << ", top = " << s.top() << "\n";

    s.pop();
    assert(s.size() == 1);
    assert(s.top() == 1);
    std::cout << "  ✓ pop(): size = " << s.size() << ", top = " << s.top() << "\n";

    s.pop();
    assert(s.size() == 0);
    assert(s.empty());
    std::cout << "  ✓ pop(): size = " << s.size() << ", empty = true\n";
}

void test_emplace() {
    std::cout << "\nTesting emplace...\n";

    std::stack<std::string> s;

    // emplace - construct in-place
    s.emplace("Hello");
    assert(s.size() == 1);
    assert(s.top() == "Hello");
    std::cout << "  ✓ emplace(\"Hello\"): top = " << s.top() << "\n";

    s.emplace("World");
    assert(s.size() == 2);
    assert(s.top() == "World");
    std::cout << "  ✓ emplace(\"World\"): top = " << s.top() << "\n";

    // Test with complex construction
    s.emplace(5, 'x');  // Construct string with 5 'x' characters
    assert(s.size() == 3);
    assert(s.top() == "xxxxx");
    std::cout << "  ✓ emplace(5, 'x'): top = " << s.top() << "\n";
}

void test_capacity() {
    std::cout << "\nTesting capacity functions...\n";

    std::stack<int> s;

    // empty
    assert(s.empty());
    std::cout << "  ✓ empty() on new stack: true\n";

    s.push(1);
    assert(!s.empty());
    std::cout << "  ✓ empty() after push: false\n";

    // size
    assert(s.size() == 1);
    std::cout << "  ✓ size() = " << s.size() << "\n";

    s.push(2);
    s.push(3);
    assert(s.size() == 3);
    std::cout << "  ✓ size() after 3 pushes = " << s.size() << "\n";

    s.pop();
    assert(s.size() == 2);
    std::cout << "  ✓ size() after 1 pop = " << s.size() << "\n";
}

void test_comparison_operators() {
    std::cout << "\nTesting comparison operators...\n";

    std::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    std::stack<int> s2;
    s2.push(1);
    s2.push(2);
    s2.push(3);

    std::stack<int> s3;
    s3.push(1);
    s3.push(2);
    s3.push(4);

    // operator==
    assert(s1 == s2);
    assert(!(s1 == s3));
    std::cout << "  ✓ operator==: s1 == s2, s1 != s3\n";

    // operator!=
    assert(!(s1 != s2));
    assert(s1 != s3);
    std::cout << "  ✓ operator!=: s1 != s3\n";

    // operator<
    assert(s1 < s3);
    assert(!(s3 < s1));
    std::cout << "  ✓ operator<: s1 < s3\n";

    // operator<=
    assert(s1 <= s2);
    assert(s1 <= s3);
    assert(!(s3 <= s1));
    std::cout << "  ✓ operator<=: s1 <= s2, s1 <= s3\n";

    // operator>
    assert(s3 > s1);
    assert(!(s1 > s3));
    std::cout << "  ✓ operator>: s3 > s1\n";

    // operator>=
    assert(s1 >= s2);
    assert(s3 >= s1);
    assert(!(s1 >= s3));
    std::cout << "  ✓ operator>=: s1 >= s2, s3 >= s1\n";
}

void test_swap() {
    std::cout << "\nTesting swap...\n";

    std::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    std::stack<int> s2;
    s2.push(10);
    s2.push(20);

    // Store original values
    auto s1_size_before = s1.size();
    auto s2_size_before = s2.size();
    auto s1_top_before = s1.top();
    auto s2_top_before = s2.top();

    // Swap using std::swap
    std::swap(s1, s2);

    assert(s1.size() == s2_size_before);
    assert(s2.size() == s1_size_before);
    assert(s1.top() == s2_top_before);
    assert(s2.top() == s1_top_before);
    std::cout << "  ✓ std::swap: s1 (size=" << s1.size() << ", top=" << s1.top()
              << ") <-> s2 (size=" << s2.size() << ", top=" << s2.top() << ")\n";

    // Swap back using member swap
    s1.swap(s2);
    assert(s1.size() == s1_size_before);
    assert(s2.size() == s2_size_before);
    assert(s1.top() == s1_top_before);
    assert(s2.top() == s2_top_before);
    std::cout << "  ✓ member swap: restored original values\n";
}

void test_different_underlying_containers() {
    std::cout << "\nTesting with different underlying containers...\n";

    // Default (uses std::deque)
    std::stack<int> s1;
    s1.push(1);
    s1.push(2);
    assert(s1.top() == 2);
    std::cout << "  ✓ stack<int> (default deque): top = " << s1.top() << "\n";

    // Using std::vector
    std::stack<int, std::vector<int>> s2;
    s2.push(1);
    s2.push(2);
    assert(s2.top() == 2);
    std::cout << "  ✓ stack<int, vector<int>>: top = " << s2.top() << "\n";

    // Test with strings
    std::stack<std::string> s3;
    s3.push("First");
    s3.push("Second");
    s3.push("Third");
    assert(s3.top() == "Third");
    std::cout << "  ✓ stack<string>: top = " << s3.top() << "\n";
}

void test_lifo_behavior() {
    std::cout << "\nTesting LIFO (Last-In-First-Out) behavior...\n";

    std::stack<int> s;

    // Push in order 1, 2, 3, 4, 5
    for (int i = 1; i <= 5; ++i) {
        s.push(i);
    }

    std::cout << "  Pushed: 1, 2, 3, 4, 5\n";
    std::cout << "  Popping: ";

    // Pop should give us 5, 4, 3, 2, 1 (reverse order)
    int expected = 5;
    while (!s.empty()) {
        assert(s.top() == expected);
        std::cout << s.top();
        if (expected > 1) std::cout << ", ";
        s.pop();
        expected--;
    }
    std::cout << "\n  ✓ LIFO behavior verified\n";
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "Testing std_module.stack (C++20)\n";
    std::cout << "===========================================\n\n";

    try {
        test_basic_construction();
        test_push_pop_operations();
        test_emplace();
        test_capacity();
        test_comparison_operators();
        test_swap();
        test_different_underlying_containers();
        test_lifo_behavior();

        std::cout << "\n===========================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "===========================================\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\n❌ Test failed with unknown exception\n";
        return 1;
    }
}
