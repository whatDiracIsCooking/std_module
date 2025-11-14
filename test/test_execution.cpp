/**
 * @file test_execution.cpp
 * @brief Comprehensive test for std_module.execution (C++20)
 */

import std_module.execution;

#include <iostream>  // For output
#include <cassert>   // For assertions
#include <algorithm> // For parallel algorithms
#include <vector>    // For test data
#include <numeric>   // For iota

void test_execution_policies() {
    std::cout << "Testing execution policy objects...\n";

    // Test that policy objects exist and have correct types
    [[maybe_unused]] auto seq_policy = std::execution::seq;
    [[maybe_unused]] auto par_policy = std::execution::par;
    [[maybe_unused]] auto par_unseq_policy = std::execution::par_unseq;
    [[maybe_unused]] auto unseq_policy = std::execution::unseq;

    std::cout << "  ✓ All execution policy objects accessible\n";
}

void test_is_execution_policy() {
    std::cout << "\nTesting is_execution_policy trait...\n";

    // Test that standard execution policies are recognized
    static_assert(std::is_execution_policy_v<std::execution::sequenced_policy>);
    static_assert(std::is_execution_policy_v<std::execution::parallel_policy>);
    static_assert(std::is_execution_policy_v<std::execution::parallel_unsequenced_policy>);
    static_assert(std::is_execution_policy_v<std::execution::unsequenced_policy>);

    std::cout << "  ✓ is_execution_policy recognizes all standard policies\n";

    // Test that non-execution-policy types are not recognized
    static_assert(!std::is_execution_policy_v<int>);
    static_assert(!std::is_execution_policy_v<std::string>);

    std::cout << "  ✓ is_execution_policy correctly rejects non-policies\n";
}

void test_parallel_algorithms_basic() {
    std::cout << "\nTesting basic parallel algorithm usage...\n";

    std::vector<int> data(1000);
    std::iota(data.begin(), data.end(), 0);

    // Test with sequenced policy
    std::sort(std::execution::seq, data.begin(), data.end(), std::greater<>());
    assert(data[0] == 999);
    assert(data[999] == 0);
    std::cout << "  ✓ std::sort with seq policy works\n";

    // Reset data
    std::iota(data.begin(), data.end(), 0);

    // Test with parallel policy
    std::sort(std::execution::par, data.begin(), data.end(), std::greater<>());
    assert(data[0] == 999);
    assert(data[999] == 0);
    std::cout << "  ✓ std::sort with par policy works\n";

    // Reset data
    std::iota(data.begin(), data.end(), 0);

    // Test with parallel_unsequenced policy
    std::sort(std::execution::par_unseq, data.begin(), data.end(), std::greater<>());
    assert(data[0] == 999);
    assert(data[999] == 0);
    std::cout << "  ✓ std::sort with par_unseq policy works\n";

    // Reset data
    std::iota(data.begin(), data.end(), 0);

    // Test with unsequenced policy
    std::sort(std::execution::unseq, data.begin(), data.end(), std::greater<>());
    assert(data[0] == 999);
    assert(data[999] == 0);
    std::cout << "  ✓ std::sort with unseq policy works\n";
}

void test_for_each_policies() {
    std::cout << "\nTesting std::for_each with execution policies...\n";

    std::vector<int> data(100, 0);

    // Sequenced
    std::for_each(std::execution::seq, data.begin(), data.end(), [](int& x) { x = 1; });
    assert(std::all_of(data.begin(), data.end(), [](int x) { return x == 1; }));
    std::cout << "  ✓ std::for_each with seq policy\n";

    // Parallel
    std::fill(data.begin(), data.end(), 0);
    std::for_each(std::execution::par, data.begin(), data.end(), [](int& x) { x = 2; });
    assert(std::all_of(data.begin(), data.end(), [](int x) { return x == 2; }));
    std::cout << "  ✓ std::for_each with par policy\n";

    // Parallel unsequenced
    std::fill(data.begin(), data.end(), 0);
    std::for_each(std::execution::par_unseq, data.begin(), data.end(), [](int& x) { x = 3; });
    assert(std::all_of(data.begin(), data.end(), [](int x) { return x == 3; }));
    std::cout << "  ✓ std::for_each with par_unseq policy\n";

    // Unsequenced
    std::fill(data.begin(), data.end(), 0);
    std::for_each(std::execution::unseq, data.begin(), data.end(), [](int& x) { x = 4; });
    assert(std::all_of(data.begin(), data.end(), [](int x) { return x == 4; }));
    std::cout << "  ✓ std::for_each with unseq policy\n";
}

void test_transform_policies() {
    std::cout << "\nTesting std::transform with execution policies...\n";

    std::vector<int> input(100);
    std::iota(input.begin(), input.end(), 0);
    std::vector<int> output(100);

    // Sequenced
    std::transform(std::execution::seq, input.begin(), input.end(), output.begin(),
                   [](int x) { return x * 2; });
    assert(output[50] == 100);
    std::cout << "  ✓ std::transform with seq policy\n";

    // Parallel
    std::fill(output.begin(), output.end(), 0);
    std::transform(std::execution::par, input.begin(), input.end(), output.begin(),
                   [](int x) { return x * 3; });
    assert(output[50] == 150);
    std::cout << "  ✓ std::transform with par policy\n";
}

void test_count_policies() {
    std::cout << "\nTesting std::count with execution policies...\n";

    std::vector<int> data(1000, 42);
    data[100] = 1;
    data[500] = 1;

    // Sequenced
    auto count_seq = std::count(std::execution::seq, data.begin(), data.end(), 1);
    assert(count_seq == 2);
    std::cout << "  ✓ std::count with seq policy: " << count_seq << "\n";

    // Parallel
    auto count_par = std::count(std::execution::par, data.begin(), data.end(), 1);
    assert(count_par == 2);
    std::cout << "  ✓ std::count with par policy: " << count_par << "\n";
}

int main() {
    std::cout << "=== std_module.execution Comprehensive Test Suite ===\n\n";

    test_execution_policies();
    test_is_execution_policy();
    test_parallel_algorithms_basic();
    test_for_each_policies();
    test_transform_policies();
    test_count_policies();

    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}
