/**
 * @file test_typeinfo.cpp
 * @brief Comprehensive test for std_module.typeinfo (C++20)
 */

import std_module.typeinfo;

#include <iostream>  // For cout
#include <cassert>   // For assertions

// Test classes for polymorphic behavior
class Base {
public:
    virtual ~Base() = default;
};

class Derived : public Base {
};

class Other {
public:
    virtual ~Other() = default;
};

void test_type_info_basic() {
    std::cout << "Testing basic type_info functionality...\n";

    // Test typeid on fundamental types
    const std::type_info& ti_int = typeid(int);
    const std::type_info& ti_double = typeid(double);
    const std::type_info& ti_int2 = typeid(int);

    // Test equality
    assert(ti_int == ti_int2);
    std::cout << "  ✓ Same types are equal\n";

    // Test inequality
    assert(ti_int != ti_double);
    std::cout << "  ✓ Different types are not equal\n";

    // Test name() - note: result is implementation-defined
    std::cout << "  ✓ Type name for int: " << ti_int.name() << "\n";
    std::cout << "  ✓ Type name for double: " << ti_double.name() << "\n";
}

void test_type_info_classes() {
    std::cout << "\nTesting type_info with classes...\n";

    // Test with class types
    const std::type_info& ti_base = typeid(Base);
    const std::type_info& ti_derived = typeid(Derived);
    const std::type_info& ti_other = typeid(Other);

    assert(ti_base != ti_derived);
    std::cout << "  ✓ Base and Derived have different type_info\n";

    assert(ti_derived != ti_other);
    std::cout << "  ✓ Derived and Other have different type_info\n";

    std::cout << "  ✓ Type name for Base: " << ti_base.name() << "\n";
    std::cout << "  ✓ Type name for Derived: " << ti_derived.name() << "\n";
}

void test_type_info_polymorphic() {
    std::cout << "\nTesting type_info with polymorphic objects...\n";

    Base base;
    Derived derived;
    Base* ptr_to_derived = &derived;

    // Static type vs dynamic type
    const std::type_info& static_type = typeid(ptr_to_derived);  // Type of the pointer
    const std::type_info& dynamic_type = typeid(*ptr_to_derived);  // Type of the object

    assert(static_type == typeid(Base*));
    std::cout << "  ✓ Static type of pointer is Base*\n";

    assert(dynamic_type == typeid(Derived));
    std::cout << "  ✓ Dynamic type of object is Derived\n";

    assert(dynamic_type != typeid(Base));
    std::cout << "  ✓ Dynamic type differs from base class\n";
}

void test_type_info_hash() {
    std::cout << "\nTesting type_info hash_code...\n";

    const std::type_info& ti_int = typeid(int);
    const std::type_info& ti_int2 = typeid(int);
    const std::type_info& ti_double = typeid(double);

    // Same types should have same hash
    assert(ti_int.hash_code() == ti_int2.hash_code());
    std::cout << "  ✓ Same types have same hash_code\n";

    // Different types typically have different hash (not guaranteed, but very likely)
    std::cout << "  ✓ Hash code for int: " << ti_int.hash_code() << "\n";
    std::cout << "  ✓ Hash code for double: " << ti_double.hash_code() << "\n";
}

void test_bad_cast() {
    std::cout << "\nTesting bad_cast exception...\n";

    Base base;
    Derived derived;
    Other other;

    // Successful dynamic_cast
    Base* ptr = &derived;
    Derived* derived_ptr = dynamic_cast<Derived*>(ptr);
    assert(derived_ptr != nullptr);
    std::cout << "  ✓ Valid dynamic_cast succeeds\n";

    // Failed dynamic_cast with pointers returns nullptr (no exception)
    ptr = &base;
    derived_ptr = dynamic_cast<Derived*>(ptr);
    assert(derived_ptr == nullptr);
    std::cout << "  ✓ Failed dynamic_cast with pointer returns nullptr\n";

    // Failed dynamic_cast with references throws bad_cast
    try {
        Base& ref = base;  // ref to Base object
        Derived& derived_ref = dynamic_cast<Derived&>(ref);  // Try to cast to Derived
        (void)derived_ref;  // Suppress unused warning
        assert(false && "Should have thrown bad_cast");
    } catch (const std::bad_cast& e) {
        std::cout << "  ✓ bad_cast exception caught: " << e.what() << "\n";
    }
}

void test_bad_typeid() {
    std::cout << "\nTesting bad_typeid exception...\n";

    // typeid on null pointer should throw bad_typeid
    Base* null_ptr = nullptr;

    try {
        const std::type_info& ti = typeid(*null_ptr);
        (void)ti;  // Suppress unused warning
        assert(false && "Should have thrown bad_typeid");
    } catch (const std::bad_typeid& e) {
        std::cout << "  ✓ bad_typeid exception caught: " << e.what() << "\n";
    }
}

void test_type_info_before() {
    std::cout << "\nTesting type_info::before...\n";

    const std::type_info& ti_int = typeid(int);
    const std::type_info& ti_double = typeid(double);

    // before() provides implementation-defined ordering
    bool int_before_double = ti_int.before(ti_double);
    bool double_before_int = ti_double.before(ti_int);

    // They should not both be true (unless they're the same type, which they're not)
    assert(!(int_before_double && double_before_int));
    std::cout << "  ✓ before() provides consistent ordering\n";

    // Same type should not be before itself
    assert(!ti_int.before(ti_int));
    std::cout << "  ✓ Type is not before itself\n";
}

void test_exception_hierarchy() {
    std::cout << "\nTesting exception hierarchy...\n";

    // bad_cast and bad_typeid inherit from std::exception
    try {
        throw std::bad_cast();
    } catch (const std::exception& e) {
        std::cout << "  ✓ bad_cast is caught as std::exception\n";
    }

    try {
        throw std::bad_typeid();
    } catch (const std::exception& e) {
        std::cout << "  ✓ bad_typeid is caught as std::exception\n";
    }
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "  std_module.typeinfo Test Suite\n";
    std::cout << "===========================================\n\n";

    test_type_info_basic();
    test_type_info_classes();
    test_type_info_polymorphic();
    test_type_info_hash();
    test_bad_cast();
    test_bad_typeid();
    test_type_info_before();
    test_exception_hierarchy();

    std::cout << "\n===========================================\n";
    std::cout << "  All tests passed!\n";
    std::cout << "===========================================\n";

    return 0;
}
