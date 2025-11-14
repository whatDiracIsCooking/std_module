/**
 * @file test_memory_resource.cpp
 * @brief Comprehensive test for std_module.memory_resource (C++20)
 */

import std_module.memory_resource;

#include <iostream>  // For output
#include <cassert>   // For assertions
#include <vector>    // For pmr::vector tests
#include <string>    // For pmr::string tests

void test_memory_resource_functions() {
    std::cout << "Testing memory resource functions...\n";

    // Get default resource
    auto* default_rsrc = std::pmr::get_default_resource();
    assert(default_rsrc != nullptr);
    std::cout << "  ✓ get_default_resource() returns non-null\n";

    // Get new_delete_resource
    auto* new_delete_rsrc = std::pmr::new_delete_resource();
    assert(new_delete_rsrc != nullptr);
    std::cout << "  ✓ new_delete_resource() returns non-null\n";

    // Get null_memory_resource
    auto* null_rsrc = std::pmr::null_memory_resource();
    assert(null_rsrc != nullptr);
    std::cout << "  ✓ null_memory_resource() returns non-null\n";

    // Set and restore default resource
    auto* old_default = std::pmr::set_default_resource(new_delete_rsrc);
    assert(std::pmr::get_default_resource() == new_delete_rsrc);
    std::pmr::set_default_resource(old_default);
    assert(std::pmr::get_default_resource() == old_default);
    std::cout << "  ✓ set_default_resource() works correctly\n";
}

void test_polymorphic_allocator() {
    std::cout << "\nTesting polymorphic_allocator...\n";

    // Create allocator with default resource
    std::pmr::polymorphic_allocator<int> alloc1;
    std::cout << "  ✓ polymorphic_allocator default construction\n";

    // Create allocator with specific resource
    std::pmr::polymorphic_allocator<int> alloc2(std::pmr::new_delete_resource());
    std::cout << "  ✓ polymorphic_allocator with specific resource\n";

    // Allocate and deallocate
    int* p = alloc1.allocate(10);
    assert(p != nullptr);
    alloc1.deallocate(p, 10);
    std::cout << "  ✓ allocate/deallocate works\n";

    // Test with different types
    std::pmr::polymorphic_allocator<std::string> string_alloc;
    std::string* str_p = string_alloc.allocate(1);
    assert(str_p != nullptr);
    string_alloc.construct(str_p, "Hello, PMR!");
    assert(*str_p == "Hello, PMR!");
    string_alloc.destroy(str_p);
    string_alloc.deallocate(str_p, 1);
    std::cout << "  ✓ construct/destroy works with strings\n";
}

void test_monotonic_buffer_resource() {
    std::cout << "\nTesting monotonic_buffer_resource...\n";

    // Default construction
    std::pmr::monotonic_buffer_resource mbr1;
    std::cout << "  ✓ monotonic_buffer_resource default construction\n";

    // Construction with buffer
    char buffer[1024];
    std::pmr::monotonic_buffer_resource mbr2(buffer, sizeof(buffer));
    std::cout << "  ✓ monotonic_buffer_resource with buffer\n";

    // Use with polymorphic_allocator
    std::pmr::polymorphic_allocator<int> alloc(&mbr2);
    int* p1 = alloc.allocate(10);
    int* p2 = alloc.allocate(20);
    assert(p1 != nullptr);
    assert(p2 != nullptr);
    std::cout << "  ✓ monotonic_buffer_resource allocation works\n";

    // Note: monotonic_buffer_resource doesn't actually free until destruction
    alloc.deallocate(p1, 10);  // This is a no-op
    alloc.deallocate(p2, 20);  // This is a no-op
    std::cout << "  ✓ monotonic_buffer_resource deallocate (no-op) works\n";
}

void test_synchronized_pool_resource() {
    std::cout << "\nTesting synchronized_pool_resource...\n";

    // Default construction
    std::pmr::synchronized_pool_resource spr1;
    std::cout << "  ✓ synchronized_pool_resource default construction\n";

    // Construction with options
    std::pmr::pool_options opts;
    opts.max_blocks_per_chunk = 100;
    opts.largest_required_pool_block = 1024;
    std::pmr::synchronized_pool_resource spr2(opts);
    std::cout << "  ✓ synchronized_pool_resource with options\n";

    // Use with polymorphic_allocator
    std::pmr::polymorphic_allocator<int> alloc(&spr1);
    int* p = alloc.allocate(10);
    assert(p != nullptr);
    alloc.deallocate(p, 10);
    std::cout << "  ✓ synchronized_pool_resource allocation/deallocation works\n";
}

void test_unsynchronized_pool_resource() {
    std::cout << "\nTesting unsynchronized_pool_resource...\n";

    // Default construction
    std::pmr::unsynchronized_pool_resource upr1;
    std::cout << "  ✓ unsynchronized_pool_resource default construction\n";

    // Construction with options
    std::pmr::pool_options opts;
    opts.max_blocks_per_chunk = 50;
    opts.largest_required_pool_block = 512;
    std::pmr::unsynchronized_pool_resource upr2(opts);
    std::cout << "  ✓ unsynchronized_pool_resource with options\n";

    // Use with polymorphic_allocator
    std::pmr::polymorphic_allocator<double> alloc(&upr1);
    double* p = alloc.allocate(20);
    assert(p != nullptr);
    for (int i = 0; i < 20; ++i) {
        p[i] = i * 1.5;
    }
    assert(p[10] == 15.0);
    alloc.deallocate(p, 20);
    std::cout << "  ✓ unsynchronized_pool_resource allocation/deallocation works\n";
}

void test_pool_options() {
    std::cout << "\nTesting pool_options...\n";

    std::pmr::pool_options opts;

    // Set options
    opts.max_blocks_per_chunk = 200;
    opts.largest_required_pool_block = 2048;

    assert(opts.max_blocks_per_chunk == 200);
    assert(opts.largest_required_pool_block == 2048);

    std::cout << "  ✓ pool_options members accessible\n";
    std::cout << "    max_blocks_per_chunk: " << opts.max_blocks_per_chunk << "\n";
    std::cout << "    largest_required_pool_block: " << opts.largest_required_pool_block << "\n";
}

void test_pmr_containers() {
    std::cout << "\nTesting PMR containers...\n";

    char buffer[4096];
    std::pmr::monotonic_buffer_resource mbr(buffer, sizeof(buffer));

    // Test pmr::vector
    std::pmr::vector<int> vec(&mbr);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    assert(vec.size() == 3);
    assert(vec[1] == 2);
    std::cout << "  ✓ pmr::vector works with custom allocator\n";

    // Test pmr::string
    std::pmr::string str("Hello, PMR!", &mbr);
    assert(str == "Hello, PMR!");
    std::cout << "  ✓ pmr::string works with custom allocator\n";
}

void test_null_memory_resource() {
    std::cout << "\nTesting null_memory_resource...\n";

    auto* null_rsrc = std::pmr::null_memory_resource();
    std::pmr::polymorphic_allocator<int> alloc(null_rsrc);

    bool threw = false;
    try {
        // This should throw because null_memory_resource always fails
        int* p = alloc.allocate(1);
        (void)p;  // Suppress unused warning if it doesn't throw
    } catch (const std::bad_alloc&) {
        threw = true;
    }

    assert(threw);
    std::cout << "  ✓ null_memory_resource throws on allocation as expected\n";
}

int main() {
    std::cout << "=== std_module.memory_resource Comprehensive Test Suite ===\n\n";

    test_memory_resource_functions();
    test_polymorphic_allocator();
    test_monotonic_buffer_resource();
    test_synchronized_pool_resource();
    test_unsynchronized_pool_resource();
    test_pool_options();
    test_pmr_containers();
    test_null_memory_resource();

    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}
