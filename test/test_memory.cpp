/**
 * @file test_memory.cpp
 * @brief Tests for std_module.memory
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that smart pointers and memory utilities are accessible through the module.
 */

import std_module.memory;
import std_module.test_framework;

int main() {
    test::test_header("std_module.memory");

    test::section("Testing symbol accessibility");

    // Test unique_ptr
    auto ptr = std::make_unique<int>(42);
    test::assert_true(*ptr == 42, "make_unique");
    ptr.reset(new int(100));
    test::success("unique_ptr::reset");
    int* raw = ptr.release();
    delete raw;
    test::success("unique_ptr::release");

    // Test unique_ptr with arrays
    auto arr = std::make_unique<int[]>(5);
    arr[0] = 10;
    test::success("make_unique array");

    auto arr2 = std::make_unique_for_overwrite<int[]>(3);
    test::success("make_unique_for_overwrite");

    // Test shared_ptr
    auto sp1 = std::make_shared<int>(42);
    test::assert_true(sp1.use_count() == 1, "make_shared");
    auto sp2 = sp1;
    test::assert_true(sp1.use_count() == 2, "shared_ptr copy");
    sp2.reset();
    test::assert_true(sp1.use_count() == 1, "shared_ptr::reset");

    // Test weak_ptr
    std::weak_ptr<int> weak = sp1;
    test::assert_true(!weak.expired(), "weak_ptr");
    if (auto locked = weak.lock()) {
        test::success("weak_ptr::lock");
    }

    // Test allocate_shared
    std::allocator<int> alloc;
    auto sp3 = std::allocate_shared<int>(alloc, 555);
    test::assert_true(*sp3 == 555, "allocate_shared");

    auto sp4 = std::make_shared_for_overwrite<int>();
    test::success("make_shared_for_overwrite");

    // Test smart pointer casting
    struct Base { virtual ~Base() = default; int val = 10; };
    struct Derived : Base { int dval = 20; };
    auto derived_sp = std::make_shared<Derived>();
    auto base_sp = std::static_pointer_cast<Base>(derived_sp);
    test::success("static_pointer_cast");
    auto derived_again = std::dynamic_pointer_cast<Derived>(base_sp);
    test::assert_true(derived_again != nullptr, "dynamic_pointer_cast");

    // Test addressof
    int value = 42;
    int* addr = std::addressof(value);
    test::assert_true(addr == &value, "addressof");

    // Test to_address
    test::assert_true(std::to_address(addr) == addr, "to_address");
    auto uniq = std::make_unique<int>(100);
    test::assert_true(*std::to_address(uniq) == 100, "to_address with unique_ptr");

    // Test pointer_traits
    using traits = std::pointer_traits<int*>;
    int* ptr_to = traits::pointer_to(value);
    test::assert_true(ptr_to == &value, "pointer_traits::pointer_to");

    // Test allocator
    std::allocator<int> alloc2;
    int* p = alloc2.allocate(5);
    std::construct_at(p, 99);
    test::assert_true(*p == 99, "allocator::allocate and construct_at");
    std::destroy_at(p);
    alloc2.deallocate(p, 5);
    test::success("destroy_at and deallocate");

    // Test allocator_traits
    using traits2 = std::allocator_traits<std::allocator<int>>;
    std::allocator<int> alloc3;
    int* p2 = traits2::allocate(alloc3, 1);
    traits2::construct(alloc3, p2, 999);
    test::assert_true(*p2 == 999, "allocator_traits");
    traits2::destroy(alloc3, p2);
    traits2::deallocate(alloc3, p2, 1);
    test::success("allocator_traits destroy/deallocate");

    // Test uninitialized algorithms
    std::allocator<int> alloc4;
    int* buffer = alloc4.allocate(5);
    std::uninitialized_fill(buffer, buffer + 5, 42);
    test::assert_true(buffer[0] == 42, "uninitialized_fill");
    std::destroy(buffer, buffer + 5);
    
    std::uninitialized_fill_n(buffer, 3, 77);
    test::success("uninitialized_fill_n");
    std::destroy_n(buffer, 3);
    
    int source[] = {10, 20, 30};
    std::uninitialized_copy(source, source + 3, buffer);
    test::assert_true(buffer[0] == 10, "uninitialized_copy");
    std::destroy(buffer, buffer + 3);
    
    std::uninitialized_copy_n(source, 2, buffer);
    test::success("uninitialized_copy_n");
    std::destroy_n(buffer, 2);
    
    alloc4.deallocate(buffer, 5);

    // Test assume_aligned
    alignas(16) int aligned_buffer[4] = {1, 2, 3, 4};
    int* aligned_ptr = std::assume_aligned<16>(aligned_buffer);
    test::assert_true(aligned_ptr[0] == 1, "assume_aligned");

    // Test owner_less
    auto sp5 = std::make_shared<int>(10);
    auto sp6 = sp5;
    std::owner_less<std::shared_ptr<int>> cmp;
    bool same_owner = !cmp(sp5, sp6) && !cmp(sp6, sp5);
    test::assert_true(same_owner, "owner_less");

    test::test_footer();
    return 0;
}
