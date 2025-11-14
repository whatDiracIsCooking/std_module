/**
 * @file barrier.cppm
 * @brief C++20 barrier module wrapper
 */

module;
#include <barrier>
export module std_module.barrier;

export namespace std {
    // Barrier class template
    using std::barrier;

    // Arrival token type
    // Note: arrival_token is an implementation-defined type returned by arrive()
}
