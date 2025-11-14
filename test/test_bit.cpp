/**
 * @file test_bit.cpp
 * @brief Tests for std_module.bit
 *
 * Comprehensive test suite for C++20 <bit> functionality through modules.
 */

import std_module.bit;

#include <iostream>
#include <cassert>
#include <cstdint>

// Test bit_cast function
void test_bit_cast()
{
    std::cout << "\nTesting bit_cast:\n";

    // float to uint32_t
    float f = 3.14159f;
    auto u = std::bit_cast<std::uint32_t>(f);
    auto f2 = std::bit_cast<float>(u);
    assert(f == f2);
    std::cout << "  ✓ bit_cast float<->uint32_t: " << f << " -> 0x" << std::hex << u << std::dec << " -> " << f2 << "\n";

    // double to uint64_t
    double d = 2.71828;
    auto u64 = std::bit_cast<std::uint64_t>(d);
    auto d2 = std::bit_cast<double>(u64);
    assert(d == d2);
    std::cout << "  ✓ bit_cast double<->uint64_t works\n";

    // int to float (reinterpret bits)
    std::uint32_t int_val = 0x40490FDB; // Represents pi as float
    float pi = std::bit_cast<float>(int_val);
    std::cout << "  ✓ bit_cast int->float: 0x" << std::hex << int_val << std::dec << " -> " << pi << "\n";
}

// Test has_single_bit (checks if value is a power of 2)
void test_has_single_bit()
{
    std::cout << "\nTesting has_single_bit:\n";

    assert(std::has_single_bit(1u));
    assert(std::has_single_bit(2u));
    assert(std::has_single_bit(4u));
    assert(std::has_single_bit(8u));
    assert(std::has_single_bit(16u));
    assert(std::has_single_bit(1024u));
    std::cout << "  ✓ Powers of 2 (1, 2, 4, 8, 16, 1024) detected correctly\n";

    assert(!std::has_single_bit(0u));
    assert(!std::has_single_bit(3u));
    assert(!std::has_single_bit(5u));
    assert(!std::has_single_bit(15u));
    assert(!std::has_single_bit(100u));
    std::cout << "  ✓ Non-powers of 2 (0, 3, 5, 15, 100) detected correctly\n";
}

// Test bit_ceil (rounds up to next power of 2)
void test_bit_ceil()
{
    std::cout << "\nTesting bit_ceil:\n";

    assert(std::bit_ceil(0u) == 1u);
    assert(std::bit_ceil(1u) == 1u);
    assert(std::bit_ceil(2u) == 2u);
    assert(std::bit_ceil(3u) == 4u);
    assert(std::bit_ceil(5u) == 8u);
    assert(std::bit_ceil(15u) == 16u);
    assert(std::bit_ceil(17u) == 32u);
    std::cout << "  ✓ bit_ceil(0)=1, bit_ceil(1)=1, bit_ceil(2)=2, bit_ceil(3)=4\n";
    std::cout << "  ✓ bit_ceil(5)=8, bit_ceil(15)=16, bit_ceil(17)=32\n";
}

// Test bit_floor (rounds down to previous power of 2)
void test_bit_floor()
{
    std::cout << "\nTesting bit_floor:\n";

    assert(std::bit_floor(0u) == 0u);
    assert(std::bit_floor(1u) == 1u);
    assert(std::bit_floor(2u) == 2u);
    assert(std::bit_floor(3u) == 2u);
    assert(std::bit_floor(5u) == 4u);
    assert(std::bit_floor(15u) == 8u);
    assert(std::bit_floor(16u) == 16u);
    assert(std::bit_floor(31u) == 16u);
    std::cout << "  ✓ bit_floor(0)=0, bit_floor(1)=1, bit_floor(2)=2, bit_floor(3)=2\n";
    std::cout << "  ✓ bit_floor(5)=4, bit_floor(15)=8, bit_floor(16)=16, bit_floor(31)=16\n";
}

// Test bit_width (number of bits needed to represent value)
void test_bit_width()
{
    std::cout << "\nTesting bit_width:\n";

    assert(std::bit_width(0u) == 0);
    assert(std::bit_width(1u) == 1);
    assert(std::bit_width(2u) == 2);
    assert(std::bit_width(3u) == 2);
    assert(std::bit_width(4u) == 3);
    assert(std::bit_width(7u) == 3);
    assert(std::bit_width(8u) == 4);
    assert(std::bit_width(255u) == 8);
    assert(std::bit_width(256u) == 9);
    std::cout << "  ✓ bit_width(0)=0, bit_width(1)=1, bit_width(2)=2, bit_width(3)=2\n";
    std::cout << "  ✓ bit_width(4)=3, bit_width(7)=3, bit_width(8)=4\n";
    std::cout << "  ✓ bit_width(255)=8, bit_width(256)=9\n";
}

// Test rotl (rotate left)
void test_rotl()
{
    std::cout << "\nTesting rotl (rotate left):\n";

    std::uint8_t val = 0b10110001;
    assert(std::rotl(val, 0) == 0b10110001);
    assert(std::rotl(val, 1) == 0b01100011);
    assert(std::rotl(val, 2) == 0b11000110);
    assert(std::rotl(val, 4) == 0b00011011);
    std::cout << "  ✓ rotl(0b10110001, 0) = 0b10110001\n";
    std::cout << "  ✓ rotl(0b10110001, 1) = 0b01100011\n";
    std::cout << "  ✓ rotl(0b10110001, 2) = 0b11000110\n";
    std::cout << "  ✓ rotl(0b10110001, 4) = 0b00011011\n";

    // Test wrapping
    assert(std::rotl(val, 8) == val);
    std::cout << "  ✓ rotl wraps correctly: rotl(val, 8) = val\n";
}

// Test rotr (rotate right)
void test_rotr()
{
    std::cout << "\nTesting rotr (rotate right):\n";

    std::uint8_t val = 0b10110001;
    assert(std::rotr(val, 0) == 0b10110001);
    assert(std::rotr(val, 1) == 0b11011000);
    assert(std::rotr(val, 2) == 0b01101100);
    assert(std::rotr(val, 4) == 0b00011011);
    std::cout << "  ✓ rotr(0b10110001, 0) = 0b10110001\n";
    std::cout << "  ✓ rotr(0b10110001, 1) = 0b11011000\n";
    std::cout << "  ✓ rotr(0b10110001, 2) = 0b01101100\n";
    std::cout << "  ✓ rotr(0b10110001, 4) = 0b00011011\n";

    // Test wrapping
    assert(std::rotr(val, 8) == val);
    std::cout << "  ✓ rotr wraps correctly: rotr(val, 8) = val\n";
}

// Test countl_zero (count leading zeros)
void test_countl_zero()
{
    std::cout << "\nTesting countl_zero:\n";

    assert(std::countl_zero(std::uint8_t(0)) == 8);
    assert(std::countl_zero(std::uint8_t(1)) == 7);
    assert(std::countl_zero(std::uint8_t(0b00000001)) == 7);
    assert(std::countl_zero(std::uint8_t(0b00000010)) == 6);
    assert(std::countl_zero(std::uint8_t(0b00001000)) == 4);
    assert(std::countl_zero(std::uint8_t(0b10000000)) == 0);
    std::cout << "  ✓ countl_zero(0b00000000) = 8\n";
    std::cout << "  ✓ countl_zero(0b00000001) = 7\n";
    std::cout << "  ✓ countl_zero(0b00000010) = 6\n";
    std::cout << "  ✓ countl_zero(0b00001000) = 4\n";
    std::cout << "  ✓ countl_zero(0b10000000) = 0\n";
}

// Test countl_one (count leading ones)
void test_countl_one()
{
    std::cout << "\nTesting countl_one:\n";

    assert(std::countl_one(std::uint8_t(0)) == 0);
    assert(std::countl_one(std::uint8_t(0xFF)) == 8);
    assert(std::countl_one(std::uint8_t(0b11111111)) == 8);
    assert(std::countl_one(std::uint8_t(0b11111110)) == 7);
    assert(std::countl_one(std::uint8_t(0b11110000)) == 4);
    assert(std::countl_one(std::uint8_t(0b10000000)) == 1);
    std::cout << "  ✓ countl_one(0b00000000) = 0\n";
    std::cout << "  ✓ countl_one(0b11111111) = 8\n";
    std::cout << "  ✓ countl_one(0b11111110) = 7\n";
    std::cout << "  ✓ countl_one(0b11110000) = 4\n";
    std::cout << "  ✓ countl_one(0b10000000) = 1\n";
}

// Test countr_zero (count trailing zeros)
void test_countr_zero()
{
    std::cout << "\nTesting countr_zero:\n";

    assert(std::countr_zero(std::uint8_t(0)) == 8);
    assert(std::countr_zero(std::uint8_t(1)) == 0);
    assert(std::countr_zero(std::uint8_t(0b00000001)) == 0);
    assert(std::countr_zero(std::uint8_t(0b00000010)) == 1);
    assert(std::countr_zero(std::uint8_t(0b00001000)) == 3);
    assert(std::countr_zero(std::uint8_t(0b10000000)) == 7);
    std::cout << "  ✓ countr_zero(0b00000000) = 8\n";
    std::cout << "  ✓ countr_zero(0b00000001) = 0\n";
    std::cout << "  ✓ countr_zero(0b00000010) = 1\n";
    std::cout << "  ✓ countr_zero(0b00001000) = 3\n";
    std::cout << "  ✓ countr_zero(0b10000000) = 7\n";
}

// Test countr_one (count trailing ones)
void test_countr_one()
{
    std::cout << "\nTesting countr_one:\n";

    assert(std::countr_one(std::uint8_t(0)) == 0);
    assert(std::countr_one(std::uint8_t(0xFF)) == 8);
    assert(std::countr_one(std::uint8_t(0b11111111)) == 8);
    assert(std::countr_one(std::uint8_t(0b01111111)) == 7);
    assert(std::countr_one(std::uint8_t(0b00001111)) == 4);
    assert(std::countr_one(std::uint8_t(0b00000001)) == 1);
    std::cout << "  ✓ countr_one(0b00000000) = 0\n";
    std::cout << "  ✓ countr_one(0b11111111) = 8\n";
    std::cout << "  ✓ countr_one(0b01111111) = 7\n";
    std::cout << "  ✓ countr_one(0b00001111) = 4\n";
    std::cout << "  ✓ countr_one(0b00000001) = 1\n";
}

// Test popcount (count number of 1 bits)
void test_popcount()
{
    std::cout << "\nTesting popcount:\n";

    assert(std::popcount(std::uint8_t(0)) == 0);
    assert(std::popcount(std::uint8_t(0xFF)) == 8);
    assert(std::popcount(std::uint8_t(0b00000001)) == 1);
    assert(std::popcount(std::uint8_t(0b00000011)) == 2);
    assert(std::popcount(std::uint8_t(0b10101010)) == 4);
    assert(std::popcount(std::uint8_t(0b11111111)) == 8);
    std::cout << "  ✓ popcount(0b00000000) = 0\n";
    std::cout << "  ✓ popcount(0b11111111) = 8\n";
    std::cout << "  ✓ popcount(0b00000001) = 1\n";
    std::cout << "  ✓ popcount(0b00000011) = 2\n";
    std::cout << "  ✓ popcount(0b10101010) = 4\n";
}

// Test endian enumeration
void test_endian()
{
    std::cout << "\nTesting endian:\n";

    // Test that endian enum values exist
    [[maybe_unused]] auto little = std::endian::little;
    [[maybe_unused]] auto big = std::endian::big;
    [[maybe_unused]] auto native = std::endian::native;

    std::cout << "  ✓ std::endian::little exists\n";
    std::cout << "  ✓ std::endian::big exists\n";
    std::cout << "  ✓ std::endian::native exists\n";

    // Check native endianness
    if (std::endian::native == std::endian::little)
    {
        std::cout << "  ✓ Native byte order is little-endian\n";
    }
    else if (std::endian::native == std::endian::big)
    {
        std::cout << "  ✓ Native byte order is big-endian\n";
    }
    else
    {
        std::cout << "  ✓ Native byte order is mixed-endian\n";
    }
}

int main()
{
    std::cout << "=================================\n";
    std::cout << "Testing std_module.bit\n";
    std::cout << "=================================\n";

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

        std::cout << "\n=================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "=================================\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
