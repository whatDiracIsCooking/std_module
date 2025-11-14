/**
 * @file format.cppm
 * @brief C++20 format module wrapper
 */

module;

#include <format>

export module std_module.format;

export namespace std
{
using std::format;
using std::format_string;
using std::format_to;
using std::format_to_n;
using std::formatted_size;
using std::vformat;
}  // namespace std

