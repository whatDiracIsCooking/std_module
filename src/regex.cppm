/**
 * @file regex.cppm
 * @brief C++20 module wrapper for <regex>
 */

module;
#include <regex>
export module std_module.regex;

export namespace std {
    // Main regex class
    using std::basic_regex;
    using std::regex;
    using std::wregex;

    // Match results
    using std::match_results;
    using std::cmatch;
    using std::smatch;
    using std::wcmatch;
    using std::wsmatch;

    // Sub-match
    using std::sub_match;
    using std::csub_match;
    using std::ssub_match;
    using std::wcsub_match;
    using std::wssub_match;

    // Algorithms
    using std::regex_match;
    using std::regex_search;
    using std::regex_replace;

    // Iterators
    using std::regex_iterator;
    using std::cregex_iterator;
    using std::sregex_iterator;
    using std::wcregex_iterator;
    using std::wsregex_iterator;

    using std::regex_token_iterator;
    using std::cregex_token_iterator;
    using std::sregex_token_iterator;
    using std::wcregex_token_iterator;
    using std::wsregex_token_iterator;

    // Traits
    using std::regex_traits;

    // Exception
    using std::regex_error;

    // Export regex_constants namespace
    namespace regex_constants {
        // Types
        using std::regex_constants::syntax_option_type;
        using std::regex_constants::match_flag_type;
        using std::regex_constants::error_type;

        // syntax_option_type constants
        using std::regex_constants::icase;
        using std::regex_constants::nosubs;
        using std::regex_constants::optimize;
        using std::regex_constants::collate;
        using std::regex_constants::ECMAScript;
        using std::regex_constants::basic;
        using std::regex_constants::extended;
        using std::regex_constants::awk;
        using std::regex_constants::grep;
        using std::regex_constants::egrep;

        // match_flag_type constants
        using std::regex_constants::match_default;
        using std::regex_constants::match_not_bol;
        using std::regex_constants::match_not_eol;
        using std::regex_constants::match_not_bow;
        using std::regex_constants::match_not_eow;
        using std::regex_constants::match_any;
        using std::regex_constants::match_not_null;
        using std::regex_constants::match_continuous;
        using std::regex_constants::match_prev_avail;
        using std::regex_constants::format_default;
        using std::regex_constants::format_sed;
        using std::regex_constants::format_no_copy;
        using std::regex_constants::format_first_only;

        // error_type constants
        using std::regex_constants::error_collate;
        using std::regex_constants::error_ctype;
        using std::regex_constants::error_escape;
        using std::regex_constants::error_backref;
        using std::regex_constants::error_brack;
        using std::regex_constants::error_paren;
        using std::regex_constants::error_brace;
        using std::regex_constants::error_badbrace;
        using std::regex_constants::error_range;
        using std::regex_constants::error_space;
        using std::regex_constants::error_badrepeat;
        using std::regex_constants::error_complexity;
        using std::regex_constants::error_stack;
    }
}
