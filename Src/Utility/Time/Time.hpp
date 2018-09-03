#pragma once
#include <cstdint>
#include <atomic>
#include <string>
#include <regex>

namespace C2D
{
    /*!
     * \brief Container that stores time as nanoseconds.
     * 
     * Thread safe container can convert stored time value to any 
     * time precision (weeks/days/hours/minutes/second/millisecond/microseconds/nanoseconds).
     */
    class Time
    {
    public:
        ~Time() = default;

        /*!
         * \brief Copy constructor.
         * \param other - other time container.
         */
        Time(const Time& other);

        /*!
         * \brief Move constructor
         * \param other - other time container.
         */
        Time(Time&& other) noexcept;

        /*!
         * \brief Copy assignment operator.
         * \param other - other time container.
         * \return Reference to the time container.
         */
        Time& operator=(const Time& other);

        /*!
         * \brief Move assignment operator.
         * \param other - other time container.
         * \return Reference to the time container.
         */
        Time& operator=(Time&& other) noexcept;

        /*!
         * \brief Constructs Time from specified parameters.
         * \param hours - number of hours.
         * \param minutes - number of minutes.
         * \param seconds - number of seconds.
         * \param milliseconds - number of milliseconds.
         * \param microseconds - number of microseconds.
         * \param nanoseconds - number of nanoseconds.
         */
        explicit Time(int64_t hours = 0ll,
                      int64_t minutes = 0ll,
                      int64_t seconds = 0ll,
                      int64_t milliseconds = 0ll,
                      int64_t microseconds = 0ll,
                      int64_t nanoseconds = 0ll);

        /*!
         * \brief Returns current time.
         * \return Time that contains current time values.
         */
        static Time CurrentTime();

        /*!
         * \brief Converts stored value to days.
         * \return Number of stored days.
         */
        int64_t ToDays() const;

        /*!
         * \brief Converts stored value to hours.
         * \return Number of stored hours.
         */
        int64_t ToHours() const;
        
        /*!
         * \brief Converts stored value to minutes.
         * \return Number of stored minutes.
         */
        int64_t ToMinutes() const;
        
        /*!
         * \brief Converts stored value to seconds.
         * \return Number of stored seconds.
         */
        int64_t ToSeconds() const;
        
        /*!
         * \brief Converts stored value to milliseconds.
         * \return Number of stored milliseconds.
         */
        int64_t ToMilliseconds() const;
        
        /*!
         * \brief Converts stored value to microseconds.
         * \return Number of stored microseconds.
         */
        int64_t ToMicroseconds() const;
        
        /*!
         * \brief Converts stored value to nanoseconds.
         * \return Number of stored nanoseconds.
         */
        int64_t ToNanoseconds() const;

        /*!
         * \brief Returns formated string representation of stored time.
         * \param format - template string.
         * 
         * Specified template can replace next "variables":
         *   - %d  - number of days [0-7].
         *   - %h  - number of hours [1-23].
         *   - %m  - number of minutes [0-59].
         *   - %s  - number of seconds [0-59].
         *   - %ms - number of milliseconds [0-999].
         *   - %us - number of microseconds [0-999].
         *   - %ns - number of nanoseconds [0-999].
         */
        std::string ToString(std::string&& format = "%h:%m:%s.%ms") const;

    private:
        /*! Regex for days variable in template. */
        const static std::regex DaysRegex;
        /*! Regex for hours variable in template. */
        const static std::regex HoursRegex;
        /*! Regex for minutes variable in template. */
        const static std::regex MinutesRegex;
        /*! Regex for seconds variable in template. */
        const static std::regex SecondsRegex;
        /*! Regex for milliseconds variable in template. */
        const static std::regex MillisecondsRegex;
        /*! Regex for microseconds variable in template. */
        const static std::regex MicrosecondsRegex;
        /*! Regex for days nanoseconds in template. */
        const static std::regex NanosecondsRegex;

        /*! Time value that stored as nanoseconds. */
        std::atomic_int64_t _timeValue = 0ull;
    };
    
    /*!
     * \brief Overload of == operator to compare two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return True if time values are equal.
     */
    bool operator==(const Time& left, const Time& right);
    
    /*!
     * \brief Overload of != operator to compare two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return True if time values are not equal.
     */
    bool operator!=(const Time& left, const Time& right);

    /*!
     * \brief Overload of < operator to compare two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return True if left time value is less than right time value.
     */
    bool operator<(const Time& left, const Time& right);
    
    /*!
     * \brief Overload of > operator to compare two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return True if left time value is more than right time value.
     */
    bool operator>(const Time& left, const Time& right);

    /*!
     * \brief Overload of <= operator to compare two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return True if left time value is less or equal to right time value.
     */
    bool operator<=(const Time& left, const Time& right);
    
    /*!
     * \brief Overload of >= operator to compare two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return True if left time value is more or equal to right time value.
     */
    bool operator>=(const Time& left, const Time& right);

    /*!
     * \brief Overload of binary - operator to subtract two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return Difference of the two times values.
     */
    Time operator-(const Time& left, const Time& right);
    
    /*!
     * \brief Overload of binary + operator to add two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return Sum of the two times values.
     */
    Time operator+(const Time& left, const Time& right);
    
    /*!
     * \brief Overload of binary -= operator to subtract/assign two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return Difference of the two times values.
     */
    Time& operator-=(Time& left, const Time& right);

    /*!
     * \brief Overload of binary += operator to add/assign two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return Sum of the two times values.
     */
    Time& operator+=(Time& left, const Time& right);

    /*!
     * \brief Overload of binary * operator to scale a time value.
     * \param left - a time value.
     * \param right - a number value.
     * \return left multiplied by right.
     */
    Time operator*(const Time& left, double right);

    /*!
     * \brief Overload of binary * operator to scale a time value.
     * \param left - a time value.
     * \param right - a number value.
     * \return left multiplied by right.
     */
    Time operator*(const Time& left, int64_t right);

    /*!
     * \brief Overload of binary * operator to scale a time value.
     * \param left - a number value.
     * \param right - a time value.
     * \return right multiplied by left.
     */
    Time operator*(double left, const Time& right);

    /*!
     * \brief Overload of binary * operator to scale a time value.
     * \param left - a number value.
     * \param right - a time value.
     * \return right multiplied by left.
     */
    Time operator*(int64_t left, const Time& right);

    /*!
     * \brief Overload of binary *= operator to scale/assign a time value.
     * \param left - a time value.
     * \param right - a number value.
     * \return left multiplied by right.
     */
    Time& operator*=(Time& left, double right);

    /*!
     * \brief Overload of binary *= operator to scale/assign a time value.
     * \param left - a time value.
     * \param right - a number value.
     * \return left multiplied by right.
     */
    Time& operator*=(Time& left, int64_t right);

    /*!
     * \brief Overload of binary / operator to scale a time value.
     * \param left - a time value.
     * \param right - a number value.
     * \return left divided by right.
     */
    Time operator/(const Time& left, double right);

    /*!
     * \brief Overload of binary / operator to scale a time value.
     * \param left - a time value.
     * \param right - a number value.
     * \return left divided by right.
     */
    Time operator/(const Time& left, int64_t right);

    /*!
     * \brief Overload of binary /= operator to scale/assign a time value.
     * \param left - a time value.
     * \param right -
     * \return left divided by right.
     */
    Time& operator/=(Time& left, double right);

    /*!
     * \brief Overload of binary /= operator to scale/assign a time value.
     * \param left - a time value.
     * \param right - a number value.
     * \return left divided by right.
     */
    Time& operator/=(Time& left, int64_t right);

    /*!
     * \brief Overload of binary / operator to compute the ratio of two time values.
     * \param left - a time value.
     * \param right - a time value.
     * \return left divided by right.
     */
    double operator/(const Time& left, const Time& right);

    /*!
     * \brief Overload of binary % operator to compute remainder of a time value.
     * \param left - a time value.
     * \param right - a time value.
     * \return left modulo right.
     */
    Time operator%(const Time& left, const Time& right);

    /*!
     * \brief Overload of binary %= operator to compute/assign remainder of a time value. 
     * \param left - a time value.
     * \param right - a time value.
     * \return left modulo right.
     */
    Time& operator%=(Time& left, const Time& right);
}
