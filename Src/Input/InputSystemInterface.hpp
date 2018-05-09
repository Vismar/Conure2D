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
        virtual bool ButtonPressed(KeyboardButton keyboardButton) const = 0;

        /*!
         * \brief Checks if specified button was pressed.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        virtual bool ButtonPressed(MouseButton mouseButton) const = 0;
        
        /*!
         * \brief Checks if specified button was pressed.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        virtual bool ButtonPressed(uint32_t joystickId, JoystickButton joystickButton) const = 0;

        /*!
         * \brief Checks if specified button was held down.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        virtual bool ButtonHeldDown(KeyboardButton keyboardButton) const = 0;

        /*!
         * \brief Checks if specified button was held down.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        virtual bool ButtonHeldDown(MouseButton mouseButton) const = 0;

        /*!
         * \brief Checks if specified button was held down.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        virtual bool ButtonHeldDown(uint32_t joystickId, JoystickButton joystickButton) const = 0;

        /*!
         * \brief Checks if specified button was released.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        virtual bool ButtonReleased(KeyboardButton keyboardButton) const = 0;

        /*!
         * \brief Checks if specified button was released.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        virtual bool ButtonReleased(MouseButton mouseButton) const = 0;

        /*!
         * \brief Checks if specified button was released.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        virtual bool ButtonReleased(uint32_t joystickId, JoystickButton joystickButton) const = 0;

        /*!
         * \brief Checks if any button on keyboard or mouse was pressed.
         * \return True if at least one button was pressed. Otherwise - false.
         */
        virtual bool AnyButtonPressed() const = 0;

        /*!
         * \brief Checks if any button on keyboard or mouse was held down.
         * \return True if at least one button was held down. Otherwise - false.
         */
        virtual bool AnyButtonHeldDown() const = 0;

        /*!
         * \brief Checks if any button on keyboard or mouse was released.
         * \return True if at least one button was released. Otherwise - false.
         */
        virtual bool AnyButtonReleased() const = 0;

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
        virtual JoystickDeviceInterface& Joystick(uint32_t joystickId) const = 0;

        /*!
         * \brief Checks if any joystick was used and returns id of joystick which was used last time.
         * \return Id of joystick which was used last time.
         *         If joystick was not used during the update phase, -1 will be returned.
         */
        virtual int32_t LastJoystickUsed() const = 0;

        /*!
         * \brief Sets the joystick threshold.
         * \param newThreshold - New threshold, in the range [0.0f, 100.0f]
         * 
         * The joystick threshold is the value below which no JoystickMoved event will be handled.
         * The threshold value is 0.1 by default.
         */
        virtual void SetJoystickThreshold(float newThreshold) = 0;

        /*!
         * \brief Gets the joystick threshold.
         * \return The joystick threshold value.
         */
        virtual float GetJoystickThreshold() const = 0;

        /*!
         * \brief Grabs input map.
         * \return Reference to the public interface of input map.
         */
        virtual InputMapInterface& Map() const = 0;
    };
}
