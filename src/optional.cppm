/**
 * @file optional.cppm
 * @brief C++20 optional module wrapper
 */

module;

#include <optional>

export module std_module.optional;

export namespace std
{
// Main template
using std::optional;

// Special values and types
using std::nullopt_t;
using std::nullopt;

// Exception
using std::bad_optional_access;

// Factory function
using std::make_optional;
}  // namespace std
