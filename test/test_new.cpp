/**
 * @file test_new.cpp
 * @brief Tests for std_module.new_
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.new_;
import std_module.test_framework;

int main() {
    test::test_header("std_module.new_");

    test::section("Testing symbol accessibility");

    // Test exception types
    try {
        throw std::bad_alloc();
    } catch (const std::bad_alloc&) {
        test::success("bad_alloc");
    }

    try {
        throw std::bad_array_new_length();
    } catch (const std::bad_array_new_length&) {
        test::success("bad_array_new_length");
    }

    // Test new handler functions
    auto old_handler = std::get_new_handler();
    std::set_new_handler(nullptr);
    std::set_new_handler(old_handler);
    test::success("get_new_handler/set_new_handler");

    // Test nothrow constant
    void* p = ::operator new(100, std::nothrow);
    ::operator delete(p, std::nothrow);
    test::success("nothrow constant and operators");

    // Test align_val_t (C++17)
    std::align_val_t align{64};
    void* p2 = ::operator new(256, align);
    ::operator delete(p2, align);
    test::success("align_val_t and aligned operators");

    // Test launder (C++17)
    int val = 42;
    int* laundered = std::launder(&val);
    test::assert_true(laundered != nullptr, "launder");

    // Test destroying_delete_t (C++20)
    [[maybe_unused]] std::destroying_delete_t tag = std::destroying_delete;
    test::success("destroying_delete_t");

    test::test_footer();
    return 0;
}
