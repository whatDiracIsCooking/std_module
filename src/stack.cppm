/**
 * @file stack.cppm
 * @brief C++20 stack module wrapper
 */

module;

#include <stack>

export module std_module.stack;

export namespace std
{
// Main stack template class
using std::stack;

// Comparison operators (C++20 - exported as free functions)
using std::operator==;
using std::operator!=;
using std::operator<;
using std::operator<=;
using std::operator>;
using std::operator>=;
using std::operator<=>;  // C++20 three-way comparison

// Swap specialization
using std::swap;
}  // namespace std
