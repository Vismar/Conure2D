#include "CppUnitTest.h"
#include "Input/Managers/InputDeviceManager.hpp"
#include "Input/Devices/KeyboardDevice.hpp"
#include "Input/Devices/MouseDevice.hpp"
#include "Input/Devices/JoystickDevice.hpp"
#include "Input/Utilities/Keys/KeyboardKeys.hpp"
#include "Input/Utilities/Keys/MouseButtons.hpp"
#include "Input/Utilities/Keys/JoystickButtons.hpp"
#include "Input/Utilities/Keys/JoystickAxes.hpp"
#include "Input/Utilities/InputUtilities.hpp"
#include <SFML/Window/Joystick.hpp>
#include "SFML/Window/Event.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
    // These test cases covers basic functionality of KeyStateHandler class.
    // GetMethods - checks if every device can be grabbed from the manager and pointer to it is not nullptr.
    // KeyboardEvents - check events that should be handled by keyboard device.
    // MouseEvents - check events that should be handled by mouse device.
    // JoystickEvents - checks events that should be handled by joystick devices.

    TEST_CLASS(InputDeviceManagerTests)
    {
    public:
        TEST_METHOD(GetMethods)
        {
            InputDeviceManager deviceMng;

            // Keyboard
            Assert::IsTrue(static_cast<bool>(deviceMng.GetKeyboardDevice()));
            // Mouse
            Assert::IsTrue(static_cast<bool>(deviceMng.GetMouseDevice()));
            // Joysticks
            for (auto i = 0; i < sf::Joystick::Count; ++i)
            {
                Assert::IsTrue(static_cast<bool>(deviceMng.GetJoystickDevice(i)));
            }
        }

        TEST_METHOD(KeyboardEvents)
        {
            InputDeviceManager deviceMng;
            const std::shared_ptr<KeyboardDevice>& keyboard = deviceMng.GetKeyboardDevice();
            sf::Event event;

            ///////////////////////////////////////
            // Pressing W key
            event.type = sf::Event::EventType::KeyPressed;
            event.key.code = sf::Keyboard::W;
            // Handle event
            deviceMng.HandleInputEvent(event);
            deviceMng.FinishUpdate();
            // Check keys
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::W) == KeyState::Pressed);

            ///////////////////////////////////////
            // Holding W key and pressing S key
            event.key.code = sf::Keyboard::S;
            // Handle event
            deviceMng.HandleInputEvent(event);
            deviceMng.FinishUpdate();
            // Check keys
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::W) == KeyState::HeldDown);
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::S) == KeyState::Pressed);

            ///////////////////////////////////////
            // Holding W and S keys
            deviceMng.FinishUpdate();
            // Check keys
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::W) == KeyState::HeldDown);
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::S) == KeyState::HeldDown);

            ///////////////////////////////////////
            // Releasing W and S keys
            event.type = sf::Event::EventType::KeyReleased;
            event.key.code = sf::Keyboard::W;
            // Handle events
            deviceMng.HandleInputEvent(event);
            event.key.code = sf::Keyboard::S;
            deviceMng.HandleInputEvent(event);
            deviceMng.FinishUpdate();
            // Check keys
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::W) == KeyState::Released);
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::S) == KeyState::Released);

            ///////////////////////////////////////
            // Do nothing
            deviceMng.FinishUpdate();
            // Check keys
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::W) == KeyState::NotTouched);
            Assert::IsTrue(keyboard->KeyState(KeyboardKey::S) == KeyState::NotTouched);
        }

        TEST_METHOD(MouseEvents)
        {
            InputDeviceManager deviceMng;
            const std::shared_ptr<MouseDevice>& mouse = deviceMng.GetMouseDevice();
            sf::Event event;
            
            // Buttons events
            {
                ///////////////////////////////////////
                // Pressing Left mouse button
                event.type = sf::Event::EventType::MouseButtonPressed;
                event.mouseButton.button = sf::Mouse::Button::Left;
                // Handle event
                deviceMng.HandleInputEvent(event);
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(mouse->ButtonState(MouseButton::Left) == KeyState::Pressed);
                Assert::IsTrue(mouse->ButtonState(MouseButton::Right) == KeyState::NotTouched);

                ///////////////////////////////////////
                // Holding Left mouse button and pressing Right mouse button
                event.mouseButton.button = sf::Mouse::Button::Right;
                // Handle event
                deviceMng.HandleInputEvent(event);
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(mouse->ButtonState(MouseButton::Left) == KeyState::HeldDown);
                Assert::IsTrue(mouse->ButtonState(MouseButton::Right) == KeyState::Pressed);

                ///////////////////////////////////////
                // Holding Left and Right mouse buttons
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(mouse->ButtonState(MouseButton::Left) == KeyState::HeldDown);
                Assert::IsTrue(mouse->ButtonState(MouseButton::Right) == KeyState::HeldDown);

                ///////////////////////////////////////
                // Releasing Left and Right mouse buttons
                event.type = sf::Event::EventType::MouseButtonReleased;
                event.mouseButton.button = sf::Mouse::Button::Left;
                // Handle event
                deviceMng.HandleInputEvent(event);
                event.mouseButton.button = sf::Mouse::Button::Right;
                deviceMng.HandleInputEvent(event);
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(mouse->ButtonState(MouseButton::Left) == KeyState::Released);
                Assert::IsTrue(mouse->ButtonState(MouseButton::Right) == KeyState::Released);

                ///////////////////////////////////////
                // Do nothing
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(mouse->ButtonState(MouseButton::Left) == KeyState::NotTouched);
                Assert::IsTrue(mouse->ButtonState(MouseButton::Right) == KeyState::NotTouched);
            }
            
            // Wheel events
            {
                const float wheelDiff(20.0f);

                ///////////////////////////////////////
                // Mouse wheel scroll event for vertical wheel
                event.type = sf::Event::EventType::MouseWheelScrolled;
                event.mouseWheelScroll.wheel = sf::Mouse::VerticalWheel;
                event.mouseWheelScroll.delta = wheelDiff;
                // Handle event
                deviceMng.HandleInputEvent(event);
                deviceMng.FinishUpdate();
                // Check wheel values
                Assert::IsTrue(mouse->VerticalWheelDiff() == wheelDiff);
                Assert::IsTrue(mouse->HorizontalWheelDiff() == 0.0f);

                ///////////////////////////////////////
                // Mouse wheel scroll event for horizontal wheel
                event.mouseWheelScroll.wheel = sf::Mouse::HorizontalWheel;
                // Handle event
                deviceMng.HandleInputEvent(event);
                deviceMng.FinishUpdate();
                // Check wheel values
                Assert::IsTrue(mouse->VerticalWheelDiff() == 0.0f);
                Assert::IsTrue(mouse->HorizontalWheelDiff() == wheelDiff);

                ///////////////////////////////////////
                // Mouse wheel scroll event for none of the two wheels
                // Handle events
                deviceMng.FinishUpdate();
                // Check wheel values
                Assert::IsTrue(mouse->VerticalWheelDiff() == 0.0f);
                Assert::IsTrue(mouse->HorizontalWheelDiff() == 0.0f);
            }

            // Move events
            {
                event.type = sf::Event::EventType::MouseMoved;
                int x = 100;
                int y = 100;

                ///////////////////////////////////////
                // Mouse move event
                event.mouseMove.x = x;
                event.mouseMove.y = y;
                // Handle event
                deviceMng.HandleInputEvent(event);
                // Check mouse position
                Assert::IsTrue(mouse->PositionX() == x);
                Assert::IsTrue(mouse->PositionY() == y);

                ///////////////////////////////////////
                // Mouse move event
                event.mouseMove.x = x = 359;
                event.mouseMove.y = y = 165;
                // Handle event
                deviceMng.HandleInputEvent(event);
                // Check mouse position
                Assert::IsTrue(mouse->PositionX() == x);
                Assert::IsTrue(mouse->PositionY() == y);
            }
        }

        TEST_METHOD(JoystickEvents)
        {
            InputDeviceManager deviceMng;
            sf::Event event;
            
            ///////////////////////////////////////
            // Joystick ids
            for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
            {
                Assert::IsTrue(deviceMng.GetJoystickDevice(i)->_joystickId == i);
            }

            // Connection events
            {
                event.type = sf::Event::EventType::JoystickConnected;
                event.joystickConnect.joystickId = 5;
                deviceMng.HandleInputEvent(event);
                Assert::IsTrue(deviceMng.GetJoystickDevice(5)->IsConnected());
                event.type = sf::Event::EventType::JoystickDisconnected;
                deviceMng.HandleInputEvent(event);
                Assert::IsFalse(deviceMng.GetJoystickDevice(5)->IsConnected());
            }

            // Button events
            {
                ///////////////////////////////////////
                // Pressing Button0
                event.type = sf::Event::EventType::JoystickButtonPressed;
                event.joystickButton.joystickId = 1;
                event.joystickButton.button = static_cast<int>(JoystickButton::Button0);
                // Handle event
                deviceMng.HandleInputEvent(event);
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->IsConnected());
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button0) == KeyState::Pressed);
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button1) == KeyState::NotTouched);

                ///////////////////////////////////////
                // Holding Button0 key and pressing Button1
                event.joystickButton.button = static_cast<int>(JoystickButton::Button1);
                // Handle event
                deviceMng.HandleInputEvent(event);
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button0) == KeyState::HeldDown);
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button1) == KeyState::Pressed);

                ////////////////////////////////////////
                // Holding Button0 and Button1
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button0) == KeyState::HeldDown);
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button1) == KeyState::HeldDown);

                ///////////////////////////////////////
                // Releasing Button0 and Button1
                event.type = sf::Event::EventType::JoystickButtonReleased;
                event.joystickButton.button = static_cast<int>(JoystickButton::Button0);
                // Handle events
                deviceMng.HandleInputEvent(event);
                event.joystickButton.button = static_cast<int>(JoystickButton::Button1);
                deviceMng.HandleInputEvent(event);
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button0) == KeyState::Released);
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button1) == KeyState::Released);

                ///////////////////////////////////////
                // Do nothing
                deviceMng.FinishUpdate();
                // Check buttons
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button0) == KeyState::NotTouched);
                Assert::IsTrue(deviceMng.GetJoystickDevice(1)->ButtonState(JoystickButton::Button1) == KeyState::NotTouched);
            }

            // Axis events
            {
                ///////////////////////////////////////
                // Moving axis
                event.type = sf::Event::EventType::JoystickMoved;
                event.joystickMove.joystickId = 3;
                event.joystickMove.axis = static_cast<sf::Joystick::Axis>(JoystickAxis::X);
                event.joystickMove.position = 50.0f;
                // Handle event
                deviceMng.HandleInputEvent(event);
                Assert::IsTrue(deviceMng.GetJoystickDevice(3)->IsConnected());
                // Check axis
                Assert::IsTrue(deviceMng.GetJoystickDevice(3)->JoystickAxisPosition(JoystickAxis::X) == 50.0f / 100.0f);
            }
        }
    };
}