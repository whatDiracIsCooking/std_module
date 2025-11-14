/**
 * @file test_system_error.cpp
 * @brief Comprehensive tests for std_module.system_error
 */

import std_module.system_error;

#include <iostream>
#include <cassert>
#include <string>

void test_error_category()
{
    std::cout << "\n[Testing Error Categories]\n";

    // Test generic_category
    const auto& gen_cat = std::generic_category();
    std::cout << "  ✓ generic_category name: " << gen_cat.name() << "\n";

    // Test system_category
    const auto& sys_cat = std::system_category();
    std::cout << "  ✓ system_category name: " << sys_cat.name() << "\n";

    // Test that categories are different
    assert(&gen_cat != &sys_cat);
    std::cout << "  ✓ Categories are distinct\n";

    // Test error message
    std::string msg = gen_cat.message(0);
    std::cout << "  ✓ Error message for code 0: " << msg << "\n";
}

void test_error_code()
{
    std::cout << "\n[Testing Error Code]\n";

    // Default construction
    std::error_code ec;
    assert(ec.value() == 0);
    assert(ec.category() == std::system_category());
    std::cout << "  ✓ Default error_code: value=" << ec.value() << "\n";

    // Construction with value and category
    std::error_code ec2(static_cast<int>(std::errc::invalid_argument),
                        std::generic_category());
    assert(ec2.value() != 0);
    std::cout << "  ✓ error_code with value: " << ec2.value()
              << ", message: " << ec2.message() << "\n";

    // Test bool conversion
    assert(!ec);  // Default is false
    assert(ec2);  // Non-zero is true
    std::cout << "  ✓ Bool conversion works\n";

    // Test assignment
    ec = ec2;
    assert(ec.value() == ec2.value());
    std::cout << "  ✓ Assignment works\n";

    // Test clear
    ec.clear();
    assert(ec.value() == 0);
    std::cout << "  ✓ Clear works\n";
}

void test_error_condition()
{
    std::cout << "\n[Testing Error Condition]\n";

    // Default construction
    std::error_condition econd;
    assert(econd.value() == 0);
    std::cout << "  ✓ Default error_condition: value=" << econd.value() << "\n";

    // Construction with value and category
    std::error_condition econd2(static_cast<int>(std::errc::permission_denied),
                                std::generic_category());
    assert(econd2.value() != 0);
    std::cout << "  ✓ error_condition with value: " << econd2.value()
              << ", message: " << econd2.message() << "\n";

    // Test bool conversion
    assert(!econd);
    assert(econd2);
    std::cout << "  ✓ Bool conversion works\n";
}

void test_errc_enum()
{
    std::cout << "\n[Testing errc Enumeration]\n";

    // Test various errc values
    auto ec1 = std::make_error_code(std::errc::invalid_argument);
    std::cout << "  ✓ errc::invalid_argument: " << ec1.message() << "\n";

    auto ec2 = std::make_error_code(std::errc::permission_denied);
    std::cout << "  ✓ errc::permission_denied: " << ec2.message() << "\n";

    auto ec3 = std::make_error_code(std::errc::no_such_file_or_directory);
    std::cout << "  ✓ errc::no_such_file_or_directory: " << ec3.message() << "\n";

    auto ec4 = std::make_error_code(std::errc::operation_not_permitted);
    std::cout << "  ✓ errc::operation_not_permitted: " << ec4.message() << "\n";

    // Test that different errc values are different
    assert(ec1 != ec2);
    std::cout << "  ✓ Different errc values are not equal\n";
}

void test_make_error_code()
{
    std::cout << "\n[Testing make_error_code]\n";

    auto ec = std::make_error_code(std::errc::invalid_argument);
    assert(ec.category() == std::generic_category());
    std::cout << "  ✓ make_error_code creates error_code: " << ec.message() << "\n";

    auto econd = std::make_error_condition(std::errc::permission_denied);
    assert(econd.category() == std::generic_category());
    std::cout << "  ✓ make_error_condition creates error_condition: "
              << econd.message() << "\n";
}

void test_system_error_exception()
{
    std::cout << "\n[Testing system_error Exception]\n";

    // Test construction with error_code
    std::error_code ec(static_cast<int>(std::errc::invalid_argument),
                       std::generic_category());
    std::system_error se1(ec);
    std::cout << "  ✓ system_error from error_code: " << se1.what() << "\n";

    // Test construction with error_code and message
    std::system_error se2(ec, "Custom message");
    std::string what_str = se2.what();
    assert(what_str.find("Custom message") != std::string::npos);
    std::cout << "  ✓ system_error with message: " << se2.what() << "\n";

    // Test code() method
    assert(se1.code() == ec);
    std::cout << "  ✓ system_error::code() returns correct error_code\n";

    // Test throwing and catching
    try {
        throw std::system_error(ec, "Test exception");
    }
    catch (const std::system_error& e) {
        std::cout << "  ✓ Caught system_error: " << e.what() << "\n";
    }
    catch (...) {
        assert(false && "Should catch as system_error");
    }
}

void test_error_code_comparison()
{
    std::cout << "\n[Testing Error Code Comparison]\n";

    std::error_code ec1(1, std::generic_category());
    std::error_code ec2(1, std::generic_category());
    std::error_code ec3(2, std::generic_category());

    assert(ec1 == ec2);
    std::cout << "  ✓ Equal error_codes are equal\n";

    assert(ec1 != ec3);
    std::cout << "  ✓ Different error_codes are not equal\n";

    // Test three-way comparison
    assert((ec1 <=> ec2) == 0);
    assert((ec1 <=> ec3) != 0);
    std::cout << "  ✓ Three-way comparison works\n";
}

void test_error_traits()
{
    std::cout << "\n[Testing Error Traits]\n";

    // Test is_error_code_enum - errc is NOT an error_code_enum
    bool is_code_enum = std::is_error_code_enum<std::errc>::value;
    assert(!is_code_enum);  // errc is NOT an error_code_enum
    std::cout << "  ✓ is_error_code_enum<errc>: " << is_code_enum << " (correctly false)\n";

    // Test is_error_code_enum_v
    bool is_code_enum_v = std::is_error_code_enum_v<std::errc>;
    assert(!is_code_enum_v);  // errc is NOT an error_code_enum
    std::cout << "  ✓ is_error_code_enum_v<errc>: " << is_code_enum_v << " (correctly false)\n";

    // Test is_error_condition_enum - errc IS an error_condition_enum
    bool is_cond_enum = std::is_error_condition_enum<std::errc>::value;
    assert(is_cond_enum);
    std::cout << "  ✓ is_error_condition_enum<errc>: " << is_cond_enum << "\n";

    // Test is_error_condition_enum_v
    bool is_cond_enum_v = std::is_error_condition_enum_v<std::errc>;
    assert(is_cond_enum_v);
    std::cout << "  ✓ is_error_condition_enum_v<errc>: " << is_cond_enum_v << "\n";
}

void test_hash_support()
{
    std::cout << "\n[Testing Hash Support]\n";

    std::error_code ec(42, std::generic_category());
    std::hash<std::error_code> hasher;
    auto hash_value = hasher(ec);
    std::cout << "  ✓ Hash of error_code: " << hash_value << "\n";

    // Test that same codes have same hash
    std::error_code ec2(42, std::generic_category());
    assert(hasher(ec) == hasher(ec2));
    std::cout << "  ✓ Equal error_codes have equal hash\n";
}

void test_practical_use_cases()
{
    std::cout << "\n[Testing Practical Use Cases]\n";

    // Simulating a function that returns an error code
    auto divide = [](int a, int b) -> std::error_code {
        if (b == 0) {
            return std::make_error_code(std::errc::invalid_argument);
        }
        return std::error_code();  // Success
    };

    auto result1 = divide(10, 2);
    assert(!result1);  // Success
    std::cout << "  ✓ Successful operation returns default error_code\n";

    auto result2 = divide(10, 0);
    assert(result2);  // Error
    std::cout << "  ✓ Failed operation returns error: " << result2.message() << "\n";

    // Using error_code in conditional
    if (auto ec = divide(5, 0); ec) {
        std::cout << "  ✓ Error detected in conditional: " << ec.message() << "\n";
    }
}

int main()
{
    std::cout << "==============================================\n";
    std::cout << "Testing std_module.system_error\n";
    std::cout << "==============================================\n";

    try {
        test_error_category();
        test_error_code();
        test_error_condition();
        test_errc_enum();
        test_make_error_code();
        test_system_error_exception();
        test_error_code_comparison();
        test_error_traits();
        test_hash_support();
        test_practical_use_cases();

        std::cout << "\n==============================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "==============================================\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
