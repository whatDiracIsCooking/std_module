/**
 * @file exception.cppm
 * @brief C++20 exception module wrapper
 */

module;

#include <exception>

export module std_module.exception;

export namespace std
{
// Exception base classes
using std::exception;
using std::bad_exception;
using std::nested_exception;

// Exception pointer support
using std::exception_ptr;
using std::current_exception;
using std::rethrow_exception;
using std::make_exception_ptr;

// Nested exception functions
using std::throw_with_nested;
using std::rethrow_if_nested;

// Terminate handler
using std::terminate;
using std::terminate_handler;
using std::get_terminate;
using std::set_terminate;

// Uncaught exceptions
using std::uncaught_exceptions;
}  // namespace std
