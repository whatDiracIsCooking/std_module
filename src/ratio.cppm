/**
 * @file ratio.cppm
 * @brief C++20 ratio module wrapper
 */

module;

#include <ratio>

export module std_module.ratio;

export namespace std
{
// Primary template
using std::ratio;

// Convenience typedefs for SI units
using std::atto;
using std::femto;
using std::pico;
using std::nano;
using std::micro;
using std::milli;
using std::centi;
using std::deci;
using std::deca;
using std::hecto;
using std::kilo;
using std::mega;
using std::giga;
using std::tera;
using std::peta;
using std::exa;

// Ratio arithmetic
using std::ratio_add;
using std::ratio_subtract;
using std::ratio_multiply;
using std::ratio_divide;

// Ratio comparison
using std::ratio_equal;
using std::ratio_not_equal;
using std::ratio_less;
using std::ratio_less_equal;
using std::ratio_greater;
using std::ratio_greater_equal;

// Helper templates (C++17)
using std::ratio_equal_v;
using std::ratio_not_equal_v;
using std::ratio_less_v;
using std::ratio_less_equal_v;
using std::ratio_greater_v;
using std::ratio_greater_equal_v;
}  // namespace std
