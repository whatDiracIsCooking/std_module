/**
 * @file test_istream.cpp
 * @brief Tests for std_module.istream
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that input stream classes and operations are accessible through the module.
 */

import std_module.istream;
import std_module.test_framework;

// Need these for testing with string streams
#include <sstream>
#include <string>

int main() {
    test::test_header("std_module.istream");

    test::section("Testing symbol accessibility");

    // Test basic extraction operators are accessible
    std::istringstream iss("42 3.14 hello");
    int i;
    double d;
    std::string s;

    iss >> i >> d >> s;
    test::success("extraction operators (>>) for int, double, string");

    // Test istream member functions are accessible
    std::istringstream iss2("ABC");
    char c = static_cast<char>(iss2.get());
    c = static_cast<char>(iss2.peek());
    iss2.putback('B');
    iss2.unget();
    test::success("get, peek, putback, unget");

    // Test read and gcount
    char buffer[10];
    std::istringstream iss3("Hello");
    iss3.read(buffer, 5);
    auto count = iss3.gcount();
    test::assert_true(count > 0, "read and gcount");

    // Test getline
    std::istringstream iss4("Line one\nLine two");
    std::string line;
    std::getline(iss4, line);
    std::getline(iss4, line, '\n');
    test::success("getline (free function)");

    // Test stream state functions
    std::istringstream iss5("123");
    test::assert_true(iss5.good(), "good");
    test::assert_true(!iss5.eof(), "eof");
    test::assert_true(!iss5.fail(), "fail");
    iss5.clear();
    test::success("clear");

    // Test ws manipulator
    std::istringstream iss6("  data");
    iss6 >> std::ws;
    test::success("ws manipulator");

    // Test wide streams
    std::wistringstream wiss(L"42 hello");
    int wi;
    std::wstring ws;
    wiss >> wi >> ws;
    test::success("wide character input streams");

    // Test iostream (bidirectional)
    std::stringstream ss;
    ss << "test" << 42;
    std::string word;
    int num;
    ss >> word >> num;
    test::success("iostream (bidirectional)");

    // Test stream positioning
    std::istringstream iss7("0123456789");
    auto pos = iss7.tellg();
    iss7.seekg(0);
    test::assert_true(pos >= 0, "tellg and seekg");

    // Test ignore
    std::istringstream iss8("skip:keep");
    iss8.ignore(100, ':');
    test::success("ignore");

    test::test_footer();
    return 0;
}
