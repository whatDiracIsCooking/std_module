/**
 * @file test_execution.cpp
 * @brief Tests for std_module.execution
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.execution;
import std_module.test_framework;

// FUTURE: When std_module.algorithm and std_module.vector are available,
// remove these includes
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    test::test_header("std_module.execution");

    test::section("Testing execution policy objects");

    // Test that all policy objects are accessible
    [[maybe_unused]] auto seq = std::execution::seq;
    [[maybe_unused]] auto par = std::execution::par;
    [[maybe_unused]] auto par_unseq = std::execution::par_unseq;
    [[maybe_unused]] auto unseq = std::execution::unseq;
    test::success("all execution policy objects accessible");

    test::section("Testing is_execution_policy trait");

    // Test compile-time trait recognition
    static_assert(std::is_execution_policy_v<std::execution::sequenced_policy>);
    static_assert(std::is_execution_policy_v<std::execution::parallel_policy>);
    static_assert(std::is_execution_policy_v<std::execution::parallel_unsequenced_policy>);
    static_assert(std::is_execution_policy_v<std::execution::unsequenced_policy>);
    static_assert(!std::is_execution_policy_v<int>);
    test::success("is_execution_policy trait works");

    test::section("Testing with parallel algorithms");

    // Just verify policies can be passed to algorithms (not testing algorithm correctness)
    std::vector<int> data{5, 2, 8, 1, 9};

    std::sort(std::execution::seq, data.begin(), data.end());
    test::success("seq policy with std::sort");

    std::sort(std::execution::par, data.begin(), data.end());
    test::success("par policy with std::sort");

    std::sort(std::execution::par_unseq, data.begin(), data.end());
    test::success("par_unseq policy with std::sort");

    std::sort(std::execution::unseq, data.begin(), data.end());
    test::success("unseq policy with std::sort");

    // Test with for_each
    std::for_each(std::execution::seq, data.begin(), data.end(), [](int& x) { x *= 2; });
    test::success("execution policies with std::for_each");

    test::test_footer();
    return 0;
}
