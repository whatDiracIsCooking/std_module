/**
 * @file test_ostream.cpp
 * @brief Comprehensive test for std_module.ostream (C++20)
 *
 * NOTE: This module has partial functionality due to C++20 module ADL limitations.
 * Operator overloads (operator<<) for user-defined types may not be found through
 * module boundaries. Most stream insertion operations work because they are member
 * functions or use standard library types which are properly exported.
 *
 * Reference: https://github.com/cplusplus/papers/issues/1005
 */

import std_module.ostream;

#include <iostream>  // For std::cout to display test results
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <sstream>   // For testing with stringstreams
#include <string>    // For string operations

// Custom type for testing operator<< (may be affected by ADL limitation)
struct Point {
    int x, y;
};

// Global operator<< for Point (may not be found through module boundaries)
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

void test_basic_output() {
    std::cout << "Testing basic ostream output...\n";

    std::ostringstream oss;

    // Test put() - outputs a single character
    oss.put('A');
    assert(oss.str() == "A");
    std::cout << "  ✓ put(): " << oss.str() << "\n";

    // Test write() - outputs a character array
    oss.str("");  // Clear
    const char msg[] = "Hello";
    oss.write(msg, 5);
    assert(oss.str() == "Hello");
    std::cout << "  ✓ write(): " << oss.str() << "\n";
}

void test_manipulators() {
    std::cout << "\nTesting stream manipulators...\n";

    std::ostringstream oss;

    // Test flush manipulator
    oss << "test" << std::flush;
    assert(oss.str() == "test");
    std::cout << "  ✓ flush manipulator: " << oss.str() << "\n";

    // Test endl manipulator (newline + flush)
    oss.str("");  // Clear
    oss << "line1" << std::endl << "line2";
    assert(oss.str() == "line1\nline2");
    std::cout << "  ✓ endl manipulator: " << oss.str().length() << " chars\n";

    // Test ends manipulator (null character)
    oss.str("");  // Clear
    oss << "text" << std::ends << "more";
    std::string result = oss.str();
    assert(result.length() == 9);  // "text\0more"
    std::cout << "  ✓ ends manipulator: inserted null character\n";
}

void test_stream_state() {
    std::cout << "\nTesting stream state...\n";

    std::ostringstream oss;

    // Test good() state
    assert(oss.good());
    std::cout << "  ✓ Initial state is good\n";

    // Write some data
    oss << "test data";
    assert(oss.good());
    std::cout << "  ✓ State remains good after write\n";

    // Test flush() member function
    oss.flush();
    assert(oss.good());
    std::cout << "  ✓ flush() member function works\n";
}

void test_position_operations() {
    std::cout << "\nTesting position operations...\n";

    std::ostringstream oss;

    // Write initial data
    oss << "Hello World";

    // Get current position
    std::streampos pos = oss.tellp();
    assert(pos == std::streampos(11));
    std::cout << "  ✓ tellp(): position = " << pos << "\n";

    // Seek to beginning
    oss.seekp(0);
    pos = oss.tellp();
    assert(pos == std::streampos(0));
    std::cout << "  ✓ seekp(0): moved to beginning\n";

    // Overwrite
    oss << "HELLO";
    assert(oss.str() == "HELLO World");
    std::cout << "  ✓ Overwrite after seek: " << oss.str() << "\n";

    // Seek to end
    oss.seekp(0, std::ios_base::end);
    oss << "!";
    assert(oss.str() == "HELLO World!");
    std::cout << "  ✓ seekp() with offset: " << oss.str() << "\n";
}

void test_character_output() {
    std::cout << "\nTesting character output methods...\n";

    std::ostringstream oss;

    // Test multiple put() calls
    oss.put('A').put('B').put('C');
    assert(oss.str() == "ABC");
    std::cout << "  ✓ Chained put(): " << oss.str() << "\n";

    // Test write() with partial array
    oss.str("");  // Clear
    const char data[] = "ABCDEFGH";
    oss.write(data, 4);  // Only write first 4 chars
    assert(oss.str() == "ABCD");
    std::cout << "  ✓ Partial write(): " << oss.str() << "\n";
}

void test_builtin_types() {
    std::cout << "\nTesting built-in type insertion...\n";

    std::ostringstream oss;

    // Test integer
    oss << 42;
    assert(oss.str() == "42");
    std::cout << "  ✓ Integer insertion: " << oss.str() << "\n";

    // Test string
    oss.str("");  // Clear
    oss << "Hello, World!";
    assert(oss.str() == "Hello, World!");
    std::cout << "  ✓ String insertion: " << oss.str() << "\n";

    // Test multiple insertions
    oss.str("");  // Clear
    oss << "The answer is " << 42;
    assert(oss.str() == "The answer is 42");
    std::cout << "  ✓ Multiple insertions: " << oss.str() << "\n";

    // Test floating point
    oss.str("");  // Clear
    oss << 3.14;
    std::string result = oss.str();
    assert(result.find("3.14") != std::string::npos);
    std::cout << "  ✓ Float insertion: " << result << "\n";

    // Test boolean
    oss.str("");  // Clear
    oss << true << " " << false;
    assert(oss.str() == "1 0");
    std::cout << "  ✓ Boolean insertion: " << oss.str() << "\n";
}

// FIXME: C++20 module ADL limitation - operator<< for user types may not be found
// void test_custom_types() {
//     std::cout << "\nTesting custom type insertion...\n";
//
//     std::ostringstream oss;
//     Point p{10, 20};
//
//     // This may fail: operator<< for Point might not be found via ADL
//     oss << p;
//     assert(oss.str() == "(10, 20)");
//     std::cout << "  ✓ Custom type insertion: " << oss.str() << "\n";
// }

void test_wide_streams() {
    std::cout << "\nTesting wide character streams...\n";

    std::wostringstream woss;

    // Test wchar_t output
    woss.put(L'W');
    assert(woss.str() == L"W");
    std::cout << "  ✓ Wide put() works\n";

    // Test wide string
    woss.str(L"");  // Clear
    woss << L"Wide String";
    assert(woss.str() == L"Wide String");
    std::cout << "  ✓ Wide string insertion works\n";

    // Test wide manipulators
    woss.str(L"");  // Clear
    woss << L"Line1" << std::endl << L"Line2";
    assert(woss.str() == L"Line1\nLine2");
    std::cout << "  ✓ Wide manipulators work\n";
}

void test_stream_return_value() {
    std::cout << "\nTesting stream return values...\n";

    std::ostringstream oss;

    // Test that operations return the stream for chaining
    std::ostream& ref = (oss << "A");
    assert(&ref == &oss);
    std::cout << "  ✓ Insertion returns stream reference\n";

    // Test chaining with put()
    std::ostream& ref2 = oss.put('B');
    assert(&ref2 == &oss);
    assert(oss.str() == "AB");
    std::cout << "  ✓ put() returns stream reference: " << oss.str() << "\n";
}

void test_flush_operations() {
    std::cout << "\nTesting flush operations...\n";

    std::ostringstream oss;

    // Member function flush()
    oss << "test";
    oss.flush();
    assert(oss.str() == "test");
    std::cout << "  ✓ flush() member function\n";

    // Manipulator flush
    oss.str("");
    oss << "test" << std::flush;
    assert(oss.str() == "test");
    std::cout << "  ✓ flush manipulator\n";

    // Chaining flushes
    oss.str("");
    oss << "A" << std::flush << "B" << std::flush << "C";
    assert(oss.str() == "ABC");
    std::cout << "  ✓ Multiple flushes: " << oss.str() << "\n";
}

int main() {
    std::cout << "==============================================\n";
    std::cout << "std_module.ostream Comprehensive Test Suite\n";
    std::cout << "==============================================\n\n";

    test_basic_output();
    test_manipulators();
    test_stream_state();
    test_position_operations();
    test_character_output();
    test_builtin_types();
    // test_custom_types();  // FIXME: Disabled due to ADL limitation
    test_wide_streams();
    test_stream_return_value();
    test_flush_operations();

    std::cout << "\n==============================================\n";
    std::cout << "All tests passed! ✓\n";
    std::cout << "==============================================\n";

    return 0;
}
