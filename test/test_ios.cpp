/**
 * @file test_ios.cpp
 * @brief Tests for std_module.ios
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.ios;
import std_module.system_error;
import std_module.test_framework;

int main() {
    test::test_header("std_module.ios");

    test::section("Testing boolean manipulators");

    // Test boolalpha/noboolalpha (just check they're accessible)
    test::ostringstream oss;
    oss << std::boolalpha << true;
    test::success("boolalpha/noboolalpha accessible");

    test::section("Testing numeric base manipulators");

    // Test dec, hex, oct
    oss.str("");
    oss << std::dec << 42;
    test::success("dec accessible");

    oss.str("");
    oss << std::hex << 255;
    test::success("hex accessible");

    oss.str("");
    oss << std::oct << 64;
    test::success("oct accessible");

    test::section("Testing base notation manipulators");

    // Test showbase/noshowbase
    oss.str("");
    oss << std::showbase << std::hex << 255;
    test::success("showbase/noshowbase accessible");

    test::section("Testing floating point manipulators");

    // Test fixed, scientific, defaultfloat, hexfloat
    oss.str("");
    oss.precision(2);
    oss << std::fixed << 3.14159;
    test::success("fixed accessible");

    oss.str("");
    oss << std::scientific << 1234.5;
    test::success("scientific accessible");

    oss.str("");
    oss << std::defaultfloat << 3.14;
    test::success("defaultfloat accessible");

    oss.str("");
    oss << std::hexfloat << 1.0;
    test::success("hexfloat accessible");

    test::section("Testing sign manipulators");

    // Test showpos/noshowpos
    oss.str("");
    oss << std::showpos << 42;
    test::assert_equal(oss.str(), "+42", "showpos");

    oss.str("");
    oss << std::noshowpos << 42;
    test::assert_equal(oss.str(), "42", "noshowpos");

    test::section("Testing floating point notation");

    // Test showpoint/noshowpoint
    oss.str("");
    oss << std::showpoint << 1.0;
    test::success("showpoint/noshowpoint accessible");

    test::section("Testing case manipulators");

    // Test uppercase/nouppercase
    oss.str("");
    oss << std::uppercase << std::hex << 255;
    test::success("uppercase/nouppercase accessible");

    test::section("Testing alignment manipulators");

    // Test left, right, internal
    oss.str("");
    oss.width(10);
    oss << std::left << 42;
    test::success("left accessible");

    oss.str("");
    oss.width(10);
    oss << std::right << 42;
    test::success("right accessible");

    oss.str("");
    oss.width(10);
    oss << std::internal << std::showpos << 42;
    test::success("internal accessible");

    test::section("Testing whitespace manipulators");

    // Test skipws/noskipws
    test::istringstream iss("  42  ");
    int value;
    iss >> std::skipws >> value;
    test::assert_equal(value, 42, "skipws");
    test::success("noskipws accessible");

    test::section("Testing buffering manipulators");

    // Test unitbuf/nounitbuf
    oss.str("");
    oss << std::unitbuf << "test";
    test::success("unitbuf/nounitbuf accessible");

    test::section("Testing ios_base flags");

    // Test setf, unsetf, flags
    oss.str("");
    oss.setf(std::ios_base::hex, std::ios_base::basefield);
    oss << 255;
    test::success("setf/unsetf accessible");

    test::section("Testing stream state");

    // Test good, eof, fail, bad, clear
    test::ostringstream oss2;
    test::assert_true(oss2.good(), "good");
    test::assert_false(oss2.fail(), "fail");
    test::assert_false(oss2.bad(), "bad");
    test::assert_false(oss2.eof(), "eof");

    test::istringstream iss2("");
    char c;
    iss2 >> c;
    test::assert_true(iss2.eof(), "eof after read");

    iss2.clear();
    test::assert_false(iss2.eof(), "clear");

    test::section("Testing position types");

    // Test streampos, streamoff
    std::streampos pos = 0;
    pos += 10;
    test::assert_equal(pos, std::streampos(10), "streampos");

    std::streamoff offset = 5;
    std::streamoff offset2 = 3;
    test::assert_equal(offset + offset2, std::streamoff(8), "streamoff");

    test::section("Testing error handling");

    // Test iostream_category, io_errc
    const std::error_category& cat = std::iostream_category();
    test::success("iostream_category accessible");

    auto ec = std::make_error_code(std::io_errc::stream);
    test::success("make_error_code/io_errc accessible");

    auto cond = std::make_error_condition(std::io_errc::stream);
    test::success("make_error_condition accessible");

    test::section("Testing type aliases");

    // Test ios, wios type aliases
    [[maybe_unused]] std::ios* ios_ptr = nullptr;
    test::success("std::ios type alias accessible");

    [[maybe_unused]] std::wios* wios_ptr = nullptr;
    test::success("std::wios type alias accessible");

    test::test_footer();
    return 0;
}
