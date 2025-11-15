/**
 * @file test_typeindex.cpp
 * @brief Tests for std_module.typeindex
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.typeindex;
import std_module.test_framework;
#include <typeinfo>  // for typeid operator
#include <cstddef>   // for size_t

int main() {
    test::test_header("std_module.typeindex");

    test::section("Testing symbol accessibility");

    // type_index construction
    std::type_index ti1(typeid(int));
    std::type_index ti2(typeid(double));
    test::assert_true(ti1.name() != nullptr, "type_index construction");

    // Comparison
    test::assert_true(ti1 == ti1, "operator==");
    test::assert_true(ti1 != ti2, "operator!=");
    test::assert_true((ti1 < ti2) || (ti2 < ti1), "operator<");

    // Three-way comparison
    auto cmp = ti1 <=> ti1;
    test::assert_true(cmp == 0, "operator<=>");

    // name()
    const char* name = ti1.name();
    test::assert_true(name != nullptr, "name");

    // hash_code()
    size_t hash1 = ti1.hash_code();
    size_t hash2 = ti1.hash_code();
    test::assert_equal(hash1, hash2, "hash_code");

    // Hash support
    std::hash<std::type_index> hasher;
    test::assert_true(hasher(ti1) == hasher(ti1), "hash");

    test::test_footer();
    return 0;
}
