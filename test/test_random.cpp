/**
 * @file test_random.cpp
 * @brief Comprehensive tests for std_module.random
 */

import std_module.random;

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

void test_random_engines()
{
    std::cout << "\n[Testing Random Engines]\n";

    // Test default_random_engine
    std::default_random_engine dre;
    auto val1 = dre();
    std::cout << "  ✓ default_random_engine: " << val1 << "\n";

    // Test mt19937
    std::mt19937 mt;
    auto val2 = mt();
    std::cout << "  ✓ mt19937: " << val2 << "\n";

    // Test mt19937_64
    std::mt19937_64 mt64;
    auto val3 = mt64();
    std::cout << "  ✓ mt19937_64: " << val3 << "\n";

    // Test minstd_rand
    std::minstd_rand minstd;
    auto val4 = minstd();
    std::cout << "  ✓ minstd_rand: " << val4 << "\n";

    // Test ranlux24
    std::ranlux24 rlx24;
    auto val5 = rlx24();
    std::cout << "  ✓ ranlux24: " << val5 << "\n";

    // Test that seeding works
    std::mt19937 mt_seeded(12345);
    auto seeded_val = mt_seeded();
    std::cout << "  ✓ Seeded mt19937: " << seeded_val << "\n";
}

void test_random_device()
{
    std::cout << "\n[Testing Random Device]\n";

    std::random_device rd;
    auto val = rd();
    std::cout << "  ✓ random_device: " << val << "\n";

    // Test entropy (may return 0 on some systems)
    auto entropy = rd.entropy();
    std::cout << "  ✓ random_device entropy: " << entropy << "\n";
}

void test_seed_seq()
{
    std::cout << "\n[Testing Seed Sequence]\n";

    std::seed_seq seq{1, 2, 3, 4, 5};
    std::mt19937 gen(seq);
    auto val = gen();
    std::cout << "  ✓ seed_seq initialized generator: " << val << "\n";

    // Test size
    auto size = seq.size();
    assert(size == 5);
    std::cout << "  ✓ seed_seq size: " << size << "\n";
}

void test_uniform_distributions()
{
    std::cout << "\n[Testing Uniform Distributions]\n";

    std::mt19937 gen(42);

    // uniform_int_distribution
    std::uniform_int_distribution<int> uid(1, 6);
    auto dice_roll = uid(gen);
    assert(dice_roll >= 1 && dice_roll <= 6);
    std::cout << "  ✓ uniform_int_distribution (dice): " << dice_roll << "\n";

    // uniform_real_distribution
    std::uniform_real_distribution<double> urd(0.0, 1.0);
    auto real_val = urd(gen);
    assert(real_val >= 0.0 && real_val <= 1.0);
    std::cout << "  ✓ uniform_real_distribution: " << real_val << "\n";
}

void test_bernoulli_distributions()
{
    std::cout << "\n[Testing Bernoulli Distributions]\n";

    std::mt19937 gen(42);

    // bernoulli_distribution
    std::bernoulli_distribution bd(0.5);
    auto coin_flip = bd(gen);
    std::cout << "  ✓ bernoulli_distribution (coin flip): " << coin_flip << "\n";

    // binomial_distribution
    std::binomial_distribution<int> binom(10, 0.5);
    auto binom_val = binom(gen);
    assert(binom_val >= 0 && binom_val <= 10);
    std::cout << "  ✓ binomial_distribution: " << binom_val << "\n";

    // geometric_distribution
    std::geometric_distribution<int> geom(0.5);
    auto geom_val = geom(gen);
    std::cout << "  ✓ geometric_distribution: " << geom_val << "\n";

    // negative_binomial_distribution
    std::negative_binomial_distribution<int> neg_binom(5, 0.5);
    auto neg_binom_val = neg_binom(gen);
    std::cout << "  ✓ negative_binomial_distribution: " << neg_binom_val << "\n";
}

void test_poisson_distributions()
{
    std::cout << "\n[Testing Poisson Distributions]\n";

    std::mt19937 gen(42);

    // poisson_distribution
    std::poisson_distribution<int> poisson(4.0);
    auto pois_val = poisson(gen);
    std::cout << "  ✓ poisson_distribution: " << pois_val << "\n";

    // exponential_distribution
    std::exponential_distribution<double> expo(1.0);
    auto expo_val = expo(gen);
    std::cout << "  ✓ exponential_distribution: " << expo_val << "\n";

    // gamma_distribution
    std::gamma_distribution<double> gamma(2.0, 2.0);
    auto gamma_val = gamma(gen);
    std::cout << "  ✓ gamma_distribution: " << gamma_val << "\n";

    // weibull_distribution
    std::weibull_distribution<double> weibull(2.0, 2.0);
    auto weibull_val = weibull(gen);
    std::cout << "  ✓ weibull_distribution: " << weibull_val << "\n";

    // extreme_value_distribution
    std::extreme_value_distribution<double> extreme(0.0, 1.0);
    auto extreme_val = extreme(gen);
    std::cout << "  ✓ extreme_value_distribution: " << extreme_val << "\n";
}

void test_normal_distributions()
{
    std::cout << "\n[Testing Normal Distributions]\n";

    std::mt19937 gen(42);

    // normal_distribution
    std::normal_distribution<double> normal(0.0, 1.0);
    auto normal_val = normal(gen);
    std::cout << "  ✓ normal_distribution: " << normal_val << "\n";

    // lognormal_distribution
    std::lognormal_distribution<double> lognormal(0.0, 1.0);
    auto lognormal_val = lognormal(gen);
    std::cout << "  ✓ lognormal_distribution: " << lognormal_val << "\n";

    // chi_squared_distribution
    std::chi_squared_distribution<double> chi_squared(5.0);
    auto chi_val = chi_squared(gen);
    std::cout << "  ✓ chi_squared_distribution: " << chi_val << "\n";

    // cauchy_distribution
    std::cauchy_distribution<double> cauchy(0.0, 1.0);
    auto cauchy_val = cauchy(gen);
    std::cout << "  ✓ cauchy_distribution: " << cauchy_val << "\n";

    // fisher_f_distribution
    std::fisher_f_distribution<double> fisher(5.0, 10.0);
    auto fisher_val = fisher(gen);
    std::cout << "  ✓ fisher_f_distribution: " << fisher_val << "\n";

    // student_t_distribution
    std::student_t_distribution<double> student(10.0);
    auto student_val = student(gen);
    std::cout << "  ✓ student_t_distribution: " << student_val << "\n";
}

void test_sampling_distributions()
{
    std::cout << "\n[Testing Sampling Distributions]\n";

    std::mt19937 gen(42);

    // discrete_distribution
    std::discrete_distribution<int> discrete{1, 2, 3, 4, 5};
    auto discrete_val = discrete(gen);
    std::cout << "  ✓ discrete_distribution: " << discrete_val << "\n";

    // piecewise_constant_distribution
    std::vector<double> intervals{0.0, 1.0, 2.0, 3.0};
    std::vector<double> weights{1.0, 2.0, 1.0};
    std::piecewise_constant_distribution<double> piecewise_const(
        intervals.begin(), intervals.end(), weights.begin()
    );
    auto pw_const_val = piecewise_const(gen);
    std::cout << "  ✓ piecewise_constant_distribution: " << pw_const_val << "\n";

    // piecewise_linear_distribution
    std::vector<double> intervals2{0.0, 1.0, 2.0};
    std::vector<double> densities{0.0, 1.0, 0.0};
    std::piecewise_linear_distribution<double> piecewise_lin(
        intervals2.begin(), intervals2.end(), densities.begin()
    );
    auto pw_lin_val = piecewise_lin(gen);
    std::cout << "  ✓ piecewise_linear_distribution: " << pw_lin_val << "\n";
}

void test_generate_canonical()
{
    std::cout << "\n[Testing Utility Functions]\n";

    std::mt19937 gen(42);

    // generate_canonical - generates random number in [0, 1)
    auto canonical_val = std::generate_canonical<double, 10>(gen);
    assert(canonical_val >= 0.0 && canonical_val < 1.0);
    std::cout << "  ✓ generate_canonical<double, 10>: " << canonical_val << "\n";

    auto canonical_float = std::generate_canonical<float, 10>(gen);
    assert(canonical_float >= 0.0f && canonical_float < 1.0f);
    std::cout << "  ✓ generate_canonical<float, 10>: " << canonical_float << "\n";
}

void test_distribution_properties()
{
    std::cout << "\n[Testing Distribution Properties]\n";

    std::mt19937 gen(42);

    // Test min/max
    std::uniform_int_distribution<int> uid(10, 20);
    assert(uid.min() == 10);
    assert(uid.max() == 20);
    std::cout << "  ✓ Distribution min/max: [" << uid.min() << ", " << uid.max() << "]\n";

    // Test param
    auto params = uid.param();
    std::cout << "  ✓ Distribution param() works\n";

    // Test reset
    uid.reset();
    std::cout << "  ✓ Distribution reset() works\n";

    // Test normal distribution mean/stddev
    std::normal_distribution<double> normal(5.0, 2.0);
    assert(normal.mean() == 5.0);
    assert(normal.stddev() == 2.0);
    std::cout << "  ✓ Normal distribution mean: " << normal.mean()
              << ", stddev: " << normal.stddev() << "\n";
}

void test_engine_adaptors()
{
    std::cout << "\n[Testing Engine Adaptors]\n";

    // discard_block_engine
    std::ranlux24 rlx24;  // This is actually a discard_block_engine
    auto val1 = rlx24();
    std::cout << "  ✓ discard_block_engine (ranlux24): " << val1 << "\n";

    // Test discard
    std::mt19937 gen(42);
    auto before = gen();
    gen.discard(1000);
    auto after = gen();
    std::cout << "  ✓ Engine discard: before=" << before << ", after=" << after << "\n";
}

void test_practical_use_cases()
{
    std::cout << "\n[Testing Practical Use Cases]\n";

    std::mt19937 gen(42);

    // Generate random numbers in a range
    std::uniform_int_distribution<int> dist(1, 100);
    std::vector<int> random_numbers;
    for (int i = 0; i < 10; ++i) {
        random_numbers.push_back(dist(gen));
    }
    std::cout << "  ✓ Generated 10 random numbers: ";
    for (int n : random_numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // Shuffle a vector
    std::vector<int> values{1, 2, 3, 4, 5};
    std::shuffle(values.begin(), values.end(), gen);
    std::cout << "  ✓ Shuffled vector: ";
    for (int v : values) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::cout << "==============================================\n";
    std::cout << "Testing std_module.random\n";
    std::cout << "==============================================\n";

    try {
        test_random_engines();
        test_random_device();
        test_seed_seq();
        test_uniform_distributions();
        test_bernoulli_distributions();
        test_poisson_distributions();
        test_normal_distributions();
        test_sampling_distributions();
        test_generate_canonical();
        test_distribution_properties();
        test_engine_adaptors();
        test_practical_use_cases();

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
