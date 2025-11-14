/**
 * @file test_algorithm.cpp
 * @brief Comprehensive test for std_module.algorithm (C++20)
 */

import std_module.algorithm;
import std_module.vector;
import std_module.iostream;
import std_module.iterator;
import std_module.exception;

// Minimal includes for fundamental types and iterator operators
// Note: C++20 module ADL limitations require these for iterator comparison operators
#include <cstddef>   // For size_t - fundamental type
#include <iterator>  // For iterator operators (__gnu_cxx::__normal_iterator operators)

// Helper function to check assertions (replacement for assert macro)
inline void check(bool condition, const char* message) {
    if (!condition) {
        std::cout << "CHECK FAILED: " << message << "\n";
        std::terminate();
    }
}

// Helper function to print vector
template<typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

void test_non_modifying_operations() {
    std::cout << "Testing non-modifying sequence operations...\n";

    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Test all_of, any_of, none_of
    bool all_positive = std::all_of(vec.begin(), vec.end(), [](int x) { return x > 0; });
    check(all_positive, "all_of failed");
    std::cout << "  ✓ all_of: All elements are positive\n";

    bool any_even = std::any_of(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    check(any_even, "any_of failed");
    std::cout << "  ✓ any_of: Found even number\n";

    bool none_negative = std::none_of(vec.begin(), vec.end(), [](int x) { return x < 0; });
    check(none_negative, "none_of failed");
    std::cout << "  ✓ none_of: No negative numbers\n";

    // Test count and count_if
    int count = std::count(vec.begin(), vec.end(), 5);
    check(count == 1, "count failed");
    std::cout << "  ✓ count: Found 5 once\n";

    int even_count = std::count_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    check(even_count == 5, "count_if failed");
    std::cout << "  ✓ count_if: Found 5 even numbers\n";

    // Test find
    auto it = std::find(vec.begin(), vec.end(), 7);
    check(it != vec.end() && *it == 7, "find failed");
    std::cout << "  ✓ find: Found 7 at position " << (it - vec.begin()) << "\n";

    // Test find_if
    auto it2 = std::find_if(vec.begin(), vec.end(), [](int x) { return x > 8; });
    check(it2 != vec.end() && *it2 == 9, "find_if failed");
    std::cout << "  ✓ find_if: Found first element > 8: " << *it2 << "\n";

    // Test adjacent_find
    std::vector<int> vec2 = {1, 2, 2, 3, 4, 5};
    auto it3 = std::adjacent_find(vec2.begin(), vec2.end());
    check(it3 != vec2.end() && *it3 == 2, "adjacent_find failed");
    std::cout << "  ✓ adjacent_find: Found adjacent duplicate: " << *it3 << "\n";
}

void test_modifying_operations() {
    std::cout << "\nTesting modifying sequence operations...\n";

    // Test copy
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst(5);
    std::copy(src.begin(), src.end(), dst.begin());
    check(dst == src, "copy failed");
    std::cout << "  ✓ copy: ";
    print_vector(dst);
    std::cout << "\n";

    // Test copy_if
    std::vector<int> evens;
    std::copy_if(src.begin(), src.end(), std::back_inserter(evens),
                 [](int x) { return x % 2 == 0; });
    check(evens.size() == 2 && evens[0] == 2 && evens[1] == 4, "copy_if failed");
    std::cout << "  ✓ copy_if (evens): ";
    print_vector(evens);
    std::cout << "\n";

    // Test transform
    std::vector<int> doubled(5);
    std::transform(src.begin(), src.end(), doubled.begin(),
                   [](int x) { return x * 2; });
    check(doubled[0] == 2 && doubled[4] == 10, "transform failed");
    std::cout << "  ✓ transform (doubled): ";
    print_vector(doubled);
    std::cout << "\n";

    // Test fill
    std::vector<int> filled(5);
    std::fill(filled.begin(), filled.end(), 42);
    check(std::all_of(filled.begin(), filled.end(), [](int x) { return x == 42; }), "fill failed");
    std::cout << "  ✓ fill: All elements set to 42\n";

    // Test replace
    std::vector<int> vec = {1, 2, 3, 2, 5};
    std::replace(vec.begin(), vec.end(), 2, 99);
    check(vec[1] == 99 && vec[3] == 99, "replace failed");
    std::cout << "  ✓ replace: Replaced 2 with 99\n";

    // Test remove (doesn't actually remove, returns new end)
    std::vector<int> vec2 = {1, 2, 3, 2, 5, 2};
    auto new_end = std::remove(vec2.begin(), vec2.end(), 2);
    vec2.erase(new_end, vec2.end());
    check(vec2.size() == 3 && vec2[0] == 1 && vec2[1] == 3 && vec2[2] == 5, "remove failed");
    std::cout << "  ✓ remove: Removed all 2s: ";
    print_vector(vec2);
    std::cout << "\n";

    // Test reverse
    std::vector<int> vec3 = {1, 2, 3, 4, 5};
    std::reverse(vec3.begin(), vec3.end());
    check(vec3[0] == 5 && vec3[4] == 1, "reverse failed");
    std::cout << "  ✓ reverse: ";
    print_vector(vec3);
    std::cout << "\n";

    // Test rotate
    std::vector<int> vec4 = {1, 2, 3, 4, 5};
    std::rotate(vec4.begin(), vec4.begin() + 2, vec4.end());
    check(vec4[0] == 3 && vec4[4] == 2, "rotate failed");
    std::cout << "  ✓ rotate: ";
    print_vector(vec4);
    std::cout << "\n";

    // Test unique
    std::vector<int> vec5 = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    auto new_end2 = std::unique(vec5.begin(), vec5.end());
    vec5.erase(new_end2, vec5.end());
    check(vec5.size() == 5, "unique failed");
    std::cout << "  ✓ unique: ";
    print_vector(vec5);
    std::cout << "\n";
}

void test_sorting_operations() {
    std::cout << "\nTesting sorting operations...\n";

    // Test sort
    std::vector<int> vec = {5, 2, 8, 1, 9, 3, 7};
    std::sort(vec.begin(), vec.end());
    check(std::is_sorted(vec.begin(), vec.end()), "sort_heap failed");
    std::cout << "  ✓ sort: ";
    print_vector(vec);
    std::cout << "\n";

    // Test stable_sort (maintains relative order of equal elements)
    std::vector<int> vec2 = {3, 1, 4, 1, 5, 9, 2, 6};
    std::stable_sort(vec2.begin(), vec2.end());
    check(std::is_sorted(vec2.begin(), vec2.end()), "stable_sort failed");
    std::cout << "  ✓ stable_sort: ";
    print_vector(vec2);
    std::cout << "\n";

    // Test partial_sort
    std::vector<int> vec3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::partial_sort(vec3.begin(), vec3.begin() + 3, vec3.end());
    check(vec3[0] == 1 && vec3[1] == 2 && vec3[2] == 3, "partial_sort failed");
    std::cout << "  ✓ partial_sort (first 3): ";
    print_vector(vec3);
    std::cout << "\n";

    // Test is_sorted
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    check(std::is_sorted(sorted.begin(), sorted.end()), "is_sorted failed");
    std::cout << "  ✓ is_sorted: Confirmed vector is sorted\n";

    // Test nth_element
    std::vector<int> vec4 = {3, 1, 4, 1, 5, 9, 2, 6};
    std::nth_element(vec4.begin(), vec4.begin() + 4, vec4.end());
    // After nth_element, vec4[4] contains the 5th smallest element
    std::cout << "  ✓ nth_element: 5th element is " << vec4[4] << "\n";
}

void test_binary_search_operations() {
    std::cout << "\nTesting binary search operations...\n";

    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Test binary_search
    bool found = std::binary_search(vec.begin(), vec.end(), 5);
    check(found, "binary_search failed to find 5");
    std::cout << "  ✓ binary_search: Found 5\n";

    bool not_found = std::binary_search(vec.begin(), vec.end(), 15);
    check(!not_found, "binary_search incorrectly found 15");
    std::cout << "  ✓ binary_search: 15 not found\n";

    // Test lower_bound
    auto it = std::lower_bound(vec.begin(), vec.end(), 5);
    check(it != vec.end() && *it == 5, "lower_bound failed");
    std::cout << "  ✓ lower_bound: Found 5 at position " << (it - vec.begin()) << "\n";

    // Test upper_bound
    auto it2 = std::upper_bound(vec.begin(), vec.end(), 5);
    check(it2 != vec.end() && *it2 == 6, "upper_bound failed");
    std::cout << "  ✓ upper_bound: First element > 5 is " << *it2 << "\n";

    // Test equal_range
    auto range = std::equal_range(vec.begin(), vec.end(), 5);
    check(range.first != vec.end() && *range.first == 5, "equal_range failed");
    std::cout << "  ✓ equal_range: Found range for 5\n";
}

void test_set_operations() {
    std::cout << "\nTesting set operations...\n";

    std::vector<int> set1 = {1, 2, 3, 4, 5};
    std::vector<int> set2 = {3, 4, 5, 6, 7};

    // Test set_union
    std::vector<int> union_result;
    std::set_union(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   std::back_inserter(union_result));
    check(union_result.size() == 7, "set_union failed");
    std::cout << "  ✓ set_union: ";
    print_vector(union_result);
    std::cout << "\n";

    // Test set_intersection
    std::vector<int> intersection_result;
    std::set_intersection(set1.begin(), set1.end(),
                          set2.begin(), set2.end(),
                          std::back_inserter(intersection_result));
    check(intersection_result.size() == 3, "set_intersection failed");
    std::cout << "  ✓ set_intersection: ";
    print_vector(intersection_result);
    std::cout << "\n";

    // Test set_difference
    std::vector<int> diff_result;
    std::set_difference(set1.begin(), set1.end(),
                        set2.begin(), set2.end(),
                        std::back_inserter(diff_result));
    check(diff_result.size() == 2, "set_difference failed");
    std::cout << "  ✓ set_difference: ";
    print_vector(diff_result);
    std::cout << "\n";

    // Test includes
    std::vector<int> subset = {2, 3, 4};
    bool is_subset = std::includes(set1.begin(), set1.end(),
                                    subset.begin(), subset.end());
    check(is_subset, "includes failed");
    std::cout << "  ✓ includes: {2,3,4} is subset of set1\n";

    // Test merge
    std::vector<int> merged;
    std::merge(set1.begin(), set1.end(),
               set2.begin(), set2.end(),
               std::back_inserter(merged));
    check(merged.size() == 10, "merge failed");
    std::cout << "  ✓ merge: ";
    print_vector(merged);
    std::cout << "\n";
}

void test_heap_operations() {
    std::cout << "\nTesting heap operations...\n";

    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};

    // Test make_heap
    std::make_heap(vec.begin(), vec.end());
    check(std::is_heap(vec.begin(), vec.end()), "make_heap failed");
    std::cout << "  ✓ make_heap: Created max heap: ";
    print_vector(vec);
    std::cout << "\n";

    // Test push_heap
    vec.push_back(10);
    std::push_heap(vec.begin(), vec.end());
    check(std::is_heap(vec.begin(), vec.end()), "make_heap failed");
    std::cout << "  ✓ push_heap: Added 10 to heap\n";

    // Test pop_heap
    std::pop_heap(vec.begin(), vec.end());
    int max_val = vec.back();
    vec.pop_back();
    check(max_val == 10, "pop_heap failed");
    std::cout << "  ✓ pop_heap: Removed max element: " << max_val << "\n";

    // Test sort_heap
    std::sort_heap(vec.begin(), vec.end());
    check(std::is_sorted(vec.begin(), vec.end()), "sort_heap failed");
    std::cout << "  ✓ sort_heap: ";
    print_vector(vec);
    std::cout << "\n";
}

void test_minmax_operations() {
    std::cout << "\nTesting min/max operations...\n";

    // Test min and max
    int a = 5, b = 10;
    check(std::min(a, b) == 5, "min failed");
    check(std::max(a, b) == 10, "max failed");
    std::cout << "  ✓ min/max: min(" << a << ", " << b << ") = " << std::min(a, b) << "\n";

    // Test minmax
    auto [min_val, max_val] = std::minmax(a, b);
    check(min_val == 5 && max_val == 10, "minmax failed");
    std::cout << "  ✓ minmax: returns pair (" << min_val << ", " << max_val << ")\n";

    // Test min_element and max_element
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    auto min_it = std::min_element(vec.begin(), vec.end());
    auto max_it = std::max_element(vec.begin(), vec.end());
    check(*min_it == 1 && *max_it == 9, "min_element/max_element failed");
    std::cout << "  ✓ min_element: " << *min_it << ", max_element: " << *max_it << "\n";

    // Test minmax_element
    auto [min_it2, max_it2] = std::minmax_element(vec.begin(), vec.end());
    check(*min_it2 == 1 && *max_it2 == 9, "minmax_element failed");
    std::cout << "  ✓ minmax_element: (" << *min_it2 << ", " << *max_it2 << ")\n";

    // Test clamp
    int value = 15;
    int clamped = std::clamp(value, 0, 10);
    check(clamped == 10, "clamp failed (upper bound)");
    std::cout << "  ✓ clamp: clamp(15, 0, 10) = " << clamped << "\n";

    value = -5;
    clamped = std::clamp(value, 0, 10);
    check(clamped == 0, "clamp failed (lower bound)");
    std::cout << "  ✓ clamp: clamp(-5, 0, 10) = " << clamped << "\n";
}

void test_comparison_operations() {
    std::cout << "\nTesting comparison operations...\n";

    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {1, 2, 3, 4, 5};
    std::vector<int> vec3 = {1, 2, 3, 4, 6};

    // Test equal
    bool are_equal = std::equal(vec1.begin(), vec1.end(), vec2.begin());
    check(are_equal, "equal failed");
    std::cout << "  ✓ equal: vec1 == vec2\n";

    are_equal = std::equal(vec1.begin(), vec1.end(), vec3.begin());
    check(!are_equal, "equal failed (should be not equal)");
    std::cout << "  ✓ equal: vec1 != vec3\n";

    // Test lexicographical_compare
    bool is_less = std::lexicographical_compare(vec1.begin(), vec1.end(),
                                                 vec3.begin(), vec3.end());
    check(is_less, "lexicographical_compare failed");
    std::cout << "  ✓ lexicographical_compare: vec1 < vec3\n";
}

void test_permutation_operations() {
    std::cout << "\nTesting permutation operations...\n";

    std::vector<int> vec = {1, 2, 3};

    // Test is_permutation
    std::vector<int> perm = {3, 1, 2};
    bool is_perm = std::is_permutation(vec.begin(), vec.end(), perm.begin());
    check(is_perm, "is_permutation failed");
    std::cout << "  ✓ is_permutation: {3,1,2} is permutation of {1,2,3}\n";

    // Test next_permutation
    std::cout << "  ✓ next_permutation: Generating all permutations of {1,2,3}:\n";
    int count = 0;
    do {
        std::cout << "    ";
        print_vector(vec);
        std::cout << "\n";
        count++;
    } while (std::next_permutation(vec.begin(), vec.end()));
    check(count == 6, "next_permutation count failed"); // 3! = 6 permutations

    // Test prev_permutation
    std::vector<int> vec2 = {3, 2, 1};
    std::prev_permutation(vec2.begin(), vec2.end());
    check(vec2[0] == 3 && vec2[1] == 1 && vec2[2] == 2, "prev_permutation failed");
    std::cout << "  ✓ prev_permutation: ";
    print_vector(vec2);
    std::cout << "\n";
}

void test_partitioning_operations() {
    std::cout << "\nTesting partitioning operations...\n";

    // Test partition
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto pivot = std::partition(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    std::cout << "  ✓ partition (evens first): ";
    print_vector(vec);
    std::cout << "\n";

    // Test is_partitioned
    bool is_part = std::is_partitioned(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    check(is_part, "is_partitioned failed");
    std::cout << "  ✓ is_partitioned: Vector is partitioned by even/odd\n";

    // Test partition_point
    auto pp = std::partition_point(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    std::cout << "  ✓ partition_point: Partition boundary at position " << (pp - vec.begin()) << "\n";
}

void test_for_each_operations() {
    std::cout << "\nTesting for_each operations...\n";

    std::vector<int> vec = {1, 2, 3, 4, 5};
    int sum = 0;

    // Test for_each
    std::for_each(vec.begin(), vec.end(), [&sum](int x) { sum += x; });
    check(sum == 15, "for_each failed");
    std::cout << "  ✓ for_each: Sum = " << sum << "\n";

    // Test for_each_n
    sum = 0;
    std::for_each_n(vec.begin(), 3, [&sum](int x) { sum += x; });
    check(sum == 6, "for_each_n failed");
    std::cout << "  ✓ for_each_n (first 3): Sum = " << sum << "\n";
}

int main() {
    std::cout << "==============================================\n";
    std::cout << "std_module.algorithm Comprehensive Test Suite\n";
    std::cout << "==============================================\n\n";

    test_non_modifying_operations();
    test_modifying_operations();
    test_sorting_operations();
    test_binary_search_operations();
    test_set_operations();
    test_heap_operations();
    test_minmax_operations();
    test_comparison_operations();
    test_permutation_operations();
    test_partitioning_operations();
    test_for_each_operations();

    std::cout << "\n==============================================\n";
    std::cout << "All tests passed! ✓\n";
    std::cout << "==============================================\n";

    return 0;
}
