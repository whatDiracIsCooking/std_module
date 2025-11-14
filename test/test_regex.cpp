/**
 * @file test_regex.cpp
 * @brief Comprehensive tests for std_module.regex
 */

import std_module.regex;
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

// Test basic regex_match
void test_regex_match() {
    std::cout << "\n=== Testing regex_match ===\n";

    // Basic match
    std::string text = "hello";
    std::regex pattern("hello");
    bool matched = std::regex_match(text, pattern);
    assert(matched);
    std::cout << "  ✓ Basic match: \"" << text << "\" matches \"hello\"\n";

    // Non-match
    matched = std::regex_match("world", pattern);
    assert(!matched);
    std::cout << "  ✓ Non-match: \"world\" does not match \"hello\"\n";

    // Pattern with groups
    std::string email = "user@example.com";
    std::regex email_pattern(R"((\w+)@(\w+)\.(\w+))");
    std::smatch matches;
    matched = std::regex_match(email, matches, email_pattern);
    assert(matched);
    assert(matches.size() == 4); // Full match + 3 groups
    assert(matches[1].str() == "user");
    assert(matches[2].str() == "example");
    assert(matches[3].str() == "com");
    std::cout << "  ✓ Email pattern: " << matches[0].str()
              << " (user=" << matches[1].str() << ", domain=" << matches[2].str()
              << ", tld=" << matches[3].str() << ")\n";

    // Case-insensitive match
    std::regex case_insensitive("HELLO", std::regex_constants::icase);
    matched = std::regex_match("hello", case_insensitive);
    assert(matched);
    std::cout << "  ✓ Case-insensitive match works\n";
}

// Test regex_search
void test_regex_search() {
    std::cout << "\n=== Testing regex_search ===\n";

    // Find pattern in larger text
    std::string text = "The answer is 42 and the question is unknown";
    std::regex number_pattern(R"(\d+)");
    std::smatch match;
    bool found = std::regex_search(text, match, number_pattern);
    assert(found);
    assert(match[0].str() == "42");
    std::cout << "  ✓ Found number: " << match[0].str() << " at position " << match.position() << "\n";

    // Search for word boundaries
    std::regex word_pattern(R"(\bis\b)");
    found = std::regex_search(text, match, word_pattern);
    assert(found);
    assert(match[0].str() == "is");
    std::cout << "  ✓ Found word 'is' with word boundaries\n";

    // Multiple searches
    std::string multi_text = "abc 123 def 456 ghi";
    std::regex digit_pattern(R"(\d+)");
    std::string::const_iterator search_start(multi_text.cbegin());
    int count = 0;
    while (std::regex_search(search_start, multi_text.cend(), match, digit_pattern)) {
        count++;
        search_start = match.suffix().first;
    }
    assert(count == 2);
    std::cout << "  ✓ Found " << count << " number sequences in text\n";
}

// Test regex_replace
void test_regex_replace() {
    std::cout << "\n=== Testing regex_replace ===\n";

    // Simple replacement
    std::string text = "hello world";
    std::regex pattern("world");
    std::string result = std::regex_replace(text, pattern, "universe");
    assert(result == "hello universe");
    std::cout << "  ✓ Simple replace: \"" << result << "\"\n";

    // Replace with capture groups
    std::string date = "2024-01-15";
    std::regex date_pattern(R"((\d{4})-(\d{2})-(\d{2}))");
    result = std::regex_replace(date, date_pattern, "$2/$3/$1");
    assert(result == "01/15/2024");
    std::cout << "  ✓ Date format conversion: " << date << " → " << result << "\n";

    // Replace all occurrences
    text = "foo bar foo baz foo";
    pattern = std::regex("foo");
    result = std::regex_replace(text, pattern, "qux");
    assert(result == "qux bar qux baz qux");
    std::cout << "  ✓ Replace all: \"" << result << "\"\n";

    // Replace with format_no_copy flag (only matched parts)
    text = "abc123def456ghi";
    pattern = std::regex(R"(\d+)");
    result = std::regex_replace(text, pattern, "[$&]", std::regex_constants::format_no_copy);
    assert(result == "[123][456]");
    std::cout << "  ✓ Format no copy: \"" << result << "\"\n";
}

// Test regex iterators
void test_regex_iterator() {
    std::cout << "\n=== Testing regex_iterator ===\n";

    std::string text = "The numbers are 42, 17, and 99";
    std::regex pattern(R"(\d+)");

    // Iterate through all matches
    std::vector<std::string> numbers;
    std::sregex_iterator iter(text.begin(), text.end(), pattern);
    std::sregex_iterator end;

    for (; iter != end; ++iter) {
        numbers.push_back(iter->str());
    }

    assert(numbers.size() == 3);
    assert(numbers[0] == "42");
    assert(numbers[1] == "17");
    assert(numbers[2] == "99");

    std::cout << "  ✓ Found " << numbers.size() << " numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Iterator with wide strings
    std::wstring wtext = L"hello 123 world 456";
    std::wregex wpattern(LR"(\d+)");
    std::wsregex_iterator witer(wtext.begin(), wtext.end(), wpattern);
    std::wsregex_iterator wend;

    int wcount = 0;
    for (; witer != wend; ++witer) {
        wcount++;
    }
    assert(wcount == 2);
    std::cout << "  ✓ Wide string iterator found " << wcount << " matches\n";
}

// Test regex_token_iterator
void test_regex_token_iterator() {
    std::cout << "\n=== Testing regex_token_iterator ===\n";

    // Tokenize by delimiter
    std::string text = "one,two,three,four";
    std::regex pattern(",");

    std::vector<std::string> tokens;
    std::sregex_token_iterator iter(text.begin(), text.end(), pattern, -1); // -1 = non-matching parts
    std::sregex_token_iterator end;

    for (; iter != end; ++iter) {
        tokens.push_back(iter->str());
    }

    assert(tokens.size() == 4);
    assert(tokens[0] == "one");
    assert(tokens[1] == "two");
    assert(tokens[2] == "three");
    assert(tokens[3] == "four");

    std::cout << "  ✓ Tokenized: ";
    for (const auto& token : tokens) {
        std::cout << "\"" << token << "\" ";
    }
    std::cout << "\n";

    // Extract only matching parts (submatch 0)
    text = "The numbers are 42, 17, and 99";
    pattern = std::regex(R"(\d+)");

    std::vector<std::string> numbers;
    std::sregex_token_iterator num_iter(text.begin(), text.end(), pattern, 0); // 0 = matching parts

    for (; num_iter != end; ++num_iter) {
        numbers.push_back(num_iter->str());
    }

    assert(numbers.size() == 3);
    std::cout << "  ✓ Extracted numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

// Test match_results and sub_match
void test_match_results() {
    std::cout << "\n=== Testing match_results ===\n";

    std::string text = "Name: John Doe, Age: 30";
    std::regex pattern(R"(Name: (\w+) (\w+), Age: (\d+))");
    std::smatch matches;

    bool found = std::regex_search(text, matches, pattern);
    assert(found);

    // Test match_results properties
    assert(matches.size() == 4); // Full match + 3 groups
    assert(!matches.empty());
    assert(matches.ready());

    std::cout << "  ✓ Full match: \"" << matches[0].str() << "\"\n";
    std::cout << "  ✓ First name: \"" << matches[1].str() << "\"\n";
    std::cout << "  ✓ Last name: \"" << matches[2].str() << "\"\n";
    std::cout << "  ✓ Age: \"" << matches[3].str() << "\"\n";

    // Test prefix and suffix
    assert(matches.prefix().str() == "");
    assert(matches.suffix().str() == "");
    std::cout << "  ✓ Prefix and suffix work\n";

    // Test sub_match properties
    const std::ssub_match& first_name = matches[1];
    assert(first_name.matched);
    assert(first_name.length() == 4);
    std::cout << "  ✓ Sub-match length: " << first_name.length() << "\n";
}

// Test regex syntax options
void test_regex_syntax() {
    std::cout << "\n=== Testing regex syntax options ===\n";

    // ECMAScript (default)
    std::regex ecma(R"(\d+)", std::regex_constants::ECMAScript);
    assert(std::regex_match("123", ecma));
    std::cout << "  ✓ ECMAScript syntax works\n";

    // Extended (POSIX)
    std::regex extended(R"([0-9]+)", std::regex_constants::extended);
    assert(std::regex_match("456", extended));
    std::cout << "  ✓ Extended syntax works\n";

    // Basic (POSIX)
    std::regex basic("[0-9][0-9]*", std::regex_constants::basic);
    assert(std::regex_match("789", basic));
    std::cout << "  ✓ Basic syntax works\n";

    // Case-insensitive flag
    std::regex icase("hello", std::regex_constants::icase);
    assert(std::regex_match("HELLO", icase));
    assert(std::regex_match("HeLLo", icase));
    std::cout << "  ✓ Case-insensitive flag works\n";

    // Optimize flag (just verify it compiles)
    std::regex optimized(R"(\d+)", std::regex_constants::optimize);
    assert(std::regex_match("999", optimized));
    std::cout << "  ✓ Optimize flag accepted\n";
}

// Test regex_error exception
void test_regex_error() {
    std::cout << "\n=== Testing regex_error ===\n";

    // Invalid regex pattern should throw
    try {
        std::regex invalid("[invalid");
        assert(false); // Should not reach here
    } catch (const std::regex_error& e) {
        std::cout << "  ✓ Caught regex_error: " << e.what() << "\n";
        std::cout << "  ✓ Error code: " << static_cast<int>(e.code()) << "\n";
    }

    // Another invalid pattern
    try {
        std::regex invalid("(unclosed group");
        assert(false);
    } catch (const std::regex_error& e) {
        std::cout << "  ✓ Caught unclosed group error\n";
    }
}

// Test wide character support
void test_wide_char() {
    std::cout << "\n=== Testing wide character support ===\n";

    // wregex and wsmatch
    std::wstring text = L"Hello 世界 123";
    std::wregex pattern(LR"(\d+)");
    std::wsmatch matches;

    bool found = std::regex_search(text, matches, pattern);
    assert(found);
    assert(matches[0].str() == L"123");
    std::cout << "  ✓ Wide character regex works\n";

    // Wide character replacement
    std::wstring result = std::regex_replace(text, pattern, L"[NUM]");
    assert(result == L"Hello 世界 [NUM]");
    std::cout << "  ✓ Wide character replacement works\n";
}

// Test C-string support
void test_cstring() {
    std::cout << "\n=== Testing C-string support ===\n";

    const char* text = "test 123 string";
    std::regex pattern(R"(\d+)");
    std::cmatch matches;

    bool found = std::regex_search(text, matches, pattern);
    assert(found);
    assert(matches[0].str() == "123");
    std::cout << "  ✓ C-string regex_search works\n";

    // Match entire C-string
    const char* exact = "12345";
    found = std::regex_match(exact, matches, std::regex(R"(\d+)"));
    assert(found);
    std::cout << "  ✓ C-string regex_match works\n";
}

// Test complex patterns
void test_complex_patterns() {
    std::cout << "\n=== Testing complex patterns ===\n";

    // URL pattern
    std::string url = "https://www.example.com/path?query=value";
    std::regex url_pattern(R"((https?)://([^/]+)(/[^?]*)?\??(.*))");
    std::smatch matches;

    bool found = std::regex_match(url, matches, url_pattern);
    assert(found);
    assert(matches[1].str() == "https");
    assert(matches[2].str() == "www.example.com");
    assert(matches[3].str() == "/path");
    assert(matches[4].str() == "query=value");
    std::cout << "  ✓ URL parsing: protocol=" << matches[1].str()
              << ", host=" << matches[2].str() << "\n";

    // Phone number pattern
    std::string phone = "(123) 456-7890";
    std::regex phone_pattern(R"(\((\d{3})\)\s*(\d{3})-(\d{4}))");
    found = std::regex_match(phone, matches, phone_pattern);
    assert(found);
    std::string normalized = matches[1].str() + matches[2].str() + matches[3].str();
    assert(normalized == "1234567890");
    std::cout << "  ✓ Phone number normalized: " << normalized << "\n";

    // IPv4 address pattern
    std::string ip = "192.168.1.1";
    std::regex ip_pattern(R"((\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3}))");
    found = std::regex_match(ip, matches, ip_pattern);
    assert(found);
    std::cout << "  ✓ IPv4 address parsed: " << ip << "\n";
}

int main() {
    std::cout << "Testing std_module.regex\n";
    std::cout << "========================\n";

    try {
        test_regex_match();
        test_regex_search();
        test_regex_replace();
        test_regex_iterator();
        test_regex_token_iterator();
        test_match_results();
        test_regex_syntax();
        test_regex_error();
        test_wide_char();
        test_cstring();
        test_complex_patterns();

        std::cout << "\n✅ All regex tests passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
