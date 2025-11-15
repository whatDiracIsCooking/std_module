/**
 * @file test_system_error.cpp
 * @brief Tests for std_module.system_error
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.system_error;
import std_module.test_framework;

int main() {
    test::test_header("std_module.system_error");

    test::section("Testing symbol accessibility");

    // Test error categories
    [[maybe_unused]] auto& gen_cat = std::generic_category();
    [[maybe_unused]] auto& sys_cat = std::system_category();
    test::success("generic_category and system_category");

    // Test error_code
    std::error_code ec;
    test::assert_true(ec.value() == 0, "error_code default construction");
    test::assert_true(!ec, "error_code bool conversion");

    std::error_code ec2(1, std::generic_category());
    test::assert_true(ec2.value() == 1, "error_code construction with value");
    test::assert_true((bool)ec2, "error_code bool conversion (true)");

    // Test error_condition
    std::error_condition econd;
    test::success("error_condition");

    // Test errc
    auto code = std::make_error_code(std::errc::invalid_argument);
    test::success("make_error_code");

    auto cond = std::make_error_condition(std::errc::permission_denied);
    test::success("make_error_condition");

    // Test system_error exception
    try {
        throw std::system_error(ec2, "test");
    } catch (const std::system_error& e) {
        test::success("system_error");
    }

    // Test traits
    [[maybe_unused]] bool is_cond_enum = std::is_error_condition_enum_v<std::errc>;
    test::success("is_error_condition_enum");

    // Test hash
    std::hash<std::error_code> hasher;
    [[maybe_unused]] auto h = hasher(ec2);
    test::success("hash");

    test::test_footer();
    return 0;
}
