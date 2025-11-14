/**
 * @file test_new.cpp
 * @brief Comprehensive test for std_module.new_ (C++20)
 * Note: Module name has underscore suffix to avoid C++ keyword conflict
 */

import std_module.new_;

#include <iostream>  // For output
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <cstddef>   // For size_t
#include <memory>    // For std::unique_ptr

// Custom new handler for testing
void custom_new_handler() {
    std::cout << "  ✓ Custom new handler called\n";
    throw std::bad_alloc();  // Standard behavior: throw bad_alloc
}

// Test basic bad_alloc exception
void test_bad_alloc() {
    std::cout << "Testing std::bad_alloc exception...\n";

    try {
        throw std::bad_alloc();
    } catch (const std::bad_alloc& e) {
        std::cout << "  ✓ Caught std::bad_alloc: " << e.what() << "\n";
    }

    // Test that bad_alloc is derived from exception
    try {
        throw std::bad_alloc();
    } catch (const std::exception& e) {
        std::cout << "  ✓ bad_alloc is derived from std::exception\n";
    }
}

// Test bad_array_new_length exception (C++11)
void test_bad_array_new_length() {
    std::cout << "\nTesting std::bad_array_new_length exception...\n";

    try {
        throw std::bad_array_new_length();
    } catch (const std::bad_array_new_length& e) {
        std::cout << "  ✓ Caught std::bad_array_new_length: " << e.what() << "\n";
    }

    // Test inheritance hierarchy
    try {
        throw std::bad_array_new_length();
    } catch (const std::bad_alloc& e) {
        std::cout << "  ✓ bad_array_new_length is derived from std::bad_alloc\n";
    }
}

// Test new handler functions
void test_new_handler() {
    std::cout << "\nTesting new handler functions...\n";

    // Get current handler (probably nullptr)
    std::new_handler old_handler = std::get_new_handler();
    std::cout << "  ✓ Retrieved current new handler\n";

    // Set a custom handler
    std::new_handler prev = std::set_new_handler(custom_new_handler);
    std::cout << "  ✓ Set custom new handler\n";

    // Verify it was set
    std::new_handler current = std::get_new_handler();
    assert(current == custom_new_handler);
    std::cout << "  ✓ Verified custom handler is active\n";

    // Restore original handler
    std::set_new_handler(old_handler);
    std::cout << "  ✓ Restored original handler\n";
}

// Test nothrow_t and nothrow constant
void test_nothrow() {
    std::cout << "\nTesting nothrow allocation...\n";

    // Allocate with nothrow - should return nullptr on failure, not throw
    void* ptr = ::operator new(100, std::nothrow);
    assert(ptr != nullptr);
    std::cout << "  ✓ Allocated memory with std::nothrow\n";

    // Clean up
    ::operator delete(ptr, std::nothrow);
    std::cout << "  ✓ Deallocated memory with std::nothrow\n";

    // Test nothrow_t type
    std::nothrow_t nothrow_tag = std::nothrow;
    void* ptr2 = ::operator new(200, nothrow_tag);
    assert(ptr2 != nullptr);
    std::cout << "  ✓ Used std::nothrow_t tag type\n";
    ::operator delete(ptr2, nothrow_tag);
}

// Test align_val_t (C++17)
void test_align_val() {
    std::cout << "\nTesting aligned allocation (C++17)...\n";

    // Allocate aligned memory
    std::align_val_t alignment{64};
    void* ptr = ::operator new(256, alignment);
    assert(ptr != nullptr);
    assert(reinterpret_cast<std::uintptr_t>(ptr) % 64 == 0);
    std::cout << "  ✓ Allocated 64-byte aligned memory\n";

    // Deallocate
    ::operator delete(ptr, alignment);
    std::cout << "  ✓ Deallocated aligned memory\n";

    // Test nothrow aligned allocation
    void* ptr2 = ::operator new(128, alignment, std::nothrow);
    assert(ptr2 != nullptr);
    assert(reinterpret_cast<std::uintptr_t>(ptr2) % 64 == 0);
    std::cout << "  ✓ Allocated aligned memory with nothrow\n";
    ::operator delete(ptr2, alignment);
}

// Test array allocation
void test_array_allocation() {
    std::cout << "\nTesting array allocation...\n";

    // Allocate array
    int* arr = new int[10];
    assert(arr != nullptr);
    std::cout << "  ✓ Allocated int array with new[]\n";

    // Use the array
    for (int i = 0; i < 10; ++i) {
        arr[i] = i * 2;
    }
    assert(arr[5] == 10);

    // Deallocate
    delete[] arr;
    std::cout << "  ✓ Deallocated array with delete[]\n";

    // Test nothrow array allocation
    int* arr2 = new (std::nothrow) int[20];
    assert(arr2 != nullptr);
    std::cout << "  ✓ Allocated array with nothrow\n";
    delete[] arr2;
}

// Simple class for placement new testing
struct TestObject {
    int value;
    explicit TestObject(int v) : value(v) {}
    ~TestObject() = default;
};

// Test placement new
void test_placement_new() {
    std::cout << "\nTesting placement new...\n";

    // Allocate raw memory
    alignas(TestObject) unsigned char buffer[sizeof(TestObject) * 2];

    // Construct objects in the buffer using placement new
    TestObject* p1 = new (&buffer[0]) TestObject(42);
    assert(p1->value == 42);
    std::cout << "  ✓ Placement new with object: " << p1->value << "\n";

    TestObject* p2 = new (&buffer[sizeof(TestObject)]) TestObject(99);
    assert(p2->value == 99);
    std::cout << "  ✓ Placement new with second object: " << p2->value << "\n";

    // Manually call destructors (required for placement new)
    p1->~TestObject();
    p2->~TestObject();
    std::cout << "  ✓ Manually destroyed placed objects\n";
}

// Test std::launder (C++17)
void test_launder() {
    std::cout << "\nTesting std::launder (C++17)...\n";

    // Allocate storage
    alignas(TestObject) unsigned char buffer[sizeof(TestObject)];

    // Construct an object
    TestObject* p = new (&buffer) TestObject(42);
    assert(p->value == 42);

    // Use launder to get a valid pointer after placement new
    TestObject* laundered = std::launder(reinterpret_cast<TestObject*>(&buffer));
    assert(laundered->value == 42);
    std::cout << "  ✓ std::launder returned valid pointer: " << laundered->value << "\n";

    // Destroy the object
    laundered->~TestObject();

    // Construct a new object in the same location
    TestObject* p2 = new (&buffer) TestObject(100);
    laundered = std::launder(reinterpret_cast<TestObject*>(&buffer));
    assert(laundered->value == 100);
    std::cout << "  ✓ std::launder works after reusing storage: " << laundered->value << "\n";

    laundered->~TestObject();
}

// Test sized deallocation (if available)
void test_sized_deallocation() {
    std::cout << "\nTesting sized deallocation...\n";

    // Allocate memory
    std::size_t size = 256;
    void* ptr = ::operator new(size);
    assert(ptr != nullptr);
    std::cout << "  ✓ Allocated " << size << " bytes\n";

    // Deallocate - sized deallocation may not be available
    ::operator delete(ptr);
    std::cout << "  ✓ Deallocated memory\n";

    // Test aligned allocation and deallocation
    std::align_val_t alignment{32};
    void* ptr2 = ::operator new(128, alignment);
    assert(ptr2 != nullptr);
    std::cout << "  ✓ Allocated aligned memory\n";

    ::operator delete(ptr2, alignment);
    std::cout << "  ✓ Deallocated aligned memory\n";
}

#ifdef __cpp_lib_hardware_interference_size
// Test hardware interference sizes (C++17, may not be available)
void test_hardware_interference_size() {
    std::cout << "\nTesting hardware interference sizes (C++17)...\n";

    std::size_t destructive = std::hardware_destructive_interference_size;
    std::size_t constructive = std::hardware_constructive_interference_size;

    std::cout << "  ✓ Destructive interference size: " << destructive << " bytes\n";
    std::cout << "  ✓ Constructive interference size: " << constructive << " bytes\n";

    assert(destructive > 0);
    assert(constructive > 0);
}
#endif

// Test destroying_delete_t (C++20)
void test_destroying_delete() {
    std::cout << "\nTesting std::destroying_delete_t (C++20)...\n";

    // We can't easily test the destroying delete behavior without
    // a class that uses it, but we can verify the type exists
    [[maybe_unused]] std::destroying_delete_t tag = std::destroying_delete;
    std::cout << "  ✓ std::destroying_delete_t type is available\n";
    std::cout << "  ✓ std::destroying_delete constant is available\n";

    // Note: Destroying delete is used in operator delete overloads
    // that handle destruction themselves. This is an advanced feature
    // mainly used by allocator-aware types.
}

// Test that types are movable/copyable as expected
void test_type_properties() {
    std::cout << "\nTesting type properties...\n";

    // nothrow_t should be default constructible
    std::nothrow_t nt1;
    std::nothrow_t nt2 = nt1;
    std::cout << "  ✓ std::nothrow_t is copyable\n";

    // align_val_t is an enum class
    std::align_val_t align1{16};
    std::align_val_t align2 = align1;
    assert(align1 == align2);
    std::cout << "  ✓ std::align_val_t is copyable and comparable\n";
}

// Test basic operator new/delete
void test_basic_operators() {
    std::cout << "\nTesting basic operator new/delete...\n";

    // Single object
    int* p = new int(42);
    assert(p != nullptr);
    assert(*p == 42);
    std::cout << "  ✓ operator new for single object\n";
    delete p;
    std::cout << "  ✓ operator delete for single object\n";

    // Array
    int* arr = new int[5]{1, 2, 3, 4, 5};
    assert(arr != nullptr);
    assert(arr[2] == 3);
    std::cout << "  ✓ operator new[] for array\n";
    delete[] arr;
    std::cout << "  ✓ operator delete[] for array\n";
}

// Test that allocation failure throws bad_alloc
void test_allocation_failure() {
    std::cout << "\nTesting allocation failure handling...\n";

    // Set a handler that throws
    std::set_new_handler(custom_new_handler);

    // Try to allocate an impossibly large amount
    // Note: Modern systems may not fail here due to overcommit,
    // so we just test that the handler mechanism works
    try {
        // Request a huge allocation
        [[maybe_unused]] void* ptr = ::operator new(static_cast<std::size_t>(-1) / 2);
        // If we got here, the allocation succeeded (unlikely) or overcommit is on
        ::operator delete(ptr);
        std::cout << "  ⚠ Large allocation succeeded (overcommit enabled?)\n";
    } catch (const std::bad_alloc& e) {
        std::cout << "  ✓ Allocation failure triggered bad_alloc\n";
    }

    // Restore handler
    std::set_new_handler(nullptr);
}

int main() {
    std::cout << "==============================================\n";
    std::cout << "std_module.new Comprehensive Test Suite\n";
    std::cout << "==============================================\n\n";

    test_bad_alloc();
    test_bad_array_new_length();
    test_new_handler();
    test_nothrow();
    test_align_val();
    test_array_allocation();
    test_placement_new();
    test_launder();
    test_sized_deallocation();

#ifdef __cpp_lib_hardware_interference_size
    test_hardware_interference_size();
#else
    std::cout << "\nNote: hardware_interference_size not available on this compiler\n";
#endif

    test_destroying_delete();
    test_type_properties();
    test_basic_operators();
    test_allocation_failure();

    std::cout << "\n==============================================\n";
    std::cout << "All tests passed! ✓\n";
    std::cout << "==============================================\n";

    return 0;
}
