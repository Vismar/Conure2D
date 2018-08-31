#pragma once
#include "Utility/Time/Time.hpp"

namespace Conure::Utility
{
    /*!
     * \brief Simple class that provides functionality to store a time span.
     */
    class TimeSpan
    {
    public:
        TimeSpan(const TimeSpan& other) = default;
        TimeSpan(TimeSpan&& other) = default;
        TimeSpan& operator=(const TimeSpan& other) = default;
        TimeSpan& operator=(TimeSpan&& other) = default;
        TimeSpan() = default;
        ~TimeSpan() = default;

        /*!
         * \brief Constructor from specified time values.
         * \param start - time value that represent start of the time span.
         * \param end - time value that represent end of the time span.
         */
        TimeSpan(Time start, Time end);

        /*!
         * \brief Sets new end of the time period.
         * \param newEnd - new time value which will be used as the end of the time period.
         * 
         * Previous "end" value will be used as "start" value.
         */
        void SetNewEnd(const Time& newEnd);

        /*!
         * \brief Sets new end of the time period.
         * \param newEnd - new time value which will be used as the end of the time period.
         * 
         * Previous "end" value will be used as "start" value.
         */
        void SetNewEnd(Time&& newEnd);

        /*!
         * \brief Returns duration of the stored time period.
         * \return Difference between end and start of the stored time period.
         */
        Time Duration() const;

        /*!
         * \brief Grabs past time value.
         * \return Const reference to the past time value.
         */
        const Time& Start() const;

        /*!
         * \brief Grabs current time value.
         * \return Const reference to the current time value.
         */
        const Time& End() const;

    private:
        /*! Time value that represent start of the time span. */
        Time _start;
        /*! Time value that represent end of the time span. */
        Time _end;
    };
}