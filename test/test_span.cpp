/**
 * @file test_span.cpp
 * @brief Comprehensive tests for std_module.span
 *
 * Tests span functionality from the C++20 <span> header.
 */

import std_module.span;
#include <cassert>
#include <cstdio>
#include <vector>
#include <array>

// Test span creation from array
void test_span_from_array()
{
    puts("\n=== Testing span from array ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> s(arr);

    assert(s.size() == 5);
    assert(s[0] == 1);
    assert(s[4] == 5);
    puts("  ✓ span from C array");
}

// Test span creation from std::array
void test_span_from_std_array()
{
    puts("\n=== Testing span from std::array ===");

    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    std::span s(arr);

    assert(s.size() == 5);
    assert(s[0] == 1);
    assert(s[4] == 5);
    puts("  ✓ span from std::array");
}

// Test span creation from std::vector
void test_span_from_vector()
{
    puts("\n=== Testing span from std::vector ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::span<int> s(vec);

    assert(s.size() == 5);
    assert(s[0] == 1);
    assert(s[4] == 5);
    puts("  ✓ span from std::vector");
}

// Test fixed extent span
void test_fixed_extent_span()
{
    puts("\n=== Testing fixed extent span ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span<int, 5> s(arr);

    assert(s.size() == 5);
    assert(s.extent == 5);
    static_assert(s.extent == 5);
    puts("  ✓ fixed extent span");
}

// Test dynamic extent span
void test_dynamic_extent_span()
{
    puts("\n=== Testing dynamic extent span ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span<int, std::dynamic_extent> s(arr);

    assert(s.size() == 5);
    assert(s.extent == std::dynamic_extent);
    static_assert(s.extent == std::dynamic_extent);
    puts("  ✓ dynamic extent span");
}

// Test span element access
void test_span_element_access()
{
    puts("\n=== Testing span element access ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> s(arr);

    // operator[]
    assert(s[0] == 1);
    assert(s[4] == 5);
    puts("  ✓ operator[]");

    // front/back
    assert(s.front() == 1);
    assert(s.back() == 5);
    puts("  ✓ front/back");

    // data
    assert(s.data() == arr);
    puts("  ✓ data");
}

// Test span iterators
void test_span_iterators()
{
    puts("\n=== Testing span iterators ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> s(arr);

    int sum = 0;
    for (int x : s) {
        sum += x;
    }
    assert(sum == 15);
    puts("  ✓ range-based for loop");

    auto it = s.begin();
    assert(*it == 1);
    assert(*(s.end() - 1) == 5);
    puts("  ✓ begin/end");

    auto rit = s.rbegin();
    assert(*rit == 5);
    assert(*(s.rend() - 1) == 1);
    puts("  ✓ rbegin/rend");
}

// Test span subspan operations
void test_span_subspan()
{
    puts("\n=== Testing span subspan operations ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> s(arr);

    // first
    auto first3 = s.first(3);
    assert(first3.size() == 3);
    assert(first3[0] == 1);
    assert(first3[2] == 3);
    puts("  ✓ first(n)");

    // last
    auto last2 = s.last(2);
    assert(last2.size() == 2);
    assert(last2[0] == 4);
    assert(last2[1] == 5);
    puts("  ✓ last(n)");

    // subspan
    auto sub = s.subspan(1, 3);
    assert(sub.size() == 3);
    assert(sub[0] == 2);
    assert(sub[2] == 4);
    puts("  ✓ subspan(offset, count)");
}

// Test span modification through non-const span
void test_span_modification()
{
    puts("\n=== Testing span modification ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> s(arr);

    s[0] = 10;
    s[4] = 50;

    assert(arr[0] == 10);
    assert(arr[4] == 50);
    puts("  ✓ modification through span");
}

// Test const span
void test_const_span()
{
    puts("\n=== Testing const span ===");

    const int arr[] = {1, 2, 3, 4, 5};
    std::span<const int> s(arr);

    assert(s.size() == 5);
    assert(s[0] == 1);
    // s[0] = 10; // This should not compile
    puts("  ✓ const span");
}

// Test empty span
void test_empty_span()
{
    puts("\n=== Testing empty span ===");

    std::span<int> s;

    assert(s.empty());
    assert(s.size() == 0);
    assert(s.data() == nullptr);
    puts("  ✓ empty span");
}

// Test span size operations
void test_span_size()
{
    puts("\n=== Testing span size operations ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> s(arr);

    assert(s.size() == 5);
    assert(s.size_bytes() == 5 * sizeof(int));
    assert(!s.empty());
    puts("  ✓ size/size_bytes/empty");
}

// Test as_bytes
void test_as_bytes()
{
    puts("\n=== Testing as_bytes ===");

    int arr[] = {1, 2, 3};
    std::span<int> s(arr);

    auto bytes = std::as_bytes(s);
    assert(bytes.size() == 3 * sizeof(int));
    puts("  ✓ as_bytes");
}

// Test as_writable_bytes
void test_as_writable_bytes()
{
    puts("\n=== Testing as_writable_bytes ===");

    int arr[] = {1, 2, 3};
    std::span<int> s(arr);

    auto bytes = std::as_writable_bytes(s);
    assert(bytes.size() == 3 * sizeof(int));

    // Modify through byte span
    if (bytes.size() > 0) {
        bytes[0] = std::byte{0xFF};
    }
    puts("  ✓ as_writable_bytes");
}

// Test span deduction guides
void test_span_deduction()
{
    puts("\n=== Testing span deduction guides ===");

    int arr[] = {1, 2, 3, 4, 5};
    std::span s(arr);  // Deduces std::span<int, 5>

    assert(s.size() == 5);
    puts("  ✓ span deduction from array");

    std::vector<int> vec = {1, 2, 3};
    std::span s2(vec);  // Deduces std::span<int>

    assert(s2.size() == 3);
    puts("  ✓ span deduction from vector");
}

int main()
{
    puts("Testing std_module.span...");

    test_span_from_array();
    test_span_from_std_array();
    test_span_from_vector();
    test_fixed_extent_span();
    test_dynamic_extent_span();
    test_span_element_access();
    test_span_iterators();
    test_span_subspan();
    test_span_modification();
    test_const_span();
    test_empty_span();
    test_span_size();
    test_as_bytes();
    test_as_writable_bytes();
    test_span_deduction();

    puts("\n✓ All tests passed!");
    return 0;
}
