/**
 * @file charconv.cppm
 * @brief C++20 charconv module wrapper
 */

module;

#include <charconv>

export module std_module.charconv;

export namespace std
{
// Conversion functions
using std::to_chars;
using std::from_chars;

// Result types
using std::to_chars_result;
using std::from_chars_result;

// Floating-point format specification
using std::chars_format;
}  // namespace std
