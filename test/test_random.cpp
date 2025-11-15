/**
 * @file test_random.cpp
 * @brief Tests for std_module.random
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.random;
import std_module.test_framework;
#include <cstddef>  // For size_t

int main() {
    test::test_header("std_module.random");

    test::section("Testing symbol accessibility");

    // Test random engines
    std::default_random_engine dre;
    test::assert_true(dre() >= 0, "default_random_engine");

    std::mt19937 mt;
    test::assert_true(mt() > 0, "mt19937");

    std::mt19937_64 mt64;
    test::assert_true(mt64() > 0, "mt19937_64");

    std::minstd_rand minstd;
    test::assert_true(minstd() > 0, "minstd_rand");

    std::ranlux24 rlx;
    test::assert_true(rlx() > 0, "ranlux24");

    // Test random_device
    std::random_device rd;
    test::assert_true(rd() >= 0, "random_device");

    // Test seed_seq
    std::seed_seq seq{1, 2, 3};
    test::assert_equal(seq.size(), static_cast<size_t>(3), "seed_seq");

    // Test distributions
    std::uniform_int_distribution<int> uid(1, 6);
    test::assert_true(uid(mt) >= 1, "uniform_int_distribution");

    std::uniform_real_distribution<double> urd(0.0, 1.0);
    test::assert_true(urd(mt) >= 0.0, "uniform_real_distribution");

    std::bernoulli_distribution bd(0.5);
    [[maybe_unused]] bool b = bd(mt);
    test::success("bernoulli_distribution");

    std::binomial_distribution<int> binom(10, 0.5);
    test::assert_true(binom(mt) >= 0, "binomial_distribution");

    std::geometric_distribution<int> geom(0.5);
    test::assert_true(geom(mt) >= 0, "geometric_distribution");

    std::negative_binomial_distribution<int> neg_binom(5, 0.5);
    test::assert_true(neg_binom(mt) >= 0, "negative_binomial_distribution");

    std::poisson_distribution<int> poisson(4.0);
    test::assert_true(poisson(mt) >= 0, "poisson_distribution");

    std::exponential_distribution<double> expo(1.0);
    test::assert_true(expo(mt) >= 0.0, "exponential_distribution");

    std::gamma_distribution<double> gamma(2.0, 2.0);
    test::assert_true(gamma(mt) >= 0.0, "gamma_distribution");

    std::weibull_distribution<double> weibull(2.0, 2.0);
    test::assert_true(weibull(mt) >= 0.0, "weibull_distribution");

    std::extreme_value_distribution<double> extreme(0.0, 1.0);
    [[maybe_unused]] double ev = extreme(mt);
    test::success("extreme_value_distribution");

    std::normal_distribution<double> normal(0.0, 1.0);
    [[maybe_unused]] double n = normal(mt);
    test::success("normal_distribution");

    std::lognormal_distribution<double> lognormal(0.0, 1.0);
    test::assert_true(lognormal(mt) >= 0.0, "lognormal_distribution");

    std::chi_squared_distribution<double> chi_squared(5.0);
    test::assert_true(chi_squared(mt) >= 0.0, "chi_squared_distribution");

    std::cauchy_distribution<double> cauchy(0.0, 1.0);
    [[maybe_unused]] double c = cauchy(mt);
    test::success("cauchy_distribution");

    std::fisher_f_distribution<double> fisher(5.0, 10.0);
    test::assert_true(fisher(mt) >= 0.0, "fisher_f_distribution");

    std::student_t_distribution<double> student(10.0);
    [[maybe_unused]] double t = student(mt);
    test::success("student_t_distribution");

    std::discrete_distribution<int> discrete{1, 2, 3};
    test::assert_true(discrete(mt) >= 0, "discrete_distribution");

    // Test generate_canonical
    auto canonical = std::generate_canonical<double, 10>(mt);
    test::assert_true(canonical >= 0.0 && canonical < 1.0, "generate_canonical");

    test::test_footer();
    return 0;
}
