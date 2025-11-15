/**
 * @file set.cppm
 * @brief C++20 set module wrapper
 */

module;

#include <set>

export module std_module.set;

export namespace std
{
// Ordered associative containers
using std::set;
using std::multiset;

// Utility functions
using std::move;

// Comparison operators for iterators (fix ADL issues)
using std::operator==;
using std::operator!=;
using std::operator<;
using std::operator<=;
using std::operator>;
using std::operator>=;
using std::operator<=>;
}  // namespace std
