/**
 * @file test_ranges.cpp
 * @brief Comprehensive tests for std_module.ranges
 *
 * Tests range concepts, views, adaptors, and utilities from the C++20 <ranges> header.
 */

import std_module.ranges;
#include <cassert>
#include <cstdio>
#include <vector>
#include <array>
#include <string>

// Test range concepts
void test_range_concepts()
{
    puts("\n=== Testing range concepts ===");

    static_assert(std::ranges::range<std::vector<int>>);
    static_assert(std::ranges::range<std::array<int, 5>>);
    static_assert(std::ranges::range<int[10]>);
    puts("  ✓ range concept");

    static_assert(std::ranges::sized_range<std::vector<int>>);
    static_assert(std::ranges::sized_range<std::array<int, 5>>);
    puts("  ✓ sized_range concept");

    static_assert(std::ranges::forward_range<std::vector<int>>);
    static_assert(std::ranges::bidirectional_range<std::vector<int>>);
    static_assert(std::ranges::random_access_range<std::vector<int>>);
    static_assert(std::ranges::contiguous_range<std::vector<int>>);
    puts("  ✓ iterator category concepts");
}

// Test range access
void test_range_access()
{
    puts("\n=== Testing range access ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};

    auto b = std::ranges::begin(vec);
    auto e = std::ranges::end(vec);
    assert(*b == 1);
    assert(*(e - 1) == 5);
    puts("  ✓ begin/end");

    auto s = std::ranges::size(vec);
    assert(s == 5);
    puts("  ✓ size");

    auto is_empty = std::ranges::empty(vec);
    assert(!is_empty);
    puts("  ✓ empty");

    auto d = std::ranges::data(vec);
    assert(d[0] == 1);
    puts("  ✓ data");
}

// Test subrange
void test_subrange()
{
    puts("\n=== Testing subrange ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::ranges::subrange sr(vec.begin() + 1, vec.begin() + 4);

    assert(std::ranges::size(sr) == 3);
    assert(*std::ranges::begin(sr) == 2);
    puts("  ✓ subrange creation and access");
}

// Test views::all
void test_views_all()
{
    puts("\n=== Testing views::all ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto v = std::ranges::views::all(vec);

    assert(std::ranges::size(v) == 5);
    assert(*std::ranges::begin(v) == 1);
    puts("  ✓ views::all");
}

// Test views::filter
void test_views_filter()
{
    puts("\n=== Testing views::filter ===");

    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    auto even = vec | std::ranges::views::filter([](int x) { return x % 2 == 0; });

    int count = 0;
    for (int x : even) {
        assert(x % 2 == 0);
        count++;
    }
    assert(count == 3);
    puts("  ✓ views::filter");
}

// Test views::transform
void test_views_transform()
{
    puts("\n=== Testing views::transform ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto doubled = vec | std::ranges::views::transform([](int x) { return x * 2; });

    int expected = 2;
    for (int x : doubled) {
        assert(x == expected);
        expected += 2;
    }
    puts("  ✓ views::transform");
}

// Test views::take
void test_views_take()
{
    puts("\n=== Testing views::take ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto first_three = vec | std::ranges::views::take(3);

    int count = 0;
    int expected = 1;
    for (int x : first_three) {
        assert(x == expected);
        expected++;
        count++;
    }
    assert(count == 3);
    puts("  ✓ views::take");
}

// Test views::drop
void test_views_drop()
{
    puts("\n=== Testing views::drop ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto last_two = vec | std::ranges::views::drop(3);

    int count = 0;
    int expected = 4;
    for (int x : last_two) {
        assert(x == expected);
        expected++;
        count++;
    }
    assert(count == 2);
    puts("  ✓ views::drop");
}

// Test views::reverse
void test_views_reverse()
{
    puts("\n=== Testing views::reverse ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto reversed = vec | std::ranges::views::reverse;

    int expected = 5;
    for (int x : reversed) {
        assert(x == expected);
        expected--;
    }
    puts("  ✓ views::reverse");
}

// Test chaining views
void test_view_composition()
{
    puts("\n=== Testing view composition ===");

    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = vec
        | std::ranges::views::filter([](int x) { return x % 2 == 0; })
        | std::ranges::views::transform([](int x) { return x * 3; })
        | std::ranges::views::take(3);

    std::vector<int> expected_values = {6, 12, 18};
    int idx = 0;
    for (int x : result) {
        assert(x == expected_values[idx]);
        idx++;
    }
    assert(idx == 3);
    puts("  ✓ view composition (filter | transform | take)");
}

// Test empty_view
void test_empty_view()
{
    puts("\n=== Testing empty_view ===");

    std::ranges::empty_view<int> ev;
    assert(std::ranges::empty(ev));
    assert(std::ranges::size(ev) == 0);
    puts("  ✓ empty_view");
}

// Test single_view
void test_single_view()
{
    puts("\n=== Testing single_view ===");

    std::ranges::single_view sv(42);
    assert(std::ranges::size(sv) == 1);
    assert(*std::ranges::begin(sv) == 42);
    puts("  ✓ single_view");
}

// Test iota_view
void test_iota_view()
{
    puts("\n=== Testing iota_view ===");

    std::ranges::iota_view iv(1, 6);
    int expected = 1;
    for (int x : iv) {
        assert(x == expected);
        expected++;
    }
    assert(expected == 6);
    puts("  ✓ iota_view");
}

// Test counted
void test_counted()
{
    puts("\n=== Testing views::counted ===");

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto first_three = std::ranges::views::counted(vec.begin(), 3);

    int count = 0;
    int expected = 1;
    for (int x : first_three) {
        assert(x == expected);
        expected++;
        count++;
    }
    assert(count == 3);
    puts("  ✓ views::counted");
}

int main()
{
    puts("Testing std_module.ranges...");

    test_range_concepts();
    test_range_access();
    test_subrange();
    test_views_all();
    test_views_filter();
    test_views_transform();
    test_views_take();
    test_views_drop();
    test_views_reverse();
    test_view_composition();
    test_empty_view();
    test_single_view();
    test_iota_view();
    test_counted();

    puts("\n✓ All tests passed!");
    return 0;
}
