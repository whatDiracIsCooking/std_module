/**
 * @file execution.cppm
 * @brief C++20 execution module wrapper
 */

module;

#include <execution>

export module std_module.execution;

export namespace std
{
// Execution policy traits
using std::is_execution_policy;
using std::is_execution_policy_v;
}  // namespace std

// Export nested namespace separately
export namespace std::execution
{
// Policy types
using std::execution::sequenced_policy;
using std::execution::parallel_policy;
using std::execution::parallel_unsequenced_policy;
using std::execution::unsequenced_policy;

// Policy objects
using std::execution::seq;
using std::execution::par;
using std::execution::par_unseq;
using std::execution::unseq;
}  // namespace std::execution
