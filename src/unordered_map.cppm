/**
 * @file unordered_map.cppm
 * @brief C++20 unordered_map module wrapper
 */

module;

#include <unordered_map>

export module std_module.unordered_map;

export namespace std
{
// Container classes
using std::unordered_map;
using std::unordered_multimap;

// Helper functions (C++20)
using std::erase_if;
}  // namespace std
