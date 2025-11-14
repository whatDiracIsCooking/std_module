/**
 * @file syncstream.cppm
 * @brief C++20 syncstream module wrapper
 */

module;

#include <syncstream>

export module std_module.syncstream;

export namespace std
{
// Synchronized stream buffer classes
using std::basic_syncbuf;
using std::syncbuf;
using std::wsyncbuf;

// Synchronized output stream classes
using std::basic_osyncstream;
using std::osyncstream;
using std::wosyncstream;
}  // namespace std
