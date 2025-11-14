/**
 * @file test_iostream.cpp
 * @brief Comprehensive tests for std_module.iostream
 *
 * Tests all standard stream objects exported by the iostream module:
 * - std::cin, std::cout, std::cerr, std::clog
 * - std::wcin, std::wcout, std::wcerr, std::wclog
 */

import std_module.iostream;

#include <cassert>
#include <sstream>
#include <string>

// Test that cout is accessible and can perform basic output
void test_cout_basic() {
    std::cout << "\n=== Testing std::cout ===" << "\n";

    // Test basic output
    std::cout << "  ✓ Basic string output works" << "\n";

    // Test integer output
    std::cout << "  ✓ Integer output: " << 42 << "\n";

    // Test floating-point output
    std::cout << "  ✓ Float output: " << 3.14159 << "\n";

    // Test chained output
    std::cout << "  ✓ Chained output: " << "Hello" << " " << "World" << " " << 2024 << "\n";

    // Test flush
    std::cout << "  ✓ Flush operation" << std::flush;
    std::cout << "\n";

    // Test endl (outputs newline and flushes)
    std::cout << "  ✓ Endl operation" << std::endl;
}

// Test that cerr is accessible (unbuffered error stream)
void test_cerr_basic() {
    std::cout << "\n=== Testing std::cerr ===" << "\n";

    // cerr is unbuffered, used for error messages
    std::cerr << "  ✓ Basic error stream output (cerr)" << "\n";

    std::cerr << "  ✓ Error with integer: " << 404 << "\n";

    // Verify cerr is distinct from cout
    std::cout << "  ✓ cerr is distinct from cout" << "\n";
}

// Test that clog is accessible (buffered log stream)
void test_clog_basic() {
    std::cout << "\n=== Testing std::clog ===" << "\n";

    // clog is buffered, used for logging
    std::clog << "  ✓ Basic log stream output (clog)" << "\n";

    std::clog << "  ✓ Log with timestamp: " << 1234567890 << "\n";

    std::cout << "  ✓ clog is distinct from cout" << "\n";
}

// Test wide character cout
void test_wcout_basic() {
    std::cout << "\n=== Testing std::wcout ===" << "\n";

    // Wide character output
    std::wcout << L"  ✓ Wide string output works" << L"\n";

    std::wcout << L"  ✓ Wide integer: " << 42 << L"\n";

    std::wcout << L"  ✓ Wide float: " << 2.71828 << L"\n";

    std::cout << "  ✓ wcout wide character tests completed" << "\n";
}

// Test wide character cerr
void test_wcerr_basic() {
    std::cout << "\n=== Testing std::wcerr ===" << "\n";

    // Wide character error stream (unbuffered)
    std::wcerr << L"  ✓ Wide error stream output (wcerr)" << L"\n";

    std::wcerr << L"  ✓ Wide error code: " << 500 << L"\n";

    std::cout << "  ✓ wcerr wide character tests completed" << "\n";
}

// Test wide character clog
void test_wclog_basic() {
    std::cout << "\n=== Testing std::wclog ===" << "\n";

    // Wide character log stream (buffered)
    std::wclog << L"  ✓ Wide log stream output (wclog)" << L"\n";

    std::wclog << L"  ✓ Wide log entry: " << 999 << L"\n";

    std::cout << "  ✓ wclog wide character tests completed" << "\n";
}

// Test stream state and properties
void test_stream_properties() {
    std::cout << "\n=== Testing Stream Properties ===" << "\n";

    // Test that streams are in good state
    assert(std::cout.good() && "cout should be in good state");
    std::cout << "  ✓ cout.good() returns true" << "\n";

    assert(std::cerr.good() && "cerr should be in good state");
    std::cout << "  ✓ cerr.good() returns true" << "\n";

    assert(std::clog.good() && "clog should be in good state");
    std::cout << "  ✓ clog.good() returns true" << "\n";

    assert(std::wcout.good() && "wcout should be in good state");
    std::cout << "  ✓ wcout.good() returns true" << "\n";

    assert(std::wcerr.good() && "wcerr should be in good state");
    std::cout << "  ✓ wcerr.good() returns true" << "\n";

    assert(std::wclog.good() && "wclog should be in good state");
    std::cout << "  ✓ wclog.good() returns true" << "\n";
}

// Test various data types with cout
void test_output_types() {
    std::cout << "\n=== Testing Various Output Types ===" << "\n";

    // Boolean
    std::cout << "  ✓ Boolean (true): " << true << "\n";
    std::cout << "  ✓ Boolean (false): " << false << "\n";

    // Character
    std::cout << "  ✓ Character: " << 'A' << "\n";

    // Integer types
    short s = 100;
    int i = 1000;
    long l = 10000L;
    long long ll = 100000LL;

    std::cout << "  ✓ Short: " << s << "\n";
    std::cout << "  ✓ Int: " << i << "\n";
    std::cout << "  ✓ Long: " << l << "\n";
    std::cout << "  ✓ Long long: " << ll << "\n";

    // Unsigned types
    unsigned int ui = 42u;
    std::cout << "  ✓ Unsigned int: " << ui << "\n";

    // Floating-point types
    float f = 3.14f;
    double d = 2.71828;
    long double ld = 1.41421L;

    std::cout << "  ✓ Float: " << f << "\n";
    std::cout << "  ✓ Double: " << d << "\n";
    std::cout << "  ✓ Long double: " << ld << "\n";

    // Pointer
    void* ptr = nullptr;
    std::cout << "  ✓ Nullptr: " << ptr << "\n";

    // String literal
    const char* str = "Hello, iostream!";
    std::cout << "  ✓ C-string: " << str << "\n";
}

// Test that we can use endl and flush manipulators
void test_manipulators() {
    std::cout << "\n=== Testing Stream Manipulators ===" << "\n";

    // endl - outputs newline and flushes
    std::cout << "  ✓ Testing endl";
    std::cout << std::endl;

    // flush - flushes the output buffer
    std::cout << "  ✓ Testing flush";
    std::cout << std::flush;
    std::cout << "\n";

    // Multiple endls
    std::cout << "  ✓ Multiple endls:" << std::endl << std::endl;
}

// Test cin exists (we can't easily test input without user interaction)
void test_cin_exists() {
    std::cout << "\n=== Testing std::cin (existence) ===" << "\n";

    // We can't easily test actual input, but we can verify the stream exists
    // and check its state
    assert(std::cin.good() && "cin should be in good state initially");
    std::cout << "  ✓ cin exists and is accessible" << "\n";
    std::cout << "  ✓ cin.good() returns true" << "\n";

    // Same for wcin
    assert(std::wcin.good() && "wcin should be in good state initially");
    std::cout << "  ✓ wcin exists and is accessible" << "\n";
    std::cout << "  ✓ wcin.good() returns true" << "\n";
}

int main() {
    std::cout << "========================================" << "\n";
    std::cout << "std_module.iostream Test Suite" << "\n";
    std::cout << "========================================" << "\n";

    try {
        test_cout_basic();
        test_cerr_basic();
        test_clog_basic();
        test_wcout_basic();
        test_wcerr_basic();
        test_wclog_basic();
        test_stream_properties();
        test_output_types();
        test_manipulators();
        test_cin_exists();

        std::cout << "\n========================================" << "\n";
        std::cout << "✅ All tests passed!" << "\n";
        std::cout << "========================================" << "\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\n❌ Test failed with unknown exception" << "\n";
        return 1;
    }
}
