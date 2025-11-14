/**
 * @file codecvt.cppm
 * @brief C++20 codecvt module wrapper
 * @note <codecvt> is deprecated in C++17, but still part of the standard library
 */

module;

#include <codecvt>

export module std_module.codecvt;

export namespace std
{
// Facet classes for UTF-8 conversion
using std::codecvt_utf8;
using std::codecvt_utf16;
using std::codecvt_utf8_utf16;

// Conversion mode enum and constants
using std::codecvt_mode;

// Mode flags (these are constexpr values in std::codecvt_mode)
// Note: Individual enum values are implicitly exported with the enum type
}  // namespace std
