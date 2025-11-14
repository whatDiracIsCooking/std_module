/**
 * @file fstream.cppm
 * @brief C++20 fstream module wrapper
 */

module;

#include <fstream>

export module std_module.fstream;

export namespace std
{
// File buffer classes
using std::basic_filebuf;
using std::filebuf;
using std::wfilebuf;

// Input file stream classes
using std::basic_ifstream;
using std::ifstream;
using std::wifstream;

// Output file stream classes
using std::basic_ofstream;
using std::ofstream;
using std::wofstream;

// Bidirectional file stream classes
using std::basic_fstream;
using std::fstream;
using std::wfstream;
}  // namespace std
