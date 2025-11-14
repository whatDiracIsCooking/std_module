/**
 * @file bitset.cppm
 * @brief C++20 bitset module wrapper
 */

module;

#include <bitset>

export module std_module.bitset;

// Export all of std namespace from <bitset>
export namespace std
{
// Main bitset class template
using std::bitset;

// Hash support
using std::hash;

// Bitwise operators (non-member functions)
using std::operator&;
using std::operator|;
using std::operator^;
}  // namespace std
