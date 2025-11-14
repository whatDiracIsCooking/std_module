/**
 * @file thread.cppm
 * @brief C++20 thread module wrapper
 */

module;

#include <thread>

export module std_module.thread;

export namespace std
{
// Thread class
using std::thread;

// jthread (C++20)
using std::jthread;

// this_thread namespace
namespace this_thread
{
using std::this_thread::get_id;
using std::this_thread::yield;
using std::this_thread::sleep_for;
using std::this_thread::sleep_until;
}  // namespace this_thread
}  // namespace std
