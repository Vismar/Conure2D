#pragma once
#include <memory>
#include <vector>

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
        ~InputDeviceManager() = default;

        /*!
         * \brief Simple constructor to initialize required devices.
         */
        InputDeviceManager();

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
        const std::shared_ptr<KeyboardDevice>& GetKeyboardDevice() const;

        /*!
         * \brief Returns mouse device.
         * \return Const reference to mouse device.
         */
        const std::shared_ptr<MouseDevice>& GetMouseDevice() const;

        /*!
         * \brief Returns specified joystick device.
         * \param joystickId - Inner identifier of joystick.
         * \return Const reference to specified joystick device.
         */
        const std::shared_ptr<JoystickDevice>& GetJoystickDevice(const int joystickId) const;

    private:
        /*! Pointer to keyboard device. */
        std::shared_ptr<KeyboardDevice> _keyboard;
        /*! Pointer to mouse device. */
        std::shared_ptr<MouseDevice> _mouse;
        /*! Array of joystick devices. */
        std::vector<std::shared_ptr<JoystickDevice>> _joysticks;
    };
}