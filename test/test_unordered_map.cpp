/**
 * @file test_unordered_map.cpp
 * @brief Comprehensive tests for std_module.unordered_map
 *
 * Tests all exported symbols from <unordered_map> including:
 * - std::unordered_map container
 * - std::unordered_multimap container
 * - C++20 erase_if helper
 */

import std_module.unordered_map;

#include <iostream>
#include <cassert>
#include <string>
#include <functional>

// Test basic unordered_map operations
void test_basic_unordered_map()
{
    std::cout << "\n=== Testing Basic unordered_map ===\n";

    std::unordered_map<int, std::string> map;

    // Insert elements
    map[1] = "one";
    map[2] = "two";
    map[3] = "three";

    assert(map.size() == 3);
    std::cout << "  ✓ Inserted 3 elements\n";

    // Access elements
    assert(map[1] == "one");
    assert(map[2] == "two");
    assert(map[3] == "three");
    std::cout << "  ✓ Elements accessed correctly\n";

    // Find element
    auto it = map.find(2);
    assert(it != map.end());
    assert(it->second == "two");
    std::cout << "  ✓ find() works correctly\n";

    // Erase element
    map.erase(2);
    assert(map.size() == 2);
    assert(map.find(2) == map.end());
    std::cout << "  ✓ erase() works correctly\n";
}

// Test unordered_map with custom hasher
void test_custom_hasher()
{
    std::cout << "\n=== Testing unordered_map with Custom Hash ===\n";

    struct Point {
        int x, y;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct PointHash {
        std::size_t operator()(const Point& p) const {
            return std::hash<int>{}(p.x) ^ (std::hash<int>{}(p.y) << 1);
        }
    };

    std::unordered_map<Point, std::string, PointHash> point_map;

    Point p1{0, 0};
    Point p2{1, 1};
    Point p3{10, 20};
    point_map[p1] = "origin";
    point_map[p2] = "diagonal";
    point_map[p3] = "somewhere";

    assert(point_map.size() == 3);
    std::cout << "  ✓ Custom hasher works with user-defined types\n";

    assert(point_map[p1] == "origin");
    std::cout << "  ✓ Elements accessible with custom hasher\n";
}

// Test unordered_map iteration
void test_iteration()
{
    std::cout << "\n=== Testing unordered_map Iteration ===\n";

    std::unordered_map<std::string, int> scores = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92}
    };

    int total = 0;
    for (const auto& [name, score] : scores) {
        total += score;
    }

    assert(total == 95 + 87 + 92);
    std::cout << "  ✓ Iteration works correctly, total score: " << total << "\n";

    // Count elements
    int count = 0;
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        count++;
    }
    assert(count == 3);
    std::cout << "  ✓ Iterator-based counting works: " << count << " elements\n";
}

// Test unordered_map with insert and emplace
void test_insert_emplace()
{
    std::cout << "\n=== Testing insert and emplace ===\n";

    std::unordered_map<int, std::string> map;

    // insert
    auto result1 = map.insert({1, "one"});
    auto& [it1, inserted1] = result1;
    assert(inserted1);
    assert(it1->second == "one");
    std::cout << "  ✓ insert() successful\n";

    // Try to insert duplicate
    auto result2 = map.insert({1, "ONE"});
    auto& [it2, inserted2] = result2;
    assert(!inserted2);
    assert(it2->second == "one");  // Original value unchanged
    std::cout << "  ✓ Duplicate insert rejected correctly\n";

    // emplace
    auto result3 = map.emplace(2, "two");
    auto& [it3, inserted3] = result3;
    assert(inserted3);
    assert(it3->second == "two");
    std::cout << "  ✓ emplace() successful\n";

    // try_emplace (C++17)
    auto result4 = map.try_emplace(3, "three");
    auto& [it4, inserted4] = result4;
    assert(inserted4);
    std::cout << "  ✓ try_emplace() successful\n";
}

// Test unordered_multimap
void test_unordered_multimap()
{
    std::cout << "\n=== Testing unordered_multimap ===\n";

    std::unordered_multimap<std::string, int> multimap;

    // Insert multiple values with same key
    multimap.insert({"apple", 1});
    multimap.insert({"apple", 2});
    multimap.insert({"apple", 3});
    multimap.insert({"banana", 4});

    assert(multimap.size() == 4);
    std::cout << "  ✓ Inserted 4 elements (including duplicates)\n";

    // Count elements with key "apple"
    auto count = multimap.count("apple");
    assert(count == 3);
    std::cout << "  ✓ count() found 3 elements with key 'apple'\n";

    // Find all elements with key "apple"
    auto range = multimap.equal_range("apple");
    int sum = 0;
    for (auto it = range.first; it != range.second; ++it) {
        sum += it->second;
    }
    assert(sum == 1 + 2 + 3);
    std::cout << "  ✓ equal_range() found all values: sum = " << sum << "\n";
}

// Test bucket interface
void test_bucket_interface()
{
    std::cout << "\n=== Testing Bucket Interface ===\n";

    std::unordered_map<int, std::string> map = {
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}
    };

    std::cout << "  ✓ Bucket count: " << map.bucket_count() << "\n";
    std::cout << "  ✓ Load factor: " << map.load_factor() << "\n";
    std::cout << "  ✓ Max load factor: " << map.max_load_factor() << "\n";

    // Rehash
    size_t old_bucket_count = map.bucket_count();
    map.rehash(100);
    assert(map.bucket_count() >= 100);
    std::cout << "  ✓ rehash() increased bucket count from " << old_bucket_count
              << " to " << map.bucket_count() << "\n";

    // Elements still accessible after rehash
    assert(map[1] == "one");
    std::cout << "  ✓ Elements still accessible after rehash\n";
}

// Test erase_if (C++20)
void test_erase_if()
{
    std::cout << "\n=== Testing erase_if (C++20) ===\n";

    std::unordered_map<int, std::string> map = {
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"}
    };

    // Erase all elements with even keys
    auto erased = std::erase_if(map, [](const auto& pair) {
        return pair.first % 2 == 0;
    });

    assert(erased == 2);  // Erased 2 and 4
    assert(map.size() == 3);
    assert(map.find(2) == map.end());
    assert(map.find(4) == map.end());
    assert(map.find(1) != map.end());
    assert(map.find(3) != map.end());
    assert(map.find(5) != map.end());

    std::cout << "  ✓ erase_if() removed " << erased << " elements with even keys\n";
    std::cout << "  ✓ Remaining elements: " << map.size() << "\n";
}

// Test contains (C++20)
void test_contains()
{
    std::cout << "\n=== Testing contains (C++20) ===\n";

    std::unordered_map<std::string, int> map = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };

    assert(map.contains("Alice"));
    assert(map.contains("Bob"));
    assert(!map.contains("Dave"));

    std::cout << "  ✓ contains() works correctly\n";
}

// Test clear and empty
void test_clear_empty()
{
    std::cout << "\n=== Testing clear and empty ===\n";

    std::unordered_map<int, int> map = {{1, 1}, {2, 2}, {3, 3}};

    assert(!map.empty());
    assert(map.size() == 3);
    std::cout << "  ✓ Map initially not empty\n";

    map.clear();
    assert(map.empty());
    assert(map.size() == 0);
    std::cout << "  ✓ Map cleared and is now empty\n";
}

// Test swap
void test_swap()
{
    std::cout << "\n=== Testing swap ===\n";

    std::unordered_map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
    std::unordered_map<int, std::string> map2 = {{10, "ten"}, {20, "twenty"}};

    map1.swap(map2);

    assert(map1.size() == 2);
    assert(map2.size() == 2);
    assert(map1[10] == "ten");
    assert(map2[1] == "one");

    std::cout << "  ✓ swap() exchanged contents correctly\n";
}

// Test equality comparison
void test_equality()
{
    std::cout << "\n=== Testing Equality Comparison ===\n";

    std::unordered_map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
    std::unordered_map<int, std::string> map2 = {{1, "one"}, {2, "two"}};
    std::unordered_map<int, std::string> map3 = {{1, "one"}, {3, "three"}};

    assert(map1 == map2);
    assert(map1 != map3);

    std::cout << "  ✓ Equality comparison works correctly\n";
}

int main()
{
    std::cout << "Testing std_module.unordered_map\n";
    std::cout << "=================================\n";

    test_basic_unordered_map();
    test_custom_hasher();
    test_iteration();
    test_insert_emplace();
    test_unordered_multimap();
    test_bucket_interface();
    test_erase_if();
    test_contains();
    test_clear_empty();
    test_swap();
    test_equality();

    std::cout << "\n✓ All unordered_map tests passed!\n";
    return 0;
}
