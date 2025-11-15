/**
 * @file test_syncstream.cpp
 * @brief Tests for std_module.syncstream
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.syncstream;
import std_module.test_framework;

#include <sstream>

int main() {
    test::test_header("std_module.syncstream");

    test::section("Testing symbol accessibility");

    // Basic osyncstream
    std::ostringstream oss;
    std::osyncstream sync_out(oss);
    sync_out << "test";
    test::success("osyncstream construction and operator<<");

    // emit
    sync_out.emit();
    test::assert_true(oss.str().size() > 0, "emit");

    // rdbuf
    std::syncbuf* buf = sync_out.rdbuf();
    test::assert_true(buf != nullptr, "rdbuf");
    test::assert_true(buf->get_wrapped() == oss.rdbuf(), "get_wrapped");

    // emit_on_sync
    buf->set_emit_on_sync(true);
    buf->set_emit_on_sync(false);
    test::success("set_emit_on_sync");

    // Wide osyncstream
    std::wostringstream woss;
    std::wosyncstream wsync(woss);
    wsync << L"wide";
    test::success("wosyncstream");

    // syncbuf directly
    std::ostringstream oss2;
    std::syncbuf sbuf(oss2.rdbuf());
    sbuf.sputn("direct", 6);
    sbuf.emit();
    test::assert_true(oss2.str().size() > 0, "syncbuf");

    test::test_footer();
    return 0;
}
