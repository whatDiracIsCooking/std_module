/**
 * @file ranges.cppm
 * @brief C++20 ranges module wrapper
 */

module;

#include <ranges>

export module std_module.ranges;

export namespace std
{
namespace ranges
{
// Range access
using std::ranges::begin;
using std::ranges::end;
using std::ranges::cbegin;
using std::ranges::cend;
using std::ranges::rbegin;
using std::ranges::rend;
using std::ranges::crbegin;
using std::ranges::crend;
using std::ranges::size;
using std::ranges::ssize;
using std::ranges::empty;
using std::ranges::data;
using std::ranges::cdata;

// Range concepts
using std::ranges::range;
using std::ranges::borrowed_range;
using std::ranges::sized_range;
using std::ranges::view;
using std::ranges::input_range;
using std::ranges::output_range;
using std::ranges::forward_range;
using std::ranges::bidirectional_range;
using std::ranges::random_access_range;
using std::ranges::contiguous_range;
using std::ranges::common_range;
using std::ranges::viewable_range;

// Range utilities
using std::ranges::subrange;
using std::ranges::subrange_kind;
using std::ranges::dangling;
using std::ranges::borrowed_iterator_t;
using std::ranges::borrowed_subrange_t;
using std::ranges::iterator_t;
using std::ranges::sentinel_t;
using std::ranges::range_difference_t;
using std::ranges::range_size_t;
using std::ranges::range_value_t;
using std::ranges::range_reference_t;
using std::ranges::range_rvalue_reference_t;

// View interface
using std::ranges::view_interface;
using std::ranges::view_base;

// Range factories
using std::ranges::empty_view;
using std::ranges::single_view;
using std::ranges::iota_view;
using std::ranges::istream_view;

// Range adaptors
using std::ranges::ref_view;
using std::ranges::owning_view;
using std::ranges::filter_view;
using std::ranges::transform_view;
using std::ranges::take_view;
using std::ranges::take_while_view;
using std::ranges::drop_view;
using std::ranges::drop_while_view;
using std::ranges::join_view;
using std::ranges::split_view;
using std::ranges::lazy_split_view;
using std::ranges::common_view;
using std::ranges::reverse_view;
using std::ranges::elements_view;
using std::ranges::keys_view;
using std::ranges::values_view;

// views namespace
namespace views
{
using std::ranges::views::all;
using std::ranges::views::all_t;
using std::ranges::views::filter;
using std::ranges::views::transform;
using std::ranges::views::take;
using std::ranges::views::take_while;
using std::ranges::views::drop;
using std::ranges::views::drop_while;
using std::ranges::views::join;
using std::ranges::views::split;
using std::ranges::views::lazy_split;
using std::ranges::views::counted;
using std::ranges::views::common;
using std::ranges::views::reverse;
using std::ranges::views::elements;
using std::ranges::views::keys;
using std::ranges::views::values;
using std::ranges::views::empty;
using std::ranges::views::single;
using std::ranges::views::iota;
using std::ranges::views::istream;
}  // namespace views

}  // namespace ranges
}  // namespace std
