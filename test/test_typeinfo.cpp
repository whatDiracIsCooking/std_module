/**
 * @file test_typeinfo.cpp
 * @brief Tests for std_module.typeinfo
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.typeinfo;
import std_module.test_framework;

int main() {
    test::test_header("std_module.typeinfo");

    test::section("Testing symbol accessibility");

    // type_info basics
    const std::type_info& ti1 = typeid(int);
    const std::type_info& ti2 = typeid(double);
    test::assert_true(ti1 == ti1, "type_info operator==");
    test::assert_true(ti1 != ti2, "type_info operator!=");

    // name()
    test::assert_true(ti1.name() != nullptr, "name");

    // hash_code()
    test::assert_equal(ti1.hash_code(), ti1.hash_code(), "hash_code");

    // before()
    test::assert_false(ti1.before(ti1), "before");

    // Polymorphic types
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};
    Base base;
    Derived derived;
    Base* ptr = &derived;
    test::assert_true(typeid(*ptr) == typeid(Derived), "polymorphic type");

    // bad_cast exception
    bool caught_bad_cast = false;
    try {
        Base& ref = base;
        [[maybe_unused]] Derived& dref = dynamic_cast<Derived&>(ref);
    } catch (const std::bad_cast&) {
        caught_bad_cast = true;
    }
    test::assert_true(caught_bad_cast, "bad_cast");

    // bad_typeid exception
    bool caught_bad_typeid = false;
    try {
        Base* null_ptr = nullptr;
        [[maybe_unused]] const std::type_info& ti = typeid(*null_ptr);
    } catch (const std::bad_typeid&) {
        caught_bad_typeid = true;
    }
    test::assert_true(caught_bad_typeid, "bad_typeid");

    // Exception hierarchy
    try {
        throw std::bad_cast();
    } catch (const std::exception&) {
        test::success("bad_cast inherits from exception");
    }

    test::test_footer();
    return 0;
}
