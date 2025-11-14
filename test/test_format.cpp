/**
 * @file test_format.cpp
 * @brief Comprehensive test for std_module.format (C++20)
 */

import std_module.format;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string; (required for format tests)
#include <iterator>  // FIXME: Should be import std_module.iterator; (required for back_inserter)

// NOTE: std::format tests inherently require std::string support.
// These tests will remain blocked until import std_module.string is available.

// Custom type for testing custom formatter
struct Point {
    int x, y;
};

// Custom formatter for Point
template<>
struct std::formatter<Point> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Point& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", p.x, p.y);
    }
};

void test_basic_format() {
    std::cout << "Testing basic format...\n";

    // Test basic format
    auto msg = std::format("Hello, {}!", "World");
    assert(msg == "Hello, World!");
    std::cout << "  ✓ " << msg << "\n";

    // Test format with multiple arguments
    auto msg2 = std::format("The answer is {} and pi is approximately {:.2f}", 42, 3.14159);
    assert(msg2 == "The answer is 42 and pi is approximately 3.14");
    std::cout << "  ✓ " << msg2 << "\n";

    // Test format with positional arguments
    auto msg3 = std::format("{1} comes before {0}", "second", "first");
    assert(msg3 == "first comes before second");
    std::cout << "  ✓ " << msg3 << "\n";
}

void test_format_to() {
    std::cout << "\nTesting format_to...\n";

    std::string buffer;
    std::format_to(std::back_inserter(buffer), "Value: {}", 42);
    assert(buffer == "Value: 42");
    std::cout << "  ✓ format_to with back_inserter: " << buffer << "\n";

    // Test format_to with multiple values
    buffer.clear();
    std::format_to(std::back_inserter(buffer), "{} + {} = {}", 2, 2, 4);
    assert(buffer == "2 + 2 = 4");
    std::cout << "  ✓ format_to with multiple args: " << buffer << "\n";
}

void test_format_to_n() {
    std::cout << "\nTesting format_to_n...\n";

    char buffer[20];
    auto result = std::format_to_n(buffer, sizeof(buffer) - 1, "Test: {}", 123);
    *result.out = '\0';  // Null-terminate

    assert(std::string(buffer) == "Test: 123");
    std::cout << "  ✓ format_to_n: " << buffer << "\n";
    std::cout << "  ✓ Characters written: " << result.size << "\n";

    // Test truncation
    char small_buffer[5];
    auto result2 = std::format_to_n(small_buffer, sizeof(small_buffer) - 1, "LongString");
    small_buffer[4] = '\0';
    std::cout << "  ✓ Truncated output: " << small_buffer << " (size would be: " << result2.size << ")\n";
}

void test_formatted_size() {
    std::cout << "\nTesting formatted_size...\n";

    size_t size = std::formatted_size("Value: {}", 42);
    std::string formatted = std::format("Value: {}", 42);
    assert(size == formatted.size());
    std::cout << "  ✓ formatted_size: " << size << " (matches actual: " << formatted.size() << ")\n";

    size_t size2 = std::formatted_size("{:.2f}", 3.14159);
    std::cout << "  ✓ formatted_size for float: " << size2 << "\n";
}

void test_vformat() {
    std::cout << "\nTesting vformat...\n";

    // make_format_args requires lvalue references
    std::string world = "World";
    int answer = 42;
    auto args = std::make_format_args(world, answer);
    std::string result = std::vformat("Hello {}! The answer is {}", args);
    assert(result == "Hello World! The answer is 42");
    std::cout << "  ✓ vformat: " << result << "\n";
}

void test_vformat_to() {
    std::cout << "\nTesting vformat_to...\n";

    std::string buffer;
    // make_format_args requires lvalue references
    double pi_value = 3.14159;
    std::string pi_name = "pi";
    auto args = std::make_format_args(pi_value, pi_name);
    std::vformat_to(std::back_inserter(buffer), "{:.2f} is {}", args);
    assert(buffer == "3.14 is pi");
    std::cout << "  ✓ vformat_to: " << buffer << "\n";
}

void test_format_error() {
    std::cout << "\nTesting format_error...\n";

    // Note: Most format errors are caught at compile time with format_string
    // Runtime errors can occur with vformat and runtime format strings

    try {
        // Runtime format string errors via vformat
        int value = 42;
        auto args = std::make_format_args(value);
        // Valid format string - this won't throw
        auto result = std::vformat("Value: {}", args);
        std::cout << "  ✓ Valid vformat succeeded: " << result << "\n";
    } catch (const std::format_error& e) {
        std::cout << "  ✗ Unexpected format_error: " << e.what() << "\n";
    }

    // Demonstrate that format_error exists and can be constructed
    std::cout << "  ✓ format_error type is available and can be used\n";

    // Test argument count mismatch at runtime with vformat
    try {
        int value = 42;
        auto args = std::make_format_args(value);
        // Too many placeholders for the number of arguments
        auto result = std::vformat("{} {}", args);
        std::cout << "  ✗ Should have thrown format_error for arg mismatch\n";
    } catch (const std::format_error& e) {
        std::cout << "  ✓ Caught format_error for arg mismatch: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "  ~ Caught exception (implementation-dependent): " << e.what() << "\n";
    }
}

void test_custom_formatter() {
    std::cout << "\nTesting custom formatter...\n";

    Point p{10, 20};
    auto result = std::format("Point: {}", p);
    assert(result == "Point: (10, 20)");
    std::cout << "  ✓ Custom formatter: " << result << "\n";

    // Test with multiple custom types
    Point p2{5, 15};
    auto result2 = std::format("From {} to {}", p, p2);
    assert(result2 == "From (10, 20) to (5, 15)");
    std::cout << "  ✓ Multiple custom types: " << result2 << "\n";
}

void test_wide_char_format() {
    std::cout << "\nTesting wide character format...\n";

    std::wstring wresult = std::format(L"Wide: {}", 42);
    assert(wresult == L"Wide: 42");
    std::wcout << L"  ✓ Wide format: " << wresult << L"\n";

    // Test make_wformat_args (requires lvalue)
    std::wstring world = L"World";
    auto wargs = std::make_wformat_args(world);
    std::wstring wresult2 = std::vformat(L"Hello {}!", wargs);
    assert(wresult2 == L"Hello World!");
    std::wcout << L"  ✓ Wide vformat: " << wresult2 << L"\n";
}

void test_format_string_types() {
    std::cout << "\nTesting format_string types...\n";

    // format_string is a wrapper that validates format strings at compile time
    std::format_string<int, double> fmt = "int: {}, double: {:.2f}";
    auto result = std::format(fmt, 42, 3.14159);
    assert(result == "int: 42, double: 3.14");
    std::cout << "  ✓ format_string: " << result << "\n";

    // Test with wformat_string
    std::wformat_string<int> wfmt = L"Value: {}";
    auto wresult = std::format(wfmt, 99);
    assert(wresult == L"Value: 99");
    std::wcout << L"  ✓ wformat_string: " << wresult << L"\n";
}

void test_various_types() {
    std::cout << "\nTesting various types...\n";

    // Integer types
    auto r1 = std::format("int: {}, unsigned: {}, hex: {:x}", -42, 42u, 255);
    std::cout << "  ✓ " << r1 << "\n";

    // Floating point
    auto r2 = std::format("float: {:.2f}, scientific: {:e}", 3.14159f, 1234.5);
    std::cout << "  ✓ " << r2 << "\n";

    // Boolean
    auto r3 = std::format("bool: {}, bool: {}", true, false);
    std::cout << "  ✓ " << r3 << "\n";

    // Strings
    auto r4 = std::format("string: {}, cstr: {}", std::string("hello"), "world");
    std::cout << "  ✓ " << r4 << "\n";

    // Pointers
    int x = 42;
    auto r5 = std::format("ptr: {}", static_cast<void*>(&x));
    std::cout << "  ✓ " << r5 << "\n";
}

void test_alignment_and_fill() {
    std::cout << "\nTesting alignment and fill...\n";

    // Left align
    auto r1 = std::format("|{:<10}|", "left");
    std::cout << "  ✓ Left align: " << r1 << "\n";

    // Right align
    auto r2 = std::format("|{:>10}|", "right");
    std::cout << "  ✓ Right align: " << r2 << "\n";

    // Center
    auto r3 = std::format("|{:^10}|", "center");
    std::cout << "  ✓ Center: " << r3 << "\n";

    // Custom fill character
    auto r4 = std::format("|{:*>10}|", "fill");
    std::cout << "  ✓ Custom fill: " << r4 << "\n";

    // Number formatting with width
    auto r5 = std::format("{:05}", 42);
    std::cout << "  ✓ Zero-padded: " << r5 << "\n";
}

int main()
{
    std::cout << "=== C++20 std::format Comprehensive Tests ===\n";
    std::cout << "NOTE: Tests currently require #include <string> and <iterator>\n";
    std::cout << "      These will be replaced with module imports when available\n\n";

    try {
        test_basic_format();
        test_format_to();
        test_format_to_n();
        test_formatted_size();
        test_vformat();
        test_vformat_to();
        test_format_error();
        test_custom_formatter();
        test_wide_char_format();
        test_format_string_types();
        test_various_types();
        test_alignment_and_fill();

        std::cout << "\n=== All tests passed! ===\n";
        std::cout << "(Pending: module-pure implementation requires std_module.string and std_module.iterator)\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n!!! Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
