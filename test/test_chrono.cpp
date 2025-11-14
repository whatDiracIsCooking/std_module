/**
 * @file test_chrono.cpp
 * @brief Tests for std_module.chrono
 *
 * Verifies module integration - NOT standard library correctness.
 * Tests that symbols are accessible and callable through the module.
 */

import std_module.chrono;
import std_module.test_framework;

int main() {
    test::test_header("std_module.chrono");

    using namespace std::chrono;
    using namespace std::chrono_literals;

    test::section("Testing duration types and literals");

    // Test that duration types are constructible and callable
    [[maybe_unused]] nanoseconds ns(100);
    [[maybe_unused]] microseconds us(100);
    [[maybe_unused]] milliseconds ms(100);
    [[maybe_unused]] seconds s(100);
    [[maybe_unused]] minutes m(100);
    [[maybe_unused]] hours h(100);
    [[maybe_unused]] days d(100);
    [[maybe_unused]] weeks w(100);
    [[maybe_unused]] months mon(100);
    [[maybe_unused]] years y(100);
    test::success("duration types constructible");

    // Test literals are accessible
    auto lit_h = 1h;
    auto lit_min = 1min;
    auto lit_s = 1s;
    auto lit_ms = 1ms;
    auto lit_us = 1us;
    auto lit_ns = 1ns;
    test::assert_true(lit_h.count() > 0, "duration literals");

    // Test arithmetic operators are callable
    auto sum = lit_h + lit_min;
    auto diff = lit_h - lit_min;
    test::assert_true(sum.count() > 0, "duration arithmetic");

    test::section("Testing clocks");

    // Test that clocks are accessible and callable
    auto sys_now = system_clock::now();
    auto steady_now = steady_clock::now();
    auto hr_now = high_resolution_clock::now();
    auto utc_now = utc_clock::now();
    auto tai_now = tai_clock::now();
    auto gps_now = gps_clock::now();
    auto file_now = file_clock::now();
    test::success("all clock types accessible");

    test::section("Testing time_point operations");

    // Test time_point arithmetic is callable
    auto later = sys_now + 1h;
    auto earlier = sys_now - 1h;
    auto duration_diff = later - sys_now;
    test::assert_true(later > sys_now, "time_point arithmetic and comparison");

    test::section("Testing duration conversions");

    // Test conversion functions are callable
    auto cast_result = duration_cast<seconds>(milliseconds(1000));
    auto floor_result = floor<seconds>(milliseconds(1500));
    auto ceil_result = ceil<seconds>(milliseconds(1500));
    auto round_result = round<seconds>(milliseconds(1500));
    auto abs_result = abs(seconds(-5));
    test::assert_true(cast_result.count() > 0, "duration conversions");

    test::section("Testing calendar types");

    // Test calendar types are constructible
    year yr{2025};
    month mo{11};
    day dy{14};
    weekday wd{Monday};
    year_month_day ymd{yr, mo, dy};

    // Test calendar operators (operator/)
    auto ym = yr / mo;
    auto md = mo / dy;
    auto ymd2 = yr / mo / dy;
    test::success("calendar types and operators accessible");

    // Test calendar constants
    [[maybe_unused]] auto jan = January;
    [[maybe_unused]] auto mon_const = Monday;
    test::success("calendar constants accessible");

    test::section("Testing calendar conversions");

    // Test sys_days conversions
    sys_days sd{ymd};
    year_month_day ymd_back{sd};
    test::success("calendar conversions callable");

    test::section("Testing hh_mm_ss");

    // Test hh_mm_ss is constructible and callable
    auto dur = 3h + 25min + 45s;
    hh_mm_ss hms{dur};
    test::assert_true(hms.hours().count() > 0, "hh_mm_ss");

    // Test is_am/is_pm, make12/make24
    test::assert_true(is_am(hours(10)), "is_am");
    test::assert_true(is_pm(hours(14)), "is_pm");
    auto h12 = make12(hours(14));
    auto h24 = make24(hours(2), true);
    test::assert_true(h12.count() > 0, "make12/make24");

    test::section("Testing time zones");

    // Test time zone functions are callable (may throw if tzdb unavailable)
    try {
        const auto& tzdb = get_tzdb();
        const auto* current = current_zone();
        zoned_time zt{current, sys_now};
        test::success("time zone functions accessible");
    } catch (...) {
        test::success("time zone functions accessible (tzdb unavailable)");
    }

    test::section("Testing clock conversions");

    // Test clock_cast is callable
    auto utc_cast = clock_cast<utc_clock>(sys_now);
    auto tai_cast = clock_cast<tai_clock>(sys_now);
    test::success("clock_cast accessible");

    test::section("Testing duration traits");

    // Test trait is accessible
    [[maybe_unused]] constexpr bool trait = treat_as_floating_point_v<seconds>;
    test::success("duration traits accessible");

    test::test_footer();
    return 0;
}
