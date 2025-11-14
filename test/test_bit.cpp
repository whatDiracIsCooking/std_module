/**
 * @file test_bit.cpp
 * @brief Tests for std_module.bit
 *
 * Demonstrates pure module-only testing with test_framework.
 * Uses ONLY imports - no #include <iostream> or #include <cassert>!
 */

import std_module.bit;
import std_module.test_framework;

#include <cstdint>

void test_bit_cast() {
    test::section("Testing bit_cast");

    float f = 3.14159f;
    auto u = std::bit_cast<std::uint32_t>(f);
    auto f2 = std::bit_cast<float>(u);
    test::assert_equal(f, f2, "float round-trip");

    double d = 2.71828;
    auto u64 = std::bit_cast<std::uint64_t>(d);
    auto d2 = std::bit_cast<double>(u64);
    test::assert_equal(d, d2, "double round-trip");
}

void test_has_single_bit() {
    test::section("Testing has_single_bit");

    test::assert_true(std::has_single_bit(1u) && std::has_single_bit(2u) &&
                      std::has_single_bit(8u) && std::has_single_bit(1024u),
                      "powers of 2");
    test::assert_true(!std::has_single_bit(0u) && !std::has_single_bit(3u) &&
                      !std::has_single_bit(15u),
                      "non-powers of 2");
}

void test_bit_ceil() {
    test::section("Testing bit_ceil");

    test::assert_equal(std::bit_ceil(0u), 1u, "bit_ceil(0)");
    test::assert_equal(std::bit_ceil(3u), 4u, "bit_ceil(3)");
    test::assert_equal(std::bit_ceil(5u), 8u, "bit_ceil(5)");
    test::assert_equal(std::bit_ceil(17u), 32u, "bit_ceil(17)");
}

void test_bit_floor() {
    test::section("Testing bit_floor");

    test::assert_equal(std::bit_floor(0u), 0u, "bit_floor(0)");
    test::assert_equal(std::bit_floor(3u), 2u, "bit_floor(3)");
    test::assert_equal(std::bit_floor(15u), 8u, "bit_floor(15)");
    test::assert_equal(std::bit_floor(31u), 16u, "bit_floor(31)");
}

void test_bit_width() {
    test::section("Testing bit_width");

    test::assert_equal(std::bit_width(0u), 0, "bit_width(0)");
    test::assert_equal(std::bit_width(1u), 1, "bit_width(1)");
    test::assert_equal(std::bit_width(7u), 3, "bit_width(7)");
    test::assert_equal(std::bit_width(255u), 8, "bit_width(255)");
}

void test_rotl() {
    test::section("Testing rotl");

    std::uint8_t val = 0b10110001;
    test::assert_equal(std::rotl(val, 0), std::uint8_t(0b10110001), "rotl 0 bits");
    test::assert_equal(std::rotl(val, 1), std::uint8_t(0b01100011), "rotl 1 bit");
    test::assert_equal(std::rotl(val, 4), std::uint8_t(0b00011011), "rotl 4 bits");
    test::assert_equal(std::rotl(val, 8), val, "rotl wraps");
}

void test_rotr() {
    test::section("Testing rotr");

    std::uint8_t val = 0b10110001;
    test::assert_equal(std::rotr(val, 0), std::uint8_t(0b10110001), "rotr 0 bits");
    test::assert_equal(std::rotr(val, 1), std::uint8_t(0b11011000), "rotr 1 bit");
    test::assert_equal(std::rotr(val, 4), std::uint8_t(0b00011011), "rotr 4 bits");
    test::assert_equal(std::rotr(val, 8), val, "rotr wraps");
}

void test_countl_zero() {
    test::section("Testing countl_zero");

    test::assert_equal(std::countl_zero(std::uint8_t(0)), 8, "countl_zero(0)");
    test::assert_equal(std::countl_zero(std::uint8_t(1)), 7, "countl_zero(1)");
    test::assert_equal(std::countl_zero(std::uint8_t(0b00001000)), 4, "countl_zero(0b00001000)");
    test::assert_equal(std::countl_zero(std::uint8_t(0b10000000)), 0, "countl_zero(0b10000000)");
}

void test_countl_one() {
    test::section("Testing countl_one");

    test::assert_equal(std::countl_one(std::uint8_t(0)), 0, "countl_one(0)");
    test::assert_equal(std::countl_one(std::uint8_t(0xFF)), 8, "countl_one(0xFF)");
    test::assert_equal(std::countl_one(std::uint8_t(0b11111110)), 7, "countl_one(0b11111110)");
    test::assert_equal(std::countl_one(std::uint8_t(0b11110000)), 4, "countl_one(0b11110000)");
}

void test_countr_zero() {
    test::section("Testing countr_zero");

    test::assert_equal(std::countr_zero(std::uint8_t(0)), 8, "countr_zero(0)");
    test::assert_equal(std::countr_zero(std::uint8_t(1)), 0, "countr_zero(1)");
    test::assert_equal(std::countr_zero(std::uint8_t(0b00001000)), 3, "countr_zero(0b00001000)");
    test::assert_equal(std::countr_zero(std::uint8_t(0b10000000)), 7, "countr_zero(0b10000000)");
}

void test_countr_one() {
    test::section("Testing countr_one");

    test::assert_equal(std::countr_one(std::uint8_t(0)), 0, "countr_one(0)");
    test::assert_equal(std::countr_one(std::uint8_t(0xFF)), 8, "countr_one(0xFF)");
    test::assert_equal(std::countr_one(std::uint8_t(0b01111111)), 7, "countr_one(0b01111111)");
    test::assert_equal(std::countr_one(std::uint8_t(0b00001111)), 4, "countr_one(0b00001111)");
}

void test_popcount() {
    test::section("Testing popcount");

    test::assert_equal(std::popcount(std::uint8_t(0)), 0, "popcount(0)");
    test::assert_equal(std::popcount(std::uint8_t(0xFF)), 8, "popcount(0xFF)");
    test::assert_equal(std::popcount(std::uint8_t(0b00000001)), 1, "popcount(0b00000001)");
    test::assert_equal(std::popcount(std::uint8_t(0b10101010)), 4, "popcount(0b10101010)");
}

void test_endian() {
    test::section("Testing endian");

    [[maybe_unused]] auto little = std::endian::little;
    [[maybe_unused]] auto big = std::endian::big;
    [[maybe_unused]] auto native = std::endian::native;

    if (std::endian::native == std::endian::little) {
        test::success("Native byte order: little-endian");
    } else if (std::endian::native == std::endian::big) {
        test::success("Native byte order: big-endian");
    } else {
        test::success("Native byte order: mixed-endian");
    }
}

int main() {
    test::test_header("std_module.bit");

    test_bit_cast();
    test_has_single_bit();
    test_bit_ceil();
    test_bit_floor();
    test_bit_width();
    test_rotl();
    test_rotr();
    test_countl_zero();
    test_countl_one();
    test_countr_zero();
    test_countr_one();
    test_popcount();
    test_endian();

    test::test_footer();
    return 0;
}
