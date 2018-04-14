#pragma once
#include "Input/InputSystemHandlerInterface.hpp"
#include "Input/InputSystemInterface.hpp"
#include "Input/Devices/KeyboardDevice.hpp"
#include "Input/Devices/MouseDevice.hpp"
#include "Input/Devices/JoystickDevice.hpp"
#include "Input/Utilities/MappedInput/InputMap.hpp"
//#include "Utility/Containers/RingBuffer/RingBuffer.hpp"
#include <memory>

namespace Input
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
    class InputSystem : public InputSystemInterface, public InputSystemHandlerInterface
    {
    public:
        InputSystem(const InputSystem& other) = delete;
        InputSystem(InputSystem&& other) = delete;
        InputSystem& operator=(const InputSystem& other) = delete;
        InputSystem& operator=(InputSystem&& other) = delete;
        InputSystem() = delete;
        ~InputSystem() = default;

        /*!
         * \brief Default constructor.
         * \param logicLoopTimeSpan - time span of logic loop that will be used to check input events.
         */
        InputSystem(const Utility::TimeSpan& logicLoopTimeSpan);

        /*!
         * \brief Handles input events.
         * \param inputEvent - SFML event which will be handled by input system.
         * \param time - time stamp that will be used by input system.
         */
        void HandleInputEvent(const sf::Event& inputEvent, const Utility::Time& time) final;

        /*!
         * \brief Checks if specified button was pressed.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        bool ButtonPressed(const KeyboardButton keyboardButton) const final;
        
        /*!
         * \brief Checks if specified button was pressed.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        bool ButtonPressed(const MouseButton mouseButton) const final;
        
        /*!
         * \brief Checks if specified button was pressed.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was pressed. Otherwise - false.
         */
        bool ButtonPressed(const uint32_t joystickId, const JoystickButton joystickButton) const final;

        /*!
         * \brief Checks if specified button was held down.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        bool ButtonHeldDown(const KeyboardButton keyboardButton) const final;
        
        /*!
         * \brief Checks if specified button was held down.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        bool ButtonHeldDown(const MouseButton mouseButton) const final;
        
        /*!
         * \brief Checks if specified button was held down.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was held down. Otherwise - false.
         */
        bool ButtonHeldDown(const uint32_t joystickId, const JoystickButton joystickButton) const final;

        /*!
         * \brief Checks if specified button was released.
         * \param keyboardButton - keyboard button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        bool ButtonReleased(const KeyboardButton keyboardButton) const final;
        
        /*!
         * \brief Checks if specified button was released.
         * \param mouseButton - mouse button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        bool ButtonReleased(const MouseButton mouseButton) const final;
        
        /*!
         * \brief Checks if specified button was released.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button which will be checked.
         * \return True if specified button was released. Otherwise - false.
         */
        bool ButtonReleased(const uint32_t joystickId, const JoystickButton joystickButton) const final;

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
        JoystickDeviceInterface& Joystick(const uint32_t joystickId) const final;

        /*!
         * \brief Grabs input map.
         * \return Reference to the public interface of input map.
         */
        InputMapInterface& Map() const final;

    private:
        /*! Const reference to the logic loop time span that is used by input system to check button states. */
        const Utility::TimeSpan& _logicLoopTimeSpan;
        /*! Keyboard device which handles keyboard events. */
        std::unique_ptr<KeyboardDevice> _keyboard;
        /*! Mouse device which handles mouse events. */
        std::unique_ptr<MouseDevice> _mouse;
        /*! Array of joystick devices that handles joystick events. */
        std::vector<std::unique_ptr<JoystickDevice>> _joystick;
        /*! Input map system which stores and handle control of mapped actions and axes. */
        std::unique_ptr<InputMap> _inputMap;
        //Utility::RingBuffer<> _inputEvents;
    };
}
