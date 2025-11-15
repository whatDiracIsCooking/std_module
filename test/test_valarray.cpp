/**
 * @file test_valarray.cpp
 * @brief Tests for std_module.valarray
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.valarray;
import std_module.test_framework;

int main() {
    test::test_header("std_module.valarray");

    test::section("Testing symbol accessibility");

    // Basic construction
    std::valarray<int> v1;
    std::valarray<int> v2(5);
    std::valarray<int> v3(42, 5);
    std::valarray<int> v4{1, 2, 3, 4, 5};
    test::assert_equal(v4.size(), 5ull, "valarray construction");

    // Element access
    test::assert_equal(v4[0], 1, "operator[]");
    v4[0] = 10;
    test::assert_equal(v4[0], 10, "operator[] write");

    // size and resize
    test::assert_equal(v4.size(), 5ull, "size");
    v4.resize(3);
    test::assert_equal(v4.size(), 3ull, "resize");

    // Aggregate functions
    std::valarray<int> v5{1, 2, 3, 4, 5};
    test::assert_equal(v5.sum(), 15, "sum");
    test::assert_equal(v5.min(), 1, "min");
    test::assert_equal(v5.max(), 5, "max");

    // apply
    auto v6 = v5.apply([](int x) { return x * 2; });
    test::assert_equal(v6[0], 2, "apply");

    // shift and cshift
    auto v7 = v5.shift(1);
    auto v8 = v5.cshift(1);
    test::assert_true(v7.size() == v5.size(), "shift");
    test::assert_true(v8.size() == v5.size(), "cshift");

    // Compound assignment
    std::valarray<int> v9{10, 20, 30};
    v9 += 5;
    test::assert_equal(v9[0], 15, "operator+=");
    v9 -= 5;
    test::assert_equal(v9[0], 10, "operator-=");
    v9 *= 2;
    test::assert_equal(v9[0], 20, "operator*=");
    v9 /= 2;
    test::assert_equal(v9[0], 10, "operator/=");

    // Transcendental functions
    std::valarray<double> vd{1.0, 2.0, 3.0};
    auto vd_abs = std::abs(vd);
    auto vd_sqrt = std::sqrt(vd);
    auto vd_exp = std::exp(vd);
    auto vd_log = std::log(vd);
    auto vd_sin = std::sin(vd);
    auto vd_cos = std::cos(vd);
    test::assert_true(vd_abs.size() > 0, "transcendental functions");

    // pow
    auto vd_pow = std::pow(vd, 2.0);
    test::assert_true(vd_pow.size() > 0, "pow");

    // begin/end
    int sum = 0;
    for (auto val : v5) {
        sum += val;
    }
    test::assert_equal(sum, 15, "begin/end iteration");

    // swap
    std::valarray<int> v10{1, 2, 3};
    std::valarray<int> v11{4, 5, 6};
    std::swap(v10, v11);
    test::assert_equal(v10[0], 4, "swap");

    test::test_footer();
    return 0;
}
