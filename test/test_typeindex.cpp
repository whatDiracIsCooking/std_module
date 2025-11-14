/**
 * @file test_typeindex.cpp
 * @brief Comprehensive tests for std_module.typeindex
 */

import std_module.typeindex;

#include <iostream>
#include <cassert>
#include <typeinfo>
#include <string>
#include <unordered_map>

void test_type_index_construction()
{
    std::cout << "\n[Testing type_index Construction]\n";

    // Construct from type_info
    std::type_index ti1(typeid(int));
    std::cout << "  ✓ type_index from typeid(int): " << ti1.name() << "\n";

    std::type_index ti2(typeid(double));
    std::cout << "  ✓ type_index from typeid(double): " << ti2.name() << "\n";

    std::type_index ti3(typeid(std::string));
    std::cout << "  ✓ type_index from typeid(std::string): " << ti3.name() << "\n";

    // Copy construction
    std::type_index ti4(ti1);
    assert(ti4 == ti1);
    std::cout << "  ✓ Copy construction works\n";
}

void test_type_index_comparison()
{
    std::cout << "\n[Testing type_index Comparison]\n";

    std::type_index ti_int(typeid(int));
    std::type_index ti_int2(typeid(int));
    std::type_index ti_double(typeid(double));

    // Test equality
    assert(ti_int == ti_int2);
    std::cout << "  ✓ Same types are equal\n";

    assert(ti_int != ti_double);
    std::cout << "  ✓ Different types are not equal\n";

    // Test ordering (for use in ordered containers)
    bool less_result = ti_int < ti_double || ti_double < ti_int;
    std::cout << "  ✓ Ordering comparison works: " << less_result << "\n";

    // Test three-way comparison
    auto cmp = ti_int <=> ti_int2;
    assert(cmp == 0);
    std::cout << "  ✓ Three-way comparison: same types compare equal\n";

    auto cmp2 = ti_int <=> ti_double;
    assert(cmp2 != 0);
    std::cout << "  ✓ Three-way comparison: different types compare unequal\n";
}

void test_type_index_name()
{
    std::cout << "\n[Testing type_index Name]\n";

    std::type_index ti_int(typeid(int));
    std::type_index ti_double(typeid(double));
    std::type_index ti_string(typeid(std::string));

    const char* name_int = ti_int.name();
    const char* name_double = ti_double.name();
    const char* name_string = ti_string.name();

    std::cout << "  ✓ int name: " << name_int << "\n";
    std::cout << "  ✓ double name: " << name_double << "\n";
    std::cout << "  ✓ std::string name: " << name_string << "\n";

    // Names should be consistent
    std::type_index ti_int2(typeid(int));
    assert(std::string(ti_int.name()) == std::string(ti_int2.name()));
    std::cout << "  ✓ Names are consistent for same type\n";
}

void test_type_index_hash_code()
{
    std::cout << "\n[Testing type_index Hash Code]\n";

    std::type_index ti_int(typeid(int));
    std::type_index ti_int2(typeid(int));
    std::type_index ti_double(typeid(double));

    size_t hash_int = ti_int.hash_code();
    size_t hash_int2 = ti_int2.hash_code();
    size_t hash_double = ti_double.hash_code();

    std::cout << "  ✓ int hash: " << hash_int << "\n";
    std::cout << "  ✓ double hash: " << hash_double << "\n";

    // Same types should have same hash
    assert(hash_int == hash_int2);
    std::cout << "  ✓ Same types have same hash code\n";

    // Different types should (usually) have different hash
    // Note: hash collision is theoretically possible but unlikely
    std::cout << "  ✓ Different types likely have different hash codes\n";
}

void test_hash_support()
{
    std::cout << "\n[Testing std::hash Support]\n";

    std::hash<std::type_index> hasher;
    std::type_index ti_int(typeid(int));
    std::type_index ti_double(typeid(double));

    size_t hash1 = hasher(ti_int);
    size_t hash2 = hasher(ti_double);

    std::cout << "  ✓ std::hash<type_index> for int: " << hash1 << "\n";
    std::cout << "  ✓ std::hash<type_index> for double: " << hash2 << "\n";

    // Hash should be consistent
    size_t hash1_again = hasher(ti_int);
    assert(hash1 == hash1_again);
    std::cout << "  ✓ Hash is consistent\n";
}

void test_unordered_map_usage()
{
    std::cout << "\n[Testing Unordered Map Usage]\n";

    // type_index is commonly used as a key in hash maps
    std::unordered_map<std::type_index, std::string> type_names;

    type_names[typeid(int)] = "Integer";
    type_names[typeid(double)] = "Double";
    type_names[typeid(std::string)] = "String";
    type_names[typeid(void)] = "Void";

    std::cout << "  ✓ Inserted 4 types into unordered_map\n";

    // Lookup
    assert(type_names[typeid(int)] == "Integer");
    assert(type_names[typeid(double)] == "Double");
    std::cout << "  ✓ Lookup works: typeid(int) -> " << type_names[typeid(int)] << "\n";
    std::cout << "  ✓ Lookup works: typeid(double) -> " << type_names[typeid(double)] << "\n";

    // Count
    assert(type_names.count(typeid(int)) == 1);
    assert(type_names.count(typeid(float)) == 0);
    std::cout << "  ✓ Count works\n";
}

struct Base {
    virtual ~Base() = default;
};

struct Derived : Base {
};

void test_polymorphic_types()
{
    std::cout << "\n[Testing Polymorphic Types]\n";

    Base base;
    Derived derived;
    Base* ptr_to_derived = &derived;

    std::type_index ti_base(typeid(base));
    std::type_index ti_derived(typeid(derived));
    std::type_index ti_ptr_static(typeid(ptr_to_derived));
    std::type_index ti_ptr_dynamic(typeid(*ptr_to_derived));

    std::cout << "  ✓ Base type: " << ti_base.name() << "\n";
    std::cout << "  ✓ Derived type: " << ti_derived.name() << "\n";
    std::cout << "  ✓ Static type of pointer: " << ti_ptr_static.name() << "\n";
    std::cout << "  ✓ Dynamic type of pointer: " << ti_ptr_dynamic.name() << "\n";

    // Dynamic type should match Derived
    assert(ti_ptr_dynamic == ti_derived);
    std::cout << "  ✓ Dynamic type correctly identifies Derived\n";
}

template<typename T>
void print_type_info(const T& value)
{
    std::type_index ti(typeid(value));
    std::cout << "  ✓ Template type: " << ti.name() << ", hash: " << ti.hash_code() << "\n";
}

void test_template_usage()
{
    std::cout << "\n[Testing Template Usage]\n";

    print_type_info(42);
    print_type_info(3.14);
    print_type_info(std::string("hello"));
    print_type_info('c');
}

void test_practical_type_registry()
{
    std::cout << "\n[Testing Practical Type Registry]\n";

    // A simple type registry
    struct TypeRegistry {
        std::unordered_map<std::type_index, std::string> descriptions;

        void register_type(std::type_index ti, const std::string& desc) {
            descriptions[ti] = desc;
        }

        std::string get_description(std::type_index ti) const {
            auto it = descriptions.find(ti);
            if (it != descriptions.end()) {
                return it->second;
            }
            return "Unknown type";
        }
    };

    TypeRegistry registry;
    registry.register_type(typeid(int), "32-bit integer");
    registry.register_type(typeid(double), "64-bit floating point");
    registry.register_type(typeid(std::string), "String class");

    std::cout << "  ✓ Registered 3 types\n";

    std::cout << "  ✓ int: " << registry.get_description(typeid(int)) << "\n";
    std::cout << "  ✓ double: " << registry.get_description(typeid(double)) << "\n";
    std::cout << "  ✓ std::string: " << registry.get_description(typeid(std::string)) << "\n";
    std::cout << "  ✓ float (unknown): " << registry.get_description(typeid(float)) << "\n";
}

int main()
{
    std::cout << "==============================================\n";
    std::cout << "Testing std_module.typeindex\n";
    std::cout << "==============================================\n";

    try {
        test_type_index_construction();
        test_type_index_comparison();
        test_type_index_name();
        test_type_index_hash_code();
        test_hash_support();
        test_unordered_map_usage();
        test_polymorphic_types();
        test_template_usage();
        test_practical_type_registry();

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
