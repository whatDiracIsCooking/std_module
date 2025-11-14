/**
 * @file bit.cppm
 * @brief C++20 bit module wrapper
 */

module;

#include <bit>

export module std_module.bit;

export namespace std
{
// Bit manipulation functions
using std::bit_cast;
using std::has_single_bit;
using std::bit_ceil;
using std::bit_floor;
using std::bit_width;
using std::rotl;
using std::rotr;
using std::countl_zero;
using std::countl_one;
using std::countr_zero;
using std::countr_one;
using std::popcount;

// Endianness enumeration
using std::endian;
}  // namespace std
