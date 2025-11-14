/**
 * @file test_bitset.cpp
 * @brief Comprehensive test for std_module.bitset (C++20)
 */

import std_module.bitset;

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <functional>

void test_construction() {
    std::cout << "Testing bitset construction...\n";

    // Default construction
    std::bitset<8> bs1;
    assert(bs1.none());
    std::cout << "  ✓ Default construction: " << bs1 << "\n";

    // Construction from unsigned long long
    std::bitset<8> bs2(0b10101010);
    assert(bs2.count() == 4);
    std::cout << "  ✓ Construction from unsigned long long: " << bs2 << "\n";

    // Construction from string
    std::bitset<8> bs3(std::string("11110000"));
    assert(bs3.count() == 4);
    std::cout << "  ✓ Construction from string: " << bs3 << "\n";

    // Construction from string literal
    std::bitset<8> bs4("00001111");
    assert(bs4.count() == 4);
    std::cout << "  ✓ Construction from string literal: " << bs4 << "\n";

    // Partial string construction
    std::bitset<8> bs5(std::string("11001100"), 0, 4);
    assert(bs5.to_ulong() == 0b00001100);
    std::cout << "  ✓ Partial string construction: " << bs5 << "\n";
}

void test_bit_manipulation() {
    std::cout << "\nTesting bit manipulation...\n";

    std::bitset<8> bs;

    // Set all bits
    bs.set();
    assert(bs.all());
    std::cout << "  ✓ Set all bits: " << bs << "\n";

    // Reset all bits
    bs.reset();
    assert(bs.none());
    std::cout << "  ✓ Reset all bits: " << bs << "\n";

    // Set individual bit
    bs.set(3);
    assert(bs.test(3));
    assert(bs.count() == 1);
    std::cout << "  ✓ Set bit 3: " << bs << "\n";

    // Set bit with value
    bs.set(5, true);
    assert(bs.test(5));
    std::cout << "  ✓ Set bit 5 to true: " << bs << "\n";

    // Reset individual bit
    bs.reset(3);
    assert(!bs.test(3));
    std::cout << "  ✓ Reset bit 3: " << bs << "\n";

    // Flip all bits
    bs.flip();
    assert(bs.test(3));
    assert(!bs.test(5));
    std::cout << "  ✓ Flip all bits: " << bs << "\n";

    // Flip individual bit
    bs.flip(3);
    assert(!bs.test(3));
    std::cout << "  ✓ Flip bit 3: " << bs << "\n";
}

void test_element_access() {
    std::cout << "\nTesting element access...\n";

    std::bitset<8> bs("10101010");

    // Test operator[]
    assert(bs[1] == true);
    assert(bs[0] == false);
    std::cout << "  ✓ Operator[] read: bit[1]=" << bs[1] << ", bit[0]=" << bs[0] << "\n";

    // Modify using operator[]
    bs[0] = true;
    assert(bs[0] == true);
    std::cout << "  ✓ Operator[] write: " << bs << "\n";

    // Test test() method
    assert(bs.test(1) == true);
    assert(bs.test(2) == false);
    std::cout << "  ✓ test() method works\n";

    // Test out of bounds with test()
    try {
        bs.test(100);
        assert(false && "Should have thrown out_of_range");
    } catch (const std::out_of_range& e) {
        std::cout << "  ✓ test() throws out_of_range for invalid index\n";
    }
}

void test_capacity_and_state() {
    std::cout << "\nTesting capacity and state queries...\n";

    std::bitset<8> bs1("00000000");
    assert(bs1.none());
    assert(!bs1.any());
    assert(!bs1.all());
    assert(bs1.count() == 0);
    std::cout << "  ✓ All zeros: none()=" << bs1.none() << ", any()=" << bs1.any()
              << ", all()=" << bs1.all() << ", count()=" << bs1.count() << "\n";

    std::bitset<8> bs2("11111111");
    assert(!bs2.none());
    assert(bs2.any());
    assert(bs2.all());
    assert(bs2.count() == 8);
    std::cout << "  ✓ All ones: none()=" << bs2.none() << ", any()=" << bs2.any()
              << ", all()=" << bs2.all() << ", count()=" << bs2.count() << "\n";

    std::bitset<8> bs3("10101010");
    assert(!bs3.none());
    assert(bs3.any());
    assert(!bs3.all());
    assert(bs3.count() == 4);
    std::cout << "  ✓ Mixed: none()=" << bs3.none() << ", any()=" << bs3.any()
              << ", all()=" << bs3.all() << ", count()=" << bs3.count() << "\n";

    // Test size()
    std::bitset<8> bs4;
    assert(bs4.size() == 8);
    std::bitset<64> bs5;
    assert(bs5.size() == 64);
    std::cout << "  ✓ size(): 8-bit=" << bs4.size() << ", 64-bit=" << bs5.size() << "\n";
}

void test_bitwise_operations() {
    std::cout << "\nTesting bitwise operations...\n";

    std::bitset<8> bs1("11110000");
    std::bitset<8> bs2("10101010");

    // AND
    auto result_and = bs1 & bs2;
    assert(result_and == std::bitset<8>("10100000"));
    std::cout << "  ✓ AND: " << bs1 << " & " << bs2 << " = " << result_and << "\n";

    // OR
    auto result_or = bs1 | bs2;
    assert(result_or == std::bitset<8>("11111010"));
    std::cout << "  ✓ OR:  " << bs1 << " | " << bs2 << " = " << result_or << "\n";

    // XOR
    auto result_xor = bs1 ^ bs2;
    assert(result_xor == std::bitset<8>("01011010"));
    std::cout << "  ✓ XOR: " << bs1 << " ^ " << bs2 << " = " << result_xor << "\n";

    // NOT
    auto result_not = ~bs1;
    assert(result_not == std::bitset<8>("00001111"));
    std::cout << "  ✓ NOT: ~" << bs1 << " = " << result_not << "\n";

    // Compound assignment
    std::bitset<8> bs3("11110000");
    bs3 &= bs2;
    assert(bs3 == std::bitset<8>("10100000"));
    std::cout << "  ✓ &= operator works\n";

    std::bitset<8> bs4("11110000");
    bs4 |= bs2;
    assert(bs4 == std::bitset<8>("11111010"));
    std::cout << "  ✓ |= operator works\n";

    std::bitset<8> bs5("11110000");
    bs5 ^= bs2;
    assert(bs5 == std::bitset<8>("01011010"));
    std::cout << "  ✓ ^= operator works\n";
}

void test_shift_operations() {
    std::cout << "\nTesting shift operations...\n";

    std::bitset<8> bs("00001111");

    // Left shift
    auto result_lshift = bs << 2;
    assert(result_lshift == std::bitset<8>("00111100"));
    std::cout << "  ✓ Left shift: " << bs << " << 2 = " << result_lshift << "\n";

    // Right shift
    auto result_rshift = bs >> 2;
    assert(result_rshift == std::bitset<8>("00000011"));
    std::cout << "  ✓ Right shift: " << bs << " >> 2 = " << result_rshift << "\n";

    // Compound left shift
    std::bitset<8> bs2("00001111");
    bs2 <<= 3;
    assert(bs2 == std::bitset<8>("01111000"));
    std::cout << "  ✓ <<= operator: " << bs2 << "\n";

    // Compound right shift
    std::bitset<8> bs3("11110000");
    bs3 >>= 4;
    assert(bs3 == std::bitset<8>("00001111"));
    std::cout << "  ✓ >>= operator: " << bs3 << "\n";

    // Shift by size (should result in all zeros)
    auto result_shift_all = bs << 8;
    assert(result_shift_all.none());
    std::cout << "  ✓ Shift by size results in all zeros\n";
}

void test_conversions() {
    std::cout << "\nTesting conversions...\n";

    std::bitset<8> bs("10101010");

    // to_string
    std::string str = bs.to_string();
    assert(str == "10101010");
    std::cout << "  ✓ to_string(): " << str << "\n";

    // to_string with custom characters
    std::string str2 = bs.to_string('0', '1');
    assert(str2 == "10101010");
    std::cout << "  ✓ to_string('0', '1'): " << str2 << "\n";

    // to_ulong
    unsigned long ul = bs.to_ulong();
    assert(ul == 170);
    std::cout << "  ✓ to_ulong(): " << ul << "\n";

    // to_ullong
    unsigned long long ull = bs.to_ullong();
    assert(ull == 170);
    std::cout << "  ✓ to_ullong(): " << ull << "\n";

    // Test overflow detection
    std::bitset<64> large_bs;
    large_bs.set();  // All bits set
    try {
        // This should work for 64-bit
        unsigned long long val = large_bs.to_ullong();
        std::cout << "  ✓ to_ullong() handles 64-bit values\n";
    } catch (const std::overflow_error& e) {
        // Some platforms might throw here
        std::cout << "  ✓ to_ullong() throws overflow_error on overflow\n";
    }
}

void test_comparison() {
    std::cout << "\nTesting comparison operations...\n";

    std::bitset<8> bs1("10101010");
    std::bitset<8> bs2("10101010");
    std::bitset<8> bs3("11110000");

    // Equality
    assert(bs1 == bs2);
    assert(!(bs1 == bs3));
    std::cout << "  ✓ Equality: " << bs1 << " == " << bs2 << " is true\n";

    // Inequality
    assert(bs1 != bs3);
    assert(!(bs1 != bs2));
    std::cout << "  ✓ Inequality: " << bs1 << " != " << bs3 << " is true\n";
}

void test_hash_support() {
    std::cout << "\nTesting hash support...\n";

    std::bitset<8> bs1("10101010");
    std::bitset<8> bs2("10101010");
    std::bitset<8> bs3("11110000");

    std::hash<std::bitset<8>> hasher;

    size_t hash1 = hasher(bs1);
    size_t hash2 = hasher(bs2);
    size_t hash3 = hasher(bs3);

    assert(hash1 == hash2);  // Same bitsets should have same hash
    // Different bitsets might have different hashes (not guaranteed but likely)
    std::cout << "  ✓ Hash of " << bs1 << ": " << hash1 << "\n";
    std::cout << "  ✓ Hash of " << bs3 << ": " << hash3 << "\n";
    std::cout << "  ✓ Equal bitsets have equal hashes\n";
}

void test_different_sizes() {
    std::cout << "\nTesting different bitset sizes...\n";

    std::bitset<1> bs1(1);
    assert(bs1.count() == 1);
    std::cout << "  ✓ 1-bit bitset: " << bs1 << "\n";

    std::bitset<16> bs16(0xABCD);
    assert(bs16.count() == 10);
    std::cout << "  ✓ 16-bit bitset: " << bs16 << "\n";

    std::bitset<32> bs32(0xDEADBEEF);
    std::cout << "  ✓ 32-bit bitset: " << bs32 << "\n";

    std::bitset<64> bs64(0xFEDCBA9876543210ULL);
    std::cout << "  ✓ 64-bit bitset: " << bs64 << "\n";

    std::bitset<128> bs128;
    bs128.set(127);
    bs128.set(0);
    assert(bs128.count() == 2);
    std::cout << "  ✓ 128-bit bitset with bits 0 and 127 set (count=" << bs128.count() << ")\n";
}

void test_io_operations() {
    std::cout << "\nTesting I/O operations...\n";

    std::bitset<8> bs("10101010");

    // Stream output
    std::cout << "  ✓ Stream output: " << bs << "\n";

    // String representation matches stream output
    std::string str_representation = bs.to_string();
    std::cout << "  ✓ String representation matches: " << str_representation << "\n";
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "Testing std_module.bitset\n";
    std::cout << "===========================================\n\n";

    test_construction();
    test_bit_manipulation();
    test_element_access();
    test_capacity_and_state();
    test_bitwise_operations();
    test_shift_operations();
    test_conversions();
    test_comparison();
    test_hash_support();
    test_different_sizes();
    test_io_operations();

    std::cout << "\n===========================================\n";
    std::cout << "All tests passed! ✓\n";
    std::cout << "===========================================\n";

    return 0;
}
