#pragma once
#include "Utility/Time/TimeSpan.hpp"

namespace Input
{
    /*!
     * \brief Mouse device interface that defines required functions for getting data.
     */
    class MouseDeviceInterface
    {
    public:
        MouseDeviceInterface(const MouseDeviceInterface&) = delete;
        MouseDeviceInterface(MouseDeviceInterface&&) = delete;
        MouseDeviceInterface& operator=(const MouseDeviceInterface&) = delete;
        MouseDeviceInterface& operator=(MouseDeviceInterface&&) = delete;
        MouseDeviceInterface() = default;
        virtual ~MouseDeviceInterface() = default;
        
        /*!
         * \brief Returns wheel offset (positive is up, negative is down).
         * \return Abstract value that defines how much vertical wheel was scrolled.
         */
        virtual float VerticalWheelDiff(const Utility::TimeSpan& timeSpan) const = 0;

        /*!
         * \brief Returns wheel offset (positive is left, negative is right).
         * \return Abstract value that defines how much horizontal wheel was scrolled.
         */
        virtual float HorizontalWheelDiff(const Utility::TimeSpan& timeSpan) const = 0;

        /*!
         * \brief Returns current x coordinate of the mouse cursor relative to the top left corner of the window.
         * \return Integer value of x coordinate of the mouse cursor.
         */
        virtual int PositionX() const = 0;

        /*!
         * \brief Returns current y coordinate of the mouse cursor relative to the top left corner of the window.
         * \return Integer value of y coordinate of the mouse cursor.
         */
        virtual int PositionY() const = 0;
    };
}