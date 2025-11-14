/**
 * @file limits.cppm
 * @brief C++20 limits module wrapper
 */

module;

#include <limits>

export module std_module.limits;

export namespace std
{
// Primary template and specializations
using std::numeric_limits;

// Enumerations
using std::float_round_style;
using std::float_denorm_style;
}  // namespace std
