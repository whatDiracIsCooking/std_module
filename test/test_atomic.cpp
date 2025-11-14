/**
 * @file test_atomic.cpp
 * @brief Tests for std_module.atomic
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.atomic;
import std_module.test_framework;

int main() {
    test::test_header("std_module.atomic");

    test::section("Testing basic atomic operations");

    // Sanity check each operation is callable (not testing correctness)
    std::atomic<int> counter{42};
    test::assert_true(counter.load() == 42, "load()");

    counter.store(100);
    test::assert_true(counter.load() == 100, "store()");

    int old = counter.exchange(200);
    test::assert_true(old == 100, "exchange()");

    test::section("Testing arithmetic operations");

    old = counter.fetch_add(10);
    test::assert_true(old == 200, "fetch_add()");

    old = counter.fetch_sub(5);
    test::assert_true(old > 0, "fetch_sub()");

    counter += 10;
    test::success("operator+=");

    counter -= 5;
    test::success("operator-=");

    ++counter;
    test::success("++operator");

    counter++;
    test::success("operator++");

    test::section("Testing bitwise operations");

    std::atomic<unsigned int> bits{0b1010};
    bits.fetch_or(0b0101);
    test::success("fetch_or()");

    bits.fetch_and(0b1100);
    test::success("fetch_and()");

    bits.fetch_xor(0b0110);
    test::success("fetch_xor()");

    bits |= 0b0001;
    test::success("operator|=");

    bits &= 0b1111;
    test::success("operator&=");

    bits ^= 0b0011;
    test::success("operator^=");

    test::section("Testing compare-exchange");

    std::atomic<int> value{100};
    int expected = 100;
    bool success = value.compare_exchange_weak(expected, 200);
    test::assert_true(success, "compare_exchange_weak()");

    expected = 200;
    success = value.compare_exchange_strong(expected, 300);
    test::assert_true(success, "compare_exchange_strong()");

    test::section("Testing atomic_flag");

    std::atomic_flag flag{};  // C++20: default init clears the flag
    bool was_set = flag.test_and_set();
    test::assert_false(was_set, "test_and_set()");

    flag.clear();
    test::success("clear()");

    bool is_set = flag.test();
    test::assert_false(is_set, "test() (C++20)");

    test::section("Testing memory ordering");

    // Test that memory_order types are accessible
    std::atomic<int> mem_val{0};
    mem_val.store(10);
    test::assert_true(mem_val.load() == 10, "store/load with default memory order");

    test::section("Testing atomic type aliases");

    std::atomic_bool abool{true};
    test::assert_true(abool.load(), "atomic_bool");

    std::atomic_int aint{42};
    test::assert_true(aint.load() == 42, "atomic_int");

    std::atomic_uint auint{100u};
    test::assert_true(auint.load() == 100u, "atomic_uint");

    std::atomic_long along{1000L};
    test::assert_true(along.load() == 1000L, "atomic_long");

    std::atomic_size_t asize{sizeof(int)};
    test::assert_true(asize.load() == sizeof(int), "atomic_size_t");

    std::atomic<float> afloat{3.14f};
    test::assert_true(afloat.load() > 3.0f, "atomic<float>");

    test::section("Testing atomic pointer operations");

    int array[5] = {10, 20, 30, 40, 50};
    std::atomic<int*> ptr{array};
    test::assert_true(ptr.load() == array, "atomic pointer load");

    ptr.fetch_add(2);
    test::assert_true(*ptr.load() == 30, "fetch_add (pointer)");

    ptr.fetch_sub(1);
    test::assert_true(*ptr.load() == 20, "fetch_sub (pointer)");

    test::section("Testing lock-free properties");

    std::atomic<int> ai;
    bool is_lock_free = ai.is_lock_free();
    test::success("is_lock_free()");

    test::success("atomic_signed_lock_free accessible");
    test::success("atomic_unsigned_lock_free accessible");

    test::section("Testing wait/notify (C++20)");

    std::atomic<int> wait_val{0};
    wait_val.store(42);
    wait_val.notify_one();
    test::success("notify_one()");

    wait_val.notify_all();
    test::success("notify_all()");

    std::atomic_flag wait_flag{};
    wait_flag.test_and_set();
    wait_flag.notify_one();
    test::success("atomic_flag notify_one()");

    test::section("Testing atomic_ref (C++20)");

    int regular_int = 42;
    std::atomic_ref<int> ref(regular_int);
    ref.store(100);
    test::assert_true(regular_int == 100, "atomic_ref store()");

    ref.fetch_add(10);
    test::assert_true(regular_int == 110, "atomic_ref fetch_add()");

    test::test_footer();
    return 0;
}
