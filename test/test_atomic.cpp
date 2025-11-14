/**
 * @file test_atomic.cpp
 * @brief Comprehensive test for std_module.atomic (C++20)
 */

import std_module.atomic;

#include <iostream>
#include <cassert>   // NOTE: Must be #include - assert is a macro, not exportable via modules
#include <thread>
#include <vector>

void test_atomic_basic_operations() {
    std::cout << "Testing basic atomic operations...\n";

    std::atomic<int> counter{0};

    // Test store and load
    counter.store(42);
    assert(counter.load() == 42);
    std::cout << "  ✓ store/load: " << counter.load() << "\n";

    // Test exchange
    int old = counter.exchange(100);
    assert(old == 42);
    assert(counter.load() == 100);
    std::cout << "  ✓ exchange: old=" << old << ", new=" << counter.load() << "\n";

    // Test implicit conversion
    int value = counter;
    assert(value == 100);
    std::cout << "  ✓ implicit load: " << value << "\n";

    // Test assignment
    counter = 200;
    assert(counter.load() == 200);
    std::cout << "  ✓ assignment: " << counter.load() << "\n";
}

void test_atomic_arithmetic() {
    std::cout << "\nTesting atomic arithmetic operations...\n";

    std::atomic<int> counter{10};

    // Test fetch_add
    int old = counter.fetch_add(5);
    assert(old == 10);
    assert(counter.load() == 15);
    std::cout << "  ✓ fetch_add: old=" << old << ", new=" << counter.load() << "\n";

    // Test fetch_sub
    old = counter.fetch_sub(3);
    assert(old == 15);
    assert(counter.load() == 12);
    std::cout << "  ✓ fetch_sub: old=" << old << ", new=" << counter.load() << "\n";

    // Test operator+=
    counter += 8;
    assert(counter.load() == 20);
    std::cout << "  ✓ operator+=: " << counter.load() << "\n";

    // Test operator-=
    counter -= 5;
    assert(counter.load() == 15);
    std::cout << "  ✓ operator-=: " << counter.load() << "\n";

    // Test ++operator
    int val = ++counter;
    assert(val == 16);
    assert(counter.load() == 16);
    std::cout << "  ✓ ++operator: " << counter.load() << "\n";

    // Test operator++
    val = counter++;
    assert(val == 16);
    assert(counter.load() == 17);
    std::cout << "  ✓ operator++: prev=" << val << ", current=" << counter.load() << "\n";
}

void test_atomic_bitwise() {
    std::cout << "\nTesting atomic bitwise operations...\n";

    std::atomic<unsigned int> bits{0b1010};

    // Test fetch_or
    unsigned int old = bits.fetch_or(0b0101);
    assert(old == 0b1010);
    assert(bits.load() == 0b1111);
    std::cout << "  ✓ fetch_or: old=" << old << ", new=" << bits.load() << "\n";

    // Test fetch_and
    bits.store(0b1111);
    old = bits.fetch_and(0b1100);
    assert(old == 0b1111);
    assert(bits.load() == 0b1100);
    std::cout << "  ✓ fetch_and: old=" << old << ", new=" << bits.load() << "\n";

    // Test fetch_xor
    old = bits.fetch_xor(0b0110);
    assert(old == 0b1100);
    assert(bits.load() == 0b1010);
    std::cout << "  ✓ fetch_xor: old=" << old << ", new=" << bits.load() << "\n";

    // Test operator|=
    bits |= 0b0101;
    assert(bits.load() == 0b1111);
    std::cout << "  ✓ operator|=: " << bits.load() << "\n";

    // Test operator&=
    bits &= 0b1010;
    assert(bits.load() == 0b1010);
    std::cout << "  ✓ operator&=: " << bits.load() << "\n";

    // Test operator^=
    bits ^= 0b1111;
    assert(bits.load() == 0b0101);
    std::cout << "  ✓ operator^=: " << bits.load() << "\n";
}

void test_compare_exchange() {
    std::cout << "\nTesting compare-exchange operations...\n";

    std::atomic<int> value{100};

    // Test compare_exchange_weak (successful)
    int expected = 100;
    bool success = value.compare_exchange_weak(expected, 200);
    assert(success);
    assert(value.load() == 200);
    assert(expected == 100);
    std::cout << "  ✓ compare_exchange_weak (success): value=" << value.load() << "\n";

    // Test compare_exchange_weak (failed)
    expected = 100;  // Wrong expected value
    success = value.compare_exchange_weak(expected, 300);
    assert(!success);
    assert(value.load() == 200);  // Unchanged
    assert(expected == 200);  // Updated to actual value
    std::cout << "  ✓ compare_exchange_weak (fail): value=" << value.load() << ", expected=" << expected << "\n";

    // Test compare_exchange_strong (successful)
    expected = 200;
    success = value.compare_exchange_strong(expected, 400);
    assert(success);
    assert(value.load() == 400);
    std::cout << "  ✓ compare_exchange_strong (success): value=" << value.load() << "\n";

    // Test compare_exchange_strong (failed)
    expected = 100;
    success = value.compare_exchange_strong(expected, 500);
    assert(!success);
    assert(value.load() == 400);
    assert(expected == 400);
    std::cout << "  ✓ compare_exchange_strong (fail): value=" << value.load() << ", expected=" << expected << "\n";
}

void test_atomic_flag() {
    std::cout << "\nTesting atomic_flag operations...\n";

    std::atomic_flag flag = ATOMIC_FLAG_INIT;

    // Test initial state (clear)
    bool was_set = flag.test_and_set();
    assert(!was_set);
    std::cout << "  ✓ Initial test_and_set: was_set=" << was_set << "\n";

    // Test already set
    was_set = flag.test_and_set();
    assert(was_set);
    std::cout << "  ✓ Second test_and_set: was_set=" << was_set << "\n";

    // Test clear
    flag.clear();
    was_set = flag.test_and_set();
    assert(!was_set);
    std::cout << "  ✓ After clear: was_set=" << was_set << "\n";

    // Test C++20 test() method
    flag.clear();
    bool is_set = flag.test();
    assert(!is_set);
    std::cout << "  ✓ test() when clear: " << is_set << "\n";

    flag.test_and_set();
    is_set = flag.test();
    assert(is_set);
    std::cout << "  ✓ test() when set: " << is_set << "\n";
}

void test_memory_ordering() {
    std::cout << "\nTesting memory ordering...\n";

    std::atomic<int> value{0};

    // Test with different memory orders
    value.store(10, std::memory_order_relaxed);
    assert(value.load(std::memory_order_relaxed) == 10);
    std::cout << "  ✓ memory_order_relaxed\n";

    value.store(20, std::memory_order_release);
    assert(value.load(std::memory_order_acquire) == 20);
    std::cout << "  ✓ memory_order_release/acquire\n";

    value.store(30, std::memory_order_seq_cst);
    assert(value.load(std::memory_order_seq_cst) == 30);
    std::cout << "  ✓ memory_order_seq_cst\n";

    // Test exchange with memory order
    int old = value.exchange(40, std::memory_order_acq_rel);
    assert(old == 30);
    assert(value.load() == 40);
    std::cout << "  ✓ exchange with memory_order_acq_rel\n";
}

void test_atomic_types() {
    std::cout << "\nTesting various atomic type aliases...\n";

    std::atomic_bool flag{false};
    flag = true;
    assert(flag.load() == true);
    std::cout << "  ✓ atomic_bool: " << flag.load() << "\n";

    std::atomic_int counter{42};
    assert(counter.load() == 42);
    std::cout << "  ✓ atomic_int: " << counter.load() << "\n";

    std::atomic_uint ucounter{100u};
    assert(ucounter.load() == 100u);
    std::cout << "  ✓ atomic_uint: " << ucounter.load() << "\n";

    std::atomic_long lvalue{1000L};
    assert(lvalue.load() == 1000L);
    std::cout << "  ✓ atomic_long: " << lvalue.load() << "\n";

    std::atomic_size_t size{sizeof(int)};
    assert(size.load() == sizeof(int));
    std::cout << "  ✓ atomic_size_t: " << size.load() << "\n";

    std::atomic<float> fvalue{3.14f};
    assert(fvalue.load() > 3.13f && fvalue.load() < 3.15f);
    std::cout << "  ✓ atomic<float>: " << fvalue.load() << "\n";

    std::atomic<double> dvalue{2.718};
    assert(dvalue.load() > 2.717 && dvalue.load() < 2.719);
    std::cout << "  ✓ atomic<double>: " << dvalue.load() << "\n";
}

void test_atomic_pointer() {
    std::cout << "\nTesting atomic pointer operations...\n";

    int array[5] = {10, 20, 30, 40, 50};
    std::atomic<int*> ptr{array};

    // Test load
    assert(ptr.load() == array);
    assert(*ptr.load() == 10);
    std::cout << "  ✓ atomic pointer load: " << *ptr.load() << "\n";

    // Test fetch_add (pointer arithmetic)
    int* old = ptr.fetch_add(2);
    assert(old == array);
    assert(ptr.load() == array + 2);
    assert(*ptr.load() == 30);
    std::cout << "  ✓ fetch_add(2): " << *ptr.load() << "\n";

    // Test fetch_sub
    old = ptr.fetch_sub(1);
    assert(old == array + 2);
    assert(ptr.load() == array + 1);
    assert(*ptr.load() == 20);
    std::cout << "  ✓ fetch_sub(1): " << *ptr.load() << "\n";

    // Test operator++
    ptr++;
    assert(ptr.load() == array + 2);
    assert(*ptr.load() == 30);
    std::cout << "  ✓ operator++: " << *ptr.load() << "\n";

    // Test operator--
    ptr--;
    assert(ptr.load() == array + 1);
    assert(*ptr.load() == 20);
    std::cout << "  ✓ operator--: " << *ptr.load() << "\n";
}

void test_is_lock_free() {
    std::cout << "\nTesting is_lock_free...\n";

    std::atomic<int> ai;
    std::atomic<char> ac;
    std::atomic<long long> all;

    std::cout << "  ✓ atomic<int> is lock-free: " << ai.is_lock_free() << "\n";
    std::cout << "  ✓ atomic<char> is lock-free: " << ac.is_lock_free() << "\n";
    std::cout << "  ✓ atomic<long long> is lock-free: " << all.is_lock_free() << "\n";

    // Test always lock-free types
    std::cout << "  ✓ atomic_signed_lock_free is always lock-free: "
              << std::atomic_signed_lock_free::is_always_lock_free << "\n";
    std::cout << "  ✓ atomic_unsigned_lock_free is always lock-free: "
              << std::atomic_unsigned_lock_free::is_always_lock_free << "\n";
}

void test_fences() {
    std::cout << "\nTesting fence operations...\n";

    // Test atomic_thread_fence
    std::atomic_thread_fence(std::memory_order_acquire);
    std::cout << "  ✓ atomic_thread_fence(acquire)\n";

    std::atomic_thread_fence(std::memory_order_release);
    std::cout << "  ✓ atomic_thread_fence(release)\n";

    std::atomic_thread_fence(std::memory_order_seq_cst);
    std::cout << "  ✓ atomic_thread_fence(seq_cst)\n";

    // Test atomic_signal_fence
    std::atomic_signal_fence(std::memory_order_acquire);
    std::cout << "  ✓ atomic_signal_fence(acquire)\n";
}

void test_wait_notify() {
    std::cout << "\nTesting wait/notify operations (C++20)...\n";

    std::atomic<int> value{0};

    // Test basic wait/notify with a thread
    std::thread waiter([&value]() {
        value.wait(0);  // Wait until value is not 0
    });

    // Give waiter thread time to start waiting
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Change value and notify
    value.store(42);
    value.notify_one();

    waiter.join();
    std::cout << "  ✓ wait/notify_one: value changed to " << value.load() << "\n";

    // Test notify_all
    std::atomic<bool> ready{false};
    std::vector<std::thread> waiters;

    for (int i = 0; i < 3; ++i) {
        waiters.emplace_back([&ready]() {
            ready.wait(false);
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ready.store(true);
    ready.notify_all();

    for (auto& t : waiters) {
        t.join();
    }
    std::cout << "  ✓ notify_all: woke up " << waiters.size() << " threads\n";
}

void test_atomic_flag_wait_notify() {
    std::cout << "\nTesting atomic_flag wait/notify (C++20)...\n";

    std::atomic_flag flag = ATOMIC_FLAG_INIT;

    std::thread waiter([&flag]() {
        flag.wait(false);  // Wait until flag is set
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    flag.test_and_set();
    flag.notify_one();

    waiter.join();
    std::cout << "  ✓ atomic_flag wait/notify_one\n";
}

void test_atomic_ref() {
    std::cout << "\nTesting atomic_ref (C++20)...\n";

    int regular_int = 0;
    std::atomic_ref<int> ref(regular_int);

    // Test that atomic_ref operations affect the underlying variable
    ref.store(42);
    assert(regular_int == 42);
    assert(ref.load() == 42);
    std::cout << "  ✓ atomic_ref store/load: " << regular_int << "\n";

    ref.fetch_add(10);
    assert(regular_int == 52);
    std::cout << "  ✓ atomic_ref fetch_add: " << regular_int << "\n";

    ref++;
    assert(regular_int == 53);
    std::cout << "  ✓ atomic_ref operator++: " << regular_int << "\n";

    // Test that atomic_ref provides atomic access
    std::cout << "  ✓ atomic_ref is lock-free: " << ref.is_lock_free() << "\n";
}

void test_multithreaded_increment() {
    std::cout << "\nTesting multithreaded atomic increment...\n";

    const int num_threads = 4;
    const int increments_per_thread = 1000;
    std::atomic<int> counter{0};

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter, increments_per_thread]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                counter++;
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    int expected = num_threads * increments_per_thread;
    assert(counter.load() == expected);
    std::cout << "  ✓ " << num_threads << " threads × " << increments_per_thread
              << " increments = " << counter.load() << "\n";
}

int main() {
    std::cout << "=== std_module.atomic Comprehensive Test Suite ===\n\n";

    test_atomic_basic_operations();
    test_atomic_arithmetic();
    test_atomic_bitwise();
    test_compare_exchange();
    test_atomic_flag();
    test_memory_ordering();
    test_atomic_types();
    test_atomic_pointer();
    test_is_lock_free();
    test_fences();
    test_wait_notify();
    test_atomic_flag_wait_notify();
    test_atomic_ref();
    test_multithreaded_increment();

    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}
