/**
 * @file valarray.cppm
 * @brief C++20 valarray module wrapper
 */

module;

#include <valarray>

export module std_module.valarray;

export namespace std
{
// Main class template
using std::valarray;

// Slice classes
using std::slice;
using std::slice_array;
using std::gslice;
using std::gslice_array;
using std::mask_array;
using std::indirect_array;

// Helper functions
using std::begin;
using std::end;
using std::swap;

// Transcendental functions
using std::abs;
using std::acos;
using std::asin;
using std::atan;
using std::atan2;
using std::cos;
using std::cosh;
using std::exp;
using std::log;
using std::log10;
using std::pow;
using std::sin;
using std::sinh;
using std::sqrt;
using std::tan;
using std::tanh;
}  // namespace std
