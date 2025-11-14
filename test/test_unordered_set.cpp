/**
 * @file test_unordered_set.cpp
 * @brief Comprehensive tests for std_module.unordered_set
 */

import std_module.unordered_set;
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

// Test basic unordered_set operations
void test_basic_operations() {
    std::cout << "\n=== Testing basic operations ===\n";

    // Create unordered_set
    std::unordered_set<int> s;
    assert(s.empty());
    assert(s.size() == 0);
    std::cout << "  ✓ Empty unordered_set created\n";

    // Insert elements
    auto [it1, inserted1] = s.insert(42);
    assert(inserted1);
    assert(*it1 == 42);
    assert(s.size() == 1);
    std::cout << "  ✓ Insert element: 42\n";

    // Insert duplicate (should fail)
    auto [it2, inserted2] = s.insert(42);
    assert(!inserted2);
    assert(s.size() == 1);
    std::cout << "  ✓ Duplicate insert rejected\n";

    // Insert multiple elements
    s.insert(10);
    s.insert(20);
    s.insert(30);
    assert(s.size() == 4);
    std::cout << "  ✓ Multiple inserts: size=" << s.size() << "\n";

    // Check contains (C++20)
    assert(s.contains(42));
    assert(s.contains(10));
    assert(!s.contains(99));
    std::cout << "  ✓ contains() works\n";

    // Find element
    auto it = s.find(20);
    assert(it != s.end());
    assert(*it == 20);
    std::cout << "  ✓ find() works\n";

    // Element not found
    it = s.find(999);
    assert(it == s.end());
    std::cout << "  ✓ find() returns end() for missing element\n";
}

// Test initialization and construction
void test_construction() {
    std::cout << "\n=== Testing construction ===\n";

    // Initializer list
    std::unordered_set<int> s1{1, 2, 3, 4, 5};
    assert(s1.size() == 5);
    std::cout << "  ✓ Initializer list construction: size=" << s1.size() << "\n";

    // Copy constructor
    std::unordered_set<int> s2(s1);
    assert(s2.size() == s1.size());
    assert(s2.contains(1));
    assert(s2.contains(5));
    std::cout << "  ✓ Copy constructor works\n";

    // Move constructor
    std::unordered_set<int> s3(std::move(s2));
    assert(s3.size() == 5);
    // s2 is now in valid but unspecified state
    std::cout << "  ✓ Move constructor works\n";

    // Range constructor
    std::vector<int> vec{10, 20, 30, 40};
    std::unordered_set<int> s4(vec.begin(), vec.end());
    assert(s4.size() == 4);
    assert(s4.contains(10));
    assert(s4.contains(40));
    std::cout << "  ✓ Range constructor works\n";
}

// Test insertion methods
void test_insertion() {
    std::cout << "\n=== Testing insertion ===\n";

    std::unordered_set<std::string> s;

    // Insert single element
    s.insert("hello");
    s.insert("world");
    assert(s.size() == 2);
    std::cout << "  ✓ Single element insertion\n";

    // Insert with hint (ignored in unordered containers, but should work)
    auto it = s.begin();
    s.insert(it, "test");
    assert(s.size() == 3);
    std::cout << "  ✓ Insert with hint\n";

    // Insert range
    std::vector<std::string> words{"foo", "bar", "baz"};
    s.insert(words.begin(), words.end());
    assert(s.size() == 6);
    std::cout << "  ✓ Range insertion: size=" << s.size() << "\n";

    // Insert initializer list
    s.insert({"alpha", "beta", "gamma"});
    assert(s.size() == 9);
    std::cout << "  ✓ Initializer list insertion: size=" << s.size() << "\n";

    // Emplace
    auto [it_emp, inserted] = s.emplace("delta");
    assert(inserted);
    assert(*it_emp == "delta");
    assert(s.size() == 10);
    std::cout << "  ✓ Emplace works\n";

    // Emplace_hint
    s.emplace_hint(s.begin(), "epsilon");
    assert(s.size() == 11);
    std::cout << "  ✓ Emplace_hint works\n";
}

// Test deletion methods
void test_deletion() {
    std::cout << "\n=== Testing deletion ===\n";

    std::unordered_set<int> s{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(s.size() == 10);

    // Erase by key
    size_t erased = s.erase(5);
    assert(erased == 1);
    assert(s.size() == 9);
    assert(!s.contains(5));
    std::cout << "  ✓ Erase by key: removed 5\n";

    // Erase non-existent key
    erased = s.erase(99);
    assert(erased == 0);
    assert(s.size() == 9);
    std::cout << "  ✓ Erase non-existent key returns 0\n";

    // Erase by iterator
    auto it = s.find(3);
    assert(it != s.end());
    it = s.erase(it);
    assert(s.size() == 8);
    assert(!s.contains(3));
    std::cout << "  ✓ Erase by iterator\n";

    // Clear
    s.clear();
    assert(s.empty());
    assert(s.size() == 0);
    std::cout << "  ✓ Clear works\n";
}

// Test iteration
void test_iteration() {
    std::cout << "\n=== Testing iteration ===\n";

    std::unordered_set<int> s{1, 2, 3, 4, 5};

    // Range-based for loop
    int sum = 0;
    for (int x : s) {
        sum += x;
    }
    assert(sum == 15);
    std::cout << "  ✓ Range-based for loop: sum=" << sum << "\n";

    // Iterator loop
    int count = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        count++;
    }
    assert(count == 5);
    std::cout << "  ✓ Iterator loop: count=" << count << "\n";

    // Const iterator
    const std::unordered_set<int>& const_s = s;
    int const_sum = 0;
    for (auto it = const_s.cbegin(); it != const_s.cend(); ++it) {
        const_sum += *it;
    }
    assert(const_sum == 15);
    std::cout << "  ✓ Const iterator works\n";
}

// Test unordered_multiset
void test_multiset() {
    std::cout << "\n=== Testing unordered_multiset ===\n";

    std::unordered_multiset<int> ms;

    // Insert duplicates
    ms.insert(1);
    ms.insert(1);
    ms.insert(1);
    ms.insert(2);
    ms.insert(2);
    assert(ms.size() == 5);
    std::cout << "  ✓ Multiset allows duplicates: size=" << ms.size() << "\n";

    // Count occurrences
    assert(ms.count(1) == 3);
    assert(ms.count(2) == 2);
    assert(ms.count(3) == 0);
    std::cout << "  ✓ count(1)=" << ms.count(1) << ", count(2)=" << ms.count(2) << "\n";

    // Equal range
    auto range = ms.equal_range(1);
    int count = 0;
    for (auto it = range.first; it != range.second; ++it) {
        count++;
        assert(*it == 1);
    }
    assert(count == 3);
    std::cout << "  ✓ equal_range finds all duplicates: " << count << "\n";

    // Erase all occurrences of a key
    size_t erased = ms.erase(1);
    assert(erased == 3);
    assert(ms.size() == 2);
    std::cout << "  ✓ Erase removes all duplicates: " << erased << "\n";
}

// Test hash and equality
void test_hash() {
    std::cout << "\n=== Testing hash ===\n";

    // Hash function for built-in types
    std::hash<int> int_hasher;
    size_t h1 = int_hasher(42);
    size_t h2 = int_hasher(42);
    assert(h1 == h2);
    std::cout << "  ✓ Hash function deterministic: hash(42)=" << h1 << "\n";

    // Different values should (usually) have different hashes
    size_t h3 = int_hasher(43);
    // Note: hash collisions are possible but unlikely for adjacent integers
    std::cout << "  ✓ hash(43)=" << h3 << "\n";

    // String hash
    std::hash<std::string> string_hasher;
    size_t hs1 = string_hasher("hello");
    size_t hs2 = string_hasher("hello");
    assert(hs1 == hs2);
    std::cout << "  ✓ String hash works: hash(\"hello\")=" << hs1 << "\n";
}

// Test capacity and bucket interface
void test_buckets() {
    std::cout << "\n=== Testing buckets ===\n";

    std::unordered_set<int> s{1, 2, 3, 4, 5};

    // Bucket count
    size_t bc = s.bucket_count();
    assert(bc > 0);
    std::cout << "  ✓ bucket_count: " << bc << "\n";

    // Max bucket count
    size_t max_bc = s.max_bucket_count();
    assert(max_bc > bc);
    std::cout << "  ✓ max_bucket_count: " << max_bc << "\n";

    // Bucket size for specific bucket
    for (int val : s) {
        size_t bucket_idx = s.bucket(val);
        assert(bucket_idx < bc);
        size_t bucket_sz = s.bucket_size(bucket_idx);
        assert(bucket_sz > 0);
    }
    std::cout << "  ✓ bucket() and bucket_size() work\n";

    // Load factor
    float lf = s.load_factor();
    assert(lf > 0.0f);
    std::cout << "  ✓ load_factor: " << lf << "\n";

    // Max load factor
    float max_lf = s.max_load_factor();
    assert(max_lf > 0.0f);
    std::cout << "  ✓ max_load_factor: " << max_lf << "\n";

    // Set max load factor
    s.max_load_factor(2.0f);
    assert(s.max_load_factor() == 2.0f);
    std::cout << "  ✓ Set max_load_factor to 2.0\n";

    // Reserve
    s.reserve(100);
    assert(s.bucket_count() >= 100 / s.max_load_factor());
    std::cout << "  ✓ reserve(100): bucket_count=" << s.bucket_count() << "\n";
}

// Test swap
void test_swap() {
    std::cout << "\n=== Testing swap ===\n";

    std::unordered_set<int> s1{1, 2, 3};
    std::unordered_set<int> s2{10, 20, 30, 40};

    // Swap
    std::swap(s1, s2);
    assert(s1.size() == 4);
    assert(s2.size() == 3);
    assert(s1.contains(10));
    assert(s2.contains(1));
    std::cout << "  ✓ swap: s1.size=" << s1.size() << ", s2.size=" << s2.size() << "\n";

    // Member swap
    s1.swap(s2);
    assert(s1.size() == 3);
    assert(s2.size() == 4);
    std::cout << "  ✓ Member swap works\n";
}

// Test erase_if (C++20)
void test_erase_if() {
    std::cout << "\n=== Testing erase_if ===\n";

    std::unordered_set<int> s{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Erase even numbers
    size_t erased = std::erase_if(s, [](int x) { return x % 2 == 0; });
    assert(erased == 5);
    assert(s.size() == 5);
    assert(s.contains(1));
    assert(s.contains(3));
    assert(!s.contains(2));
    assert(!s.contains(4));
    std::cout << "  ✓ erase_if removed " << erased << " even numbers\n";

    // Erase values > 5
    erased = std::erase_if(s, [](int x) { return x > 5; });
    assert(erased == 2); // 7 and 9
    assert(s.size() == 3); // 1, 3, 5
    std::cout << "  ✓ erase_if removed " << erased << " values > 5\n";
}

// Test with custom types
void test_custom_types() {
    std::cout << "\n=== Testing custom types ===\n";

    struct Point {
        int x, y;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    // Custom hash for Point
    struct PointHash {
        size_t operator()(const Point& p) const {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };

    std::unordered_set<Point, PointHash> points;
    points.insert({1, 2});
    points.insert({3, 4});
    points.insert({1, 2}); // Duplicate

    assert(points.size() == 2);
    assert(points.contains({1, 2}));
    assert(points.contains({3, 4}));
    std::cout << "  ✓ Custom type with custom hash: size=" << points.size() << "\n";
}

// Test exception safety
void test_exceptions() {
    std::cout << "\n=== Testing exceptions ===\n";

    std::unordered_set<int> s{1, 2, 3, 4, 5};

    // at() doesn't exist for unordered_set (only for maps)
    // But we can test that operations are exception-safe

    // Copy is exception-safe
    try {
        std::unordered_set<int> s2 = s;
        assert(s2.size() == s.size());
        std::cout << "  ✓ Copy operation is safe\n";
    } catch (...) {
        assert(false); // Should not throw
    }

    std::cout << "  ✓ Basic exception safety verified\n";
}

int main() {
    std::cout << "Testing std_module.unordered_set\n";
    std::cout << "=================================\n";

    try {
        test_basic_operations();
        test_construction();
        test_insertion();
        test_deletion();
        test_iteration();
        test_multiset();
        test_hash();
        test_buckets();
        test_swap();
        test_erase_if();
        test_custom_types();
        test_exceptions();

        std::cout << "\n✅ All unordered_set tests passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
