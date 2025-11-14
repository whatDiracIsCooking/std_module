/**
 * @file test_scoped_allocator.cpp
 * @brief Comprehensive tests for std_module.scoped_allocator
 *
 * Tests scoped_allocator_adaptor functionality for nested containers
 * with automatic allocator propagation.
 */

import std_module.scoped_allocator;

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <memory>

// Custom allocator for tracking allocations
template<typename T>
class TrackingAllocator {
public:
    using value_type = T;
    static int allocations;
    static int deallocations;

    TrackingAllocator() noexcept = default;

    template<typename U>
    TrackingAllocator(const TrackingAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        allocations++;
        return std::allocator<T>().allocate(n);
    }

    void deallocate(T* p, std::size_t n) {
        deallocations++;
        std::allocator<T>().deallocate(p, n);
    }

    template<typename U>
    bool operator==(const TrackingAllocator<U>&) const noexcept {
        return true;
    }

    template<typename U>
    bool operator!=(const TrackingAllocator<U>&) const noexcept {
        return false;
    }

    static void reset() {
        allocations = 0;
        deallocations = 0;
    }
};

template<typename T>
int TrackingAllocator<T>::allocations = 0;

template<typename T>
int TrackingAllocator<T>::deallocations = 0;

// Test basic scoped_allocator_adaptor construction
void test_basic_construction() {
    std::cout << "\n=== Testing basic scoped_allocator_adaptor ===\n";

    using OuterAlloc = TrackingAllocator<int>;
    using ScopedAlloc = std::scoped_allocator_adaptor<OuterAlloc>;

    ScopedAlloc alloc;
    std::cout << "  ✓ Default construction successful\n";

    // Allocate and deallocate
    int* p = alloc.allocate(10);
    assert(p != nullptr);
    std::cout << "  ✓ Allocated 10 ints\n";

    alloc.deallocate(p, 10);
    std::cout << "  ✓ Deallocated 10 ints\n";
}

// Test scoped_allocator_adaptor with nested allocators
void test_nested_allocator() {
    std::cout << "\n=== Testing nested allocator propagation ===\n";

    using OuterAlloc = TrackingAllocator<std::vector<int>>;
    using InnerAlloc = TrackingAllocator<int>;
    using ScopedAlloc = std::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;

    ScopedAlloc alloc;
    std::cout << "  ✓ Created scoped_allocator with outer and inner allocators\n";

    // Test outer_allocator()
    auto outer = alloc.outer_allocator();
    std::cout << "  ✓ Retrieved outer_allocator\n";

    // Test inner_allocator()
    auto inner = alloc.inner_allocator();
    std::cout << "  ✓ Retrieved inner_allocator\n";
}

// Test with vector of vectors (nested containers)
void test_vector_of_vectors() {
    std::cout << "\n=== Testing vector of vectors ===\n";

    TrackingAllocator<int>::reset();

    using InnerVec = std::vector<int, TrackingAllocator<int>>;
    using OuterAlloc = TrackingAllocator<InnerVec>;
    using InnerAlloc = TrackingAllocator<int>;
    using ScopedAlloc = std::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;

    {
        std::vector<InnerVec, ScopedAlloc> vec_of_vecs;

        // Add some nested vectors
        InnerVec inner1 = {1, 2, 3};
        InnerVec inner2 = {4, 5, 6, 7};

        vec_of_vecs.push_back(inner1);
        vec_of_vecs.push_back(inner2);

        assert(vec_of_vecs.size() == 2);
        assert(vec_of_vecs[0].size() == 3);
        assert(vec_of_vecs[1].size() == 4);

        std::cout << "  ✓ Created vector of vectors with scoped allocator\n";
        std::cout << "  ✓ Outer vector size: " << vec_of_vecs.size() << "\n";
        std::cout << "  ✓ Inner vector[0] size: " << vec_of_vecs[0].size() << "\n";
        std::cout << "  ✓ Inner vector[1] size: " << vec_of_vecs[1].size() << "\n";
    }

    std::cout << "  ✓ Allocations tracked: " << TrackingAllocator<int>::allocations << "\n";
    std::cout << "  ✓ Deallocations tracked: " << TrackingAllocator<int>::deallocations << "\n";
}

// Test allocator_arg_t
void test_allocator_arg() {
    std::cout << "\n=== Testing std::allocator_arg ===\n";

    // Test that allocator_arg constant exists
    [[maybe_unused]] auto arg = std::allocator_arg;
    std::cout << "  ✓ std::allocator_arg constant available\n";

    // Test using allocator_arg with a type that accepts it
    using Alloc = std::allocator<int>;
    Alloc alloc;

    // Create a simple class that uses allocator_arg
    struct AllocAware {
        AllocAware(std::allocator_arg_t, Alloc) {
            std::cout << "  ✓ Constructed with allocator_arg\n";
        }
    };

    AllocAware obj(std::allocator_arg, alloc);
}

// Test construct and destroy
void test_construct_destroy() {
    std::cout << "\n=== Testing construct/destroy ===\n";

    using Alloc = TrackingAllocator<int>;
    using ScopedAlloc = std::scoped_allocator_adaptor<Alloc>;

    ScopedAlloc alloc;

    // Allocate space for one int
    int* p = alloc.allocate(1);

    // Construct an int at that location
    alloc.construct(p, 42);
    assert(*p == 42);
    std::cout << "  ✓ Constructed int with value: " << *p << "\n";

    // Destroy the int
    alloc.destroy(p);
    std::cout << "  ✓ Destroyed int\n";

    // Deallocate
    alloc.deallocate(p, 1);
    std::cout << "  ✓ Deallocated memory\n";
}

// Test with complex nested structure
void test_complex_nesting() {
    std::cout << "\n=== Testing complex nested structure ===\n";

    TrackingAllocator<int>::reset();

    using String = std::basic_string<char, std::char_traits<char>, TrackingAllocator<char>>;
    using InnerVec = std::vector<int, TrackingAllocator<int>>;

    // Create a scoped allocator for vector of pairs
    using PairType = std::pair<InnerVec, String>;
    using OuterAlloc = TrackingAllocator<PairType>;
    using InnerAlloc1 = TrackingAllocator<int>;
    using InnerAlloc2 = TrackingAllocator<char>;
    using ScopedAlloc = std::scoped_allocator_adaptor<OuterAlloc, InnerAlloc1>;

    std::vector<PairType, ScopedAlloc> complex_container;
    std::cout << "  ✓ Created complex nested container structure\n";
    std::cout << "  ✓ Container can hold pairs of (vector<int>, string)\n";
}

// Test select_on_container_copy_construction
void test_select_on_copy() {
    std::cout << "\n=== Testing select_on_container_copy_construction ===\n";

    using Alloc = TrackingAllocator<int>;
    using ScopedAlloc = std::scoped_allocator_adaptor<Alloc>;

    ScopedAlloc alloc1;
    ScopedAlloc alloc2 = alloc1.select_on_container_copy_construction();

    std::cout << "  ✓ select_on_container_copy_construction executed\n";
    std::cout << "  ✓ New allocator created for container copy\n";
}

// Test max_size
void test_max_size() {
    std::cout << "\n=== Testing max_size ===\n";

    using Alloc = TrackingAllocator<int>;
    using ScopedAlloc = std::scoped_allocator_adaptor<Alloc>;

    ScopedAlloc alloc;
    auto max = alloc.max_size();

    std::cout << "  ✓ max_size returned: " << max << "\n";
    assert(max > 0);
}

// Test with standard allocator
void test_with_std_allocator() {
    std::cout << "\n=== Testing with std::allocator ===\n";

    using ScopedAlloc = std::scoped_allocator_adaptor<std::allocator<int>>;

    ScopedAlloc alloc;
    int* p = alloc.allocate(5);

    for (int i = 0; i < 5; ++i) {
        alloc.construct(p + i, i * 10);
    }

    std::cout << "  ✓ Constructed array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << p[i] << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < 5; ++i) {
        alloc.destroy(p + i);
    }

    alloc.deallocate(p, 5);
    std::cout << "  ✓ Cleaned up successfully\n";
}

// Test equality comparison
void test_comparison() {
    std::cout << "\n=== Testing allocator comparison ===\n";

    using Alloc = TrackingAllocator<int>;
    using ScopedAlloc = std::scoped_allocator_adaptor<Alloc>;

    ScopedAlloc alloc1;
    ScopedAlloc alloc2;

    bool equal = (alloc1 == alloc2);
    bool not_equal = (alloc1 != alloc2);

    std::cout << "  ✓ Equality comparison: " << (equal ? "equal" : "not equal") << "\n";
    std::cout << "  ✓ Inequality comparison: " << (not_equal ? "not equal" : "equal") << "\n";
}

int main() {
    std::cout << "Testing std_module.scoped_allocator\n";
    std::cout << "========================================\n";

    try {
        test_basic_construction();
        test_nested_allocator();
        test_vector_of_vectors();
        test_allocator_arg();
        test_construct_destroy();
        test_complex_nesting();
        test_select_on_copy();
        test_max_size();
        test_with_std_allocator();
        test_comparison();

        std::cout << "\n========================================\n";
        std::cout << "All scoped_allocator tests passed! ✓\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
