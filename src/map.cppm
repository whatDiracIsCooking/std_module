/**
 * @file map.cppm
 * @brief C++20 map module wrapper
 */

module;

#include <map>

export module std_module.map;

export namespace std
{
// Main container classes
using std::map;
using std::multimap;

// Comparison functions (used by map)
using std::less;

// Utility functions for maps
using std::erase_if;
}  // namespace std
