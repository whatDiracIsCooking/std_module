/**
 * @file stop_token.cppm
 * @brief C++20 stop_token module wrapper
 */

module;

#include <stop_token>

export module std_module.stop_token;

export namespace std
{
// Stop token support (C++20)
using std::stop_token;
using std::stop_source;
using std::stop_callback;
using std::nostopstate;
using std::nostopstate_t;
}  // namespace std
