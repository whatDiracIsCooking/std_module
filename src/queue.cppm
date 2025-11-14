/**
 * @file queue.cppm
 * @brief C++20 queue module wrapper
 */

module;

#include <queue>

export module std_module.queue;

export namespace std
{
// Container adapters
using std::queue;
using std::priority_queue;

// Non-member functions for queue
using std::swap;

// Note: Comparison operators (operator==, operator!=, operator<, etc.)
// are defined as hidden friends inside the class templates, so they
// should be available through ADL when using the exported types.
}  // namespace std
