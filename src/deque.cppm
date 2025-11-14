/**
 * @file deque.cppm
 * @brief C++20 deque module wrapper
 */

module;

#include <deque>

export module std_module.deque;

export namespace std
{
// Main deque template class
using std::deque;

// Comparison operators (C++20 - exported as free functions)
using std::operator==;
using std::operator!=;
using std::operator<;
using std::operator<=;
using std::operator>;
using std::operator>=;
using std::operator<=>;  // C++20 three-way comparison

// Helper functions (erase-remove idiom C++20)
using std::erase;
using std::erase_if;

// PMR types
namespace pmr
{
using std::pmr::deque;
}  // namespace pmr
}  // namespace std
