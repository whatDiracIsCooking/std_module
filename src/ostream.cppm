/**
 * @file ostream.cppm
 * @brief C++20 ostream module wrapper
 *
 * This module provides C++20 module interface for <ostream> functionality.
 * Exports output stream classes and manipulators.
 *
 * NOTE: Due to C++20 module ADL limitations, operator<< overloads may not
 * be found correctly through module boundaries. Users may need to combine
 * import with #include for full functionality.
 */

module;
#include <ostream>

export module std_module.ostream;

export namespace std {
    // Core output stream classes
    using std::basic_ostream;
    using std::ostream;
    using std::wostream;

    // Stream manipulators
    using std::endl;
    using std::ends;
    using std::flush;

    // Position types
    using std::streampos;
    using std::wstreampos;
}
