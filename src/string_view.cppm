/**
 * @file string_view.cppm
 * @brief C++20 string_view module wrapper
 */

module;

#include <string_view>

export module std_module.string_view;

export namespace std
{
// Main class templates
using std::basic_string_view;
using std::string_view;
using std::wstring_view;
using std::u8string_view;
using std::u16string_view;
using std::u32string_view;

// Comparison operators (inline in C++20)
// These are already available through the basic_string_view template

// Hash support
using std::hash;

// Literals namespace
inline namespace literals {
    inline namespace string_view_literals {
        using std::literals::string_view_literals::operator""sv;
    }
}
}  // namespace std
