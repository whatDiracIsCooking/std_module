/**
 * @file initializer_list.cppm
 * @brief C++20 initializer_list module wrapper
 */

module;
#include <initializer_list>
export module std_module.initializer_list;

export namespace std {
    // Class template
    using std::initializer_list;

    // Support functions
    using std::begin;
    using std::end;
}
