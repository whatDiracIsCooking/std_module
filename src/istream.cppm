/**
 * @file istream.cppm
 * @brief C++20 istream module wrapper
 *
 * This module provides C++20 module interface for <istream> functionality.
 * Exports input stream classes and related manipulators.
 */

module;

#include <istream>

export module std_module.istream;

export namespace std {
    // Basic input stream class
    using std::basic_istream;

    // Type aliases for char and wchar_t streams
    using std::istream;
    using std::wistream;

    // Stream manipulators
    using std::ws;  // Discard leading whitespace

    // iostream class (for bidirectional streams)
    using std::basic_iostream;
    using std::iostream;
    using std::wiostream;
}
