/**
 * @file format.cppm
 * @brief C++20 format module wrapper
 */

module;

#include <format>

export module std_module.format;

export namespace std
{
// Core formatting functions
using std::format;
using std::vformat;
using std::format_to;
using std::vformat_to;
using std::format_to_n;
using std::formatted_size;

// Type aliases
using std::format_string;
using std::wformat_string;
using std::format_context;
using std::wformat_context;
using std::format_args;
using std::wformat_args;
using std::format_parse_context;
using std::wformat_parse_context;

// Classes and templates
using std::basic_format_string;
using std::basic_format_context;
using std::basic_format_parse_context;
using std::basic_format_arg;
using std::basic_format_args;
using std::formatter;
using std::format_error;
using std::format_to_n_result;

// Helper functions
using std::make_format_args;
using std::make_wformat_args;
using std::visit_format_arg;
}  // namespace std

