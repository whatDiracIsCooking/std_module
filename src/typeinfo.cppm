/**
 * @file typeinfo.cppm
 * @brief C++20 typeinfo module wrapper
 */

module;

#include <typeinfo>

export module std_module.typeinfo;

export namespace std
{
// Core type information class
using std::type_info;

// Exception types
using std::bad_cast;
using std::bad_typeid;
}  // namespace std
