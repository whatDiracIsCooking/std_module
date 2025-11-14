/**
 * @file mutex.cppm
 * @brief C++20 mutex module wrapper
 */

module;

#include <mutex>

export module std_module.mutex;

export namespace std
{
// Mutex types
using std::mutex;
using std::recursive_mutex;
using std::timed_mutex;
using std::recursive_timed_mutex;

// Lock guards and wrappers
using std::lock_guard;
using std::scoped_lock;
using std::unique_lock;

// Lock tags
using std::defer_lock_t;
using std::try_to_lock_t;
using std::adopt_lock_t;

// Lock tag constants
using std::defer_lock;
using std::try_to_lock;
using std::adopt_lock;

// Call once
using std::once_flag;
using std::call_once;

// Locking algorithms
using std::lock;
using std::try_lock;
}  // namespace std
