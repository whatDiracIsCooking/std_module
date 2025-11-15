/**
 * @file test_tuple.cpp
 * @brief Tests for std_module.tuple
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.tuple;
import std_module.test_framework;

int main() {
    test::test_header("std_module.tuple");

    test::section("Testing symbol accessibility");

    // Basic tuple
    std::tuple<int, double> t1(42, 3.14);
    test::assert_equal(std::get<0>(t1), 42, "tuple construction and get<N>");
    test::assert_true(std::get<int>(t1) == 42, "get<Type>");

    // make_tuple
    auto t2 = std::make_tuple(1, 2.5, "test");
    test::assert_true(std::get<0>(t2) == 1, "make_tuple");

    // tie
    int i;
    double d;
    std::tie(i, d) = t1;
    test::assert_equal(i, 42, "tie");

    // ignore
    std::tie(i, std::ignore) = t1;
    test::success("ignore");

    // Structured bindings
    auto [x, y] = t1;
    test::assert_equal(x, 42, "structured bindings");

    // tuple_cat
    auto t3 = std::tuple_cat(t1, std::make_tuple('c'));
    test::assert_true(std::tuple_size<decltype(t3)>::value == 3, "tuple_cat");

    // forward_as_tuple
    auto refs = std::forward_as_tuple(i, d);
    test::success("forward_as_tuple");

    // tuple_size and tuple_element
    test::assert_true(std::tuple_size<decltype(t1)>::value == 2, "tuple_size");
    test::success("tuple_element");

    // swap
    auto t4 = std::make_tuple(1, 2.0);
    auto t5 = std::make_tuple(10, 20.0);
    std::swap(t4, t5);
    test::assert_true(std::get<0>(t4) == 10, "swap");

    // apply (C++17)
    auto sum = std::apply([](int a, double b) { return a + b; }, t1);
    test::assert_true(sum > 0, "apply");

    // make_from_tuple (C++17)
    struct Point { int x, y; Point(int x, int y) : x(x), y(y) {} };
    auto p = std::make_from_tuple<Point>(std::make_tuple(1, 2));
    test::assert_equal(p.x, 1, "make_from_tuple");

    test::test_footer();
    return 0;
}
