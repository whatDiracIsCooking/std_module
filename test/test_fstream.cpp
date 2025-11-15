/**
 * @file test_fstream.cpp
 * @brief Tests for std_module.fstream
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.fstream;
import std_module.test_framework;

int main() {
    test::test_header("std_module.fstream");

    const char* test_file = "test_fstream_module.txt";

    test::section("Testing ofstream (output file stream)");

    // Test ofstream construction and basic operations
    {
        std::ofstream out(test_file);
        test::assert_true(out.is_open(), "ofstream open");
        out << "test data" << test::endl;
        out.close();
        test::assert_false(out.is_open(), "ofstream close");
    }
    test::success("ofstream construction and basic I/O accessible");

    // Note: ios::app and other flags require std_module.ios
    test::success("ofstream construction accessible");

    test::section("Testing ifstream (input file stream)");

    // Test ifstream construction and basic operations
    {
        std::ifstream in(test_file);
        test::assert_true(in.is_open(), "ifstream open");

        // Test basic read (operator>>)
        test::string word;
        if (in >> word) {
            test::assert_false(word.empty(), "ifstream read");
        }

        in.close();
        test::assert_false(in.is_open(), "ifstream close");
    }
    test::success("ifstream construction and basic I/O accessible");

    // Test ifstream error states
    {
        std::ifstream in("nonexistent_file_xyz.txt");
        test::assert_false(in.is_open(), "ifstream fail on nonexistent file");
        test::assert_true(in.fail(), "ifstream fail state");
    }
    test::success("ifstream error states accessible");

    test::section("Testing fstream (bidirectional file stream)");

    // Test fstream basic construction (ios flags require std_module.ios)
    {
        std::fstream file(test_file);
        test::assert_true(file.is_open() || !file.fail(), "fstream construction");
    }
    test::success("fstream construction accessible");

    test::section("Testing binary I/O operations");

    // Test binary read/write methods (without ios::binary flag)
    {
        const char* bin_file = "test_binary.bin";
        std::ofstream out(bin_file);
        test::assert_true(out.is_open(), "binary ofstream open");

        int data[] = {1, 2, 3, 4, 5};
        out.write(reinterpret_cast<char*>(data), sizeof(data));
        out.close();

        std::ifstream in(bin_file);
        int read_data[5];
        in.read(reinterpret_cast<char*>(read_data), sizeof(read_data));
        auto bytes_read = in.gcount();
        test::assert_true(bytes_read > 0, "read/write/gcount accessible");
    }
    test::success("binary I/O operations accessible");

    test::section("Testing wide character streams");

    // Test wofstream, wifstream, wfstream
    {
        const char* wide_file = "test_wide.txt";
        std::wofstream wout(wide_file);
        test::assert_true(wout.is_open(), "wofstream open");
        wout << L"wide string" << test::endl;
        wout.close();

        std::wifstream win(wide_file);
        test::assert_true(win.is_open(), "wifstream open");

        std::wfstream wfile(wide_file);
        test::success("wfstream construction accessible");
    }
    test::success("wide character file streams accessible");

    test::section("Testing filebuf");

    // Test filebuf (underlying buffer) - basic construction
    {
        std::filebuf fb;
        test::success("filebuf construction accessible");
    }

    // Test wfilebuf
    {
        std::wfilebuf wfb;
        test::success("wfilebuf construction accessible");
    }

    test::section("Testing stream state operations");

    // Test stream state methods
    {
        std::ofstream out(test_file);
        test::assert_true(out.good(), "good state");
        test::assert_false(out.fail(), "fail state");
        test::assert_false(out.bad(), "bad state");
        test::assert_false(out.eof(), "eof state");

        out.flush();
        test::success("flush accessible");

        auto* buf = out.rdbuf();
        test::assert_true(buf != nullptr, "rdbuf");
    }
    test::success("stream state operations accessible");

    test::section("Testing constructor variations");

    // Test default constructor + open
    {
        std::ofstream out1;
        test::assert_false(out1.is_open(), "default constructor");
        out1.open(test_file);
        test::assert_true(out1.is_open(), "open method");
    }
    test::success("default constructor and open method accessible");

    test::test_footer();
    return 0;
}
