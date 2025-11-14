/**
 * @file thread.cppm
 * @brief C++20 thread module wrapper
 */

module;

#include <thread>
#include <stop_token>

export module std_module.thread;

export namespace std
{
// Thread class
using std::thread;

// jthread (C++20)
using std::jthread;

// Stop token support (C++20)
using std::stop_token;
using std::stop_source;
using std::stop_callback;
using std::nostopstate;
using std::nostopstate_t;
}  // namespace std

// Export this_thread namespace
export namespace std::this_thread
{
using std::this_thread::get_id;
using std::this_thread::yield;
using std::this_thread::sleep_for;
using std::this_thread::sleep_until;
}  // namespace std::this_thread
