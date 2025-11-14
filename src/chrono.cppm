/**
 * @file chrono.cppm
 * @brief C++20 chrono module wrapper
 */

module;

#include <chrono>

export module std_module.chrono;

export namespace std::chrono
{
// Duration types
using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::hours;
using std::chrono::days;
using std::chrono::weeks;
using std::chrono::months;
using std::chrono::years;

// Core duration template
using std::chrono::duration;
using std::chrono::duration_values;

// Time point types
using std::chrono::time_point;

// Clock types
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::high_resolution_clock;
using std::chrono::utc_clock;
using std::chrono::tai_clock;
using std::chrono::gps_clock;
using std::chrono::file_clock;
using std::chrono::local_t;

// Time point aliases
using std::chrono::sys_time;
using std::chrono::sys_seconds;
using std::chrono::sys_days;
using std::chrono::utc_time;
using std::chrono::utc_seconds;
using std::chrono::tai_time;
using std::chrono::tai_seconds;
using std::chrono::gps_time;
using std::chrono::gps_seconds;
using std::chrono::file_time;
using std::chrono::local_time;
using std::chrono::local_seconds;
using std::chrono::local_days;

// Calendar types - basic
using std::chrono::day;
using std::chrono::month;
using std::chrono::year;
using std::chrono::weekday;
using std::chrono::weekday_indexed;
using std::chrono::weekday_last;
using std::chrono::month_day;
using std::chrono::month_day_last;
using std::chrono::month_weekday;
using std::chrono::month_weekday_last;
using std::chrono::year_month;
using std::chrono::year_month_day;
using std::chrono::year_month_day_last;
using std::chrono::year_month_weekday;
using std::chrono::year_month_weekday_last;

// Calendar constants
using std::chrono::last;
using std::chrono::Monday;
using std::chrono::Tuesday;
using std::chrono::Wednesday;
using std::chrono::Thursday;
using std::chrono::Friday;
using std::chrono::Saturday;
using std::chrono::Sunday;
using std::chrono::January;
using std::chrono::February;
using std::chrono::March;
using std::chrono::April;
using std::chrono::May;
using std::chrono::June;
using std::chrono::July;
using std::chrono::August;
using std::chrono::September;
using std::chrono::October;
using std::chrono::November;
using std::chrono::December;

// Time zone types
using std::chrono::tzdb;
using std::chrono::tzdb_list;
using std::chrono::time_zone;
using std::chrono::time_zone_link;
using std::chrono::leap_second;
using std::chrono::zoned_time;
using std::chrono::zoned_traits;
using std::chrono::zoned_seconds;

// Time zone functions
using std::chrono::get_tzdb;
using std::chrono::get_tzdb_list;
using std::chrono::reload_tzdb;
using std::chrono::remote_version;
using std::chrono::locate_zone;
using std::chrono::current_zone;

// Helper functions for durations
using std::chrono::duration_cast;
using std::chrono::floor;
using std::chrono::ceil;
using std::chrono::round;
using std::chrono::abs;

// Helper functions for time points
using std::chrono::time_point_cast;

// Clock casts
using std::chrono::clock_cast;
using std::chrono::clock_time_conversion;

// Hh_mm_ss helper
using std::chrono::hh_mm_ss;
using std::chrono::is_am;
using std::chrono::is_pm;
using std::chrono::make12;
using std::chrono::make24;

// Leap second helpers
using std::chrono::leap_second_info;
using std::chrono::get_leap_second_info;

// Choose helper
using std::chrono::choose;

// Type traits
using std::chrono::treat_as_floating_point;
using std::chrono::treat_as_floating_point_v;

// Literals - users can use "using namespace std::chrono_literals;"
inline namespace chrono_literals
{
using std::chrono_literals::operator""h;
using std::chrono_literals::operator""min;
using std::chrono_literals::operator""s;
using std::chrono_literals::operator""ms;
using std::chrono_literals::operator""us;
using std::chrono_literals::operator""ns;
using std::chrono_literals::operator""d;
using std::chrono_literals::operator""y;
}  // namespace chrono_literals
}  // namespace std::chrono
