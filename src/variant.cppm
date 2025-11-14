/**
 * @file variant.cppm
 * @brief C++20 variant module wrapper
 */

module;

#include <variant>

export module std_module.variant;

export namespace std
{
// Main template
using std::variant;

// Variant access
using std::get;
using std::get_if;
using std::holds_alternative;

// Visitor
using std::visit;

// Type traits
using std::variant_size;
using std::variant_size_v;
using std::variant_alternative;
using std::variant_alternative_t;

// Special values
using std::monostate;
using std::variant_npos;

// Exception
using std::bad_variant_access;
}  // namespace std
