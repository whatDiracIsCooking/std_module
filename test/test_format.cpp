/**
 * @file test_format.cpp
 * @brief Minimal test for std_module.format
 */

import std_module.format;

#include <iostream>

int main()
{
    // Test basic format
    auto msg = std::format("Hello, {}!", "World");
    std::cout << msg << std::endl;

    // Test format with multiple arguments
    auto msg2 = std::format("The answer is {} and pi is approximately {:.2f}", 42, 3.14159);
    std::cout << msg2 << std::endl;

    // Test format with positional arguments
    auto msg3 = std::format("{1} comes before {0}", "second", "first");
    std::cout << msg3 << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
