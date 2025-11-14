/**
 * @file coroutine.cppm
 * @brief C++20 coroutine module wrapper
 */

module;

#include <coroutine>

export module std_module.coroutine;

export namespace std
{
// Coroutine types
using std::coroutine_handle;
using std::coroutine_traits;

// Trivial awaitables
using std::suspend_always;
using std::suspend_never;

// No-op coroutine
using std::noop_coroutine_handle;
using std::noop_coroutine_promise;
using std::noop_coroutine;
}  // namespace std
