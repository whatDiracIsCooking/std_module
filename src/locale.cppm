/**
 * @file locale.cppm
 * @brief C++20 locale module wrapper
 */

module;

#include <locale>

export module std_module.locale;

export namespace std
{
// Main locale class
using std::locale;

// Facet base classes
using std::ctype_base;
using std::codecvt_base;

// Character classification and conversion facets
using std::ctype;
using std::ctype_byname;
using std::codecvt;
using std::codecvt_byname;

// Numeric facets
using std::num_get;
using std::num_put;
using std::numpunct;
using std::numpunct_byname;

// Collation facet
using std::collate;
using std::collate_byname;

// Time facets
using std::time_base;
using std::time_get;
using std::time_put;
using std::time_get_byname;
using std::time_put_byname;

// Monetary facets
using std::money_base;
using std::money_get;
using std::money_put;
using std::moneypunct;
using std::moneypunct_byname;

// Message facet
using std::messages_base;
using std::messages;
using std::messages_byname;

// Convenience functions for character classification
using std::isspace;
using std::isblank;
using std::iscntrl;
using std::isupper;
using std::islower;
using std::isalpha;
using std::isdigit;
using std::ispunct;
using std::isxdigit;
using std::isalnum;
using std::isprint;
using std::isgraph;

// Convenience functions for character conversion
using std::toupper;
using std::tolower;

// Locale-specific facet access
using std::has_facet;
using std::use_facet;

// Deprecated (C++11-17) but may still be available
#ifdef __cpp_lib_locale_conversions
using std::wstring_convert;
using std::wbuffer_convert;
#endif
}  // namespace std
