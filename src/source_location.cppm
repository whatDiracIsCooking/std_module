/**
 * @file source_location.cppm
 * @brief C++20 source_location module wrapper
 */

module;

#include <source_location>

export module std_module.source_location;

export namespace std
{
// Source location type
using std::source_location;
}  // namespace std
