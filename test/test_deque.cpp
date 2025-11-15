/**
 * @file test_deque.cpp
 * @brief Tests for std_module.deque
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.deque;
import std_module.test_framework;

int main() {
    test::test_header("std_module.deque");

    test::section("Testing construction and basic operations");

    // Construction
    std::deque<int> d1;
    test::assert_true(d1.empty(), "default construction");

    std::deque<int> d2{1, 2, 3, 4, 5};
    test::assert_equal(d2.size(), 5u, "initializer list construction");

    // Copy construction
    std::deque<int> d3(d2);
    test::success("copy construction");

    test::section("Testing push/pop operations");

    std::deque<int> d;
    d.push_back(1);
    d.push_front(0);
    test::assert_equal(d.front(), 0, "push_front/front");
    test::assert_equal(d.back(), 1, "push_back/back");

    d.pop_back();
    d.pop_front();
    test::success("pop_back/pop_front");

    d.emplace_back(42);
    d.emplace_front(99);
    test::success("emplace_back/emplace_front");

    test::section("Testing element access");

    std::deque<int> d5{10, 20, 30};
    test::assert_equal(d5[0], 10, "operator[]");
    test::assert_equal(d5.at(1), 20, "at()");
    test::success("element access");

    test::section("Testing iterators");

    int sum = 0;
    for (auto it = d5.begin(); it != d5.end(); ++it) {
        sum += *it;
    }
    test::assert_equal(sum, 60, "forward iteration");

    sum = 0;
    for (auto it = d5.rbegin(); it != d5.rend(); ++it) {
        sum += *it;
    }
    test::assert_equal(sum, 60, "reverse iteration");

    sum = 0;
    for (const auto& val : d5) {
        sum += val;
    }
    test::assert_equal(sum, 60, "range-based for");

    test::section("Testing capacity operations");

    test::assert_true(!d5.empty(), "empty()");
    test::assert_equal(d5.size(), 3u, "size()");
    test::assert_true(d5.max_size() > 0, "max_size()");
    d5.shrink_to_fit();
    test::success("shrink_to_fit()");

    test::section("Testing modifiers");

    d5.insert(d5.begin() + 1, 99);
    test::success("insert()");

    d5.erase(d5.begin());
    test::success("erase()");

    d5.clear();
    test::assert_true(d5.empty(), "clear()");

    d5.resize(5);
    test::assert_equal(d5.size(), 5u, "resize()");

    std::deque<int> d6{1, 2, 3};
    d5.swap(d6);
    test::success("swap()");

    test::section("Testing comparison operators");

    std::deque<int> da{1, 2, 3};
    std::deque<int> db{1, 2, 3};
    std::deque<int> dc{1, 2, 4};

    test::assert_true(da == db, "operator==");
    test::assert_true(da != dc, "operator!=");
    test::assert_true(da < dc, "operator<");
    test::assert_true(da <= db, "operator<=");
    test::assert_true(dc > da, "operator>");
    test::assert_true(db >= da, "operator>=");

    test::section("Testing assign and emplace");

    std::deque<int> d7;
    d7.assign(3, 100);
    test::success("assign()");

    d7.emplace(d7.begin(), 200);
    test::success("emplace()");

    test::test_footer();
    return 0;
}
