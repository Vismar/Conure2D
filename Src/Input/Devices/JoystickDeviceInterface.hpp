#pragma once
#include "Input/Utilities/Buttons/JoystickAxes.hpp"
#include <string>

namespace Input
{
    /*!
     * \brief Joystick device interface that defines required functions for getting data.
     */
    class JoystickDeviceInterface
    {
    public:
        JoystickDeviceInterface & operator=(const JoystickDeviceInterface&) = delete;
        JoystickDeviceInterface& operator=(JoystickDeviceInterface&&) = delete;
        JoystickDeviceInterface(JoystickDeviceInterface&& other) = delete;
        JoystickDeviceInterface() = default;
        JoystickDeviceInterface(const JoystickDeviceInterface& other) = default;
        virtual ~JoystickDeviceInterface() = default;

        /*!
         * \brief Returns position [range: -100.0f .. 100.0f] of specified joystick axis.
         * \param axis - axis, value of which is required.
         * \return Position of specified axis.
         */
        virtual float JoystickAxisPosition(JoystickAxis axis) const = 0;

        /*!
         * \brief Returns name of current joystick.
         * \return Vendors name via string,
         */
        virtual std::string Name() const = 0;

        /*!
         * \brief Returns vendor id of current joystick.
         * \return Id of vendor.
         */
        virtual uint32_t VendorId() const = 0;

        /*!
         * \brief Returns product id of current joystick.
         * \return Id of product.
         */
        virtual uint32_t ProductId() const = 0;

        /*!
         * \brief Check if current joystick is connected.
         * \return True if joystick connected. Otherwise - false.
         */
        virtual bool IsConnected() const = 0;
    };
}
