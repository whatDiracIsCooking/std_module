/**
 * @file numeric.cppm
 * @brief C++20 numeric module wrapper
 */

module;

#include <numeric>

export module std_module.numeric;

export namespace std
{
// Accumulate and reduce operations
using std::accumulate;
using std::reduce;
using std::transform_reduce;

// Product and sum operations
using std::inner_product;
using std::adjacent_difference;
using std::partial_sum;

// Scan operations (C++17)
using std::exclusive_scan;
using std::inclusive_scan;
using std::transform_exclusive_scan;
using std::transform_inclusive_scan;

// Iota operation
using std::iota;

// Greatest common divisor and least common multiple (C++17)
using std::gcd;
using std::lcm;

// Midpoint (C++20)
using std::midpoint;
}  // namespace std
