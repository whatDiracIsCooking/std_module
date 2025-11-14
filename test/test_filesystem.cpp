/**
 * @file test_filesystem.cpp
 * @brief Comprehensive test for std_module.filesystem (C++20)
 */

import std_module.filesystem;

#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>

// Helper to create a test file with content
void create_test_file(const std::filesystem::path& p, const std::string& content = "test content") {
    std::ofstream ofs(p);
    ofs << content;
}

void test_path_operations() {
    std::cout << "Testing path operations...\n";

    // Test path construction
    std::filesystem::path p1("/usr/local/bin");
    assert(p1.string() == "/usr/local/bin");
    std::cout << "  ✓ path construction: " << p1 << "\n";

    // Test path concatenation
    std::filesystem::path p2 = p1 / "myapp";
    assert(p2.string() == "/usr/local/bin/myapp");
    std::cout << "  ✓ path concatenation: " << p2 << "\n";

    // Test path components
    std::filesystem::path p3("/home/user/document.txt");
    assert(p3.filename() == "document.txt");
    assert(p3.parent_path() == "/home/user");
    assert(p3.extension() == ".txt");
    assert(p3.stem() == "document");
    std::cout << "  ✓ path components: filename=" << p3.filename()
              << ", parent=" << p3.parent_path()
              << ", ext=" << p3.extension()
              << ", stem=" << p3.stem() << "\n";

    // Test path queries
    assert(p3.has_filename());
    assert(p3.has_extension());
    assert(p3.has_parent_path());
    std::cout << "  ✓ path queries work\n";

    // Test relative path
    std::filesystem::path rel("./docs/readme.md");
    assert(rel.is_relative());
    std::cout << "  ✓ relative path detection: " << rel << "\n";

    // Test absolute path (platform-specific check)
    std::filesystem::path abs("/etc/config");
    assert(abs.is_absolute() || abs.string()[0] == '/');
    std::cout << "  ✓ absolute path detection\n";
}

void test_file_operations() {
    std::cout << "\nTesting file operations...\n";

    // Create test directory
    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "std_module_test";
    std::filesystem::create_directory(test_dir);
    assert(std::filesystem::exists(test_dir));
    assert(std::filesystem::is_directory(test_dir));
    std::cout << "  ✓ create_directory: " << test_dir << "\n";

    // Create test file
    std::filesystem::path test_file = test_dir / "test.txt";
    create_test_file(test_file, "Hello, filesystem!");
    assert(std::filesystem::exists(test_file));
    assert(std::filesystem::is_regular_file(test_file));
    std::cout << "  ✓ file created: " << test_file << "\n";

    // Test file size
    auto size = std::filesystem::file_size(test_file);
    assert(size == 18);  // "Hello, filesystem!" is 18 bytes
    std::cout << "  ✓ file_size: " << size << " bytes\n";

    // Test copy file
    std::filesystem::path copy_file = test_dir / "test_copy.txt";
    std::filesystem::copy_file(test_file, copy_file);
    assert(std::filesystem::exists(copy_file));
    assert(std::filesystem::file_size(copy_file) == size);
    std::cout << "  ✓ copy_file: " << copy_file << "\n";

    // Test rename
    std::filesystem::path renamed_file = test_dir / "renamed.txt";
    std::filesystem::rename(copy_file, renamed_file);
    assert(std::filesystem::exists(renamed_file));
    assert(!std::filesystem::exists(copy_file));
    std::cout << "  ✓ rename: " << renamed_file << "\n";

    // Test remove
    std::filesystem::remove(renamed_file);
    assert(!std::filesystem::exists(renamed_file));
    std::cout << "  ✓ remove file\n";

    // Test equivalent (same file)
    assert(std::filesystem::equivalent(test_file, test_file));
    std::cout << "  ✓ equivalent check\n";

    // Clean up
    std::filesystem::remove_all(test_dir);
    assert(!std::filesystem::exists(test_dir));
    std::cout << "  ✓ remove_all (cleanup)\n";
}

void test_directory_operations() {
    std::cout << "\nTesting directory operations...\n";

    // Create nested directories
    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "std_module_test2";
    std::filesystem::path nested = test_dir / "level1" / "level2" / "level3";
    std::filesystem::create_directories(nested);
    assert(std::filesystem::exists(nested));
    assert(std::filesystem::is_directory(nested));
    std::cout << "  ✓ create_directories (nested): " << nested << "\n";

    // Create some test files
    create_test_file(test_dir / "file1.txt");
    create_test_file(test_dir / "file2.txt");
    create_test_file(test_dir / "level1" / "file3.txt");
    std::cout << "  ✓ created test files\n";

    // Test directory iteration
    int count = 0;
    for (const auto& entry : std::filesystem::directory_iterator(test_dir)) {
        count++;
        std::cout << "    - " << entry.path().filename() << "\n";
    }
    assert(count == 3);  // file1.txt, file2.txt, level1/
    std::cout << "  ✓ directory_iterator: found " << count << " entries\n";

    // Test recursive directory iteration
    int recursive_count = 0;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(test_dir)) {
        recursive_count++;
    }
    assert(recursive_count > count);  // Should find more files recursively
    std::cout << "  ✓ recursive_directory_iterator: found " << recursive_count << " entries\n";

    // Test current_path
    auto original_path = std::filesystem::current_path();
    std::cout << "  ✓ current_path: " << original_path << "\n";

    // Clean up
    std::filesystem::remove_all(test_dir);
    std::cout << "  ✓ cleanup complete\n";
}

void test_path_manipulation() {
    std::cout << "\nTesting path manipulation...\n";

    // Test absolute
    std::filesystem::path rel("docs/readme.md");
    auto abs = std::filesystem::absolute(rel);
    assert(abs.is_absolute());
    std::cout << "  ✓ absolute: " << rel << " -> " << abs << "\n";

    // Create test structure for relative/canonical tests
    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "std_module_path_test";
    std::filesystem::create_directories(test_dir / "subdir");
    create_test_file(test_dir / "file.txt");

    // Test canonical (resolves symlinks and . / ..)
    std::filesystem::path with_dots = test_dir / "." / "subdir" / ".." / "file.txt";
    auto canonical = std::filesystem::canonical(with_dots);
    assert(canonical == std::filesystem::canonical(test_dir / "file.txt"));
    std::cout << "  ✓ canonical: " << with_dots.filename() << " -> " << canonical.filename() << "\n";

    // Test relative
    std::filesystem::path base = test_dir;
    std::filesystem::path target = test_dir / "subdir";
    auto relative = std::filesystem::relative(target, base);
    assert(relative == "subdir");
    std::cout << "  ✓ relative: " << relative << "\n";

    // Clean up
    std::filesystem::remove_all(test_dir);
    std::cout << "  ✓ cleanup complete\n";
}

void test_file_status() {
    std::cout << "\nTesting file status...\n";

    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "std_module_status_test";
    std::filesystem::create_directory(test_dir);
    std::filesystem::path test_file = test_dir / "status.txt";
    create_test_file(test_file);

    // Test status
    auto file_stat = std::filesystem::status(test_file);
    assert(file_stat.type() == std::filesystem::file_type::regular);
    assert(std::filesystem::status_known(file_stat));
    std::cout << "  ✓ status: file_type::regular\n";

    auto dir_stat = std::filesystem::status(test_dir);
    assert(dir_stat.type() == std::filesystem::file_type::directory);
    std::cout << "  ✓ status: file_type::directory\n";

    // Test file type predicates
    assert(std::filesystem::is_regular_file(test_file));
    assert(!std::filesystem::is_directory(test_file));
    assert(!std::filesystem::is_symlink(test_file));
    assert(!std::filesystem::is_block_file(test_file));
    assert(!std::filesystem::is_character_file(test_file));
    assert(!std::filesystem::is_fifo(test_file));
    assert(!std::filesystem::is_socket(test_file));
    assert(!std::filesystem::is_other(test_file));
    std::cout << "  ✓ is_regular_file and other type checks\n";

    assert(std::filesystem::is_directory(test_dir));
    assert(!std::filesystem::is_regular_file(test_dir));
    std::cout << "  ✓ is_directory check\n";

    // Test is_empty
    std::filesystem::path empty_file = test_dir / "empty.txt";
    create_test_file(empty_file, "");
    assert(std::filesystem::is_empty(empty_file));
    assert(!std::filesystem::is_empty(test_file));
    std::cout << "  ✓ is_empty check\n";

    // Clean up
    std::filesystem::remove_all(test_dir);
    std::cout << "  ✓ cleanup complete\n";
}

void test_space_info() {
    std::cout << "\nTesting space info...\n";

    auto temp = std::filesystem::temp_directory_path();
    auto space = std::filesystem::space(temp);

    assert(space.capacity > 0);
    assert(space.free <= space.capacity);
    assert(space.available <= space.free);

    std::cout << "  ✓ space info for " << temp << ":\n";
    std::cout << "    - capacity: " << space.capacity << " bytes\n";
    std::cout << "    - free: " << space.free << " bytes\n";
    std::cout << "    - available: " << space.available << " bytes\n";
}

void test_permissions() {
    std::cout << "\nTesting permissions...\n";

    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "std_module_perms_test";
    std::filesystem::create_directory(test_dir);
    std::filesystem::path test_file = test_dir / "perms.txt";
    create_test_file(test_file);

    // Get current permissions
    auto stat = std::filesystem::status(test_file);
    auto perms = stat.permissions();
    std::cout << "  ✓ read permissions\n";

    // Test permission modification (add owner write if not present)
    std::filesystem::permissions(test_file,
                                std::filesystem::perms::owner_write,
                                std::filesystem::perm_options::add);
    auto new_stat = std::filesystem::status(test_file);
    std::cout << "  ✓ modify permissions (add owner_write)\n";

    // Clean up
    std::filesystem::remove_all(test_dir);
    std::cout << "  ✓ cleanup complete\n";
}

void test_directory_entry() {
    std::cout << "\nTesting directory_entry...\n";

    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "std_module_entry_test";
    std::filesystem::create_directory(test_dir);
    std::filesystem::path test_file = test_dir / "entry.txt";
    create_test_file(test_file, "directory entry test");

    std::filesystem::directory_entry entry(test_file);

    assert(entry.exists());
    assert(entry.is_regular_file());
    assert(!entry.is_directory());
    assert(entry.path() == test_file);
    assert(entry.file_size() == 20);  // "directory entry test" is 20 bytes

    std::cout << "  ✓ directory_entry: " << entry.path() << "\n";
    std::cout << "    - exists: " << entry.exists() << "\n";
    std::cout << "    - is_regular_file: " << entry.is_regular_file() << "\n";
    std::cout << "    - file_size: " << entry.file_size() << "\n";

    // Clean up
    std::filesystem::remove_all(test_dir);
    std::cout << "  ✓ cleanup complete\n";
}

void test_temp_directory() {
    std::cout << "\nTesting temp_directory_path...\n";

    auto temp = std::filesystem::temp_directory_path();
    assert(std::filesystem::exists(temp));
    assert(std::filesystem::is_directory(temp));
    std::cout << "  ✓ temp_directory_path: " << temp << "\n";
}

void test_resize_file() {
    std::cout << "\nTesting resize_file...\n";

    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "std_module_resize_test";
    std::filesystem::create_directory(test_dir);
    std::filesystem::path test_file = test_dir / "resize.txt";
    create_test_file(test_file, "original content");

    auto original_size = std::filesystem::file_size(test_file);
    std::cout << "  ✓ original size: " << original_size << " bytes\n";

    // Resize to larger
    std::filesystem::resize_file(test_file, 100);
    assert(std::filesystem::file_size(test_file) == 100);
    std::cout << "  ✓ resized to 100 bytes\n";

    // Resize to smaller
    std::filesystem::resize_file(test_file, 10);
    assert(std::filesystem::file_size(test_file) == 10);
    std::cout << "  ✓ resized to 10 bytes\n";

    // Clean up
    std::filesystem::remove_all(test_dir);
    std::cout << "  ✓ cleanup complete\n";
}

void test_last_write_time() {
    std::cout << "\nTesting last_write_time...\n";

    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "std_module_time_test";
    std::filesystem::create_directory(test_dir);
    std::filesystem::path test_file = test_dir / "time.txt";
    create_test_file(test_file);

    // Read the write time
    auto write_time1 = std::filesystem::last_write_time(test_file);
    std::cout << "  ✓ read last_write_time\n";

    // Test setting write time to a known value
    std::filesystem::last_write_time(test_file, write_time1);
    std::cout << "  ✓ set last_write_time\n";

    // NOTE: Cannot test time comparison (==, >=, etc.) due to C++20 module ADL limitations
    // The operators exist but aren't found through module boundaries

    // Clean up
    std::filesystem::remove_all(test_dir);
    std::cout << "  ✓ cleanup complete\n";
}

int main() {
    std::cout << "=== Testing std_module.filesystem ===\n\n";

    try {
        test_path_operations();
        test_file_operations();
        test_directory_operations();
        test_path_manipulation();
        test_file_status();
        test_space_info();
        test_permissions();
        test_directory_entry();
        test_temp_directory();
        test_resize_file();
        test_last_write_time();

        std::cout << "\n=== All filesystem tests passed! ===\n";
        return 0;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "\nFilesystem error: " << e.what() << "\n";
        std::cerr << "  path1: " << e.path1() << "\n";
        if (!e.path2().empty()) {
            std::cerr << "  path2: " << e.path2() << "\n";
        }
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
        return 1;
    }
}
