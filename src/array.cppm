/**
 * @file array.cppm
 * @brief C++20 array module wrapper
 */

module;

#include <array>

export module std_module.array;

export namespace std
{
// Main template
using std::array;

// Array creation helper (C++20)
using std::to_array;

// Element access
using std::get;

// Specialized algorithms
using std::swap;

// Tuple interface
using std::tuple_size;
using std::tuple_element;

// Comparison operators are automatically available through ADL
// for std::array since they are templates in the std namespace
}  // namespace std
