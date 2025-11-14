/**
 * @file span.cppm
 * @brief C++20 span module wrapper
 */

module;

#include <span>

export module std_module.span;

export namespace std
{
// Span class template
using std::span;

// Dynamic extent constant
using std::dynamic_extent;

// Byte operations (often used with span)
using std::as_bytes;
using std::as_writable_bytes;
}  // namespace std
