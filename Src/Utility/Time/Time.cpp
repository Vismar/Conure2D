#include "Time.hpp"
#include <chrono>

using namespace Utility;

/*! Number of nanoseconds in microsecond. */
constexpr uint64_t NsInUs = 1000ull;
/*! Number of nanoseconds in millisecond. */
constexpr uint64_t NsInMs = NsInUs * 1000ull;
/*! Number of nanoseconds in second. */
constexpr uint64_t NsInS  = NsInMs * 1000ull;
/*! Number of nanoseconds in minute. */
constexpr uint64_t NsInM  = NsInS  * 60ull;
/*! Number of nanoseconds in hour. */
constexpr uint64_t NsInH  = NsInM  * 60ull;
/*! Number of nanoseconds in day. */
constexpr uint64_t NsInD  = NsInH  * 24ull;

// Regex's
const std::regex Time::DaysRegex("(%d)");
const std::regex Time::HoursRegex("(%h)");
const std::regex Time::MinutesRegex("(%m)");
const std::regex Time::SecondsRegex("(%s)");
const std::regex Time::MillisecondsRegex("(%ms)");
const std::regex Time::MicrosecondsRegex("(%us)");
const std::regex Time::NanosecondsRegex("(%ns)");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time::Time(const Time& other) : _timeValue(other._timeValue.load())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time::Time(Time&& other) noexcept  : _timeValue(other._timeValue.load())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Time::operator=(const Time& other)
{
    _timeValue = other._timeValue.load();

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Time::operator=(Time&& other) noexcept
{
    _timeValue = other._timeValue.load();

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time::Time(const uint64_t hours, const uint64_t minutes, const uint64_t seconds, 
           const uint64_t milliseconds, const uint64_t microseconds, const uint64_t nanoseconds)
: _timeValue(nanoseconds + microseconds * NsInUs + milliseconds * NsInMs +
             seconds * NsInS + minutes * NsInM + hours * NsInH)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Time::CurrentTime()
{
    const auto currentTimeDuration = std::chrono::system_clock::now().time_since_epoch();
    const uint64_t nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTimeDuration).count();

    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, nanoseconds);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t Time::ToDays() const
{
    return _timeValue.load() / NsInD;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t Time::ToHours() const
{
    return _timeValue.load() / NsInH;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t Time::ToMinutes() const
{
    return _timeValue.load() / NsInM;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t Time::ToSeconds() const
{
    return _timeValue.load() / NsInS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t Time::ToMilliseconds() const
{
    return _timeValue.load() / NsInMs;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t Time::ToMicroseconds() const
{
    return _timeValue.load() / NsInUs;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t Time::ToNanoseconds() const
{
    return _timeValue.load();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Time::ToString(std::string&& format) const
{
    auto retString(format);
    auto timeRemain = _timeValue.load();

    auto temp = timeRemain % NsInUs;     // Get nanoseconds
    timeRemain -= temp;                  // Get rid of nanoseconds
    retString = std::regex_replace(retString, NanosecondsRegex, std::to_string(temp)); 

    temp = timeRemain % NsInMs / NsInUs; // Get microseconds
    timeRemain -= temp;                  // Get rid of microseconds
    retString = std::regex_replace(retString, MicrosecondsRegex, std::to_string(temp));

    temp = timeRemain % NsInS / NsInMs;  // Get milliseconds
    timeRemain -= temp;                  // Get rid of milliseconds
    retString = std::regex_replace(retString, MillisecondsRegex, std::to_string(temp));
    
    temp = timeRemain % NsInM / NsInS;   // Get seconds
    timeRemain -= temp;                  // Get rid of seconds
    retString = std::regex_replace(retString, SecondsRegex, std::to_string(temp));

    temp = timeRemain % NsInH / NsInM;   // Get minutes
    timeRemain -= temp;                  // Get rid of minutes
    retString = std::regex_replace(retString, MinutesRegex, std::to_string(temp));

    temp = timeRemain % NsInD / NsInH;   // Get hours
    timeRemain -= temp;                  // Get rid of hours
    retString = std::regex_replace(retString, HoursRegex, std::to_string(temp));

    temp = timeRemain / NsInD;           // Get days
    retString = std::regex_replace(retString, DaysRegex, std::to_string(temp));

    return retString;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Utility::operator==(const Time& left, const Time& right)
{
    return left.ToNanoseconds() == right.ToNanoseconds();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Utility::operator!=(const Time& left, const Time& right)
{
    return !(left == right);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Utility::operator<(const Time& left, const Time& right)
{
    return left.ToNanoseconds() < right.ToNanoseconds();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Utility::operator>(const Time& left, const Time& right)
{
    return !(left < right);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Utility::operator<=(const Time& left, const Time& right)
{
    return (left < right) || (left == right);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Utility::operator>=(const Time& left, const Time& right)
{
    return (left > right) || (left == right);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator-(const Time& left, const Time& right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, left.ToNanoseconds() - right.ToNanoseconds());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator+(const Time& left, const Time& right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, left.ToNanoseconds() + right.ToNanoseconds());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Utility::operator-=(Time& left, const Time& right)
{
    left = left - right;
    return left;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Utility::operator+=(Time& left, const Time& right)
{
    left = left + right;
    return left;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator*(const Time& left, const double right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, static_cast<uint64_t>(left.ToNanoseconds() * right));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator*(const Time& left, const uint64_t right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, left.ToNanoseconds() * right);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator*(const double left, const Time& right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, static_cast<uint64_t>(left * right.ToNanoseconds()));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator*(const uint64_t left, const Time& right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, left * right.ToNanoseconds());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Utility::operator*=(Time& left, const double right)
{
    left = left * right;
    return left;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Utility::operator*=(Time& left, const uint64_t right)
{
    left = left * right;
    return left;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator/(const Time& left, const double right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, static_cast<uint64_t>(left.ToNanoseconds() / right));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator/(const Time& left, const uint64_t right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, left.ToNanoseconds() / right);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Utility::operator/=(Time& left, const double right)
{
    left = left / right;
    return left;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Utility::operator/=(Time& left, const uint64_t right)
{
    left = left / right;
    return left;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Utility::operator/(const Time& left, const Time& right)
{
    return static_cast<double>(left.ToNanoseconds()) / right.ToNanoseconds();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time Utility::operator%(const Time& left, const Time& right)
{
    // 0 hours, 0 minutes, 0 seconds, 0 milliseconds, 0 microseconds
    return Time(0ull, 0ull, 0ull, 0ull, 0ull, left.ToNanoseconds() % right.ToNanoseconds());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time& Utility::operator%=(Time& left, const Time& right)
{
    left = left % right;
    return left;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
