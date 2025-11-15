/**
 * @file test_scoped_allocator.cpp
 * @brief Tests for std_module.scoped_allocator
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.scoped_allocator;
import std_module.test_framework;

int main() {
    test::test_header("std_module.scoped_allocator");

    test::section("Testing symbol accessibility");

    // Test basic scoped_allocator_adaptor
    using Alloc = std::allocator<int>;
    using ScopedAlloc = std::scoped_allocator_adaptor<Alloc>;

    ScopedAlloc alloc;
    test::success("scoped_allocator_adaptor construction");

    // Test allocation
    int* p = alloc.allocate(10);
    test::assert_true(p != nullptr, "allocate");

    alloc.deallocate(p, 10);
    test::success("deallocate");

    // Test nested allocators
    using InnerAlloc = std::allocator<int>;
    using NestedAlloc = std::scoped_allocator_adaptor<Alloc, InnerAlloc>;

    NestedAlloc nested_alloc;
    test::success("nested scoped_allocator construction");

    auto outer = nested_alloc.outer_allocator();
    test::success("outer_allocator()");

    auto inner = nested_alloc.inner_allocator();
    test::success("inner_allocator()");

    // Test construct/destroy
    int* p2 = alloc.allocate(1);
    alloc.construct(p2, 42);
    test::assert_equal(*p2, 42, "construct");

    alloc.destroy(p2);
    test::success("destroy");

    alloc.deallocate(p2, 1);

    // Test allocator_arg
    [[maybe_unused]] auto arg = std::allocator_arg;
    test::success("allocator_arg constant");

    // Test select_on_container_copy_construction
    ScopedAlloc alloc2 = alloc.select_on_container_copy_construction();
    test::success("select_on_container_copy_construction");

    // Test max_size
    auto max = alloc.max_size();
    test::assert_true(max > 0, "max_size");

    test::test_footer();
    return 0;
}
