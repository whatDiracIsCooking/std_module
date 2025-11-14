/**
 * @file test_numeric.cpp
 * @brief Comprehensive test for std_module.numeric (C++20)
 */

import std_module.numeric;

#include <iostream>  // For output
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <vector>    // FIXME: Should be import std_module.vector when available
#include <functional> // For std::plus, std::multiplies, etc.

void test_accumulate() {
    std::cout << "Testing accumulate...\n";

    std::vector<int> v = {1, 2, 3, 4, 5};

    // Test basic accumulate with default sum
    int sum = std::accumulate(v.begin(), v.end(), 0);
    assert(sum == 15);
    std::cout << "  ✓ Sum: " << sum << "\n";

    // Test accumulate with initial value
    int sum_with_init = std::accumulate(v.begin(), v.end(), 100);
    assert(sum_with_init == 115);
    std::cout << "  ✓ Sum with initial value: " << sum_with_init << "\n";

    // Test accumulate with multiplication
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
    assert(product == 120);
    std::cout << "  ✓ Product: " << product << "\n";

    // Test with floating point
    std::vector<double> vd = {1.5, 2.5, 3.5};
    double sum_double = std::accumulate(vd.begin(), vd.end(), 0.0);
    assert(sum_double == 7.5);
    std::cout << "  ✓ Double sum: " << sum_double << "\n";
}

void test_reduce() {
    std::cout << "\nTesting reduce...\n";

    std::vector<int> v = {1, 2, 3, 4, 5};

    // Test basic reduce (C++17)
    int sum = std::reduce(v.begin(), v.end());
    assert(sum == 15);
    std::cout << "  ✓ Reduce sum: " << sum << "\n";

    // Test reduce with initial value
    int sum_with_init = std::reduce(v.begin(), v.end(), 100);
    assert(sum_with_init == 115);
    std::cout << "  ✓ Reduce with initial value: " << sum_with_init << "\n";

    // Test reduce with binary operation
    int product = std::reduce(v.begin(), v.end(), 1, std::multiplies<int>());
    assert(product == 120);
    std::cout << "  ✓ Reduce product: " << product << "\n";
}

void test_transform_reduce() {
    std::cout << "\nTesting transform_reduce...\n";

    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {2, 3, 4, 5};

    // Test dot product (sum of products)
    int dot_product = std::transform_reduce(v1.begin(), v1.end(), v2.begin(), 0);
    assert(dot_product == 40); // 1*2 + 2*3 + 3*4 + 4*5 = 2 + 6 + 12 + 20 = 40
    std::cout << "  ✓ Dot product: " << dot_product << "\n";

    // Test sum of squares
    auto square = [](int x) { return x * x; };
    int sum_of_squares = std::transform_reduce(v1.begin(), v1.end(), 0, std::plus<>(), square);
    assert(sum_of_squares == 30); // 1 + 4 + 9 + 16 = 30
    std::cout << "  ✓ Sum of squares: " << sum_of_squares << "\n";
}

void test_inner_product() {
    std::cout << "\nTesting inner_product...\n";

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    // Test basic inner product
    int result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);
    assert(result == 32); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    std::cout << "  ✓ Inner product: " << result << "\n";

    // Test with custom operations
    int result2 = std::inner_product(v1.begin(), v1.end(), v2.begin(), 1,
                                      std::multiplies<>(), std::plus<>());
    assert(result2 == 315); // init=1, then: 1 * (1+4) * (2+5) * (3+6) = 1 * 5 * 7 * 9 = 315
    std::cout << "  ✓ Inner product with custom ops: " << result2 << "\n";
}

void test_adjacent_difference() {
    std::cout << "\nTesting adjacent_difference...\n";

    std::vector<int> v = {2, 4, 6, 8, 10};
    std::vector<int> result(v.size());

    // Test basic adjacent_difference
    std::adjacent_difference(v.begin(), v.end(), result.begin());
    assert(result[0] == 2);  // First element is copied
    assert(result[1] == 2);  // 4 - 2 = 2
    assert(result[2] == 2);  // 6 - 4 = 2
    std::cout << "  ✓ Adjacent differences: [" << result[0] << ", " << result[1]
              << ", " << result[2] << ", " << result[3] << ", " << result[4] << "]\n";

    // Test with custom operation
    std::vector<int> result2(v.size());
    std::adjacent_difference(v.begin(), v.end(), result2.begin(), std::plus<>());
    assert(result2[0] == 2);   // First element is copied
    assert(result2[1] == 6);   // 2 + 4 = 6
    assert(result2[2] == 10);  // 4 + 6 = 10
    std::cout << "  ✓ Adjacent sums: [" << result2[0] << ", " << result2[1]
              << ", " << result2[2] << ", " << result2[3] << ", " << result2[4] << "]\n";
}

void test_partial_sum() {
    std::cout << "\nTesting partial_sum...\n";

    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Test basic partial_sum
    std::partial_sum(v.begin(), v.end(), result.begin());
    assert(result[0] == 1);
    assert(result[1] == 3);   // 1 + 2
    assert(result[2] == 6);   // 1 + 2 + 3
    assert(result[3] == 10);  // 1 + 2 + 3 + 4
    assert(result[4] == 15);  // 1 + 2 + 3 + 4 + 5
    std::cout << "  ✓ Partial sums: [" << result[0] << ", " << result[1]
              << ", " << result[2] << ", " << result[3] << ", " << result[4] << "]\n";

    // Test with custom operation (partial products)
    std::vector<int> result2(v.size());
    std::partial_sum(v.begin(), v.end(), result2.begin(), std::multiplies<>());
    assert(result2[0] == 1);
    assert(result2[1] == 2);    // 1 * 2
    assert(result2[2] == 6);    // 1 * 2 * 3
    assert(result2[3] == 24);   // 1 * 2 * 3 * 4
    assert(result2[4] == 120);  // 1 * 2 * 3 * 4 * 5
    std::cout << "  ✓ Partial products: [" << result2[0] << ", " << result2[1]
              << ", " << result2[2] << ", " << result2[3] << ", " << result2[4] << "]\n";
}

void test_exclusive_scan() {
    std::cout << "\nTesting exclusive_scan (C++17)...\n";

    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Test exclusive_scan with initial value 0
    std::exclusive_scan(v.begin(), v.end(), result.begin(), 0);
    assert(result[0] == 0);   // init
    assert(result[1] == 1);   // 0 + 1
    assert(result[2] == 3);   // 0 + 1 + 2
    assert(result[3] == 6);   // 0 + 1 + 2 + 3
    assert(result[4] == 10);  // 0 + 1 + 2 + 3 + 4
    std::cout << "  ✓ Exclusive scan: [" << result[0] << ", " << result[1]
              << ", " << result[2] << ", " << result[3] << ", " << result[4] << "]\n";

    // Test with custom operation
    std::vector<int> result2(v.size());
    std::exclusive_scan(v.begin(), v.end(), result2.begin(), 1, std::multiplies<>());
    assert(result2[0] == 1);   // init
    assert(result2[1] == 1);   // 1 * 1
    assert(result2[2] == 2);   // 1 * 1 * 2
    assert(result2[3] == 6);   // 1 * 1 * 2 * 3
    assert(result2[4] == 24);  // 1 * 1 * 2 * 3 * 4
    std::cout << "  ✓ Exclusive scan (product): [" << result2[0] << ", " << result2[1]
              << ", " << result2[2] << ", " << result2[3] << ", " << result2[4] << "]\n";
}

void test_inclusive_scan() {
    std::cout << "\nTesting inclusive_scan (C++17)...\n";

    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Test basic inclusive_scan
    std::inclusive_scan(v.begin(), v.end(), result.begin());
    assert(result[0] == 1);
    assert(result[1] == 3);   // 1 + 2
    assert(result[2] == 6);   // 1 + 2 + 3
    assert(result[3] == 10);  // 1 + 2 + 3 + 4
    assert(result[4] == 15);  // 1 + 2 + 3 + 4 + 5
    std::cout << "  ✓ Inclusive scan: [" << result[0] << ", " << result[1]
              << ", " << result[2] << ", " << result[3] << ", " << result[4] << "]\n";

    // Test with custom operation
    std::vector<int> result2(v.size());
    std::inclusive_scan(v.begin(), v.end(), result2.begin(), std::multiplies<>());
    assert(result2[0] == 1);
    assert(result2[1] == 2);    // 1 * 2
    assert(result2[2] == 6);    // 1 * 2 * 3
    assert(result2[3] == 24);   // 1 * 2 * 3 * 4
    assert(result2[4] == 120);  // 1 * 2 * 3 * 4 * 5
    std::cout << "  ✓ Inclusive scan (product): [" << result2[0] << ", " << result2[1]
              << ", " << result2[2] << ", " << result2[3] << ", " << result2[4] << "]\n";

    // Test with initial value
    std::vector<int> result3(v.size());
    std::inclusive_scan(v.begin(), v.end(), result3.begin(), std::plus<>(), 100);
    assert(result3[0] == 101);  // 100 + 1
    assert(result3[1] == 103);  // 100 + 1 + 2
    std::cout << "  ✓ Inclusive scan with init: [" << result3[0] << ", " << result3[1] << ", ...]\n";
}

void test_transform_exclusive_scan() {
    std::cout << "\nTesting transform_exclusive_scan (C++17)...\n";

    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Square then exclusive scan
    auto square = [](int x) { return x * x; };
    std::transform_exclusive_scan(v.begin(), v.end(), result.begin(), 0, std::plus<>(), square);
    assert(result[0] == 0);    // init
    assert(result[1] == 1);    // 0 + 1^2
    assert(result[2] == 5);    // 0 + 1^2 + 2^2
    assert(result[3] == 14);   // 0 + 1^2 + 2^2 + 3^2
    assert(result[4] == 30);   // 0 + 1^2 + 2^2 + 3^2 + 4^2
    std::cout << "  ✓ Transform exclusive scan (squares): [" << result[0] << ", " << result[1]
              << ", " << result[2] << ", " << result[3] << ", " << result[4] << "]\n";
}

void test_transform_inclusive_scan() {
    std::cout << "\nTesting transform_inclusive_scan (C++17)...\n";

    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> result(v.size());

    // Square then inclusive scan
    auto square = [](int x) { return x * x; };
    std::transform_inclusive_scan(v.begin(), v.end(), result.begin(), std::plus<>(), square);
    assert(result[0] == 1);    // 1^2
    assert(result[1] == 5);    // 1^2 + 2^2
    assert(result[2] == 14);   // 1^2 + 2^2 + 3^2
    assert(result[3] == 30);   // 1^2 + 2^2 + 3^2 + 4^2
    assert(result[4] == 55);   // 1^2 + 2^2 + 3^2 + 4^2 + 5^2
    std::cout << "  ✓ Transform inclusive scan (squares): [" << result[0] << ", " << result[1]
              << ", " << result[2] << ", " << result[3] << ", " << result[4] << "]\n";

    // With initial value
    std::vector<int> result2(v.size());
    std::transform_inclusive_scan(v.begin(), v.end(), result2.begin(), std::plus<>(), square, 100);
    assert(result2[0] == 101);  // 100 + 1^2
    assert(result2[1] == 105);  // 100 + 1^2 + 2^2
    std::cout << "  ✓ Transform inclusive scan with init: [" << result2[0] << ", " << result2[1] << ", ...]\n";
}

void test_iota() {
    std::cout << "\nTesting iota...\n";

    std::vector<int> v(5);

    // Test basic iota starting from 0
    std::iota(v.begin(), v.end(), 0);
    assert(v[0] == 0);
    assert(v[1] == 1);
    assert(v[2] == 2);
    assert(v[3] == 3);
    assert(v[4] == 4);
    std::cout << "  ✓ Iota from 0: [" << v[0] << ", " << v[1] << ", " << v[2]
              << ", " << v[3] << ", " << v[4] << "]\n";

    // Test iota starting from 10
    std::iota(v.begin(), v.end(), 10);
    assert(v[0] == 10);
    assert(v[4] == 14);
    std::cout << "  ✓ Iota from 10: [" << v[0] << ", " << v[1] << ", " << v[2]
              << ", " << v[3] << ", " << v[4] << "]\n";

    // Test with floating point
    std::vector<double> vd(3);
    std::iota(vd.begin(), vd.end(), 1.5);
    assert(vd[0] == 1.5);
    assert(vd[1] == 2.5);
    assert(vd[2] == 3.5);
    std::cout << "  ✓ Iota with double: [" << vd[0] << ", " << vd[1] << ", " << vd[2] << "]\n";
}

void test_gcd_lcm() {
    std::cout << "\nTesting gcd and lcm (C++17)...\n";

    // Test GCD
    int gcd1 = std::gcd(12, 18);
    assert(gcd1 == 6);
    std::cout << "  ✓ gcd(12, 18) = " << gcd1 << "\n";

    int gcd2 = std::gcd(48, 18);
    assert(gcd2 == 6);
    std::cout << "  ✓ gcd(48, 18) = " << gcd2 << "\n";

    int gcd3 = std::gcd(7, 13);
    assert(gcd3 == 1);
    std::cout << "  ✓ gcd(7, 13) = " << gcd3 << " (coprime)\n";

    // Test LCM
    int lcm1 = std::lcm(12, 18);
    assert(lcm1 == 36);
    std::cout << "  ✓ lcm(12, 18) = " << lcm1 << "\n";

    int lcm2 = std::lcm(4, 6);
    assert(lcm2 == 12);
    std::cout << "  ✓ lcm(4, 6) = " << lcm2 << "\n";

    // Test with zero
    int gcd4 = std::gcd(0, 5);
    assert(gcd4 == 5);
    std::cout << "  ✓ gcd(0, 5) = " << gcd4 << "\n";
}

void test_midpoint() {
    std::cout << "\nTesting midpoint (C++20)...\n";

    // Test with integers
    int mid1 = std::midpoint(10, 20);
    assert(mid1 == 15);
    std::cout << "  ✓ midpoint(10, 20) = " << mid1 << "\n";

    int mid2 = std::midpoint(0, 5);
    assert(mid2 == 2);  // Rounds towards first argument
    std::cout << "  ✓ midpoint(0, 5) = " << mid2 << "\n";

    int mid3 = std::midpoint(-10, 10);
    assert(mid3 == 0);
    std::cout << "  ✓ midpoint(-10, 10) = " << mid3 << "\n";

    // Test with floating point
    double mid4 = std::midpoint(1.0, 3.0);
    assert(mid4 == 2.0);
    std::cout << "  ✓ midpoint(1.0, 3.0) = " << mid4 << "\n";

    // Test with pointers
    int arr[] = {1, 2, 3, 4, 5};
    int* mid_ptr = std::midpoint(arr, arr + 4);
    assert(mid_ptr == arr + 2);
    std::cout << "  ✓ midpoint of array pointers works correctly\n";
}

int main() {
    std::cout << "=================================================\n";
    std::cout << "  std_module.numeric - Comprehensive Test Suite\n";
    std::cout << "=================================================\n\n";

    test_accumulate();
    test_reduce();
    test_transform_reduce();
    test_inner_product();
    test_adjacent_difference();
    test_partial_sum();
    test_exclusive_scan();
    test_inclusive_scan();
    test_transform_exclusive_scan();
    test_transform_inclusive_scan();
    test_iota();
    test_gcd_lcm();
    test_midpoint();

    std::cout << "\n=================================================\n";
    std::cout << "  All tests passed! ✓\n";
    std::cout << "=================================================\n";

    return 0;
}
