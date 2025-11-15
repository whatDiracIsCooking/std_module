/**
 * @file test_ostream.cpp
 * @brief Tests for std_module.ostream
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.ostream;
import std_module.test_framework;
#include <sstream>  // For ostringstream (not in ostream module)

int main() {
    test::test_header("std_module.ostream");

    test::section("Testing symbol accessibility");

    // Test basic stream operations are accessible
    std::ostringstream oss;
    std::ostream& os = oss;  // Use ostream interface from module
    test::assert_true(os.good(), "ostream reference");

    os.put('A');
    test::success("put()");

    const char msg[] = "Hello";
    os.write(msg, 5);
    test::success("write()");

    os << "test" << std::flush;
    test::success("operator<< and flush");

    os << "line" << std::endl;
    test::success("endl");

    os << "text" << std::ends;
    test::success("ends");

    os.flush();
    test::success("flush() member");

    std::streampos pos = os.tellp();
    test::assert_true(pos >= std::streampos(0), "tellp()");

    os.seekp(0);
    test::success("seekp()");

    // Test wide streams
    std::wostringstream woss;
    std::wostream& wos = woss;  // Use wostream interface from module
    wos << L"wide" << std::endl;
    test::success("wide character streams");

    test::test_footer();
    return 0;
}
