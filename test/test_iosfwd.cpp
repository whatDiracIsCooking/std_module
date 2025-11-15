/**
 * @file test_iosfwd.cpp
 * @brief Tests for std_module.iosfwd
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that forward-declared types are accessible through the module.
 */

import std_module.iosfwd;
import std_module.test_framework;

int main() {
    test::test_header("std_module.iosfwd");

    test::section("Testing forward-declared types accessibility");

    // Test that stream types can be forward-declared (pointer declarations)
    std::istream* is_ptr = nullptr;
    std::ostream* os_ptr = nullptr;
    std::iostream* ios_ptr = nullptr;
    test::success("basic stream types (istream, ostream, iostream)");

    // Test file stream types
    std::ifstream* ifs_ptr = nullptr;
    std::ofstream* ofs_ptr = nullptr;
    std::fstream* fs_ptr = nullptr;
    test::success("file stream types (ifstream, ofstream, fstream)");

    // Test string stream types
    std::istringstream* iss_ptr = nullptr;
    std::ostringstream* oss_ptr = nullptr;
    std::stringstream* ss_ptr = nullptr;
    test::success("string stream types (istringstream, ostringstream, stringstream)");

    // Test wide character stream types
    std::wistream* wis_ptr = nullptr;
    std::wostream* wos_ptr = nullptr;
    std::wiostream* wios_ptr = nullptr;
    test::success("wide stream types (wistream, wostream, wiostream)");

    // Test buffer types
    std::streambuf* sb_ptr = nullptr;
    std::filebuf* fb_ptr = nullptr;
    std::stringbuf* strbuf_ptr = nullptr;
    test::success("buffer types (streambuf, filebuf, stringbuf)");

    // Test C++20 sync types
    std::syncbuf* syncb_ptr = nullptr;
    std::osyncstream* osync_ptr = nullptr;
    test::success("sync types (syncbuf, osyncstream)");

    // Test position types
    std::streampos pos1;
    std::wstreampos pos2;
    std::u8streampos pos3;
    std::u16streampos pos4;
    std::u32streampos pos5;
    test::success("position types (streampos, wstreampos, etc.)");

    // Test char_traits
    using traits_char = std::char_traits<char>;
    using traits_wchar = std::char_traits<wchar_t>;
    using traits_char8 = std::char_traits<char8_t>;
    using traits_char16 = std::char_traits<char16_t>;
    using traits_char32 = std::char_traits<char32_t>;
    test::success("char_traits specializations");

    // Suppress unused variable warnings
    (void)is_ptr; (void)os_ptr; (void)ios_ptr;
    (void)ifs_ptr; (void)ofs_ptr; (void)fs_ptr;
    (void)iss_ptr; (void)oss_ptr; (void)ss_ptr;
    (void)wis_ptr; (void)wos_ptr; (void)wios_ptr;
    (void)sb_ptr; (void)fb_ptr; (void)strbuf_ptr;
    (void)syncb_ptr; (void)osync_ptr;
    (void)pos1; (void)pos2; (void)pos3; (void)pos4; (void)pos5;

    test::test_footer();
    return 0;
}
