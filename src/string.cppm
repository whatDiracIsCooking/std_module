/**
 * @file string.cppm
 * @brief C++20 string module wrapper
 */

module;

#include <string>

export module std_module.string;

export namespace std
{
// Main string class templates
using std::basic_string;
using std::char_traits;

// String type aliases
using std::string;
using std::wstring;
using std::u8string;
using std::u16string;
using std::u32string;

// String conversion functions
using std::to_string;
using std::to_wstring;

// String to numeric conversions
using std::stoi;
using std::stol;
using std::stoll;
using std::stoul;
using std::stoull;
using std::stof;
using std::stod;
using std::stold;

// I/O operations
using std::getline;

// Hash support
using std::hash;

// C++20 erase/erase_if
using std::erase;
using std::erase_if;

// String literals namespace
namespace literals
{
namespace string_literals
{
using namespace std::literals::string_literals;
}  // namespace string_literals
}  // namespace literals

}  // namespace std
