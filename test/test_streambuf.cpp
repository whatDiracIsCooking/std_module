/**
 * @file test_streambuf.cpp
 * @brief Tests for std_module.streambuf
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.streambuf;
import std_module.test_framework;

// Minimal custom streambuf for testing
class TestBuffer : public std::streambuf {
public:
    TestBuffer() {
        char* buf = new char[100];
        setg(buf, buf, buf + 100);
        setp(buf, buf + 100);
    }
};

int main() {
    test::test_header("std_module.streambuf");

    test::section("Testing symbol accessibility");

    // Test basic types
    [[maybe_unused]] std::streambuf* sb = nullptr;
    [[maybe_unused]] std::wstreambuf* wsb = nullptr;
    test::success("streambuf and wstreambuf types");

    // Test custom buffer
    TestBuffer buf;
    test::assert_true(buf.in_avail() >= 0, "in_avail");
    test::assert_true(buf.pubsync() != -2, "pubsync"); // Returns -1 or 0, not -2
    [[maybe_unused]] auto loc = buf.getloc();
    test::success("getloc");

    test::test_footer();
    return 0;
}
