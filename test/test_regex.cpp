/**
 * @file test_regex.cpp
 * @brief Tests for std_module.regex
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.regex;
import std_module.test_framework;

int main() {
    test::test_header("std_module.regex");

    test::section("Testing symbol accessibility");

    // Test basic regex
    std::regex pattern("hello");
    test::assert_true(std::regex_match("hello", pattern), "regex_match");

    // Test regex_search
    std::string text = "The answer is 42";
    std::regex number_pattern(R"(\d+)");
    std::smatch match;
    test::assert_true(std::regex_search(text, match, number_pattern), "regex_search");

    // Test regex_replace
    std::string result = std::regex_replace("hello world", std::regex("world"), "universe");
    test::success("regex_replace");

    // Test regex_iterator
    std::sregex_iterator iter(text.begin(), text.end(), number_pattern);
    std::sregex_iterator end;
    test::assert_true(iter != end, "regex_iterator");

    // Test regex_token_iterator
    std::string csv = "one,two,three";
    std::regex comma(",");
    std::sregex_token_iterator tok_iter(csv.begin(), csv.end(), comma, -1);
    std::sregex_token_iterator tok_end;
    test::assert_true(tok_iter != tok_end, "regex_token_iterator");

    // Test match_results
    test::assert_true(match.ready(), "match_results::ready");
    test::assert_true(!match.empty(), "match_results::empty");
    test::assert_true(match.size() > 0, "match_results::size");

    // Test sub_match
    const std::ssub_match& sm = match[0];
    test::assert_true(sm.matched, "sub_match::matched");

    // Test regex_error
    try {
        std::regex invalid("[invalid");
        test::assert_true(false, "should have thrown");
    } catch (const std::regex_error& e) {
        test::success("regex_error");
    }

    // Test wide character support
    std::wregex wpattern(LR"(\d+)");
    test::success("wregex");

    std::wsmatch wmatch;
    test::success("wsmatch");

    // Test C-string support
    std::cmatch cmatch;
    test::success("cmatch");

    // Test syntax flags
    std::regex ecma(R"(\d+)", std::regex_constants::ECMAScript);
    test::success("ECMAScript syntax");

    std::regex icase("HELLO", std::regex_constants::icase);
    test::assert_true(std::regex_match("hello", icase), "icase flag");

    test::test_footer();
    return 0;
}
