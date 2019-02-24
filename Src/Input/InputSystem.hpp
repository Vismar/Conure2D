#pragma once
#include "Input/InputSystemHandlerInterface.hpp"
#include "Input/InputSystemInterface.hpp"
#include "Input/Devices/KeyboardDevice.hpp"
#include "Input/Devices/MouseDevice.hpp"
#include "Input/Devices/JoystickDevice.hpp"
#include "Input/Utilities/MappedInput/InputMap.hpp"
#include <memory>

namespace C2D
{
    /*!
     * \brief System that handles user input.
     * 
     * Provides functionality to:
     *  - Check buttons states of keyboard/mouse/joystick(up to 8)
     *  - Get mouse position and vertical/horizontal wheel values
     *  - Get joystick axes values and vendor information
     *  - Create/edit/delete mapped actions and axes
     */
    class [[deprecated("Will be reimplemented")]] InputSystem final : public InputSystemInterface, public InputSystemHandlerInterface
    {
    public:
        InputSystem(const InputSystem& other) = delete;
        InputSystem(InputSystem&& other) = delete;
        InputSystem& operator=(const InputSystem& other) = delete;
        InputSystem& operator=(InputSystem&& other) = delete;
        ~InputSystem() final = default;

        /*!
         * \brief Default constructor.
         * \param logicLoopTimeSpan - time span of logic loop that will be used to check input events.
         */
        InputSystem(/*const TimeSpan& logicLoopTimeSpan*/);

        /*!
         * \brief Handles input events.
         * \param inputEvent - SFML event which will be handled by input system.
         */
        void HandleInputEvent(const sf::Event& inputEvent) final;

        /*!
         * \brief Checks if specified button was pressed.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        bool ButtonPressed(KeyboardButton keyboardButton) const final;
        
        /*!
         * \brief Checks if specified button was pressed.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        bool ButtonPressed(MouseButton mouseButton) const final;
        
        /*!
         * \brief Checks if specified button was pressed.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        bool ButtonPressed(uint32_t joystickId, JoystickButton joystickButton) const final;

        /*!
         * \brief Checks if specified button was held down.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        bool ButtonHeldDown(KeyboardButton keyboardButton) const final;
        
        /*!
         * \brief Checks if specified button was held down.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        bool ButtonHeldDown(MouseButton mouseButton) const final;
        
        /*!
         * \brief Checks if specified button was held down.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        bool ButtonHeldDown(uint32_t joystickId, JoystickButton joystickButton) const final;

        /*!
         * \brief Checks if specified button was released.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        bool ButtonReleased(KeyboardButton keyboardButton) const final;
        
        /*!
         * \brief Checks if specified button was released.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        bool ButtonReleased(MouseButton mouseButton) const final;
        
        /*!
         * \brief Checks if specified button was released.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        bool ButtonReleased(uint32_t joystickId, JoystickButton joystickButton) const final;

        /*!
         * \brief Checks if any button on keyboard or mouse was pressed.
         * \return True if at least one button was pressed. Otherwise - false.
         */
        bool AnyButtonPressed() const final;

        /*!
         * \brief Checks if any button on keyboard or mouse was held down.
         * \return True if at least one button was held down. Otherwise - false.
         */
        bool AnyButtonHeldDown() const final;

        /*!
         * \brief Checks if any button on keyboard or mouse was released.
         * \return True if at least one button was released. Otherwise - false.
         */
        bool AnyButtonReleased() const final;

        /*!
         * \brief Grabs mouse device.
         * \return Reference to the public mouse device interface.
         */
        MouseDeviceInterface& Mouse() const final;

        /*!
         * \brief Grabs specified joystick device.
         * \param joystickId - id of joystick.
         * \return Reference to the public joystick device interface of specified joystick.
         */
        JoystickDeviceInterface& Joystick(uint32_t joystickId) const final;

        /*!
         * \brief Checks if any joystick was used and returns id of joystick which was used last time.
         * \return Id of joystick which was used last time.
         *         If joystick was not used during the update phase, -1 will be returned.
         */
        int32_t LastJoystickUsed() const final;

        /*!
         * \brief Sets the joystick threshold.
         * \param newThreshold - New threshold, in the range [0.0f, 100.0f]
         *
         * The joystick threshold is the value below which no JoystickMoved event will be handled.
         * The threshold value is 0.1 by default.
         */
        void SetJoystickThreshold(float newThreshold) final;

        /*!
         * \brief Gets the joystick threshold.
         * \return The joystick threshold value.
         */
        float GetJoystickThreshold() const final;

        /*!
         * \brief Grabs input map.
         * \return Reference to the public interface of input map.
         */
        InputMapInterface& Map() const final;

    private:
        /*!
         * \brief Checks if any button on keyboard or mouse is in specified state.
         * \param state - specified state in which any button should be.
         * \return True if at least one button in required state. Otherwise - false.
         */
        bool _AnyButtonState(ButtonState state) const;

        /*! Const reference to the logic loop time span that is used by input system to check button states. */
        //const TimeSpan& _logicLoopTimeSpan;
        /*! Keyboard device which handles keyboard events. */
        std::unique_ptr<KeyboardDevice> _keyboard;
        /*! Mouse device which handles mouse events. */
        std::unique_ptr<MouseDevice> _mouse;
        /*! Array of joystick devices that handles joystick events. */
        std::vector<std::unique_ptr<JoystickDevice>> _joystick;
        /*! A time when any joystick was used last time. */
        //Time _lastTimeJoystickUsed;
        /*! An id of a joystick which was used last time. */
        std::atomic<int32_t> _lastJoystickId;
        /*! Joystick threshold that will be used to filter JoystickMoved events by its value. */
        std::atomic<float> _joysticksThreshold;
        /*! Input map system which stores and handle control of mapped actions and axes. */
        std::unique_ptr<InputMap> _inputMap;
    };
}
