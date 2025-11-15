/**
 * @file test_iostream.cpp
 * @brief Tests for std_module.iostream
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that standard stream objects and operators are accessible through the module.
 */

import std_module.iostream;
import std_module.test_framework;

int main() {
    test::test_header("std_module.iostream");

    test::section("Testing stream object accessibility");

    // Test narrow stream objects are accessible
    std::cout << "  Testing cout... ";
    std::cout << "works!\n";
    test::success("cout");

    std::cerr << "  Testing cerr... works!\n";
    test::success("cerr");

    std::clog << "  Testing clog... works!\n";
    test::success("clog");

    // cin exists (can't test input without user interaction)
    test::assert_true(std::cin.good(), "cin");

    // Test wide stream objects are accessible
    std::wcout << L"  Testing wcout... works!\n";
    test::success("wcout");

    std::wcerr << L"  Testing wcerr... works!\n";
    test::success("wcerr");

    std::wclog << L"  Testing wclog... works!\n";
    test::success("wclog");

    test::assert_true(std::wcin.good(), "wcin");

    test::section("Testing stream operators");

    // Test << operator with various types
    std::cout << "  " << 42 << " " << 3.14 << " " << true << " " << 'A' << "\n";
    test::success("operator<< with primitives");

    // Test manipulators
    std::cout << "  " << std::endl;
    std::cout << "  " << std::flush;
    test::success("endl and flush manipulators");

    test::test_footer();
    return 0;
}
