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

// Export operator overloads (fixes C++20 module ADL limitation)
// CRITICAL: Without these, operators won't be found across module boundaries
using std::operator==;
using std::operator!=;
using std::operator<;
using std::operator<=;
using std::operator>;
using std::operator>=;

// PMR types
namespace pmr
{
using std::pmr::vector;
}  // namespace pmr
}  // namespace std
