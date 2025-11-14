/**
 * @file test_bit.cpp
 * @brief Tests for std_module.bit
 *
 * Comprehensive test suite for C++20 <bit> functionality through modules.
 *
 * DEMONSTRATES: Pure module-only testing with test_framework
 * - Uses ONLY: import std_module.bit + import std_module.test_framework
 * - No #include <iostream> or #include <cassert> needed!
 * - Only #include <cstdint> for uint8_t/uint32_t/uint64_t types
 */

import std_module.bit;
import std_module.test_framework;

#include <cstdint>  // For uint8_t, uint32_t, uint64_t types

// Test bit_cast function
void test_bit_cast()
{
    test::section("Testing bit_cast");

    // float to uint32_t
    float f = 3.14159f;
    auto u = std::bit_cast<std::uint32_t>(f);
    auto f2 = std::bit_cast<float>(u);
    test::assert_equal(f, f2, "bit_cast float round-trip");
    test::cout << "  " << test::checkmark() << " bit_cast float<->uint32_t: " << f << " -> 0x" << std::hex << u << std::dec << " -> " << f2 << "\n";

    // double to uint64_t
    double d = 2.71828;
    auto u64 = std::bit_cast<std::uint64_t>(d);
    auto d2 = std::bit_cast<double>(u64);
    test::assert_equal(d, d2, "bit_cast double round-trip");
    test::success("bit_cast double<->uint64_t works");

    // int to float (reinterpret bits)
    std::uint32_t int_val = 0x40490FDB; // Represents pi as float
    float pi = std::bit_cast<float>(int_val);
    test::cout << "  " << test::checkmark() << " bit_cast int->float: 0x" << std::hex << int_val << std::dec << " -> " << pi << "\n";
}

// Test has_single_bit (checks if value is a power of 2)
void test_has_single_bit()
{
    test::section("Testing has_single_bit");

    test::assert_true(std::has_single_bit(1u), "1 is power of 2");
    test::assert_true(std::has_single_bit(2u), "2 is power of 2");
    test::assert_true(std::has_single_bit(4u), "4 is power of 2");
    test::assert_true(std::has_single_bit(8u), "8 is power of 2");
    test::assert_true(std::has_single_bit(16u), "16 is power of 2");
    test::assert_true(std::has_single_bit(1024u), "1024 is power of 2");
    test::success("Powers of 2 (1, 2, 4, 8, 16, 1024) detected correctly");

    test::assert_true(!std::has_single_bit(0u), "0 is not power of 2");
    test::assert_true(!std::has_single_bit(3u), "3 is not power of 2");
    test::assert_true(!std::has_single_bit(5u), "5 is not power of 2");
    test::assert_true(!std::has_single_bit(15u), "15 is not power of 2");
    test::assert_true(!std::has_single_bit(100u), "100 is not power of 2");
    test::success("Non-powers of 2 (0, 3, 5, 15, 100) detected correctly");
}

// Test bit_ceil (rounds up to next power of 2)
void test_bit_ceil()
{
    test::section("Testing bit_ceil");

    test::assert_equal(std::bit_ceil(0u), 1u, "bit_ceil(0) == 1");
    test::assert_equal(std::bit_ceil(1u), 1u, "bit_ceil(1) == 1");
    test::assert_equal(std::bit_ceil(2u), 2u, "bit_ceil(2) == 2");
    test::assert_equal(std::bit_ceil(3u), 4u, "bit_ceil(3) == 4");
    test::assert_equal(std::bit_ceil(5u), 8u, "bit_ceil(5) == 8");
    test::assert_equal(std::bit_ceil(15u), 16u, "bit_ceil(15) == 16");
    test::assert_equal(std::bit_ceil(17u), 32u, "bit_ceil(17) == 32");
    test::success("bit_ceil(0)=1, bit_ceil(1)=1, bit_ceil(2)=2, bit_ceil(3)=4");
    test::success("bit_ceil(5)=8, bit_ceil(15)=16, bit_ceil(17)=32");
}

// Test bit_floor (rounds down to previous power of 2)
void test_bit_floor()
{
    test::section("Testing bit_floor");

    test::assert_equal(std::bit_floor(0u), 0u, "bit_floor(0) == 0");
    test::assert_equal(std::bit_floor(1u), 1u, "bit_floor(1) == 1");
    test::assert_equal(std::bit_floor(2u), 2u, "bit_floor(2) == 2");
    test::assert_equal(std::bit_floor(3u), 2u, "bit_floor(3) == 2");
    test::assert_equal(std::bit_floor(5u), 4u, "bit_floor(5) == 4");
    test::assert_equal(std::bit_floor(15u), 8u, "bit_floor(15) == 8");
    test::assert_equal(std::bit_floor(16u), 16u, "bit_floor(16) == 16");
    test::assert_equal(std::bit_floor(31u), 16u, "bit_floor(31) == 16");
    test::success("bit_floor(0)=0, bit_floor(1)=1, bit_floor(2)=2, bit_floor(3)=2");
    test::success("bit_floor(5)=4, bit_floor(15)=8, bit_floor(16)=16, bit_floor(31)=16");
}

// Test bit_width (number of bits needed to represent value)
void test_bit_width()
{
    test::section("Testing bit_width");

    test::assert_equal(std::bit_width(0u), 0, "bit_width(0) == 0");
    test::assert_equal(std::bit_width(1u), 1, "bit_width(1) == 1");
    test::assert_equal(std::bit_width(2u), 2, "bit_width(2) == 2");
    test::assert_equal(std::bit_width(3u), 2, "bit_width(3) == 2");
    test::assert_equal(std::bit_width(4u), 3, "bit_width(4) == 3");
    test::assert_equal(std::bit_width(7u), 3, "bit_width(7) == 3");
    test::assert_equal(std::bit_width(8u), 4, "bit_width(8) == 4");
    test::assert_equal(std::bit_width(255u), 8, "bit_width(255) == 8");
    test::assert_equal(std::bit_width(256u), 9, "bit_width(256) == 9");
    test::success("bit_width(0)=0, bit_width(1)=1, bit_width(2)=2, bit_width(3)=2");
    test::success("bit_width(4)=3, bit_width(7)=3, bit_width(8)=4");
    test::success("bit_width(255)=8, bit_width(256)=9");
}

// Test rotl (rotate left)
void test_rotl()
{
    test::section("Testing rotl (rotate left)");

    std::uint8_t val = 0b10110001;
    test::assert_equal(std::rotl(val, 0), std::uint8_t(0b10110001), "rotl(val, 0)");
    test::assert_equal(std::rotl(val, 1), std::uint8_t(0b01100011), "rotl(val, 1)");
    test::assert_equal(std::rotl(val, 2), std::uint8_t(0b11000110), "rotl(val, 2)");
    test::assert_equal(std::rotl(val, 4), std::uint8_t(0b00011011), "rotl(val, 4)");
    test::success("rotl(0b10110001, 0) = 0b10110001");
    test::success("rotl(0b10110001, 1) = 0b01100011");
    test::success("rotl(0b10110001, 2) = 0b11000110");
    test::success("rotl(0b10110001, 4) = 0b00011011");

    // Test wrapping
    test::assert_equal(std::rotl(val, 8), val, "rotl wraps at 8 bits");
    test::success("rotl wraps correctly: rotl(val, 8) = val");
}

// Test rotr (rotate right)
void test_rotr()
{
    test::section("Testing rotr (rotate right)");

    std::uint8_t val = 0b10110001;
    test::assert_equal(std::rotr(val, 0), std::uint8_t(0b10110001), "rotr(val, 0)");
    test::assert_equal(std::rotr(val, 1), std::uint8_t(0b11011000), "rotr(val, 1)");
    test::assert_equal(std::rotr(val, 2), std::uint8_t(0b01101100), "rotr(val, 2)");
    test::assert_equal(std::rotr(val, 4), std::uint8_t(0b00011011), "rotr(val, 4)");
    test::success("rotr(0b10110001, 0) = 0b10110001");
    test::success("rotr(0b10110001, 1) = 0b11011000");
    test::success("rotr(0b10110001, 2) = 0b01101100");
    test::success("rotr(0b10110001, 4) = 0b00011011");

    // Test wrapping
    test::assert_equal(std::rotr(val, 8), val, "rotr wraps at 8 bits");
    test::success("rotr wraps correctly: rotr(val, 8) = val");
}

// Test countl_zero (count leading zeros)
void test_countl_zero()
{
    test::section("Testing countl_zero");

    test::assert_equal(std::countl_zero(std::uint8_t(0)), 8, "countl_zero(0)");
    test::assert_equal(std::countl_zero(std::uint8_t(1)), 7, "countl_zero(1)");
    test::assert_equal(std::countl_zero(std::uint8_t(0b00000001)), 7, "countl_zero(0b00000001)");
    test::assert_equal(std::countl_zero(std::uint8_t(0b00000010)), 6, "countl_zero(0b00000010)");
    test::assert_equal(std::countl_zero(std::uint8_t(0b00001000)), 4, "countl_zero(0b00001000)");
    test::assert_equal(std::countl_zero(std::uint8_t(0b10000000)), 0, "countl_zero(0b10000000)");
    test::success("countl_zero(0b00000000) = 8");
    test::success("countl_zero(0b00000001) = 7");
    test::success("countl_zero(0b00000010) = 6");
    test::success("countl_zero(0b00001000) = 4");
    test::success("countl_zero(0b10000000) = 0");
}

// Test countl_one (count leading ones)
void test_countl_one()
{
    test::section("Testing countl_one");

    test::assert_equal(std::countl_one(std::uint8_t(0)), 0, "countl_one(0)");
    test::assert_equal(std::countl_one(std::uint8_t(0xFF)), 8, "countl_one(0xFF)");
    test::assert_equal(std::countl_one(std::uint8_t(0b11111111)), 8, "countl_one(0b11111111)");
    test::assert_equal(std::countl_one(std::uint8_t(0b11111110)), 7, "countl_one(0b11111110)");
    test::assert_equal(std::countl_one(std::uint8_t(0b11110000)), 4, "countl_one(0b11110000)");
    test::assert_equal(std::countl_one(std::uint8_t(0b10000000)), 1, "countl_one(0b10000000)");
    test::success("countl_one(0b00000000) = 0");
    test::success("countl_one(0b11111111) = 8");
    test::success("countl_one(0b11111110) = 7");
    test::success("countl_one(0b11110000) = 4");
    test::success("countl_one(0b10000000) = 1");
}

// Test countr_zero (count trailing zeros)
void test_countr_zero()
{
    test::section("Testing countr_zero");

    test::assert_equal(std::countr_zero(std::uint8_t(0)), 8, "countr_zero(0)");
    test::assert_equal(std::countr_zero(std::uint8_t(1)), 0, "countr_zero(1)");
    test::assert_equal(std::countr_zero(std::uint8_t(0b00000001)), 0, "countr_zero(0b00000001)");
    test::assert_equal(std::countr_zero(std::uint8_t(0b00000010)), 1, "countr_zero(0b00000010)");
    test::assert_equal(std::countr_zero(std::uint8_t(0b00001000)), 3, "countr_zero(0b00001000)");
    test::assert_equal(std::countr_zero(std::uint8_t(0b10000000)), 7, "countr_zero(0b10000000)");
    test::success("countr_zero(0b00000000) = 8");
    test::success("countr_zero(0b00000001) = 0");
    test::success("countr_zero(0b00000010) = 1");
    test::success("countr_zero(0b00001000) = 3");
    test::success("countr_zero(0b10000000) = 7");
}

// Test countr_one (count trailing ones)
void test_countr_one()
{
    test::section("Testing countr_one");

    test::assert_equal(std::countr_one(std::uint8_t(0)), 0, "countr_one(0)");
    test::assert_equal(std::countr_one(std::uint8_t(0xFF)), 8, "countr_one(0xFF)");
    test::assert_equal(std::countr_one(std::uint8_t(0b11111111)), 8, "countr_one(0b11111111)");
    test::assert_equal(std::countr_one(std::uint8_t(0b01111111)), 7, "countr_one(0b01111111)");
    test::assert_equal(std::countr_one(std::uint8_t(0b00001111)), 4, "countr_one(0b00001111)");
    test::assert_equal(std::countr_one(std::uint8_t(0b00000001)), 1, "countr_one(0b00000001)");
    test::success("countr_one(0b00000000) = 0");
    test::success("countr_one(0b11111111) = 8");
    test::success("countr_one(0b01111111) = 7");
    test::success("countr_one(0b00001111) = 4");
    test::success("countr_one(0b00000001) = 1");
}

// Test popcount (count number of 1 bits)
void test_popcount()
{
    test::section("Testing popcount");

    test::assert_equal(std::popcount(std::uint8_t(0)), 0, "popcount(0)");
    test::assert_equal(std::popcount(std::uint8_t(0xFF)), 8, "popcount(0xFF)");
    test::assert_equal(std::popcount(std::uint8_t(0b00000001)), 1, "popcount(0b00000001)");
    test::assert_equal(std::popcount(std::uint8_t(0b00000011)), 2, "popcount(0b00000011)");
    test::assert_equal(std::popcount(std::uint8_t(0b10101010)), 4, "popcount(0b10101010)");
    test::assert_equal(std::popcount(std::uint8_t(0b11111111)), 8, "popcount(0b11111111)");
    test::success("popcount(0b00000000) = 0");
    test::success("popcount(0b11111111) = 8");
    test::success("popcount(0b00000001) = 1");
    test::success("popcount(0b00000011) = 2");
    test::success("popcount(0b10101010) = 4");
}

// Test endian enumeration
void test_endian()
{
    test::section("Testing endian");

    // Test that endian enum values exist
    [[maybe_unused]] auto little = std::endian::little;
    [[maybe_unused]] auto big = std::endian::big;
    [[maybe_unused]] auto native = std::endian::native;

    test::success("std::endian::little exists");
    test::success("std::endian::big exists");
    test::success("std::endian::native exists");

    // Check native endianness
    if (std::endian::native == std::endian::little)
    {
        test::success("Native byte order is little-endian");
    }
    else if (std::endian::native == std::endian::big)
    {
        test::success("Native byte order is big-endian");
    }
    else
    {
        test::success("Native byte order is mixed-endian");
    }
}

int main()
{
    test::test_header("std_module.bit");

    try
    {
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
    }
    catch (...)
    {
        test::cerr << "\n" << test::crossmark() << " Test failed with exception\n";
        return 1;
    }

    return 0;
}
