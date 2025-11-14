/**
 * @file system_error.cppm
 * @brief C++20 system_error module wrapper
 */

module;

#include <system_error>

export module std_module.system_error;

export namespace std
{
// Error category base class
using std::error_category;

// Predefined error categories
using std::generic_category;
using std::system_category;

// Error code class
using std::error_code;

// Error condition class
using std::error_condition;

// System error exception
using std::system_error;

// Error code enumeration
using std::errc;

// Comparison operators
using std::operator==;
using std::operator<=>;

// Hash support
using std::hash;

// Error code creation
using std::make_error_code;
using std::make_error_condition;

// is_error_code_enum and is_error_condition_enum traits
using std::is_error_code_enum;
using std::is_error_code_enum_v;
using std::is_error_condition_enum;
using std::is_error_condition_enum_v;
}  // namespace std
