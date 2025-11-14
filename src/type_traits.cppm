/**
 * @file type_traits.cppm
 * @brief C++20 type_traits module wrapper
 */

module;

#include <type_traits>

export module std_module.type_traits;

export namespace std
{
// Primary type categories
using std::is_void;
using std::is_null_pointer;
using std::is_integral;
using std::is_floating_point;
using std::is_array;
using std::is_enum;
using std::is_union;
using std::is_class;
using std::is_function;
using std::is_pointer;
using std::is_lvalue_reference;
using std::is_rvalue_reference;
using std::is_member_object_pointer;
using std::is_member_function_pointer;

// Composite type categories
using std::is_fundamental;
using std::is_arithmetic;
using std::is_scalar;
using std::is_object;
using std::is_compound;
using std::is_reference;
using std::is_member_pointer;

// Type properties
using std::is_const;
using std::is_volatile;
using std::is_trivial;
using std::is_trivially_copyable;
using std::is_standard_layout;
using std::is_empty;
using std::is_polymorphic;
using std::is_abstract;
using std::is_final;
using std::is_aggregate;
using std::is_signed;
using std::is_unsigned;
using std::is_bounded_array;
using std::is_unbounded_array;

// Supported operations
using std::is_constructible;
using std::is_trivially_constructible;
using std::is_nothrow_constructible;
using std::is_default_constructible;
using std::is_trivially_default_constructible;
using std::is_nothrow_default_constructible;
using std::is_copy_constructible;
using std::is_trivially_copy_constructible;
using std::is_nothrow_copy_constructible;
using std::is_move_constructible;
using std::is_trivially_move_constructible;
using std::is_nothrow_move_constructible;
using std::is_assignable;
using std::is_trivially_assignable;
using std::is_nothrow_assignable;
using std::is_copy_assignable;
using std::is_trivially_copy_assignable;
using std::is_nothrow_copy_assignable;
using std::is_move_assignable;
using std::is_trivially_move_assignable;
using std::is_nothrow_move_assignable;
using std::is_destructible;
using std::is_trivially_destructible;
using std::is_nothrow_destructible;
using std::has_virtual_destructor;
using std::is_swappable_with;
using std::is_swappable;
using std::is_nothrow_swappable_with;
using std::is_nothrow_swappable;
using std::has_unique_object_representations;

// Property queries
using std::alignment_of;
using std::rank;
using std::extent;

// Type relationships
using std::is_same;
using std::is_base_of;
using std::is_convertible;
using std::is_nothrow_convertible;
using std::is_invocable;
using std::is_invocable_r;
using std::is_nothrow_invocable;
using std::is_nothrow_invocable_r;

// Const-volatility specifiers
using std::remove_cv;
using std::remove_const;
using std::remove_volatile;
using std::add_cv;
using std::add_const;
using std::add_volatile;
using std::remove_cv_t;
using std::remove_const_t;
using std::remove_volatile_t;
using std::add_cv_t;
using std::add_const_t;
using std::add_volatile_t;

// References
using std::remove_reference;
using std::add_lvalue_reference;
using std::add_rvalue_reference;
using std::remove_reference_t;
using std::add_lvalue_reference_t;
using std::add_rvalue_reference_t;

// Pointers
using std::remove_pointer;
using std::add_pointer;
using std::remove_pointer_t;
using std::add_pointer_t;

// Sign modifiers
using std::make_signed;
using std::make_unsigned;
using std::make_signed_t;
using std::make_unsigned_t;

// Arrays
using std::remove_extent;
using std::remove_all_extents;
using std::remove_extent_t;
using std::remove_all_extents_t;

// Miscellaneous transformations
using std::aligned_storage;
using std::aligned_union;
using std::decay;
using std::remove_cvref;
using std::enable_if;
using std::conditional;
using std::common_type;
using std::common_reference;
using std::basic_common_reference;
using std::underlying_type;
using std::invoke_result;
using std::void_t;
using std::type_identity;
using std::aligned_storage_t;
using std::aligned_union_t;
using std::decay_t;
using std::remove_cvref_t;
using std::enable_if_t;
using std::conditional_t;
using std::common_type_t;
using std::common_reference_t;
using std::underlying_type_t;
using std::invoke_result_t;
using std::type_identity_t;

// Logical operator traits
using std::conjunction;
using std::disjunction;
using std::negation;

// Helper variable templates (_v)
using std::is_void_v;
using std::is_null_pointer_v;
using std::is_integral_v;
using std::is_floating_point_v;
using std::is_array_v;
using std::is_enum_v;
using std::is_union_v;
using std::is_class_v;
using std::is_function_v;
using std::is_pointer_v;
using std::is_lvalue_reference_v;
using std::is_rvalue_reference_v;
using std::is_member_object_pointer_v;
using std::is_member_function_pointer_v;
using std::is_fundamental_v;
using std::is_arithmetic_v;
using std::is_scalar_v;
using std::is_object_v;
using std::is_compound_v;
using std::is_reference_v;
using std::is_member_pointer_v;
using std::is_const_v;
using std::is_volatile_v;
using std::is_trivial_v;
using std::is_trivially_copyable_v;
using std::is_standard_layout_v;
using std::is_empty_v;
using std::is_polymorphic_v;
using std::is_abstract_v;
using std::is_final_v;
using std::is_aggregate_v;
using std::is_signed_v;
using std::is_unsigned_v;
using std::is_bounded_array_v;
using std::is_unbounded_array_v;
using std::is_constructible_v;
using std::is_trivially_constructible_v;
using std::is_nothrow_constructible_v;
using std::is_default_constructible_v;
using std::is_trivially_default_constructible_v;
using std::is_nothrow_default_constructible_v;
using std::is_copy_constructible_v;
using std::is_trivially_copy_constructible_v;
using std::is_nothrow_copy_constructible_v;
using std::is_move_constructible_v;
using std::is_trivially_move_constructible_v;
using std::is_nothrow_move_constructible_v;
using std::is_assignable_v;
using std::is_trivially_assignable_v;
using std::is_nothrow_assignable_v;
using std::is_copy_assignable_v;
using std::is_trivially_copy_assignable_v;
using std::is_nothrow_copy_assignable_v;
using std::is_move_assignable_v;
using std::is_trivially_move_assignable_v;
using std::is_nothrow_move_assignable_v;
using std::is_destructible_v;
using std::is_trivially_destructible_v;
using std::is_nothrow_destructible_v;
using std::has_virtual_destructor_v;
using std::is_swappable_with_v;
using std::is_swappable_v;
using std::is_nothrow_swappable_with_v;
using std::is_nothrow_swappable_v;
using std::has_unique_object_representations_v;
using std::alignment_of_v;
using std::rank_v;
using std::extent_v;
using std::is_same_v;
using std::is_base_of_v;
using std::is_convertible_v;
using std::is_nothrow_convertible_v;
using std::is_invocable_v;
using std::is_invocable_r_v;
using std::is_nothrow_invocable_v;
using std::is_nothrow_invocable_r_v;
using std::conjunction_v;
using std::disjunction_v;
using std::negation_v;

// Constants
using std::bool_constant;
using std::true_type;
using std::false_type;
using std::integral_constant;
}  // namespace std
