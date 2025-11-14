/**
 * @file stdexcept.cppm
 * @brief C++20 stdexcept module wrapper
 */

module;

#include <stdexcept>

export module std_module.stdexcept;

export namespace std
{
// Logic error exception classes
using std::logic_error;
using std::domain_error;
using std::invalid_argument;
using std::length_error;
using std::out_of_range;

// Runtime error exception classes
using std::runtime_error;
using std::range_error;
using std::overflow_error;
using std::underflow_error;
}  // namespace std
