/**
 * @file test_memory_resource.cpp
 * @brief Tests for std_module.memory_resource
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that PMR memory resources are accessible through the module.
 */

import std_module.memory_resource;
import std_module.test_framework;

#include <vector>
#include <string>

int main() {
    test::test_header("std_module.memory_resource");

    test::section("Testing symbol accessibility");

    // Test memory resource functions
    auto* default_rsrc = std::pmr::get_default_resource();
    test::assert_true(default_rsrc != nullptr, "get_default_resource");

    auto* new_delete_rsrc = std::pmr::new_delete_resource();
    test::assert_true(new_delete_rsrc != nullptr, "new_delete_resource");

    auto* null_rsrc = std::pmr::null_memory_resource();
    test::assert_true(null_rsrc != nullptr, "null_memory_resource");

    auto* old_default = std::pmr::set_default_resource(new_delete_rsrc);
    test::assert_true(std::pmr::get_default_resource() == new_delete_rsrc, "set_default_resource");
    std::pmr::set_default_resource(old_default);

    // Test polymorphic_allocator
    std::pmr::polymorphic_allocator<int> alloc1;
    test::success("polymorphic_allocator construction");

    std::pmr::polymorphic_allocator<int> alloc2(std::pmr::new_delete_resource());
    int* p = alloc2.allocate(10);
    test::assert_true(p != nullptr, "polymorphic_allocator::allocate");
    alloc2.deallocate(p, 10);
    test::success("polymorphic_allocator::deallocate");

    // Test monotonic_buffer_resource
    char buffer[1024];
    std::pmr::monotonic_buffer_resource mbr(buffer, sizeof(buffer));
    test::success("monotonic_buffer_resource");

    std::pmr::polymorphic_allocator<int> mbr_alloc(&mbr);
    int* p2 = mbr_alloc.allocate(10);
    test::assert_true(p2 != nullptr, "monotonic_buffer_resource allocation");

    // Test synchronized_pool_resource
    std::pmr::synchronized_pool_resource spr;
    test::success("synchronized_pool_resource");

    std::pmr::pool_options opts;
    opts.max_blocks_per_chunk = 100;
    std::pmr::synchronized_pool_resource spr2(opts);
    test::success("synchronized_pool_resource with options");

    // Test unsynchronized_pool_resource
    std::pmr::unsynchronized_pool_resource upr;
    test::success("unsynchronized_pool_resource");

    // Test pool_options
    std::pmr::pool_options opts2;
    opts2.max_blocks_per_chunk = 200;
    opts2.largest_required_pool_block = 2048;
    test::assert_true(opts2.max_blocks_per_chunk == 200, "pool_options");

    // Test PMR containers
    std::pmr::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    test::assert_true(vec.size() == 2, "pmr::vector");

    std::pmr::string str("Hello, PMR!");
    test::assert_true(str == "Hello, PMR!", "pmr::string");

    test::test_footer();
    return 0;
}
