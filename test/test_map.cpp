/**
 * @file test_map.cpp
 * @brief Comprehensive test for std_module.map (C++20)
 */

import std_module.map;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string when available

void test_basic_map() {
    std::cout << "Testing basic map operations...\n";

    // Create a map
    std::map<int, std::string> ages;
    ages[25] = "Alice";
    ages[30] = "Bob";
    ages[20] = "Charlie";

    assert(ages.size() == 3);
    assert(ages[25] == "Alice");
    assert(ages[30] == "Bob");
    std::cout << "  ✓ Basic insertion and access\n";

    // Test ordered property
    auto it = ages.begin();
    assert(it->first == 20);  // Should be sorted by key
    ++it;
    assert(it->first == 25);
    ++it;
    assert(it->first == 30);
    std::cout << "  ✓ Keys are properly ordered\n";
}

void test_map_insert() {
    std::cout << "\nTesting map insert operations...\n";

    std::map<std::string, int> scores;

    // Test insert with pair
    auto result = scores.insert({"Alice", 95});
    assert(result.second == true);  // Insert succeeded
    assert(result.first->first == "Alice");
    assert(result.first->second == 95);
    std::cout << "  ✓ Insert with pair\n";

    // Test duplicate insert (should fail)
    auto result2 = scores.insert({"Alice", 100});
    assert(result2.second == false);  // Insert failed (key exists)
    assert(scores["Alice"] == 95);    // Original value unchanged
    std::cout << "  ✓ Duplicate insert rejected\n";

    // Test insert_or_assign
    auto result3 = scores.insert_or_assign("Bob", 88);
    assert(result3.second == true);  // New insertion
    std::cout << "  ✓ insert_or_assign (new key)\n";

    auto result4 = scores.insert_or_assign("Alice", 98);
    assert(result4.second == false);  // Assignment
    assert(scores["Alice"] == 98);
    std::cout << "  ✓ insert_or_assign (existing key)\n";
}

void test_map_find() {
    std::cout << "\nTesting map find operations...\n";

    std::map<int, std::string> months;
    months[1] = "January";
    months[2] = "February";
    months[12] = "December";

    // Test successful find
    auto it = months.find(2);
    assert(it != months.end());
    assert(it->second == "February");
    std::cout << "  ✓ find() returns valid iterator for existing key\n";

    // Test unsuccessful find
    auto it2 = months.find(13);
    assert(it2 == months.end());
    std::cout << "  ✓ find() returns end() for non-existing key\n";

    // Test contains (C++20)
    assert(months.contains(1) == true);
    assert(months.contains(13) == false);
    std::cout << "  ✓ contains() method\n";

    // Test count
    assert(months.count(1) == 1);
    assert(months.count(13) == 0);
    std::cout << "  ✓ count() method\n";
}

void test_map_erase() {
    std::cout << "\nTesting map erase operations...\n";

    std::map<char, int> letters;
    letters['a'] = 1;
    letters['b'] = 2;
    letters['c'] = 3;
    letters['d'] = 4;

    // Erase by key
    auto count = letters.erase('b');
    assert(count == 1);
    assert(letters.size() == 3);
    assert(letters.find('b') == letters.end());
    std::cout << "  ✓ Erase by key\n";

    // Erase by iterator
    auto it = letters.find('c');
    letters.erase(it);
    assert(letters.size() == 2);
    assert(letters.find('c') == letters.end());
    std::cout << "  ✓ Erase by iterator\n";

    // Clear all
    letters.clear();
    assert(letters.empty());
    assert(letters.size() == 0);
    std::cout << "  ✓ clear() empties the map\n";
}

void test_map_iteration() {
    std::cout << "\nTesting map iteration...\n";

    std::map<int, std::string> data;
    data[3] = "three";
    data[1] = "one";
    data[2] = "two";

    // Forward iteration
    std::string result;
    for (const auto& [key, value] : data) {
        result += value + " ";
    }
    assert(result == "one two three ");  // Should be in sorted order
    std::cout << "  ✓ Range-based for loop (ordered): " << result << "\n";

    // Iterator access
    auto it = data.begin();
    assert(it->first == 1);
    assert(it->second == "one");
    std::cout << "  ✓ Iterator dereferencing\n";

    // Reverse iteration
    std::string reverse_result;
    for (auto rit = data.rbegin(); rit != data.rend(); ++rit) {
        reverse_result += rit->second + " ";
    }
    assert(reverse_result == "three two one ");
    std::cout << "  ✓ Reverse iteration: " << reverse_result << "\n";
}

void test_map_emplace() {
    std::cout << "\nTesting map emplace operations...\n";

    std::map<std::string, std::string> contacts;

    // Test emplace
    auto result = contacts.emplace("Alice", "alice@example.com");
    assert(result.second == true);
    assert(result.first->first == "Alice");
    std::cout << "  ✓ emplace() for new key\n";

    // Test emplace hint
    auto hint = contacts.end();
    auto it = contacts.emplace_hint(hint, "Bob", "bob@example.com");
    assert(it->first == "Bob");
    std::cout << "  ✓ emplace_hint()\n";

    // Test try_emplace
    auto result2 = contacts.try_emplace("Charlie", "charlie@example.com");
    assert(result2.second == true);
    std::cout << "  ✓ try_emplace() for new key\n";

    // try_emplace with existing key (should not modify)
    auto result3 = contacts.try_emplace("Alice", "newemail@example.com");
    assert(result3.second == false);
    assert(contacts["Alice"] == "alice@example.com");  // Original value
    std::cout << "  ✓ try_emplace() preserves existing value\n";
}

void test_map_bounds() {
    std::cout << "\nTesting map bound operations...\n";

    std::map<int, char> data;
    data[10] = 'a';
    data[20] = 'b';
    data[30] = 'c';
    data[40] = 'd';

    // lower_bound
    auto lb = data.lower_bound(25);
    assert(lb->first == 30);
    std::cout << "  ✓ lower_bound(25) -> 30\n";

    // upper_bound
    auto ub = data.upper_bound(30);
    assert(ub->first == 40);
    std::cout << "  ✓ upper_bound(30) -> 40\n";

    // equal_range
    auto range = data.equal_range(20);
    assert(range.first->first == 20);
    assert(range.second->first == 30);
    std::cout << "  ✓ equal_range(20) -> [20, 30)\n";
}

void test_multimap() {
    std::cout << "\nTesting multimap (duplicate keys allowed)...\n";

    std::multimap<std::string, int> grades;
    grades.insert({"Alice", 95});
    grades.insert({"Bob", 88});
    grades.insert({"Alice", 92});  // Duplicate key allowed
    grades.insert({"Alice", 98});

    assert(grades.size() == 4);
    assert(grades.count("Alice") == 3);
    std::cout << "  ✓ Multiple values for same key\n";

    // Find all values for a key
    auto range = grades.equal_range("Alice");
    int sum = 0;
    int count = 0;
    for (auto it = range.first; it != range.second; ++it) {
        sum += it->second;
        count++;
    }
    assert(count == 3);
    assert(sum == 95 + 92 + 98);
    std::cout << "  ✓ equal_range() retrieves all values for key\n";
    std::cout << "  ✓ Alice's grades: 95, 92, 98 (avg: " << sum/count << ")\n";
}

void test_map_comparison() {
    std::cout << "\nTesting map comparison operations...\n";

    std::map<int, std::string> map1;
    map1[1] = "one";
    map1[2] = "two";

    std::map<int, std::string> map2;
    map2[1] = "one";
    map2[2] = "two";

    std::map<int, std::string> map3;
    map3[1] = "one";
    map3[3] = "three";

    assert(map1 == map2);
    assert(map1 != map3);
    std::cout << "  ✓ Map equality comparison\n";

    assert(map1 < map3);  // Lexicographic comparison
    std::cout << "  ✓ Map ordering comparison\n";
}

void test_map_with_custom_comparator() {
    std::cout << "\nTesting map with custom comparator...\n";

    // Map with reverse ordering (greater instead of less)
    std::map<int, std::string, std::greater<int>> reverse_map;
    reverse_map[1] = "one";
    reverse_map[2] = "two";
    reverse_map[3] = "three";

    auto it = reverse_map.begin();
    assert(it->first == 3);  // Should be in reverse order
    ++it;
    assert(it->first == 2);
    ++it;
    assert(it->first == 1);
    std::cout << "  ✓ Custom comparator (descending order)\n";
}

void test_erase_if() {
    std::cout << "\nTesting erase_if (C++20)...\n";

    std::map<int, int> numbers;
    for (int i = 1; i <= 10; ++i) {
        numbers[i] = i * i;
    }

    // Erase all even keys
    auto removed = std::erase_if(numbers, [](const auto& pair) {
        return pair.first % 2 == 0;
    });

    assert(removed == 5);  // Removed 2, 4, 6, 8, 10
    assert(numbers.size() == 5);
    assert(numbers.contains(1) && numbers.contains(3) && numbers.contains(5));
    assert(!numbers.contains(2) && !numbers.contains(4));
    std::cout << "  ✓ erase_if removed " << removed << " elements\n";
}

int main() {
    std::cout << "=== std_module.map Comprehensive Test Suite ===\n\n";

    try {
        test_basic_map();
        test_map_insert();
        test_map_find();
        test_map_erase();
        test_map_iteration();
        test_map_emplace();
        test_map_bounds();
        test_multimap();
        test_map_comparison();
        test_map_with_custom_comparator();
        test_erase_if();

        std::cout << "\n=== All tests passed! ✓ ===\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n=== Test failed with exception: " << e.what() << " ===\n";
        return 1;
    }
}
