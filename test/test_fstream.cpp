/**
 * @file test_fstream.cpp
 * @brief Tests for std_module.fstream
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.fstream;
import std_module.ios;
import std_module.string;
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

    // Test ofstream with modes
    {
        std::ofstream out(test_file, std::ios::app);
        test::assert_true(out.is_open(), "ofstream with append mode");
        out << "appended";
    }
    test::success("ofstream with open modes accessible");

    test::section("Testing ifstream (input file stream)");

    // Test ifstream construction and basic operations
    {
        std::ifstream in(test_file);
        test::assert_true(in.is_open(), "ifstream open");

        test::string line;
        if (std::getline(in, line)) {
            test::assert_false(line.empty(), "ifstream read");
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

    // Test fstream for read/write
    {
        // FIXME: C++20 module limitation - constructor with mode flags not visible
        // Use open() method instead of constructor with flags
        std::fstream file;
        file.open(test_file, std::ios::in | std::ios::out | std::ios::trunc);
        test::assert_true(file.is_open(), "fstream open");

        file << "bidirectional" << test::endl;
        file.seekg(0, std::ios::beg);

        test::string data;
        file >> data;
        test::assert_false(data.empty(), "fstream read/write");
    }
    test::success("fstream bidirectional I/O accessible");

    // Test file positioning
    {
        // FIXME: C++20 module limitation - use open() instead of constructor
        std::fstream file;
        file.open(test_file, std::ios::in | std::ios::out);
        file.seekg(0, std::ios::end);
        auto size = file.tellg();
        test::assert_true(size >= 0, "tellg/seekg");

        file.seekp(0, std::ios::beg);
        auto pos = file.tellp();
        test::assert_equal(pos, std::streampos(0), "tellp/seekp");
    }
    test::success("file positioning (tellg, seekg, tellp, seekp) accessible");

    test::section("Testing binary mode");

    // Test binary I/O
    {
        const char* bin_file = "test_binary.bin";
        std::ofstream out(bin_file, std::ios::binary);
        test::assert_true(out.is_open(), "binary ofstream open");

        int data[] = {1, 2, 3, 4, 5};
        out.write(reinterpret_cast<char*>(data), sizeof(data));
        out.close();

        std::ifstream in(bin_file, std::ios::binary);
        int read_data[5];
        in.read(reinterpret_cast<char*>(read_data), sizeof(read_data));
        auto bytes_read = in.gcount();
        test::assert_true(bytes_read > 0, "binary read/write and gcount");
    }
    test::success("binary mode I/O accessible");

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

        // FIXME: C++20 module limitation - use open() instead of constructor
        std::wfstream wfile;
        wfile.open(wide_file, std::ios::in | std::ios::out);
        test::assert_true(wfile.is_open(), "wfstream open");
    }
    test::success("wide character file streams accessible");

    test::section("Testing filebuf");

    // Test filebuf (underlying buffer)
    {
        std::filebuf fb;
        fb.open(test_file, std::ios::out);
        test::assert_true(fb.is_open(), "filebuf open");
        fb.sputn("filebuf test", 12);
        fb.close();
        test::assert_false(fb.is_open(), "filebuf close");
    }
    test::success("filebuf accessible");

    // Test wfilebuf
    {
        std::wfilebuf wfb;
        wfb.open(test_file, std::ios::out);
        test::assert_true(wfb.is_open(), "wfilebuf open");
        wfb.close();
    }
    test::success("wfilebuf accessible");

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
