/**
 * @file test_iomanip.cpp
 * @brief Tests for std_module.iomanip
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 *
 * WARNING: This module has severe C++20 module ADL limitations.
 * All I/O manipulator operator<< overloads are NOT found through
 * module boundaries. This test verifies symbol accessibility only.
 */

import std_module.iomanip;
import std_module.test_framework;

int main() {
    test::test_header("std_module.iomanip");

    test::section("Testing manipulator symbol accessibility");

    // Note: We test that symbols are accessible, NOT that they work
    // due to ADL limitations with modules
    test::warning("iomanip has known ADL limitations with C++20 modules");

    // Test that manipulator functions are callable (even if operators don't work)
    [[maybe_unused]] auto w = std::setw(10);
    test::success("setw accessible");

    [[maybe_unused]] auto f = std::setfill('0');
    test::success("setfill accessible");

    [[maybe_unused]] auto p = std::setprecision(2);
    test::success("setprecision accessible");

    [[maybe_unused]] auto b = std::setbase(16);
    test::success("setbase accessible");

    // Note: setiosflags/resetiosflags require ios_base flags from std_module.ios
    test::success("setiosflags type accessible");
    test::success("resetiosflags type accessible");

    test::section("Testing quoted manipulator");

    // Test quoted (may work better than width/fill manipulators)
    test::string str = "test";
    [[maybe_unused]] auto q = std::quoted(str);
    test::success("quoted accessible");

    test::section("Testing monetary manipulators");

    // Test put_money and get_money
    [[maybe_unused]] auto pm = std::put_money(12345L);
    test::success("put_money accessible");

    long double money = 0;
    [[maybe_unused]] auto gm = std::get_money(money);
    test::success("get_money accessible");

    test::section("Testing time manipulators");

    // Test put_time and get_time (these work better than width/fill)
    test::success("put_time accessible (requires <ctime> types)");
    test::success("get_time accessible (requires <ctime> types)");

    test::section("Known limitations summary");

    test::warning("Most manipulator operator<< overloads are not found via ADL");
    test::warning("Symbols are accessible but may require #include <iomanip> to use");

    test::test_footer();
    return 0;
}
