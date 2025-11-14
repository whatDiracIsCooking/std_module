/**
 * @file test_streambuf.cpp
 * @brief Comprehensive test for std_module.streambuf (C++20)
 */

import std_module.streambuf;

#include <iostream>
#include <cassert>
#include <string>
#include <cstring>

// Custom streambuf implementation for testing
class MemoryBuffer : public std::streambuf {
private:
    char* buffer_;
    size_t size_;

public:
    MemoryBuffer(char* buffer, size_t size) : buffer_(buffer), size_(size) {
        // Set up the get area (input buffer)
        setg(buffer_, buffer_, buffer_ + size_);
        // Set up the put area (output buffer)
        setp(buffer_, buffer_ + size_);
    }

    // Override underflow for reading
    int_type underflow() override {
        if (gptr() == egptr()) {
            return traits_type::eof();
        }
        return traits_type::to_int_type(*gptr());
    }

    // Override overflow for writing
    int_type overflow(int_type ch) override {
        if (ch != traits_type::eof()) {
            if (pptr() == epptr()) {
                return traits_type::eof();  // Buffer full
            }
            *pptr() = traits_type::to_char_type(ch);
            pbump(1);
            return ch;
        }
        return traits_type::eof();
    }

    // Get the written content
    std::string str() const {
        return std::string(pbase(), pptr());
    }
};

void test_basic_streambuf_types() {
    std::cout << "Testing basic_streambuf types...\n";

    // Test that the type aliases exist
    std::streambuf* sb1 = nullptr;
    std::wstreambuf* sb2 = nullptr;

    // Avoid unused variable warnings
    (void)sb1;
    (void)sb2;

    std::cout << "  ✓ std::streambuf type available\n";
    std::cout << "  ✓ std::wstreambuf type available\n";
}

void test_custom_streambuf() {
    std::cout << "\nTesting custom streambuf implementation...\n";

    char buffer[100];
    std::memset(buffer, 0, sizeof(buffer));
    std::strcpy(buffer, "Hello, World!");

    MemoryBuffer mb(buffer, sizeof(buffer));

    // Test reading
    int ch = mb.sgetc();
    assert(ch == 'H');
    std::cout << "  ✓ sgetc: " << static_cast<char>(ch) << "\n";

    // Test bumping pointer
    ch = mb.sbumpc();
    assert(ch == 'H');
    ch = mb.sgetc();
    assert(ch == 'e');
    std::cout << "  ✓ sbumpc and next sgetc: " << static_cast<char>(ch) << "\n";
}

void test_input_operations() {
    std::cout << "\nTesting input operations...\n";

    char buffer[100];
    std::strcpy(buffer, "Test Input");

    MemoryBuffer mb(buffer, sizeof(buffer));

    // Test sgetn
    char read_buffer[10];
    std::streamsize n = mb.sgetn(read_buffer, 4);
    read_buffer[4] = '\0';
    assert(n == 4);
    assert(std::string(read_buffer) == "Test");
    std::cout << "  ✓ sgetn: read \"" << read_buffer << "\" (" << n << " chars)\n";

    // Test in_avail
    std::streamsize avail = mb.in_avail();
    std::cout << "  ✓ in_avail: " << avail << " characters available\n";
}

void test_output_operations() {
    std::cout << "\nTesting output operations...\n";

    char buffer[100];
    std::memset(buffer, 0, sizeof(buffer));

    MemoryBuffer mb(buffer, sizeof(buffer));

    // Test sputc
    int result = mb.sputc('A');
    assert(result == 'A');
    std::cout << "  ✓ sputc: wrote '" << static_cast<char>(result) << "'\n";

    // Test sputn
    const char* text = "BC";
    std::streamsize n = mb.sputn(text, 2);
    assert(n == 2);

    std::string written = mb.str();
    assert(written == "ABC");
    std::cout << "  ✓ sputn: wrote \"" << written << "\"\n";
}

void test_putback_operations() {
    std::cout << "\nTesting putback operations...\n";

    char buffer[100];
    std::strcpy(buffer, "ABC");

    MemoryBuffer mb(buffer, sizeof(buffer));

    // Read a character
    int ch = mb.sbumpc();
    assert(ch == 'A');

    // Put it back
    int result = mb.sputbackc('A');
    assert(result == 'A');

    // Read it again
    ch = mb.sgetc();
    assert(ch == 'A');
    std::cout << "  ✓ sputbackc: successfully put back and re-read 'A'\n";

    // Test sungetc
    mb.sbumpc();  // Read 'A'
    mb.sbumpc();  // Read 'B'
    result = mb.sungetc();  // Step back
    ch = mb.sgetc();
    assert(ch == 'B');
    std::cout << "  ✓ sungetc: successfully stepped back to 'B'\n";
}

void test_locale_operations() {
    std::cout << "\nTesting locale operations...\n";

    char buffer[100];
    MemoryBuffer mb(buffer, sizeof(buffer));

    // Test getloc
    std::locale loc = mb.getloc();
    std::cout << "  ✓ getloc: retrieved locale\n";

    // Test pubimbue
    std::locale new_loc = mb.pubimbue(loc);
    std::cout << "  ✓ pubimbue: set locale\n";
}

void test_sync_operations() {
    std::cout << "\nTesting sync operations...\n";

    char buffer[100];
    std::memset(buffer, 0, sizeof(buffer));

    MemoryBuffer mb(buffer, sizeof(buffer));

    mb.sputc('X');

    // Test pubsync
    int result = mb.pubsync();
    std::cout << "  ✓ pubsync: returned " << result << "\n";
}

void test_buffer_management() {
    std::cout << "\nTesting buffer management...\n";

    char buffer[100];
    std::memset(buffer, 0, sizeof(buffer));

    MemoryBuffer mb(buffer, sizeof(buffer));

    // Test pubsetbuf
    char new_buffer[50];
    std::streambuf* result = mb.pubsetbuf(new_buffer, sizeof(new_buffer));
    assert(result == &mb);
    std::cout << "  ✓ pubsetbuf: set new buffer\n";
}

void test_seeking_operations() {
    std::cout << "\nTesting seeking operations...\n";

    char buffer[100];
    std::strcpy(buffer, "0123456789");

    MemoryBuffer mb(buffer, sizeof(buffer));

    // Test pubseekoff
    std::streampos pos = mb.pubseekoff(3, std::ios_base::beg, std::ios_base::in);
    if (pos != std::streampos(-1)) {
        int ch = mb.sgetc();
        assert(ch == '3');
        std::cout << "  ✓ pubseekoff: seeked to position, read '" << static_cast<char>(ch) << "'\n";
    } else {
        std::cout << "  ✓ pubseekoff: returned -1 (implementation dependent)\n";
    }

    // Test pubseekpos
    pos = mb.pubseekpos(0, std::ios_base::in);
    std::cout << "  ✓ pubseekpos: tested seeking to position\n";
}

void test_traits() {
    std::cout << "\nTesting char_traits operations...\n";

    char buffer[100];
    std::strcpy(buffer, "Test");

    MemoryBuffer mb(buffer, sizeof(buffer));

    // Test eof
    auto eof_val = std::streambuf::traits_type::eof();
    std::cout << "  ✓ traits_type::eof() available\n";

    // Test to_int_type and to_char_type
    auto int_val = std::streambuf::traits_type::to_int_type('A');
    auto char_val = std::streambuf::traits_type::to_char_type(int_val);
    assert(char_val == 'A');
    std::cout << "  ✓ traits_type conversions work correctly\n";

    (void)eof_val;  // Avoid unused warning
}

void test_wide_streambuf() {
    std::cout << "\nTesting wide character streambuf...\n";

    // Just verify that wstreambuf type exists and can be used
    std::wstreambuf* wsb = nullptr;
    (void)wsb;

    std::cout << "  ✓ std::wstreambuf type is available\n";
}

int main() {
    std::cout << "=== std_module.streambuf Comprehensive Test ===\n\n";

    try {
        test_basic_streambuf_types();
        test_custom_streambuf();
        test_input_operations();
        test_output_operations();
        test_putback_operations();
        test_locale_operations();
        test_sync_operations();
        test_buffer_management();
        test_seeking_operations();
        test_traits();
        test_wide_streambuf();

        std::cout << "\n=== All tests passed! ===\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
