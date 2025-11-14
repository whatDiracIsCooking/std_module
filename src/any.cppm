/**
 * @file any.cppm
 * @brief C++20 any module wrapper
 */

module;

#include <any>

export module std_module.any;

export namespace std
{
// Main class
using std::any;

// Exception
using std::bad_any_cast;

// Functions
using std::any_cast;
using std::make_any;
using std::swap;
}  // namespace std
