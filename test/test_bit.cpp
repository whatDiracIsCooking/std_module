/**
 * @file test_bit.cpp
 * @brief Tests for std_module.bit
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.bit;
import std_module.test_framework;

#include <cstdint>

int main() {
    test::test_header("std_module.bit");

    // Test that bit manipulation functions are accessible and callable
    std::uint8_t val = 0b10110001;
    float f = 3.14159f;

    test::section("Testing symbol accessibility");

    // Sanity check each function is callable (not testing std lib correctness)
    test::assert_equal(std::bit_cast<std::uint32_t>(f), std::bit_cast<std::uint32_t>(f), "bit_cast");
    test::assert_true(std::has_single_bit(8u), "has_single_bit");
    test::assert_true(std::bit_ceil(5u) > 0, "bit_ceil");
    test::assert_true(std::bit_floor(5u) < 10, "bit_floor");
    test::assert_true(std::bit_width(255u) > 0, "bit_width");
    test::assert_true(std::rotl(val, 1) != 0, "rotl");
    test::assert_true(std::rotr(val, 1) != 0, "rotr");
    test::assert_true(std::countl_zero(std::uint8_t(1)) > 0, "countl_zero");
    test::assert_true(std::countl_one(std::uint8_t(0xFF)) > 0, "countl_one");
    test::assert_true(std::countr_zero(std::uint8_t(2)) > 0, "countr_zero");
    test::assert_true(std::countr_one(std::uint8_t(0xFF)) > 0, "countr_one");
    test::assert_true(std::popcount(std::uint8_t(0xFF)) > 0, "popcount");

    // Test endian enum is accessible
    [[maybe_unused]] auto e = std::endian::native;
    test::success("endian enum accessible");

    test::test_footer();
    return 0;
}
