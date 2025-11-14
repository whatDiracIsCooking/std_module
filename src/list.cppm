/**
 * @file list.cppm
 * @brief C++20 list module wrapper
 */

module;

#include <list>

export module std_module.list;

export namespace std
{
// Main template class
using std::list;

// Non-member functions
using std::swap;

// Comparison operators
using std::operator==;
using std::operator!=;
using std::operator<;
using std::operator<=;
using std::operator>;
using std::operator>=;
using std::operator<=>;

// Erase functions (C++20)
using std::erase;
using std::erase_if;
}  // namespace std
