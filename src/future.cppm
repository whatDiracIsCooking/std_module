/**
 * @file future.cppm
 * @brief C++20 future module wrapper
 */

module;
#include <future>
export module std_module.future;

export namespace std {
    // Enumerations
    using std::future_status;
    using std::launch;
    using std::future_errc;

    // Classes
    using std::future_error;
    using std::promise;
    using std::packaged_task;
    using std::future;
    using std::shared_future;

    // Functions
    using std::async;
    using std::future_category;

    // Specialized algorithms
    using std::swap;

    // Helper type
    using std::uses_allocator;
}
