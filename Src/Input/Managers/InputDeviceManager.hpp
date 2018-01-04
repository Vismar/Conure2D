#pragma once

namespace sf { class Event; }

namespace Input
{
    class KeyboardDevice;
    class MouseDevice;
    class JoystickDevice;

    /*!
     * \brief Manager that handles updates for all input devices.
     */
    class InputDeviceManager
    {
    public:
        InputDeviceManager(const InputDeviceManager&) = delete;
        InputDeviceManager(InputDeviceManager&&) = delete;
        InputDeviceManager& operator=(const InputDeviceManager&) = delete;
        InputDeviceManager& operator=(InputDeviceManager&&) = delete;

        /*!
         * \brief Simple constructor to initialize required devices.
         */
        InputDeviceManager();

        /*!
         * \brief Destructor that deletes stored devices.
         */
        ~InputDeviceManager();

        /*!
         * \brief Handles all input events.
         * \param event - event to handle.
         */
        void HandleInputEvent(const sf::Event event);

        /*!
         * \brief After handling events, manager should finish update of input to reset and clear some parameters.
         */
        void FinishUpdate();

        /*!
         * \brief Returns keyboard device.
         * \return Const reference to keyboard device.
         */
        const KeyboardDevice& GetKeyboardDevice() const;

        /*!
         * \brief Returns mouse device.
         * \return Const reference to mouse device.
         */
        const MouseDevice& GetMouseDevice() const;

        /*!
         * \brief Returns specified joystick device.
         * \param joystickId - Inner identifier of joystick.
         * \return Const reference to specified joystick device.
         */
        const JoystickDevice& GetJoystickDevice(const int joystickId) const;

    private:
        /*! Pointer to keyboard device. */
        KeyboardDevice* _keyboard;
        /*! Pointer to mouse device. */
        MouseDevice* _mouse;
        /*! Array of joystick devices. */
        JoystickDevice* _joysticks;
    };
}