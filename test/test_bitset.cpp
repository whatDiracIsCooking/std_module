/**
 * @file test_bitset.cpp
 * @brief Tests for std_module.bitset
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.bitset;
import std_module.test_framework;

int main() {
    test::test_header("std_module.bitset");

    test::section("Testing symbol accessibility");

    // Test that bitset types and operations are accessible (not testing correctness)
    std::bitset<8> bs;

    // Construction variants
    std::bitset<8> bs1;
    std::bitset<8> bs2(0b10101010);
    std::bitset<8> bs3("11110000");
    test::success("construction (default, value, string)");

    // Bit manipulation
    bs.set();
    bs.reset();
    bs.set(3);
    bs.reset(3);
    bs.flip();
    bs.flip(3);
    test::success("set, reset, flip");

    // Element access
    [[maybe_unused]] bool b = bs[1];
    bs[1] = true;
    [[maybe_unused]] bool t = bs.test(1);
    test::success("operator[], test");

    // State queries
    [[maybe_unused]] bool any = bs.any();
    [[maybe_unused]] bool none = bs.none();
    [[maybe_unused]] bool all = bs.all();
    [[maybe_unused]] auto count = bs.count();
    [[maybe_unused]] auto size = bs.size();
    test::success("any, none, all, count, size");

    // Bitwise operations
    std::bitset<8> bs4("11110000"), bs5("10101010");
    [[maybe_unused]] auto and_result = bs4 & bs5;
    [[maybe_unused]] auto or_result = bs4 | bs5;
    [[maybe_unused]] auto xor_result = bs4 ^ bs5;
    [[maybe_unused]] auto not_result = ~bs4;
    bs4 &= bs5;
    bs4 |= bs5;
    bs4 ^= bs5;
    test::success("bitwise operators (&, |, ^, ~, &=, |=, ^=)");

    // Shift operations
    [[maybe_unused]] auto lshift = bs << 2;
    [[maybe_unused]] auto rshift = bs >> 2;
    bs <<= 2;
    bs >>= 2;
    test::success("shift operators (<<, >>, <<=, >>=)");

    // Conversions
    [[maybe_unused]] auto str = bs.to_string();
    [[maybe_unused]] auto ul = bs.to_ulong();
    [[maybe_unused]] auto ull = bs.to_ullong();
    test::success("to_string, to_ulong, to_ullong");

    // Comparison
    [[maybe_unused]] bool eq = (bs == bs2);
    [[maybe_unused]] bool ne = (bs != bs2);
    test::success("comparison operators (==, !=)");

    // Hash support
    std::hash<std::bitset<8>> hasher;
    [[maybe_unused]] auto hash = hasher(bs);
    test::success("hash support");

    test::test_footer();
    return 0;
}
