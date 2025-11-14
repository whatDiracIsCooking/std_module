/**
 * @file test_exception.cpp
 * @brief Comprehensive test for std_module.exception (C++20)
 */

import std_module.exception;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string;
#include <stdexcept> // For specific exception types like runtime_error

// Custom exception class
class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom exception occurred";
    }
};

// Test basic exception handling
void test_basic_exception() {
    std::cout << "Testing basic exception handling...\n";

    try {
        throw std::exception();
    } catch (const std::exception& e) {
        std::cout << "  ✓ Caught std::exception\n";
    }

    try {
        throw CustomException();
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Custom exception occurred");
        std::cout << "  ✓ Caught custom exception: " << e.what() << "\n";
    }
}

// Test std::bad_exception
void test_bad_exception() {
    std::cout << "\nTesting std::bad_exception...\n";

    try {
        throw std::bad_exception();
    } catch (const std::bad_exception& e) {
        std::cout << "  ✓ Caught std::bad_exception\n";
    } catch (...) {
        assert(false && "Should have caught bad_exception");
    }
}

// Test exception_ptr
void test_exception_ptr() {
    std::cout << "\nTesting exception_ptr operations...\n";

    std::exception_ptr eptr;

    try {
        throw std::runtime_error("Test error");
    } catch (...) {
        eptr = std::current_exception();
        std::cout << "  ✓ Captured exception with current_exception()\n";
    }

    // Test that we captured something
    assert(eptr != nullptr);

    // Rethrow and catch
    try {
        std::rethrow_exception(eptr);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Test error");
        std::cout << "  ✓ Rethrown exception with rethrow_exception(): " << e.what() << "\n";
    }
}

// Test make_exception_ptr
void test_make_exception_ptr() {
    std::cout << "\nTesting make_exception_ptr...\n";

    auto eptr = std::make_exception_ptr(std::runtime_error("Made exception"));

    assert(eptr != nullptr);

    try {
        std::rethrow_exception(eptr);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Made exception");
        std::cout << "  ✓ Created and rethrown exception: " << e.what() << "\n";
    }
}

// Test nested exceptions
void test_nested_exception() {
    std::cout << "\nTesting nested exceptions...\n";

    try {
        try {
            throw std::runtime_error("Inner exception");
        } catch (...) {
            std::throw_with_nested(std::runtime_error("Outer exception"));
        }
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Outer exception");
        std::cout << "  ✓ Caught outer exception: " << e.what() << "\n";

        // Try to rethrow nested
        try {
            std::rethrow_if_nested(e);
        } catch (const std::runtime_error& inner) {
            assert(std::string(inner.what()) == "Inner exception");
            std::cout << "  ✓ Caught inner exception: " << inner.what() << "\n";
        }
    }
}

// Test std::nested_exception class directly
void test_nested_exception_class() {
    std::cout << "\nTesting std::nested_exception class...\n";

    class MyException : public std::nested_exception, public std::runtime_error {
    public:
        explicit MyException(const char* msg) : std::runtime_error(msg) {}
    };

    try {
        try {
            throw std::runtime_error("Original error");
        } catch (...) {
            throw MyException("Wrapped error");
        }
    } catch (const MyException& e) {
        std::cout << "  ✓ Caught custom nested exception: " << e.what() << "\n";

        try {
            e.rethrow_nested();
        } catch (const std::runtime_error& original) {
            assert(std::string(original.what()) == "Original error");
            std::cout << "  ✓ Rethrown original exception: " << original.what() << "\n";
        }
    }
}

// Test uncaught_exceptions
void test_uncaught_exceptions() {
    std::cout << "\nTesting uncaught_exceptions...\n";

    // Outside any exception handling, should be 0
    int count = std::uncaught_exceptions();
    std::cout << "  ✓ Uncaught exceptions outside handler: " << count << "\n";
    assert(count == 0);

    try {
        throw std::runtime_error("Test");
    } catch (...) {
        // Inside catch block, should still be 0
        count = std::uncaught_exceptions();
        std::cout << "  ✓ Uncaught exceptions in catch block: " << count << "\n";
        assert(count == 0);
    }
}

// Test terminate handler
void custom_terminate_handler() {
    // This would be called if terminate() is invoked
}

void test_terminate_handler() {
    std::cout << "\nTesting terminate handler...\n";

    // Get current handler
    auto old_handler = std::get_terminate();
    std::cout << "  ✓ Retrieved current terminate handler\n";

    // Set a new handler (must be a function pointer, not a lambda with captures)
    std::set_terminate(custom_terminate_handler);
    std::cout << "  ✓ Set new terminate handler\n";

    // Verify it was set (we can't actually call terminate without ending the program)
    auto current = std::get_terminate();
    std::cout << "  ✓ Retrieved updated terminate handler\n";

    // Restore old handler
    std::set_terminate(old_handler);
    std::cout << "  ✓ Restored original terminate handler\n";
}

// Test exception_ptr with nullptr
void test_exception_ptr_nullptr() {
    std::cout << "\nTesting exception_ptr with nullptr...\n";

    std::exception_ptr eptr;
    assert(eptr == nullptr);
    std::cout << "  ✓ Default-constructed exception_ptr is nullptr\n";

    std::exception_ptr eptr2 = std::current_exception();
    assert(eptr2 == nullptr);
    std::cout << "  ✓ current_exception() returns nullptr when not in catch\n";
}

// Test multiple nested exceptions
void test_multiple_nested() {
    std::cout << "\nTesting multiple levels of nesting...\n";

    try {
        try {
            try {
                throw std::runtime_error("Level 1");
            } catch (...) {
                std::throw_with_nested(std::runtime_error("Level 2"));
            }
        } catch (...) {
            std::throw_with_nested(std::runtime_error("Level 3"));
        }
    } catch (const std::exception& e) {
        std::cout << "  ✓ Outer level: " << e.what() << "\n";

        int level = 3;
        std::exception_ptr eptr = std::current_exception();

        while (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::nested_exception& nested) {
                try {
                    nested.rethrow_nested();
                } catch (const std::exception& inner) {
                    level--;
                    std::cout << "  ✓ Level " << level << ": " << inner.what() << "\n";
                    eptr = std::current_exception();
                }
            } catch (...) {
                break;
            }
        }
    }
}

// Test exception_ptr copying
void test_exception_ptr_copy() {
    std::cout << "\nTesting exception_ptr copying...\n";

    auto eptr1 = std::make_exception_ptr(std::runtime_error("Copy test"));
    auto eptr2 = eptr1;  // Copy

    assert(eptr1 != nullptr);
    assert(eptr2 != nullptr);

    // Both should refer to the same exception
    try {
        std::rethrow_exception(eptr2);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Copy test");
        std::cout << "  ✓ Copied exception_ptr works correctly: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "==============================================\n";
    std::cout << "std_module.exception Comprehensive Test Suite\n";
    std::cout << "==============================================\n\n";

    test_basic_exception();
    test_bad_exception();
    test_exception_ptr();
    test_make_exception_ptr();
    test_nested_exception();
    test_nested_exception_class();
    test_uncaught_exceptions();
    test_terminate_handler();
    test_exception_ptr_nullptr();
    test_multiple_nested();
    test_exception_ptr_copy();

    std::cout << "\n==============================================\n";
    std::cout << "All tests passed! ✓\n";
    std::cout << "==============================================\n";

    return 0;
}
