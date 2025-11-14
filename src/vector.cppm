/**
 * @file vector.cppm
 * @brief C++20 vector module wrapper
 */

module;

#include <vector>

export module std_module.vector;

export namespace std
{
// Main template
using std::vector;

// Helper functions (erase-remove idiom C++20)
using std::erase;
using std::erase_if;
}  // namespace std

// Export PMR types in their own namespace
export namespace std::pmr
{
using std::pmr::vector;
}  // namespace std::pmr
