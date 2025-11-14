/**
 * @file iterator.cppm
 * @brief C++20 iterator module wrapper
 */

module;

#include <iterator>

export module std_module.iterator;

export namespace std
{
// Iterator tags
using std::input_iterator_tag;
using std::output_iterator_tag;
using std::forward_iterator_tag;
using std::bidirectional_iterator_tag;
using std::random_access_iterator_tag;
using std::contiguous_iterator_tag;

// Iterator operations
using std::advance;
using std::distance;
using std::next;
using std::prev;

// Iterator adaptors
using std::reverse_iterator;
using std::move_iterator;
using std::back_insert_iterator;
using std::front_insert_iterator;
using std::insert_iterator;
using std::move_sentinel;

// Iterator primitives
using std::iterator_traits;
using std::incrementable_traits;
using std::indirectly_readable_traits;

// Iterator inserters
using std::back_inserter;
using std::front_inserter;
using std::inserter;

// Move iterator utilities
using std::make_move_iterator;
using std::make_reverse_iterator;

// Container access
using std::begin;
using std::end;
using std::cbegin;
using std::cend;
using std::rbegin;
using std::rend;
using std::crbegin;
using std::crend;

// Container operations
using std::size;
using std::ssize;
using std::empty;
using std::data;

// C++20 iterator utilities
using std::counted_iterator;
using std::common_iterator;
using std::default_sentinel_t;
using std::default_sentinel;
using std::unreachable_sentinel_t;
using std::unreachable_sentinel;

// C++20 iterator concepts (conditionally available)
#if __cpp_lib_concepts >= 202002L
using std::input_iterator;
using std::output_iterator;
using std::forward_iterator;
using std::bidirectional_iterator;
using std::random_access_iterator;
using std::contiguous_iterator;
using std::input_or_output_iterator;
using std::sentinel_for;
using std::sized_sentinel_for;
using std::indirectly_readable;
using std::indirectly_writable;
#endif

// C++20 projected operations
#if __cpp_lib_concepts >= 202002L
using std::projected;
using std::indirect_result_t;
#endif

// Iterator type aliases
using std::iter_difference_t;
using std::iter_value_t;
using std::iter_reference_t;
using std::iter_rvalue_reference_t;

}  // namespace std

// Export ranges namespace for C++20 iterator utilities
export namespace std::ranges
{
using std::ranges::iter_move;
using std::ranges::iter_swap;
}  // namespace std::ranges
