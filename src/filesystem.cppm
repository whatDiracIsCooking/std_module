/**
 * @file filesystem.cppm
 * @brief C++20 filesystem module wrapper
 */

module;

#include <filesystem>

export module std_module.filesystem;

export namespace std
{
// Convenience exports in std namespace
using std::filesystem::path;
using std::filesystem::filesystem_error;

// filesystem namespace
namespace filesystem
{
// Main types
using std::filesystem::path;
using std::filesystem::filesystem_error;
using std::filesystem::directory_entry;
using std::filesystem::directory_iterator;
using std::filesystem::recursive_directory_iterator;
using std::filesystem::file_status;
using std::filesystem::space_info;
using std::filesystem::file_time_type;

// Enumerations
using std::filesystem::file_type;
using std::filesystem::perms;
using std::filesystem::perm_options;
using std::filesystem::copy_options;
using std::filesystem::directory_options;

// Path operations
using std::filesystem::absolute;
using std::filesystem::canonical;
using std::filesystem::weakly_canonical;
using std::filesystem::relative;
using std::filesystem::proximate;

// File operations
using std::filesystem::copy;
using std::filesystem::copy_file;
using std::filesystem::copy_symlink;
using std::filesystem::create_directory;
using std::filesystem::create_directories;
using std::filesystem::create_hard_link;
using std::filesystem::create_symlink;
using std::filesystem::create_directory_symlink;
using std::filesystem::current_path;
using std::filesystem::exists;
using std::filesystem::equivalent;
using std::filesystem::file_size;
using std::filesystem::hard_link_count;
using std::filesystem::last_write_time;
using std::filesystem::permissions;
using std::filesystem::read_symlink;
using std::filesystem::remove;
using std::filesystem::remove_all;
using std::filesystem::rename;
using std::filesystem::resize_file;
using std::filesystem::space;
using std::filesystem::status;
using std::filesystem::symlink_status;
using std::filesystem::temp_directory_path;

// File type checks
using std::filesystem::is_block_file;
using std::filesystem::is_character_file;
using std::filesystem::is_directory;
using std::filesystem::is_empty;
using std::filesystem::is_fifo;
using std::filesystem::is_other;
using std::filesystem::is_regular_file;
using std::filesystem::is_socket;
using std::filesystem::is_symlink;
using std::filesystem::status_known;

// Hash support
using std::filesystem::hash_value;

// Iterator support for range-based for loops
using std::filesystem::begin;
using std::filesystem::end;
}  // namespace filesystem

}  // namespace std
