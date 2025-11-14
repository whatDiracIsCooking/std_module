/**
 * @file iomanip.cppm
 * @brief C++20 module wrapper for <iomanip> - I/O manipulators
 */

module;
#include <iomanip>
export module std_module.iomanip;

/**
 * Export all I/O manipulator symbols from <iomanip>
 */
export namespace std {
    // Manipulators for format flags
    using std::resetiosflags;
    using std::setiosflags;

    // Manipulators for numeric formatting
    using std::setbase;
    using std::setfill;
    using std::setprecision;
    using std::setw;

    // Manipulators for monetary I/O
    using std::get_money;
    using std::put_money;

    // Manipulators for date/time I/O
    using std::get_time;
    using std::put_time;

    // Manipulators for quoted strings (C++14)
    using std::quoted;
}
