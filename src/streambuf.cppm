/**
 * @file streambuf.cppm
 * @brief C++20 streambuf module wrapper
 */

module;

#include <streambuf>

export module std_module.streambuf;

export namespace std
{
// Main template class
using std::basic_streambuf;

// Type aliases
using std::streambuf;
using std::wstreambuf;
}  // namespace std
