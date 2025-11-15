/**
 * @file test_ostream.cpp
 * @brief Tests for std_module.ostream
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.ostream;
import std_module.test_framework;

int main() {
    test::test_header("std_module.ostream");

    test::section("Testing symbol accessibility");

    // Test basic stream operations are accessible
    std::ostringstream oss;
    test::assert_true(oss.good(), "ostringstream construction");

    oss.put('A');
    test::success("put()");

    const char msg[] = "Hello";
    oss.write(msg, 5);
    test::success("write()");

    oss << "test" << std::flush;
    test::success("operator<< and flush");

    oss << "line" << std::endl;
    test::success("endl");

    oss << "text" << std::ends;
    test::success("ends");

    oss.flush();
    test::success("flush() member");

    std::streampos pos = oss.tellp();
    test::assert_true(pos >= std::streampos(0), "tellp()");

    oss.seekp(0);
    test::success("seekp()");

    // Test wide streams
    std::wostringstream woss;
    woss << L"wide" << std::endl;
    test::success("wide character streams");

    test::test_footer();
    return 0;
}
