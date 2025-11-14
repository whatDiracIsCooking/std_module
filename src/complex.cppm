/**
 * @file complex.cppm
 * @brief C++20 complex module wrapper
 */

module;

#include <complex>

export module std_module.complex;

export namespace std
{
// Complex number class template
using std::complex;

// Non-member operations
using std::real;
using std::imag;
using std::abs;
using std::arg;
using std::norm;
using std::conj;
using std::proj;
using std::polar;

// Exponential functions
using std::exp;
using std::log;
using std::log10;

// Power functions
using std::pow;
using std::sqrt;

// Trigonometric functions
using std::sin;
using std::cos;
using std::tan;
using std::asin;
using std::acos;
using std::atan;

// Hyperbolic functions
using std::sinh;
using std::cosh;
using std::tanh;
using std::asinh;
using std::acosh;
using std::atanh;

// Literals namespace
inline namespace literals
{
inline namespace complex_literals
{
using std::literals::complex_literals::operator""i;
using std::literals::complex_literals::operator""if;
using std::literals::complex_literals::operator""il;
}  // namespace complex_literals
}  // namespace literals
}  // namespace std
