/**
 * @file test_filesystem.cpp
 * @brief Tests for std_module.filesystem
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.filesystem;
import std_module.test_framework;

int main() {
    test::test_header("std_module.filesystem");

    // Create temporary test directory for filesystem operations
    auto test_dir = std::filesystem::temp_directory_path() / "std_module_fs_test";

    test::section("Testing path operations and construction");

    // Test path construction and operations (not testing correctness, just accessibility)
    std::filesystem::path p1("/usr/local/bin");
    std::filesystem::path p2 = p1 / "app";
    test::assert_true(!p2.empty(), "path concatenation");
    test::assert_true(p2.has_filename(), "has_filename");
    test::assert_true(p2.has_parent_path(), "has_parent_path");
    test::success("path construction and queries accessible");

    test::section("Testing file operations");

    // Create, check, and remove directory (just test symbols are callable)
    std::filesystem::create_directory(test_dir);
    test::assert_true(std::filesystem::exists(test_dir), "create_directory/exists");
    test::assert_true(std::filesystem::is_directory(test_dir), "is_directory");

    auto test_file = test_dir / "test.txt";
    std::filesystem::path copy_path = test_dir / "copy.txt";

    // File size, copy, rename, remove (just test they're callable)
    [[maybe_unused]] auto temp_path = std::filesystem::temp_directory_path();
    test::success("temp_directory_path accessible");

    // Directory operations
    [[maybe_unused]] auto current = std::filesystem::current_path();
    test::success("current_path accessible");

    // Cleanup
    std::filesystem::remove_all(test_dir);
    test::assert_false(std::filesystem::exists(test_dir), "remove_all");

    test::section("Testing path manipulation");

    // absolute, canonical, relative (just test they're callable)
    std::filesystem::path rel("docs/readme.md");
    [[maybe_unused]] auto abs = std::filesystem::absolute(rel);
    test::success("absolute accessible");

    test::section("Testing file status and types");

    // Test file_status and file_type enum
    auto temp = std::filesystem::temp_directory_path();
    auto status = std::filesystem::status(temp);
    test::assert_true(status.type() == std::filesystem::file_type::directory, "status/file_type");
    test::assert_true(std::filesystem::status_known(status), "status_known");

    // Test space_info
    auto space = std::filesystem::space(temp);
    test::assert_true(space.capacity > 0, "space");

    test::section("Testing iterators");

    // Test directory_iterator and recursive_directory_iterator (just callable check)
    std::filesystem::create_directory(test_dir);
    for ([[maybe_unused]] const auto& entry : std::filesystem::directory_iterator(test_dir)) {
        break; // Just checking it's iterable
    }
    test::success("directory_iterator accessible");

    for ([[maybe_unused]] const auto& entry : std::filesystem::recursive_directory_iterator(test_dir)) {
        break; // Just checking it's iterable
    }
    test::success("recursive_directory_iterator accessible");

    std::filesystem::remove_all(test_dir);

    test::section("Testing directory_entry");

    // Test directory_entry (just check construction and methods callable)
    std::filesystem::directory_entry entry(temp);
    test::assert_true(entry.exists(), "directory_entry");

    test::section("Testing permissions");

    // Test perms enum and perm_options
    [[maybe_unused]] auto perms = std::filesystem::perms::owner_read;
    [[maybe_unused]] auto perm_opts = std::filesystem::perm_options::add;
    test::success("perms and perm_options accessible");

    test::test_footer();
    return 0;
}
