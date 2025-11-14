/**
 * @file tuple.cppm
 * @brief C++20 module wrapper for <tuple>
 */

module;
#include <tuple>
export module std_module.tuple;

export namespace std {
    // Main tuple class
    using std::tuple;

    // Helper classes
    using std::tuple_size;
    using std::tuple_element;
    using std::tuple_element_t;

    // Tuple creation functions
    using std::make_tuple;
    using std::tie;
    using std::forward_as_tuple;
    using std::tuple_cat;

    // Tuple access
    using std::get;

    // Comparison operators (structured binding support is automatic)
    // Note: operator==, operator!=, operator<, etc. are in global namespace

    // swap
    using std::swap;

    // ignore (for tie)
    using std::ignore;

    // C++17 additions
    using std::apply;
    using std::make_from_tuple;
}
