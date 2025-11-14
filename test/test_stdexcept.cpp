/**
 * @file test_stdexcept.cpp
 * @brief Comprehensive test for std_module.stdexcept (C++20)
 */

import std_module.stdexcept;

#include <iostream>  // FIXME: Should be import std_module.iostream when available
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <string>    // FIXME: Should be import std_module.string when available
#include <cstring>   // For strcmp

// ==============================================================================
// Test Logic Error Exceptions
// ==============================================================================

void test_logic_error() {
    std::cout << "Testing logic_error...\n";

    // Test construction with const char*
    try {
        throw std::logic_error("Logic error message");
    } catch (const std::logic_error& e) {
        assert(std::strcmp(e.what(), "Logic error message") == 0);
        std::cout << "  ✓ logic_error(const char*): " << e.what() << "\n";
    }

    // Test construction with std::string
    try {
        std::string msg = "String-based logic error";
        throw std::logic_error(msg);
    } catch (const std::logic_error& e) {
        assert(std::strcmp(e.what(), "String-based logic error") == 0);
        std::cout << "  ✓ logic_error(std::string): " << e.what() << "\n";
    }

    // Test copy construction
    std::logic_error original("Original message");
    std::logic_error copy(original);
    assert(std::strcmp(copy.what(), "Original message") == 0);
    std::cout << "  ✓ logic_error copy construction\n";
}

void test_domain_error() {
    std::cout << "\nTesting domain_error...\n";

    // Test construction
    try {
        throw std::domain_error("Domain error: value out of domain");
    } catch (const std::domain_error& e) {
        assert(std::strcmp(e.what(), "Domain error: value out of domain") == 0);
        std::cout << "  ✓ domain_error construction: " << e.what() << "\n";
    }

    // Test inheritance from logic_error
    try {
        throw std::domain_error("Domain error");
    } catch (const std::logic_error& e) {
        std::cout << "  ✓ domain_error caught as logic_error: " << e.what() << "\n";
    }
}

void test_invalid_argument() {
    std::cout << "\nTesting invalid_argument...\n";

    // Test construction
    try {
        throw std::invalid_argument("Invalid argument provided");
    } catch (const std::invalid_argument& e) {
        assert(std::strcmp(e.what(), "Invalid argument provided") == 0);
        std::cout << "  ✓ invalid_argument construction: " << e.what() << "\n";
    }

    // Test inheritance from logic_error
    try {
        throw std::invalid_argument("Invalid arg");
    } catch (const std::logic_error& e) {
        std::cout << "  ✓ invalid_argument caught as logic_error: " << e.what() << "\n";
    }
}

void test_length_error() {
    std::cout << "\nTesting length_error...\n";

    // Test construction
    try {
        throw std::length_error("Length exceeds maximum");
    } catch (const std::length_error& e) {
        assert(std::strcmp(e.what(), "Length exceeds maximum") == 0);
        std::cout << "  ✓ length_error construction: " << e.what() << "\n";
    }

    // Test inheritance from logic_error
    try {
        throw std::length_error("Too long");
    } catch (const std::logic_error& e) {
        std::cout << "  ✓ length_error caught as logic_error: " << e.what() << "\n";
    }
}

void test_out_of_range() {
    std::cout << "\nTesting out_of_range...\n";

    // Test construction
    try {
        throw std::out_of_range("Index out of range");
    } catch (const std::out_of_range& e) {
        assert(std::strcmp(e.what(), "Index out of range") == 0);
        std::cout << "  ✓ out_of_range construction: " << e.what() << "\n";
    }

    // Test inheritance from logic_error
    try {
        throw std::out_of_range("Index 10 out of range");
    } catch (const std::logic_error& e) {
        std::cout << "  ✓ out_of_range caught as logic_error: " << e.what() << "\n";
    }
}

// ==============================================================================
// Test Runtime Error Exceptions
// ==============================================================================

void test_runtime_error() {
    std::cout << "\nTesting runtime_error...\n";

    // Test construction with const char*
    try {
        throw std::runtime_error("Runtime error occurred");
    } catch (const std::runtime_error& e) {
        assert(std::strcmp(e.what(), "Runtime error occurred") == 0);
        std::cout << "  ✓ runtime_error(const char*): " << e.what() << "\n";
    }

    // Test construction with std::string
    try {
        std::string msg = "String-based runtime error";
        throw std::runtime_error(msg);
    } catch (const std::runtime_error& e) {
        assert(std::strcmp(e.what(), "String-based runtime error") == 0);
        std::cout << "  ✓ runtime_error(std::string): " << e.what() << "\n";
    }

    // Test copy construction
    std::runtime_error original("Original runtime error");
    std::runtime_error copy(original);
    assert(std::strcmp(copy.what(), "Original runtime error") == 0);
    std::cout << "  ✓ runtime_error copy construction\n";
}

void test_range_error() {
    std::cout << "\nTesting range_error...\n";

    // Test construction
    try {
        throw std::range_error("Value out of range");
    } catch (const std::range_error& e) {
        assert(std::strcmp(e.what(), "Value out of range") == 0);
        std::cout << "  ✓ range_error construction: " << e.what() << "\n";
    }

    // Test inheritance from runtime_error
    try {
        throw std::range_error("Range error");
    } catch (const std::runtime_error& e) {
        std::cout << "  ✓ range_error caught as runtime_error: " << e.what() << "\n";
    }
}

void test_overflow_error() {
    std::cout << "\nTesting overflow_error...\n";

    // Test construction
    try {
        throw std::overflow_error("Arithmetic overflow");
    } catch (const std::overflow_error& e) {
        assert(std::strcmp(e.what(), "Arithmetic overflow") == 0);
        std::cout << "  ✓ overflow_error construction: " << e.what() << "\n";
    }

    // Test inheritance from runtime_error
    try {
        throw std::overflow_error("Overflow");
    } catch (const std::runtime_error& e) {
        std::cout << "  ✓ overflow_error caught as runtime_error: " << e.what() << "\n";
    }
}

void test_underflow_error() {
    std::cout << "\nTesting underflow_error...\n";

    // Test construction
    try {
        throw std::underflow_error("Arithmetic underflow");
    } catch (const std::underflow_error& e) {
        assert(std::strcmp(e.what(), "Arithmetic underflow") == 0);
        std::cout << "  ✓ underflow_error construction: " << e.what() << "\n";
    }

    // Test inheritance from runtime_error
    try {
        throw std::underflow_error("Underflow");
    } catch (const std::runtime_error& e) {
        std::cout << "  ✓ underflow_error caught as runtime_error: " << e.what() << "\n";
    }
}

// ==============================================================================
// Test Exception Hierarchy and Polymorphism
// ==============================================================================

void test_exception_hierarchy() {
    std::cout << "\nTesting exception hierarchy...\n";

    // Test that logic errors can be caught as std::exception
    try {
        throw std::logic_error("Logic error test");
    } catch (const std::exception& e) {
        std::cout << "  ✓ logic_error caught as std::exception: " << e.what() << "\n";
    }

    // Test that runtime errors can be caught as std::exception
    try {
        throw std::runtime_error("Runtime error test");
    } catch (const std::exception& e) {
        std::cout << "  ✓ runtime_error caught as std::exception: " << e.what() << "\n";
    }

    // Test derived exception caught as std::exception
    try {
        throw std::invalid_argument("Invalid arg test");
    } catch (const std::exception& e) {
        std::cout << "  ✓ invalid_argument caught as std::exception: " << e.what() << "\n";
    }
}

// ==============================================================================
// Test Practical Use Cases
// ==============================================================================

void test_practical_usage() {
    std::cout << "\nTesting practical usage scenarios...\n";

    // Simulate array bounds checking
    auto safe_array_access = [](int index) {
        const int size = 10;
        if (index < 0 || index >= size) {
            throw std::out_of_range("Array index " + std::to_string(index) + " is out of bounds");
        }
        return index * 2;
    };

    try {
        safe_array_access(15);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "  ✓ Array bounds checking: " << e.what() << "\n";
    }

    // Simulate input validation
    auto validate_age = [](int age) {
        if (age < 0 || age > 150) {
            throw std::invalid_argument("Age must be between 0 and 150");
        }
        return age;
    };

    try {
        validate_age(200);
        assert(false);  // Should not reach here
    } catch (const std::invalid_argument& e) {
        std::cout << "  ✓ Input validation: " << e.what() << "\n";
    }

    // Simulate mathematical domain error
    auto calculate_sqrt = [](double x) {
        if (x < 0) {
            throw std::domain_error("Cannot calculate square root of negative number");
        }
        return x;  // Simplified, would use actual sqrt
    };

    try {
        calculate_sqrt(-5.0);
        assert(false);  // Should not reach here
    } catch (const std::domain_error& e) {
        std::cout << "  ✓ Domain validation: " << e.what() << "\n";
    }
}

// ==============================================================================
// Main Test Runner
// ==============================================================================

int main() {
    std::cout << "=============================================================\n";
    std::cout << "Testing std_module.stdexcept\n";
    std::cout << "=============================================================\n\n";

    try {
        // Test logic error exceptions
        test_logic_error();
        test_domain_error();
        test_invalid_argument();
        test_length_error();
        test_out_of_range();

        // Test runtime error exceptions
        test_runtime_error();
        test_range_error();
        test_overflow_error();
        test_underflow_error();

        // Test exception hierarchy
        test_exception_hierarchy();

        // Test practical usage
        test_practical_usage();

        std::cout << "\n=============================================================\n";
        std::cout << "All tests passed! ✓\n";
        std::cout << "=============================================================\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Unexpected exception: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\n❌ Unknown exception caught\n";
        return 1;
    }
}
