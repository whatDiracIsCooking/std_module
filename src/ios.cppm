/**
 * @file ios.cppm
 * @brief C++20 ios module wrapper
 */

module;

#include <ios>

export module std_module.ios;

export namespace std
{
// Base classes
using std::ios_base;
using std::basic_ios;

// Type aliases
using std::ios;
using std::wios;

// Position types
using std::fpos;
using std::streamoff;
using std::streampos;
using std::wstreampos;

// Error handling
using std::io_errc;
using std::iostream_category;
using std::make_error_code;
using std::make_error_condition;

// Formatting manipulators - boolean
using std::boolalpha;
using std::noboolalpha;

// Formatting manipulators - base notation
using std::showbase;
using std::noshowbase;

// Formatting manipulators - floating point
using std::showpoint;
using std::noshowpoint;

// Formatting manipulators - sign
using std::showpos;
using std::noshowpos;

// Formatting manipulators - whitespace
using std::skipws;
using std::noskipws;

// Formatting manipulators - case
using std::uppercase;
using std::nouppercase;

// Formatting manipulators - buffering
using std::unitbuf;
using std::nounitbuf;

// Formatting manipulators - alignment
using std::internal;
using std::left;
using std::right;

// Formatting manipulators - numeric base
using std::dec;
using std::hex;
using std::oct;

// Formatting manipulators - floating point format
using std::fixed;
using std::scientific;
using std::hexfloat;
using std::defaultfloat;
}  // namespace std
