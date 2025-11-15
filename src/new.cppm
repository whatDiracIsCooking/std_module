/**
 * @file new.cppm
 * @brief C++20 new module wrapper
 * Note: Module name is std_module.new_ (with underscore) to avoid C++ keyword conflict
 */

module;

#include <new>

export module std_module.new_;

export namespace std
{
// Exception types
using std::bad_alloc;
using std::bad_array_new_length;

// Function pointer types
using std::new_handler;

// Tag types
using std::nothrow_t;
using std::align_val_t;
using std::destroying_delete_t;

// Constants
using std::nothrow;
using std::destroying_delete;

#ifdef __cpp_lib_hardware_interference_size
// Hardware interference sizes (C++17, may not be available on all compilers)
using std::hardware_destructive_interference_size;
using std::hardware_constructive_interference_size;
#endif

// Functions
using std::get_new_handler;
using std::set_new_handler;
using std::launder;
}  // namespace std

// Export global operator new/delete (in global namespace, not std)
export {
    // Basic operator new/delete
    using ::operator new;
    using ::operator delete;

    // Array variants
    using ::operator new[];
    using ::operator delete[];
}
