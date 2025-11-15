/**
 * @file test_format.cpp
 * @brief Tests for std_module.format
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.format;
import std_module.test_framework;

// Custom type for testing custom formatter
struct Point {
    int x, y;
};

// Custom formatter for Point (tests formatter specialization is accessible)
template<>
struct std::formatter<Point> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Point& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", p.x, p.y);
    }
};

int main() {
    test::test_header("std_module.format");

    test::section("Testing basic format functions");

    // Test format (just check it's callable and returns something)
    auto result = std::format("Value: {}", 42);
    test::assert_false(result.empty(), "format");
    test::success("format accessible");

    // Test format_to (check it's callable)
    test::string buffer;
    std::format_to(std::back_inserter(buffer), "{}", 100);
    test::assert_false(buffer.empty(), "format_to");

    // Test format_to_n (check it's callable)
    char cbuf[20];
    auto fmt_result = std::format_to_n(cbuf, 10, "{}", 123);
    test::assert_true(fmt_result.size > 0, "format_to_n");

    // Test formatted_size (check it's callable)
    auto size = std::formatted_size("{}", 42);
    test::assert_true(size > 0, "formatted_size");

    test::section("Testing vformat functions");

    // Test vformat and make_format_args (check they're callable)
    test::string str = "test";
    int val = 10;
    auto args = std::make_format_args(str, val);
    auto vresult = std::vformat("{} {}", args);
    test::assert_false(vresult.empty(), "vformat/make_format_args");

    // Test vformat_to (check it's callable)
    buffer.clear();
    std::vformat_to(std::back_inserter(buffer), "{}", args);
    test::success("vformat_to accessible");

    test::section("Testing format_string types");

    // Test format_string wrapper type
    std::format_string<int> fmt = "Value: {}";
    auto fs_result = std::format(fmt, 42);
    test::assert_false(fs_result.empty(), "format_string");

    // Test wformat_string
    std::wformat_string<int> wfmt = L"Wide: {}";
    auto wresult = std::format(wfmt, 99);
    test::assert_false(wresult.empty(), "wformat_string");

    test::section("Testing wide character support");

    // Test wide format
    auto wstr = std::format(L"Wide: {}", 42);
    test::assert_false(wstr.empty(), "wide format");

    // Test make_wformat_args
    std::wstring wval = L"test";
    auto wargs = std::make_wformat_args(wval);
    auto wvresult = std::vformat(L"{}", wargs);
    test::assert_false(wvresult.empty(), "make_wformat_args");

    test::section("Testing format_error exception");

    // Test that format_error type is accessible
    try {
        int value = 42;
        auto args2 = std::make_format_args(value);
        // Try format with mismatched args (may throw format_error)
        [[maybe_unused]] auto bad = std::vformat("{} {}", args2);
    } catch (const std::format_error&) {
        test::success("format_error type accessible");
    } catch (...) {
        // Some implementations may throw different exceptions
        test::success("format_error type accessible");
    }

    test::section("Testing custom formatters");

    // Test that custom formatter specialization works
    Point p{10, 20};
    auto presult = std::format("{}", p);
    test::assert_false(presult.empty(), "custom formatter");

    test::section("Testing format context types");

    // Just check types are accessible (not testing behavior)
    [[maybe_unused]] std::format_parse_context* parse_ctx_ptr = nullptr;
    [[maybe_unused]] std::format_context* fmt_ctx_ptr = nullptr;
    test::success("format context types accessible");

    test::test_footer();
    return 0;
}
