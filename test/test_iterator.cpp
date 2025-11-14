/**
 * @file test_iterator.cpp
 * @brief Comprehensive test for std_module.iterator (C++20)
 */

import std_module.iterator;

#include <iostream>   // For test output
#include <cassert>    // For assertions - must be #include (macro)
#include <vector>     // FIXME: Should be import std_module.vector;
#include <list>       // FIXME: Should be import std_module.list;
#include <string>     // FIXME: Should be import std_module.string;
#include <algorithm>  // FIXME: Should be import std_module.algorithm;

void test_iterator_operations() {
    std::cout << "Testing iterator operations...\n";

    std::vector<int> vec = {10, 20, 30, 40, 50};
    auto it = vec.begin();

    // Test std::advance
    std::advance(it, 2);
    assert(*it == 30);
    std::cout << "  ✓ advance(it, 2): " << *it << "\n";

    // Test std::distance
    auto dist = std::distance(vec.begin(), vec.end());
    assert(dist == 5);
    std::cout << "  ✓ distance(begin, end): " << dist << "\n";

    // Test std::next
    auto it2 = std::next(vec.begin(), 3);
    assert(*it2 == 40);
    std::cout << "  ✓ next(begin, 3): " << *it2 << "\n";

    // Test std::prev
    auto it3 = std::prev(vec.end(), 1);
    assert(*it3 == 50);
    std::cout << "  ✓ prev(end, 1): " << *it3 << "\n";

    // Test next with no offset
    auto it4 = std::next(vec.begin());
    assert(*it4 == 20);
    std::cout << "  ✓ next(begin): " << *it4 << "\n";
}

void test_reverse_iterator() {
    std::cout << "\nTesting reverse_iterator...\n";

    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Test reverse_iterator construction
    std::reverse_iterator<std::vector<int>::iterator> rit(vec.end());
    assert(*rit == 5);
    std::cout << "  ✓ reverse_iterator construction: " << *rit << "\n";

    // Test make_reverse_iterator
    auto rit2 = std::make_reverse_iterator(vec.end());
    assert(*rit2 == 5);
    std::cout << "  ✓ make_reverse_iterator: " << *rit2 << "\n";

    // Test reverse iteration
    std::vector<int> reversed;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        reversed.push_back(*it);
    }
    assert(reversed[0] == 5 && reversed[4] == 1);
    std::cout << "  ✓ reverse iteration: [";
    for (size_t i = 0; i < reversed.size(); ++i) {
        std::cout << reversed[i];
        if (i < reversed.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

void test_move_iterator() {
    std::cout << "\nTesting move_iterator...\n";

    std::vector<std::string> source = {"hello", "world", "test"};
    std::vector<std::string> dest;

    // Test make_move_iterator
    auto move_it = std::make_move_iterator(source.begin());
    dest.push_back(*move_it);

    // Note: After moving, the source string might be empty
    std::cout << "  ✓ make_move_iterator created\n";
    std::cout << "  ✓ moved string: " << dest[0] << "\n";

    // Test move_iterator with range
    std::vector<std::string> source2 = {"alpha", "beta", "gamma"};
    std::vector<std::string> dest2;
    std::copy(std::make_move_iterator(source2.begin()),
              std::make_move_iterator(source2.end()),
              std::back_inserter(dest2));

    assert(dest2.size() == 3);
    std::cout << "  ✓ move_iterator with copy: " << dest2.size() << " elements moved\n";
}

void test_insert_iterators() {
    std::cout << "\nTesting insert iterators...\n";

    // Test back_inserter
    std::vector<int> vec;
    auto back_it = std::back_inserter(vec);
    *back_it = 10;
    *back_it = 20;
    *back_it = 30;
    assert(vec.size() == 3 && vec[0] == 10 && vec[2] == 30);
    std::cout << "  ✓ back_inserter: [10, 20, 30]\n";

    // Test front_inserter
    std::list<int> lst;
    auto front_it = std::front_inserter(lst);
    *front_it = 1;
    *front_it = 2;
    *front_it = 3;
    assert(lst.size() == 3 && lst.front() == 3);
    std::cout << "  ✓ front_inserter: front element is " << lst.front() << "\n";

    // Test inserter
    std::vector<int> vec2 = {1, 2, 5};
    auto ins_it = std::inserter(vec2, vec2.begin() + 2);
    *ins_it = 3;
    *ins_it = 4;
    assert(vec2.size() == 5 && vec2[2] == 3 && vec2[3] == 4);
    std::cout << "  ✓ inserter: inserted [3, 4] at position 2\n";
}

void test_container_access() {
    std::cout << "\nTesting container access functions...\n";

    std::vector<int> vec = {10, 20, 30};

    // Test begin/end
    auto b = std::begin(vec);
    auto e = std::end(vec);
    assert(*b == 10);
    assert(std::distance(b, e) == 3);
    std::cout << "  ✓ begin/end: first element = " << *b << ", distance = " << std::distance(b, e) << "\n";

    // Test cbegin/cend (const iterators)
    auto cb = std::cbegin(vec);
    auto ce = std::cend(vec);
    assert(*cb == 10);
    std::cout << "  ✓ cbegin/cend: first element = " << *cb << "\n";

    // Test rbegin/rend
    auto rb = std::rbegin(vec);
    auto re = std::rend(vec);
    assert(*rb == 30);
    std::cout << "  ✓ rbegin/rend: first element (reversed) = " << *rb << "\n";

    // Test crbegin/crend
    auto crb = std::crbegin(vec);
    auto cre = std::crend(vec);
    assert(*crb == 30);
    std::cout << "  ✓ crbegin/crend: first element (reversed) = " << *crb << "\n";

    // Test with C array
    int arr[] = {5, 6, 7};
    auto arr_b = std::begin(arr);
    auto arr_e = std::end(arr);
    assert(*arr_b == 5);
    assert(std::distance(arr_b, arr_e) == 3);
    std::cout << "  ✓ begin/end with C array: works correctly\n";
}

void test_container_operations() {
    std::cout << "\nTesting container operations...\n";

    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Test size
    auto s = std::size(vec);
    assert(s == 5);
    std::cout << "  ✓ size: " << s << "\n";

    // Test ssize (signed size)
    auto ss = std::ssize(vec);
    assert(ss == 5);
    std::cout << "  ✓ ssize: " << ss << "\n";

    // Test empty
    assert(!std::empty(vec));
    std::vector<int> empty_vec;
    assert(std::empty(empty_vec));
    std::cout << "  ✓ empty: vec is " << (std::empty(vec) ? "empty" : "not empty") << "\n";
    std::cout << "  ✓ empty: empty_vec is " << (std::empty(empty_vec) ? "empty" : "not empty") << "\n";

    // Test data
    int* ptr = std::data(vec);
    assert(ptr[0] == 1);
    std::cout << "  ✓ data: first element via pointer = " << ptr[0] << "\n";

    // Test with C array
    int arr[] = {10, 20, 30};
    assert(std::size(arr) == 3);
    assert(!std::empty(arr));
    std::cout << "  ✓ size/empty work with C arrays\n";
}

void test_iterator_traits() {
    std::cout << "\nTesting iterator traits...\n";

    using VecIter = std::vector<int>::iterator;
    using Traits = std::iterator_traits<VecIter>;

    // Test that traits exist (compilation test mostly)
    std::cout << "  ✓ iterator_traits instantiated for vector iterator\n";

    // Test with pointer
    using PtrTraits = std::iterator_traits<int*>;
    std::cout << "  ✓ iterator_traits instantiated for pointer\n";

    // Verify random access iterator tag
    constexpr bool is_random_access =
        std::is_same_v<Traits::iterator_category, std::random_access_iterator_tag> ||
        std::is_same_v<Traits::iterator_category, std::contiguous_iterator_tag>;
    assert(is_random_access);
    std::cout << "  ✓ vector iterator is random access or contiguous\n";
}

void test_counted_iterator() {
    std::cout << "\nTesting counted_iterator (C++20)...\n";

    std::vector<int> vec = {10, 20, 30, 40, 50};

    // Create counted_iterator
    auto counted = std::counted_iterator(vec.begin(), 3);

    // Test dereferencing
    assert(*counted == 10);
    std::cout << "  ✓ counted_iterator: first element = " << *counted << "\n";

    // Test iteration with count limit
    std::vector<int> result;
    for (auto it = std::counted_iterator(vec.begin(), 3);
         it != std::default_sentinel;
         ++it) {
        result.push_back(*it);
    }
    assert(result.size() == 3);
    assert(result[0] == 10 && result[1] == 20 && result[2] == 30);
    std::cout << "  ✓ counted_iterator iteration: [10, 20, 30]\n";
}

void test_common_iterator() {
    std::cout << "\nTesting common_iterator (C++20)...\n";

    std::vector<int> vec = {5, 10, 15};

    // Create common_iterator to unify iterator and sentinel types
    using Iter = std::vector<int>::iterator;
    using Sent = std::default_sentinel_t;

    std::counted_iterator counted_it(vec.begin(), 2);
    std::common_iterator<std::counted_iterator<Iter>, Sent> common_it(counted_it);
    std::common_iterator<std::counted_iterator<Iter>, Sent> common_end(std::default_sentinel);

    std::cout << "  ✓ common_iterator created successfully\n";

    // Test dereferencing
    assert(*common_it == 5);
    std::cout << "  ✓ common_iterator: first element = " << *common_it << "\n";
}

void test_unreachable_sentinel() {
    std::cout << "\nTesting unreachable_sentinel (C++20)...\n";

    std::vector<int> vec = {1, 2, 3};

    // Test that unreachable_sentinel compiles and is never equal
    auto it = vec.begin();
    assert(it != std::unreachable_sentinel);
    std::cout << "  ✓ unreachable_sentinel: iterator != unreachable_sentinel\n";

    // unreachable_sentinel is used to indicate no bound checking
    std::cout << "  ✓ unreachable_sentinel type available\n";
}

void test_iter_operations() {
    std::cout << "\nTesting C++20 iter operations...\n";

    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {0, 0, 0};

    // Test iter_swap (in ranges namespace)
    auto it1 = vec1.begin();
    auto it2 = vec2.begin();
    std::ranges::iter_swap(it1, it2);
    assert(vec1[0] == 0 && vec2[0] == 1);
    std::cout << "  ✓ ranges::iter_swap: vec1[0] = " << vec1[0] << ", vec2[0] = " << vec2[0] << "\n";

    // Test iter_move (in ranges namespace)
    std::vector<std::string> strings = {"hello"};
    auto moved = std::ranges::iter_move(strings.begin());
    std::cout << "  ✓ ranges::iter_move: moved string = \"" << moved << "\"\n";
}

int main() {
    std::cout << "=== std_module.iterator Comprehensive Test Suite ===\n\n";

    try {
        test_iterator_operations();
        test_reverse_iterator();
        test_move_iterator();
        test_insert_iterators();
        test_container_access();
        test_container_operations();
        test_iterator_traits();
        test_counted_iterator();
        test_common_iterator();
        test_unreachable_sentinel();
        test_iter_operations();

        std::cout << "\n✓ All tests passed successfully!\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cout << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
