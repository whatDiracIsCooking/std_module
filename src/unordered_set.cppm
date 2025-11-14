/**
 * @file unordered_set.cppm
 * @brief C++20 module wrapper for <unordered_set>
 */

module;
#include <unordered_set>
export module std_module.unordered_set;

export namespace std {
    // Main unordered_set class
    using std::unordered_set;
    using std::unordered_multiset;

    // Hash function
    using std::hash;

    // Swap
    using std::swap;

    // Erase-if (C++20)
    using std::erase_if;
}
