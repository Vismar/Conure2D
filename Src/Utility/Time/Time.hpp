#pragma once
#include <cstdint>
#include <atomic>

namespace Utility
{
    /*!
     * \brief Container that stores time as nanoseconds.
     * 
     * Thread safe container can convert stored time value to any 
     * time precision (hours/minutes/second/millisecond/microseconds/nanoseconds).
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
        explicit Time(uint64_t hours = 0ll, 
                      uint64_t minutes = 0ll,
                      uint64_t seconds = 0ll,
                      uint64_t milliseconds = 0ll,
                      uint64_t microseconds = 0ll,
                      uint64_t nanoseconds = 0ll);

        /*!
         * \brief Returns current time.
         * \return Time that contains current time values.
         */
        static Time CurrentTime();

        /*!
         * \brief Converts stored value to hours.
         * \return Number of stored hours.
         */
        double ToHours() const;
        
        /*!
         * \brief Converts stored value to minutes.
         * \return Number of stored minutes.
         */
        double ToMinutes() const;
        
        /*!
         * \brief Converts stored value to seconds.
         * \return Number of stored seconds.
         */
        double ToSeconds() const;
        
        /*!
         * \brief Converts stored value to milliseconds.
         * \return Number of stored milliseconds.
         */
        uint64_t ToMilliseconds() const;
        
        /*!
         * \brief Converts stored value to microseconds.
         * \return Number of stored microseconds.
         */
        uint64_t ToMicroseconds() const;
        
        /*!
         * \brief Converts stored value to nanoseconds.
         * \return Number of stored nanoseconds.
         */
        uint64_t ToNanoseconds() const;

    private:
        /*! Time value that stored as nanoseconds. */
        std::atomic<uint64_t> _timeValue = 0;
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
    Time operator*(const Time& left, uint64_t right);

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
    Time operator*(uint64_t left, const Time& right);

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
    Time& operator*=(Time& left, uint64_t right);

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
    Time operator/(const Time& left, uint64_t right);

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
    Time& operator/=(Time& left, uint64_t right);

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
