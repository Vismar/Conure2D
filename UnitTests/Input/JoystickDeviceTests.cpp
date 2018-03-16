#include "CppUnitTest.h"
#include "Input/Devices/JoystickDevice.hpp"
#include "Input/Utilities/Keys/JoystickButtons.hpp"
#include "Input/Utilities/Keys/JoystickAxes.hpp"
#include "Input/Utilities/InputUtilities.hpp"
#include "SFML/Window/Event.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
    // These test cases covers basic functionality of JoystickDeviceTests class.
    // SetMethods - check set methods
    // ButtonEvents - checks button events (pressed/held/released)
    // AxisEvent - checks axis events

    TEST_CLASS(JoystickDeviceTests)
    {
    public:
        TEST_METHOD(SetMethods)
        {
            JoystickDevice joystick;

            ///////////////////////////////////////
            // Set joystick id
            joystick.SetJoystickId(2);
            Assert::IsTrue(joystick._joystickId == 2);

            ///////////////////////////////////////
            // Set joystick connection state
            joystick.SetJoystickConnectionState(true);
            Assert::IsTrue(joystick.IsConnected());
        }

        TEST_METHOD(ButtonEvents)
        {
            JoystickDevice joystick;
            sf::Event event;

            ///////////////////////////////////////
            // Pressing Button0
            event.type = sf::Event::EventType::JoystickButtonPressed;
            event.joystickButton.button = static_cast<int>(JoystickButton::Button0);
            // Handle event
            joystick.HandleJoystickEvents(event);
            joystick.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button0) == KeyState::Pressed);
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button1) == KeyState::NotTouched);

            ///////////////////////////////////////
            // Holding Button0 key and pressing Button1
            event.joystickButton.button = static_cast<int>(JoystickButton::Button1);
            // Handle event
            joystick.HandleJoystickEvents(event);
            joystick.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button0) == KeyState::HeldDown);
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button1) == KeyState::Pressed);
            
            ////////////////////////////////////////
            // Holding Button0 and Button1
            joystick.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button0) == KeyState::HeldDown);
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button1) == KeyState::HeldDown);

            ///////////////////////////////////////
            // Releasing Button0 and Button1
            event.type = sf::Event::EventType::JoystickButtonReleased;
            event.joystickButton.button = static_cast<int>(JoystickButton::Button0);
            // Handle events
            joystick.HandleJoystickEvents(event);
            event.joystickButton.button = static_cast<int>(JoystickButton::Button1);
            joystick.HandleJoystickEvents(event);
            joystick.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button0) == KeyState::Released);
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button1) == KeyState::Released);

            ///////////////////////////////////////
            // Do nothing
            joystick.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button0) == KeyState::NotTouched);
            Assert::IsTrue(joystick.ButtonState(JoystickButton::Button1) == KeyState::NotTouched);
        }

        TEST_METHOD(AxisEvent)
        {
            JoystickDevice joystick;
            sf::Event event;
            
            ///////////////////////////////////////
            // Moving axis
            event.type = sf::Event::EventType::JoystickMoved;
            event.joystickMove.axis = static_cast<sf::Joystick::Axis>(JoystickAxis::X);
            event.joystickMove.position = 50.0f;
            // Handle event
            joystick.HandleJoystickEvents(event);
            // Check axis
            Assert::IsTrue(joystick.JoystickAxisPosition(JoystickAxis::X) == 50.0f / 100.0f);
        }
    };
}