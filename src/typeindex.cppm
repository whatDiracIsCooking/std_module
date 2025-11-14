/**
 * @file typeindex.cppm
 * @brief C++20 typeindex module wrapper
 */

module;

#include <typeindex>

export module std_module.typeindex;

export namespace std
{
// Type index class
using std::type_index;

// Hash support
using std::hash;
}  // namespace std
