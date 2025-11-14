/**
 * @file latch.cppm
 * @brief C++20 latch module wrapper
 */

module;
#include <latch>
export module std_module.latch;

export namespace std {
    // Latch class
    using std::latch;
}
