/**
 * @file test_syncstream.cpp
 * @brief Comprehensive test for std_module.syncstream (C++20)
 */

import std_module.syncstream;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <sstream>   // FIXME: Should be import std_module.sstream when available
#include <thread>    // FIXME: Should be import std_module.thread when available
#include <vector>    // FIXME: Should be import std_module.vector when available
#include <string>    // FIXME: Should be import std_module.string when available

void test_basic_osyncstream() {
    std::cout << "Testing basic osyncstream...\n";

    std::ostringstream oss;

    // Test basic synchronized output
    {
        std::osyncstream sync_out(oss);
        sync_out << "Hello, ";
        sync_out << "World!";
        // Output is buffered until destruction or explicit emit
    }
    // After destruction, output should be emitted

    assert(oss.str() == "Hello, World!");
    std::cout << "  ✓ Basic osyncstream output: " << oss.str() << "\n";
}

void test_syncstream_emit() {
    std::cout << "\nTesting emit...\n";

    std::ostringstream oss;
    std::osyncstream sync_out(oss);

    sync_out << "First part";
    assert(oss.str().empty());  // Not yet emitted
    std::cout << "  ✓ Output buffered before emit\n";

    sync_out.emit();  // Explicitly emit
    assert(oss.str() == "First part");
    std::cout << "  ✓ Output emitted after emit(): " << oss.str() << "\n";

    sync_out << " Second part";
    sync_out.emit();
    assert(oss.str() == "First part Second part");
    std::cout << "  ✓ Multiple emits work: " << oss.str() << "\n";
}

void test_rdbuf() {
    std::cout << "\nTesting rdbuf...\n";

    std::ostringstream oss;
    std::osyncstream sync_out(oss);

    // Test that we can access the syncbuf
    std::syncbuf* buf = sync_out.rdbuf();
    assert(buf != nullptr);
    std::cout << "  ✓ rdbuf() returns non-null syncbuf\n";

    // Test that the syncbuf wraps the correct stream
    assert(buf->get_wrapped() == oss.rdbuf());
    std::cout << "  ✓ syncbuf wraps correct streambuf\n";
}

void test_wide_syncstream() {
    std::cout << "\nTesting wide character syncstream...\n";

    std::wostringstream woss;

    {
        std::wosyncstream sync_out(woss);
        sync_out << L"Wide ";
        sync_out << L"string!";
    }

    assert(woss.str() == L"Wide string!");
    std::wcout << L"  ✓ Wide osyncstream output: " << woss.str() << L"\n";
    std::cout << "  ✓ Wide character support verified\n";
}

void test_emit_on_sync() {
    std::cout << "\nTesting emit_on_sync...\n";

    std::ostringstream oss;
    std::osyncstream sync_out(oss);

    // By default, emit_on_sync is false
    sync_out << "Test" << std::flush;
    // flush doesn't emit by default

    // Enable emit on sync
    sync_out.rdbuf()->set_emit_on_sync(true);
    sync_out << " message" << std::flush;
    assert(oss.str() == "Test message");
    std::cout << "  ✓ emit_on_sync(true) causes flush to emit: " << oss.str() << "\n";

    // Disable emit on sync
    sync_out.rdbuf()->set_emit_on_sync(false);
    sync_out << " more";
    sync_out << std::flush;  // Won't emit
    assert(oss.str() == "Test message");  // Still the old value
    std::cout << "  ✓ emit_on_sync(false) prevents flush from emitting\n";

    sync_out.emit();  // Manually emit
    assert(oss.str() == "Test message more");
    std::cout << "  ✓ Manual emit works: " << oss.str() << "\n";
}

void test_multiple_syncstreams() {
    std::cout << "\nTesting multiple syncstreams to same stream...\n";

    std::ostringstream oss;

    {
        std::osyncstream sync1(oss);
        std::osyncstream sync2(oss);

        sync1 << "From sync1";
        sync2 << "From sync2";

        // Emit in order
        sync1.emit();
        sync2.emit();
    }

    // Both outputs should be present
    std::string result = oss.str();
    assert(result.find("From sync1") != std::string::npos);
    assert(result.find("From sync2") != std::string::npos);
    std::cout << "  ✓ Multiple syncstreams: " << result << "\n";
}

void test_thread_safety() {
    std::cout << "\nTesting thread safety...\n";

    std::ostringstream shared_stream;
    std::vector<std::thread> threads;

    // Launch multiple threads that write to the same stream
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&shared_stream, i]() {
            std::osyncstream sync_out(shared_stream);
            sync_out << "Thread " << i << " output\n";
            // Output is emitted atomically on destruction
        });
    }

    // Wait for all threads
    for (auto& t : threads) {
        t.join();
    }

    // Verify all threads wrote their output
    std::string result = shared_stream.str();
    for (int i = 0; i < 5; ++i) {
        std::string expected = "Thread " + std::to_string(i) + " output\n";
        assert(result.find(expected) != std::string::npos);
    }

    std::cout << "  ✓ All 5 threads wrote output successfully\n";
    std::cout << "  ✓ Thread safety verified (no interleaved output)\n";
    std::cout << "\nThread outputs:\n" << result;
}

void test_move_semantics() {
    std::cout << "\nTesting move semantics...\n";

    std::ostringstream oss;

    {
        std::osyncstream sync1(oss);
        sync1 << "Test ";

        // Move construct
        std::osyncstream sync2(std::move(sync1));
        sync2 << "message";

        // sync2 will emit on destruction
    }

    assert(oss.str() == "Test message");
    std::cout << "  ✓ Move constructor works: " << oss.str() << "\n";

    // Test move assignment
    oss.str("");  // Clear
    {
        std::osyncstream sync1(oss);
        std::osyncstream sync2(oss);

        sync1 << "First";
        sync2 = std::move(sync1);  // Move assign
        sync2 << " Second";
    }

    assert(oss.str() == "First Second");
    std::cout << "  ✓ Move assignment works: " << oss.str() << "\n";
}

void test_syncbuf_directly() {
    std::cout << "\nTesting syncbuf directly...\n";

    std::ostringstream oss;
    std::syncbuf sbuf(oss.rdbuf());

    sbuf.sputn("Direct ", 7);
    sbuf.sputn("buffer", 6);

    assert(oss.str().empty());  // Not yet emitted
    std::cout << "  ✓ syncbuf buffers output\n";

    sbuf.emit();
    assert(oss.str() == "Direct buffer");
    std::cout << "  ✓ syncbuf.emit() works: " << oss.str() << "\n";
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "std_module.syncstream Comprehensive Tests\n";
    std::cout << "===========================================\n\n";

    try {
        test_basic_osyncstream();
        test_syncstream_emit();
        test_rdbuf();
        test_wide_syncstream();
        test_emit_on_sync();
        test_multiple_syncstreams();
        test_thread_safety();
        test_move_semantics();
        test_syncbuf_directly();

        std::cout << "\n===========================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "===========================================\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
