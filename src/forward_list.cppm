/**
 * @file forward_list.cppm
 * @brief C++20 forward_list module wrapper
 */

module;
#include <forward_list>
export module std_module.forward_list;

export namespace std {
    // Class template
    using std::forward_list;

    // Comparison operators
    using std::operator==;
    using std::operator!=;
    using std::operator<;
    using std::operator<=;
    using std::operator>;
    using std::operator>=;
    using std::operator<=>;

    // Specialized algorithms
    using std::swap;

    // Erasure functions (C++20)
    using std::erase;
    using std::erase_if;
}
