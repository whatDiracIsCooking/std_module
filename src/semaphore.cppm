/**
 * @file semaphore.cppm
 * @brief C++20 semaphore module wrapper
 */

module;
#include <semaphore>
export module std_module.semaphore;

export namespace std {
    // Semaphore classes
    using std::counting_semaphore;
    using std::binary_semaphore;
}
