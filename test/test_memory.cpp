/**
 * @file test_memory.cpp
 * @brief Comprehensive tests for std_module.memory
 */

import std_module.memory;

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>

// Custom deleter for testing
struct CustomDeleter {
    void operator()(int* p) const {
        std::cout << "  ✓ Custom deleter called for: " << *p << "\n";
        delete p;
    }
};

// Test class for object lifetime management
struct TestObject {
    int value;
    static int constructed_count;
    static int destroyed_count;

    TestObject(int v = 0) : value(v) { ++constructed_count; }
    ~TestObject() { ++destroyed_count; }
};

int TestObject::constructed_count = 0;
int TestObject::destroyed_count = 0;

// Test unique_ptr basic functionality
void test_unique_ptr_basic() {
    std::cout << "\n=== Testing unique_ptr basic functionality ===\n";

    // Create unique_ptr
    auto ptr = std::make_unique<int>(42);
    assert(ptr != nullptr);
    assert(*ptr == 42);
    std::cout << "  ✓ make_unique created pointer with value: " << *ptr << "\n";

    // Move ownership
    auto ptr2 = std::move(ptr);
    assert(ptr == nullptr);
    assert(ptr2 != nullptr);
    assert(*ptr2 == 42);
    std::cout << "  ✓ Ownership transferred via move: " << *ptr2 << "\n";

    // Reset
    ptr2.reset(new int(100));
    assert(*ptr2 == 100);
    std::cout << "  ✓ Reset with new value: " << *ptr2 << "\n";

    // Release
    int* raw = ptr2.release();
    assert(ptr2 == nullptr);
    assert(*raw == 100);
    std::cout << "  ✓ Released ownership, raw pointer value: " << *raw << "\n";
    delete raw;
}

// Test unique_ptr with custom deleter
void test_unique_ptr_custom_deleter() {
    std::cout << "\n=== Testing unique_ptr with custom deleter ===\n";

    std::unique_ptr<int, CustomDeleter> ptr(new int(999), CustomDeleter{});
    assert(*ptr == 999);
    std::cout << "  ✓ unique_ptr with custom deleter created\n";
    // Deleter will be called when ptr goes out of scope
}

// Test unique_ptr arrays
void test_unique_ptr_array() {
    std::cout << "\n=== Testing unique_ptr with arrays ===\n";

    auto arr = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }
    assert(arr[2] == 20);
    std::cout << "  ✓ make_unique array created, arr[2] = " << arr[2] << "\n";

    // C++20 make_unique_for_overwrite
    auto arr2 = std::make_unique_for_overwrite<int[]>(3);
    arr2[0] = 111;
    assert(arr2[0] == 111);
    std::cout << "  ✓ make_unique_for_overwrite created array\n";
}

// Test shared_ptr basic functionality
void test_shared_ptr_basic() {
    std::cout << "\n=== Testing shared_ptr basic functionality ===\n";

    auto ptr1 = std::make_shared<int>(42);
    assert(ptr1.use_count() == 1);
    std::cout << "  ✓ make_shared created, use_count: " << ptr1.use_count() << "\n";

    auto ptr2 = ptr1;
    assert(ptr1.use_count() == 2);
    assert(ptr2.use_count() == 2);
    assert(*ptr1 == 42);
    std::cout << "  ✓ Copied shared_ptr, use_count: " << ptr1.use_count() << "\n";

    ptr2.reset();
    assert(ptr1.use_count() == 1);
    assert(ptr2 == nullptr);
    std::cout << "  ✓ Reset one shared_ptr, remaining use_count: " << ptr1.use_count() << "\n";
}

// Test weak_ptr
void test_weak_ptr() {
    std::cout << "\n=== Testing weak_ptr ===\n";

    std::weak_ptr<int> weak;

    {
        auto shared = std::make_shared<int>(123);
        weak = shared;

        assert(!weak.expired());
        assert(weak.use_count() == 1);
        std::cout << "  ✓ weak_ptr created from shared_ptr, expired: " << weak.expired() << "\n";

        if (auto locked = weak.lock()) {
            assert(*locked == 123);
            std::cout << "  ✓ Locked weak_ptr, value: " << *locked << "\n";
        }
    }

    // shared_ptr destroyed, weak_ptr should be expired
    assert(weak.expired());
    assert(weak.use_count() == 0);
    std::cout << "  ✓ After shared_ptr destruction, weak_ptr expired: " << weak.expired() << "\n";
}

// Test shared_ptr with custom allocator
void test_shared_ptr_allocator() {
    std::cout << "\n=== Testing shared_ptr with allocator ===\n";

    std::allocator<int> alloc;
    auto ptr = std::allocate_shared<int>(alloc, 555);
    assert(*ptr == 555);
    std::cout << "  ✓ allocate_shared with custom allocator: " << *ptr << "\n";
}

// Test shared_ptr make_shared_for_overwrite (C++20)
void test_make_shared_for_overwrite() {
    std::cout << "\n=== Testing make_shared_for_overwrite ===\n";

    auto ptr = std::make_shared_for_overwrite<int>();
    *ptr = 777;
    assert(*ptr == 777);
    std::cout << "  ✓ make_shared_for_overwrite created: " << *ptr << "\n";
}

// Test enable_shared_from_this
void test_enable_shared_from_this() {
    std::cout << "\n=== Testing enable_shared_from_this ===\n";

    struct MyClass : std::enable_shared_from_this<MyClass> {
        int value;
        MyClass(int v) : value(v) {}

        std::shared_ptr<MyClass> get_shared() {
            return shared_from_this();
        }
    };

    auto ptr1 = std::make_shared<MyClass>(888);
    auto ptr2 = ptr1->get_shared();

    assert(ptr1.use_count() == 2);
    assert(ptr2.use_count() == 2);
    assert(ptr1.get() == ptr2.get());
    std::cout << "  ✓ shared_from_this works, use_count: " << ptr1.use_count() << "\n";
}

// Test smart pointer casting
void test_smart_pointer_casting() {
    std::cout << "\n=== Testing smart pointer casting ===\n";

    struct Base { virtual ~Base() = default; int base_val = 10; };
    struct Derived : Base { int derived_val = 20; };

    auto derived_ptr = std::make_shared<Derived>();
    auto base_ptr = std::static_pointer_cast<Base>(derived_ptr);

    assert(base_ptr->base_val == 10);
    std::cout << "  ✓ static_pointer_cast succeeded\n";

    auto derived_again = std::dynamic_pointer_cast<Derived>(base_ptr);
    assert(derived_again != nullptr);
    assert(derived_again->derived_val == 20);
    std::cout << "  ✓ dynamic_pointer_cast succeeded\n";

    // const_pointer_cast
    auto const_ptr = std::make_shared<const int>(99);
    auto mutable_ptr = std::const_pointer_cast<int>(const_ptr);
    assert(*mutable_ptr == 99);
    std::cout << "  ✓ const_pointer_cast succeeded\n";
}

// Test addressof
void test_addressof() {
    std::cout << "\n=== Testing addressof ===\n";

    int value = 42;
    int* addr1 = &value;
    int* addr2 = std::addressof(value);

    assert(addr1 == addr2);
    std::cout << "  ✓ addressof returns correct address\n";

    // Test with object that overloads operator&
    struct WeirdClass {
        int* operator&() { return nullptr; }  // Evil overload
        int value = 123;
    };

    WeirdClass weird;
    auto* real_addr = std::addressof(weird);
    assert(real_addr != nullptr);
    assert(real_addr->value == 123);
    std::cout << "  ✓ addressof works even with overloaded operator&\n";
}

// Test to_address (C++20)
void test_to_address() {
    std::cout << "\n=== Testing to_address ===\n";

    int value = 42;
    int* ptr = &value;

    assert(std::to_address(ptr) == ptr);
    std::cout << "  ✓ to_address with raw pointer\n";

    auto unique = std::make_unique<int>(100);
    assert(*std::to_address(unique) == 100);
    std::cout << "  ✓ to_address with unique_ptr\n";
}

// Test pointer_traits
void test_pointer_traits() {
    std::cout << "\n=== Testing pointer_traits ===\n";

    using traits = std::pointer_traits<int*>;

    int value = 42;
    int* ptr = traits::pointer_to(value);

    assert(ptr == &value);
    assert(*ptr == 42);
    std::cout << "  ✓ pointer_traits::pointer_to works\n";
}

// Test allocator
void test_allocator() {
    std::cout << "\n=== Testing allocator ===\n";

    std::allocator<int> alloc;

    // Allocate memory for 5 ints
    int* ptr = alloc.allocate(5);

    // Construct objects
    for (int i = 0; i < 5; ++i) {
        std::construct_at(ptr + i, i * 10);
    }

    assert(ptr[2] == 20);
    std::cout << "  ✓ Allocated and constructed, ptr[2] = " << ptr[2] << "\n";

    // Destroy objects
    for (int i = 0; i < 5; ++i) {
        std::destroy_at(ptr + i);
    }

    // Deallocate memory
    alloc.deallocate(ptr, 5);
    std::cout << "  ✓ Destroyed and deallocated\n";
}

// Test allocator_traits
void test_allocator_traits() {
    std::cout << "\n=== Testing allocator_traits ===\n";

    using traits = std::allocator_traits<std::allocator<int>>;
    std::allocator<int> alloc;

    int* ptr = traits::allocate(alloc, 1);
    traits::construct(alloc, ptr, 999);

    assert(*ptr == 999);
    std::cout << "  ✓ allocator_traits construct: " << *ptr << "\n";

    traits::destroy(alloc, ptr);
    traits::deallocate(alloc, ptr, 1);
    std::cout << "  ✓ allocator_traits destroy and deallocate\n";
}

// Test uninitialized memory algorithms
void test_uninitialized_algorithms() {
    std::cout << "\n=== Testing uninitialized memory algorithms ===\n";

    std::allocator<int> alloc;
    int* buffer = alloc.allocate(5);

    // uninitialized_fill
    std::uninitialized_fill(buffer, buffer + 5, 42);
    assert(buffer[0] == 42);
    assert(buffer[4] == 42);
    std::cout << "  ✓ uninitialized_fill: buffer[0] = " << buffer[0] << "\n";

    // Destroy
    std::destroy(buffer, buffer + 5);

    // uninitialized_fill_n
    std::uninitialized_fill_n(buffer, 3, 77);
    assert(buffer[0] == 77);
    assert(buffer[2] == 77);
    std::cout << "  ✓ uninitialized_fill_n: buffer[2] = " << buffer[2] << "\n";

    std::destroy_n(buffer, 3);

    // uninitialized_copy
    int source[] = {10, 20, 30};
    std::uninitialized_copy(source, source + 3, buffer);
    assert(buffer[0] == 10);
    assert(buffer[2] == 30);
    std::cout << "  ✓ uninitialized_copy: buffer[2] = " << buffer[2] << "\n";

    std::destroy(buffer, buffer + 3);

    // uninitialized_copy_n
    std::uninitialized_copy_n(source, 2, buffer);
    assert(buffer[0] == 10);
    assert(buffer[1] == 20);
    std::cout << "  ✓ uninitialized_copy_n: buffer[1] = " << buffer[1] << "\n";

    std::destroy_n(buffer, 2);

    alloc.deallocate(buffer, 5);
}

// Test uninitialized_default_construct and uninitialized_value_construct
void test_uninitialized_construct() {
    std::cout << "\n=== Testing uninitialized construction ===\n";

    TestObject::constructed_count = 0;
    TestObject::destroyed_count = 0;

    std::allocator<TestObject> alloc;
    TestObject* buffer = alloc.allocate(5);

    // default construct
    std::uninitialized_default_construct(buffer, buffer + 5);
    assert(TestObject::constructed_count == 5);
    std::cout << "  ✓ uninitialized_default_construct: " << TestObject::constructed_count << " objects\n";

    std::destroy(buffer, buffer + 5);
    assert(TestObject::destroyed_count == 5);

    // value construct
    TestObject::constructed_count = 0;
    TestObject::destroyed_count = 0;
    std::uninitialized_value_construct_n(buffer, 3);
    assert(TestObject::constructed_count == 3);
    std::cout << "  ✓ uninitialized_value_construct_n: " << TestObject::constructed_count << " objects\n";

    std::destroy_n(buffer, 3);

    alloc.deallocate(buffer, 5);
}

// Test uninitialized_move
void test_uninitialized_move() {
    std::cout << "\n=== Testing uninitialized_move ===\n";

    std::allocator<std::string> alloc;

    std::string* source = alloc.allocate(3);
    std::construct_at(source + 0, "Hello");
    std::construct_at(source + 1, "World");
    std::construct_at(source + 2, "!");

    std::string* dest = alloc.allocate(3);
    std::uninitialized_move(source, source + 3, dest);

    assert(dest[0] == "Hello");
    assert(dest[1] == "World");
    assert(dest[2] == "!");
    std::cout << "  ✓ uninitialized_move: \"" << dest[0] << " " << dest[1] << dest[2] << "\"\n";

    // uninitialized_move_n (re-initialize source first since previous move emptied them)
    std::destroy(source, source + 3);
    std::construct_at(source + 0, "Foo");
    std::construct_at(source + 1, "Bar");

    std::destroy(dest, dest + 3);
    std::uninitialized_move_n(source, 2, dest);
    assert(dest[0] == "Foo");
    assert(dest[1] == "Bar");
    std::cout << "  ✓ uninitialized_move_n\n";

    std::destroy(source, source + 2);
    std::destroy(dest, dest + 2);
    alloc.deallocate(source, 3);
    alloc.deallocate(dest, 3);
}

// Test construct_at and destroy_at
void test_construct_destroy_at() {
    std::cout << "\n=== Testing construct_at and destroy_at ===\n";

    TestObject::constructed_count = 0;
    TestObject::destroyed_count = 0;

    alignas(TestObject) unsigned char buffer[sizeof(TestObject)];
    TestObject* obj = reinterpret_cast<TestObject*>(buffer);

    std::construct_at(obj, 42);
    assert(obj->value == 42);
    assert(TestObject::constructed_count == 1);
    std::cout << "  ✓ construct_at created object with value: " << obj->value << "\n";

    std::destroy_at(obj);
    assert(TestObject::destroyed_count == 1);
    std::cout << "  ✓ destroy_at destroyed object\n";
}

// Test uses_allocator
void test_uses_allocator() {
    std::cout << "\n=== Testing uses_allocator ===\n";

    // std::vector uses allocator
    bool uses_alloc = std::uses_allocator<std::vector<int>, std::allocator<int>>::value;
    assert(uses_alloc);
    std::cout << "  ✓ std::vector uses allocator: " << uses_alloc << "\n";

    // int doesn't use allocator
    bool int_uses_alloc = std::uses_allocator_v<int, std::allocator<int>>;
    assert(!int_uses_alloc);
    std::cout << "  ✓ int doesn't use allocator: " << int_uses_alloc << "\n";
}

// Test assume_aligned (C++20)
void test_assume_aligned() {
    std::cout << "\n=== Testing assume_aligned ===\n";

    alignas(16) int buffer[4] = {1, 2, 3, 4};
    int* aligned_ptr = std::assume_aligned<16>(buffer);

    assert(aligned_ptr[0] == 1);
    assert(aligned_ptr[3] == 4);
    std::cout << "  ✓ assume_aligned works, values: " << aligned_ptr[0] << ", " << aligned_ptr[3] << "\n";
}

// Test PMR allocators
void test_pmr_allocators() {
    std::cout << "\n=== Testing PMR allocators ===\n";

    // Note: Many PMR features are C++17 and may not be available in all implementations
    // Testing only the basic polymorphic_allocator which should be available

    // polymorphic_allocator
    std::pmr::polymorphic_allocator<int> pmr_alloc;
    int* ptr = pmr_alloc.allocate(1);
    pmr_alloc.construct(ptr, 333);
    assert(*ptr == 333);
    std::cout << "  ✓ polymorphic_allocator: " << *ptr << "\n";
    pmr_alloc.destroy(ptr);
    pmr_alloc.deallocate(ptr, 1);

    // FIXME: The following PMR features are not available in this compiler/stdlib:
    // - get_default_resource / set_default_resource
    // - new_delete_resource / null_memory_resource
    // - monotonic_buffer_resource
    // - synchronized_pool_resource / unsynchronized_pool_resource
    // - pool_options
}

// Test owner_less
void test_owner_less() {
    std::cout << "\n=== Testing owner_less ===\n";

    auto sp1 = std::make_shared<int>(10);
    auto sp2 = sp1;
    auto sp3 = std::make_shared<int>(10);

    std::owner_less<std::shared_ptr<int>> cmp;

    // sp1 and sp2 share ownership
    bool same_owner = !cmp(sp1, sp2) && !cmp(sp2, sp1);
    assert(same_owner);
    std::cout << "  ✓ owner_less: sp1 and sp2 have same owner\n";

    // sp1 and sp3 have different ownership
    bool diff_owner = cmp(sp1, sp3) || cmp(sp3, sp1);
    assert(diff_owner);
    std::cout << "  ✓ owner_less: sp1 and sp3 have different owners\n";
}

// Test default_delete
void test_default_delete() {
    std::cout << "\n=== Testing default_delete ===\n";

    int* raw = new int(42);
    std::default_delete<int> deleter;
    deleter(raw);
    std::cout << "  ✓ default_delete invoked\n";

    int* arr = new int[5];
    std::default_delete<int[]> arr_deleter;
    arr_deleter(arr);
    std::cout << "  ✓ default_delete<T[]> invoked for array\n";
}

int main() {
    std::cout << "Testing std_module.memory\n";
    std::cout << "========================\n";

    test_unique_ptr_basic();
    test_unique_ptr_custom_deleter();
    test_unique_ptr_array();
    test_shared_ptr_basic();
    test_weak_ptr();
    test_shared_ptr_allocator();
    test_make_shared_for_overwrite();
    test_enable_shared_from_this();
    test_smart_pointer_casting();
    test_addressof();
    test_to_address();
    test_pointer_traits();
    test_allocator();
    test_allocator_traits();
    test_uninitialized_algorithms();
    test_uninitialized_construct();
    test_uninitialized_move();
    test_construct_destroy_at();
    test_uses_allocator();
    test_assume_aligned();
    test_pmr_allocators();
    test_owner_less();
    test_default_delete();

    std::cout << "\n========================\n";
    std::cout << "All std_module.memory tests passed! ✓\n";

    return 0;
}
