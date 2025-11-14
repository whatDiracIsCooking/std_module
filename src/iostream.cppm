/**
 * @file iostream.cppm
 * @brief C++20 iostream module wrapper
 *
 * This module provides C++20 module interface for <iostream> functionality.
 * Exports standard input/output stream objects for both narrow and wide characters.
 */

module;
#include <iostream>

export module std_module.iostream;

export namespace std {
    // Standard narrow character streams
    using std::cin;
    using std::cout;
    using std::cerr;
    using std::clog;

    // Wide character streams
    using std::wcin;
    using std::wcout;
    using std::wcerr;
    using std::wclog;

    // Stream manipulators (from <ostream>)
    using std::endl;
    using std::ends;
    using std::flush;

    // EXPERIMENTAL: Export operator<< overloads (attempting to fix ADL limitation)
    // Note: This may not work due to C++20 module ADL limitations
    using std::operator<<;
    using std::operator>>;
}
