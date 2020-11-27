#pragma once
#include <iostream>
#include <cstdint>
#include <date/date.h>

using namespace std::chrono_literals;
using namespace date::literals;
using namespace date;
using std::chrono::hours;
using std::chrono::minutes;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::nanoseconds;
using SystemDays = date::sys_days;
using YearMonthDay = date::year_month_day;
using YearMonthWeekday = date::year_month_weekday;

// ---------------------------------------------------------------------------------------------------------------------
// Duration
// ---------------------------------------------------------------------------------------------------------------------

template <typename T, intmax_t Num = 1, intmax_t Denom = 1>
using Duration = std::chrono::duration<T, std::ratio<Num, Denom>>;

using SystemDuration = std::chrono::system_clock::duration;

using SteadyDuration = std::chrono::steady_clock::duration;

// ---------------------------------------------------------------------------------------------------------------------
// Time point
// ---------------------------------------------------------------------------------------------------------------------

template <class Clock, class ClockDuration = typename Clock::duration>
using TimePoint = std::chrono::time_point<Clock, ClockDuration>;

template <class ClockDuration = SystemDuration>
using SystemTimePoint = TimePoint<std::chrono::system_clock, ClockDuration>;

template <class ClockDuration = SteadyDuration>
using SteadyTimePoint = TimePoint<std::chrono::steady_clock, ClockDuration>;

/*!
 * \brief Returns current time by system clock.
 * \return Current system time point.
 */
SystemTimePoint<> CurrentSystemTime();

/*!
 * \brief Returns current time by steady clock.
 * \return Current steady time point.
 */
SteadyTimePoint<> CurrentSteadyTime();