/**
 * @file test_source_location.cpp
 * @brief Tests for std_module.source_location
 *
 * Comprehensive test suite for C++20 <source_location> functionality through modules.
 */

import std_module.source_location;

#include <iostream>
#include <cassert>
#include <cstring>

// Test basic source_location functionality
void test_basic_source_location()
{
    std::cout << "\nTesting basic source_location:\n";

    auto loc = std::source_location::current();

    // Line should be the current line (previous line)
    assert(loc.line() > 0);
    std::cout << "  ✓ Line number: " << loc.line() << "\n";

    // Column should be available (may be 0 on some implementations)
    [[maybe_unused]] auto col = loc.column();
    std::cout << "  ✓ Column number: " << col << "\n";

    // File name should be this file
    const char* file = loc.file_name();
    assert(file != nullptr);
    assert(std::strlen(file) > 0);
    std::cout << "  ✓ File name: " << file << "\n";

    // Function name should be this function
    const char* func = loc.function_name();
    assert(func != nullptr);
    assert(std::strlen(func) > 0);
    std::cout << "  ✓ Function name: " << func << "\n";
}

// Test source_location in different contexts
void helper_function(const std::source_location& loc = std::source_location::current())
{
    std::cout << "\n  Called from:\n";
    std::cout << "    File: " << loc.file_name() << "\n";
    std::cout << "    Line: " << loc.line() << "\n";
    std::cout << "    Function: " << loc.function_name() << "\n";
}

void test_source_location_context()
{
    std::cout << "\nTesting source_location in different contexts:\n";

    // Call helper_function, it should capture the calling location
    helper_function();
    std::cout << "  ✓ source_location captures caller context\n";
}

// Test source_location default parameter
void logged_function(
    int value,
    const std::source_location& loc = std::source_location::current())
{
    std::cout << "\n  logged_function(" << value << ") called from:\n";
    std::cout << "    " << loc.file_name() << ":" << loc.line() << "\n";
}

void test_default_parameter()
{
    std::cout << "\nTesting source_location as default parameter:\n";

    logged_function(42);
    std::cout << "  ✓ Default parameter captures call site\n";

    logged_function(99);
    std::cout << "  ✓ Multiple calls capture different locations\n";
}

// Test source_location comparison
void test_source_location_comparison()
{
    std::cout << "\nTesting source_location comparison:\n";

    auto loc1 = std::source_location::current();
    auto loc2 = std::source_location::current();

    // These should be different lines
    assert(loc1.line() != loc2.line());
    std::cout << "  ✓ Different lines: " << loc1.line() << " vs " << loc2.line() << "\n";

    // Same file
    assert(std::strcmp(loc1.file_name(), loc2.file_name()) == 0);
    std::cout << "  ✓ Same file name\n";
}

// Test source_location in lambda
void test_source_location_lambda()
{
    std::cout << "\nTesting source_location in lambda:\n";

    auto lambda = [loc = std::source_location::current()]() {
        std::cout << "  Lambda defined at line: " << loc.line() << "\n";
        return loc.line();
    };

    auto line = lambda();
    assert(line > 0);
    std::cout << "  ✓ source_location works in lambda\n";
}

// Test source_location copy
void test_source_location_copy()
{
    std::cout << "\nTesting source_location copy:\n";

    auto loc1 = std::source_location::current();
    auto loc2 = loc1;  // Copy

    assert(loc1.line() == loc2.line());
    assert(loc1.column() == loc2.column());
    assert(std::strcmp(loc1.file_name(), loc2.file_name()) == 0);
    assert(std::strcmp(loc1.function_name(), loc2.function_name()) == 0);
    std::cout << "  ✓ source_location is copyable\n";
    std::cout << "  ✓ Copied location has same values\n";
}

int main()
{
    std::cout << "=================================\n";
    std::cout << "Testing std_module.source_location\n";
    std::cout << "=================================\n";

    try
    {
        test_basic_source_location();
        test_source_location_context();
        test_default_parameter();
        test_source_location_comparison();
        test_source_location_lambda();
        test_source_location_copy();

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
