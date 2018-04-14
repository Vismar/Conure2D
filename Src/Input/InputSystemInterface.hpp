#pragma once
#include "Input/Utilities/Buttons/KeyboardButtons.hpp"
#include "Input/Utilities/Buttons/MouseButtons.hpp"
#include "Input/Utilities/Buttons/JoystickButtons.hpp"
#include "Input/Utilities/MappedInput/InputMapInterface.hpp"
#include "Devices/MouseDeviceInterface.hpp"
#include "Devices/JoystickDeviceInterface.hpp"

namespace Input
{
    /*!
     * \brief Public interface for input system.
     * 
     * Provides functionality to work with input system. Should be used within the game logic.
     */
    class InputSystemInterface
    {
    public:
        InputSystemInterface(const InputSystemInterface& other) = delete;
        InputSystemInterface(InputSystemInterface&& other) = delete;
        InputSystemInterface& operator=(const InputSystemInterface& other) = delete;
        InputSystemInterface& operator=(InputSystemInterface&& other) = delete;
        InputSystemInterface() = default;
        virtual ~InputSystemInterface() = default;

        /*!
         * \brief Checks if specified button was pressed.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        virtual bool ButtonPressed(const KeyboardButton keyboardButton) const = 0;

        /*!
         * \brief Checks if specified button was pressed.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        virtual bool ButtonPressed(const MouseButton mouseButton) const = 0;
        
        /*!
         * \brief Checks if specified button was pressed.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        virtual bool ButtonPressed(const uint32_t joystickId, const JoystickButton joystickButton) const = 0;

        /*!
         * \brief Checks if specified button was held down.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        virtual bool ButtonHeldDown(const KeyboardButton keyboardButton) const = 0;

        /*!
         * \brief Checks if specified button was held down.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        virtual bool ButtonHeldDown(const MouseButton mouseButton) const = 0;

        /*!
         * \brief Checks if specified button was held down.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        virtual bool ButtonHeldDown(const uint32_t joystickId, const JoystickButton joystickButton) const = 0;

        /*!
         * \brief Checks if specified button was released.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        virtual bool ButtonReleased(const KeyboardButton keyboardButton) const = 0;

        /*!
         * \brief Checks if specified button was released.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        virtual bool ButtonReleased(const MouseButton mouseButton) const = 0;

        /*!
         * \brief Checks if specified button was released.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        virtual bool ButtonReleased(const uint32_t joystickId, const JoystickButton joystickButton) const = 0;

        /*!
         * \brief Grabs mouse device.
         * \return Reference to the public mouse device interface.
         */
        virtual MouseDeviceInterface& Mouse() const = 0;

        /*!
         * \brief Grabs specified joystick device.
         * \param joystickId - id of joystick.
         * \return Reference to the public joystick device interface of specified joystick.
         */
        virtual JoystickDeviceInterface& Joystick(const uint32_t joystickId) const = 0;

        /*!
         * \brief Grabs input map.
         * \return Reference to the public interface of input map.
         */
        virtual InputMapInterface& Map() const = 0;
    };
}
