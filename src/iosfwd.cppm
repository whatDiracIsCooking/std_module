/**
 * @file iosfwd.cppm
 * @brief C++20 iosfwd module wrapper for iostream forward declarations
 */

module;
#include <iosfwd>
export module std_module.iosfwd;

export namespace std {
    // Character traits
    using std::char_traits;

    // Stream buffer templates
    using std::basic_streambuf;
    using std::streambuf;
    using std::wstreambuf;

    // Basic I/O templates
    using std::basic_ios;
    using std::ios;
    using std::wios;

    // Input/output stream templates
    using std::basic_istream;
    using std::istream;
    using std::wistream;

    using std::basic_ostream;
    using std::ostream;
    using std::wostream;

    using std::basic_iostream;
    using std::iostream;
    using std::wiostream;

    // File stream templates
    using std::basic_ifstream;
    using std::ifstream;
    using std::wifstream;

    using std::basic_ofstream;
    using std::ofstream;
    using std::wofstream;

    using std::basic_fstream;
    using std::fstream;
    using std::wfstream;

    // String stream templates
    using std::basic_istringstream;
    using std::istringstream;
    using std::wistringstream;

    using std::basic_ostringstream;
    using std::ostringstream;
    using std::wostringstream;

    using std::basic_stringstream;
    using std::stringstream;
    using std::wstringstream;

    // File buffer templates
    using std::basic_filebuf;
    using std::filebuf;
    using std::wfilebuf;

    // String buffer templates
    using std::basic_stringbuf;
    using std::stringbuf;
    using std::wstringbuf;

    // Synchronized output (C++20)
    using std::basic_syncbuf;
    using std::syncbuf;
    using std::wsyncbuf;

    using std::basic_osyncstream;
    using std::osyncstream;
    using std::wosyncstream;

    // Stream position and offset
    using std::fpos;
    using std::streampos;
    using std::wstreampos;
    using std::u8streampos;
    using std::u16streampos;
    using std::u32streampos;
}
