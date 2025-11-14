/**
 * @file condition_variable.cppm
 * @brief C++20 condition_variable module wrapper
 */

module;
#include <condition_variable>
export module std_module.condition_variable;

export namespace std {
    // Classes
    using std::condition_variable;
    using std::condition_variable_any;

    // Enumerations
    using std::cv_status;

    // Functions
    using std::notify_all_at_thread_exit;
}
