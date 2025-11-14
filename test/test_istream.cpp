/**
 * @file test_istream.cpp
 * @brief Comprehensive tests for std_module.istream
 *
 * Tests all input stream classes and manipulators exported by the istream module:
 * - std::istream, std::wistream
 * - std::iostream, std::wiostream
 * - std::ws manipulator
 * - Various input operations
 */

import std_module.istream;

#include <cassert>
#include <sstream>
#include <string>
#include <iostream>

// Test basic istream extraction operators
void test_basic_extraction() {
    std::cout << "\n=== Testing Basic Extraction Operators ===" << "\n";

    std::istringstream iss("42 3.14 hello");

    int i;
    double d;
    std::string s;

    iss >> i;
    assert(i == 42);
    std::cout << "  ✓ Integer extraction: " << i << "\n";

    iss >> d;
    assert(d == 3.14);
    std::cout << "  ✓ Double extraction: " << d << "\n";

    iss >> s;
    assert(s == "hello");
    std::cout << "  ✓ String extraction: " << s << "\n";
}

// Test istream member functions
void test_istream_members() {
    std::cout << "\n=== Testing istream Member Functions ===" << "\n";

    // Test get()
    std::istringstream iss1("ABC");
    char c = static_cast<char>(iss1.get());
    assert(c == 'A');
    std::cout << "  ✓ get() returns: " << c << "\n";

    // Test peek()
    char p = static_cast<char>(iss1.peek());
    assert(p == 'B');
    std::cout << "  ✓ peek() returns: " << p << " (without consuming)" << "\n";

    // Verify peek didn't consume
    c = static_cast<char>(iss1.get());
    assert(c == 'B');
    std::cout << "  ✓ Next get() after peek() returns: " << c << "\n";

    // Test putback()
    iss1.putback('B');
    c = static_cast<char>(iss1.get());
    assert(c == 'B');
    std::cout << "  ✓ putback() and get() returns: " << c << "\n";

    // Test unget()
    iss1.unget();
    c = static_cast<char>(iss1.get());
    assert(c == 'B');
    std::cout << "  ✓ unget() and get() returns: " << c << "\n";

    // Test read()
    std::istringstream iss2("Hello");
    char buffer[6] = {};
    iss2.read(buffer, 5);
    assert(std::string(buffer) == "Hello");
    std::cout << "  ✓ read() buffer: " << buffer << "\n";

    // Test gcount()
    std::streamsize count = iss2.gcount();
    assert(count == 5);
    std::cout << "  ✓ gcount() returns: " << count << "\n";
}

// Test getline functionality
void test_getline() {
    std::cout << "\n=== Testing getline ===" << "\n";

    std::istringstream iss("First line\nSecond line\nThird line");

    std::string line;
    std::getline(iss, line);
    assert(line == "First line");
    std::cout << "  ✓ First getline: " << line << "\n";

    std::getline(iss, line);
    assert(line == "Second line");
    std::cout << "  ✓ Second getline: " << line << "\n";

    std::getline(iss, line);
    assert(line == "Third line");
    std::cout << "  ✓ Third getline: " << line << "\n";

    // Test getline with custom delimiter
    std::istringstream iss2("apple,banana,cherry");
    std::getline(iss2, line, ',');
    assert(line == "apple");
    std::cout << "  ✓ getline with comma delimiter: " << line << "\n";

    std::getline(iss2, line, ',');
    assert(line == "banana");
    std::cout << "  ✓ getline with comma delimiter: " << line << "\n";
}

// Test stream state functions
void test_stream_state() {
    std::cout << "\n=== Testing Stream State Functions ===" << "\n";

    std::istringstream iss("123");

    assert(iss.good());
    std::cout << "  ✓ good() returns true for valid stream" << "\n";

    assert(!iss.eof());
    std::cout << "  ✓ eof() returns false before reading all data" << "\n";

    assert(!iss.fail());
    std::cout << "  ✓ fail() returns false for valid stream" << "\n";

    // Read all data
    int val;
    iss >> val;

    // Try to read past end
    iss >> val;
    assert(iss.eof() || iss.fail());
    std::cout << "  ✓ Stream sets eof/fail after reading past end" << "\n";

    // Test clear()
    iss.clear();
    assert(!iss.fail());
    std::cout << "  ✓ clear() resets error state" << "\n";
}

// Test ws manipulator (skip leading whitespace)
void test_ws_manipulator() {
    std::cout << "\n=== Testing ws Manipulator ===" << "\n";

    std::istringstream iss("   \t\n  data");

    // Without ws, get() would return whitespace
    iss >> std::ws;  // Skip leading whitespace

    char c = static_cast<char>(iss.get());
    assert(c == 'd');
    std::cout << "  ✓ ws skipped whitespace, get() returns: " << c << "\n";

    // Test ws in extraction sequence
    std::istringstream iss2("  42  ");
    int val;
    iss2 >> std::ws >> val;
    assert(val == 42);
    std::cout << "  ✓ ws in extraction chain, value: " << val << "\n";
}

// Test wide character input streams
void test_wide_streams() {
    std::cout << "\n=== Testing Wide Character Streams ===" << "\n";

    std::wistringstream wiss(L"42 3.14 hello");

    int i;
    double d;
    std::wstring ws;

    wiss >> i;
    assert(i == 42);
    std::wcout << L"  ✓ Wide integer extraction: " << i << L"\n";

    wiss >> d;
    assert(d == 3.14);
    std::wcout << L"  ✓ Wide double extraction: " << d << L"\n";

    wiss >> ws;
    assert(ws == L"hello");
    std::wcout << L"  ✓ Wide string extraction: " << ws.c_str() << L"\n";

    // Test wide getline
    std::wistringstream wiss2(L"Line one\nLine two");
    std::wstring wline;
    std::getline(wiss2, wline);
    assert(wline == L"Line one");
    std::wcout << L"  ✓ Wide getline: " << wline.c_str() << L"\n";

    std::cout << "  ✓ All wide stream tests completed" << "\n";
}

// Test iostream (bidirectional streams)
void test_iostream_bidirectional() {
    std::cout << "\n=== Testing iostream (Bidirectional) ===" << "\n";

    std::stringstream ss;

    // Test output
    ss << "Hello " << 42 << " World";
    std::cout << "  ✓ iostream output: " << ss.str() << "\n";

    // Test input from same stream
    std::string word;
    int num;

    ss >> word;
    assert(word == "Hello");
    std::cout << "  ✓ iostream input (string): " << word << "\n";

    ss >> num;
    assert(num == 42);
    std::cout << "  ✓ iostream input (int): " << num << "\n";

    ss >> word;
    assert(word == "World");
    std::cout << "  ✓ iostream input (string): " << word << "\n";

    // Test seekg and tellg
    ss.clear();
    ss.seekg(0);
    auto pos = ss.tellg();
    assert(pos == 0);
    std::cout << "  ✓ seekg(0) and tellg() returns: " << pos << "\n";
}

// Test various numeric extraction types
void test_numeric_extraction() {
    std::cout << "\n=== Testing Numeric Extraction Types ===" << "\n";

    std::istringstream iss("1 -2 300 -4000 5.5 -6.6");

    short s;
    iss >> s;
    assert(s == 1);
    std::cout << "  ✓ Short extraction: " << s << "\n";

    int i;
    iss >> i;
    assert(i == -2);
    std::cout << "  ✓ Negative int extraction: " << i << "\n";

    long l;
    iss >> l;
    assert(l == 300);
    std::cout << "  ✓ Long extraction: " << l << "\n";

    long long ll;
    iss >> ll;
    assert(ll == -4000);
    std::cout << "  ✓ Long long extraction: " << ll << "\n";

    float f;
    iss >> f;
    assert(f == 5.5f);
    std::cout << "  ✓ Float extraction: " << f << "\n";

    double d;
    iss >> d;
    assert(d == -6.6);
    std::cout << "  ✓ Double extraction: " << d << "\n";
}

// Test boolean extraction
void test_boolean_extraction() {
    std::cout << "\n=== Testing Boolean Extraction ===" << "\n";

    // Numeric bool format (default)
    std::istringstream iss1("1 0");
    bool b1, b2;
    iss1 >> b1 >> b2;
    assert(b1 == true);
    assert(b2 == false);
    std::cout << "  ✓ Numeric bool extraction: " << b1 << ", " << b2 << "\n";

    // Alpha bool format
    std::istringstream iss2("true false");
    iss2 >> std::boolalpha >> b1 >> b2;
    assert(b1 == true);
    assert(b2 == false);
    std::cout << "  ✓ Alpha bool extraction: true, false" << "\n";
}

// Test character extraction
void test_character_extraction() {
    std::cout << "\n=== Testing Character Extraction ===" << "\n";

    std::istringstream iss("A B C");
    char c1, c2, c3;

    iss >> c1 >> c2 >> c3;
    assert(c1 == 'A');
    assert(c2 == 'B');
    assert(c3 == 'C');
    std::cout << "  ✓ Character extraction: " << c1 << ", " << c2 << ", " << c3 << "\n";

    // Test get with buffer
    std::istringstream iss2("Hello");
    char buffer[10];
    iss2.get(buffer, 10);
    assert(std::string(buffer) == "Hello");
    std::cout << "  ✓ get(buffer, size): " << buffer << "\n";
}

// Test stream positioning
void test_stream_positioning() {
    std::cout << "\n=== Testing Stream Positioning ===" << "\n";

    std::istringstream iss("0123456789");

    // Test tellg
    auto pos1 = iss.tellg();
    assert(pos1 == 0);
    std::cout << "  ✓ Initial tellg(): " << pos1 << "\n";

    // Read some data
    char c;
    iss >> c;

    auto pos2 = iss.tellg();
    assert(pos2 > pos1);
    std::cout << "  ✓ tellg() after read: " << pos2 << "\n";

    // Seek back to beginning
    iss.seekg(0);
    auto pos3 = iss.tellg();
    assert(pos3 == 0);
    std::cout << "  ✓ tellg() after seekg(0): " << pos3 << "\n";

    // Verify we're back at start
    iss >> c;
    assert(c == '0');
    std::cout << "  ✓ Read after seekg(0): " << c << "\n";
}

// Test ignore() function
void test_ignore() {
    std::cout << "\n=== Testing ignore() Function ===" << "\n";

    std::istringstream iss("skip-this-part:keep-this");

    // Ignore up to ':'
    iss.ignore(100, ':');

    std::string result;
    iss >> result;
    assert(result == "keep-this");
    std::cout << "  ✓ ignore(100, ':') result: " << result << "\n";

    // Test ignore with count
    std::istringstream iss2("ABCDEFrest");
    iss2.ignore(5);  // Skip first 5 characters

    char c = static_cast<char>(iss2.get());
    assert(c == 'F');
    std::cout << "  ✓ ignore(5) then get(): " << c << "\n";
}

int main() {
    std::cout << "========================================" << "\n";
    std::cout << "std_module.istream Test Suite" << "\n";
    std::cout << "========================================" << "\n";

    try {
        test_basic_extraction();
        test_istream_members();
        test_getline();
        test_stream_state();
        test_ws_manipulator();
        test_wide_streams();
        test_iostream_bidirectional();
        test_numeric_extraction();
        test_boolean_extraction();
        test_character_extraction();
        test_stream_positioning();
        test_ignore();

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
