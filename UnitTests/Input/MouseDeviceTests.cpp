#include "CppUnitTest.h"
#include "Input/Devices/MouseDevice.hpp"
#include "Input/Utilities/Keys/MouseButtons.hpp"
#include "Input/Utilities/InputUtilities.hpp"
#include "SFML/Window/Event.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
    // These test cases covers basic functionality of MouseDeviceTests class.
    // ButtonEvents - checks button events (pressed/held/released)
    // WheelEvents - checks wheel events
    // PositionEvents - checks move events

    TEST_CLASS(MouseDeviceTests)
    {
    public:
        TEST_METHOD(ButtonEvents)
        {
            MouseDevice mouse;
            sf::Event event;

            ///////////////////////////////////////
            // Pressing Left mouse button
            event.type = sf::Event::EventType::MouseButtonPressed;
            event.mouseButton.button = sf::Mouse::Button::Left;
            // Handle event
            mouse.HandleMouseEvent(event);
            mouse.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(mouse.ButtonState(MouseButton::Left) == KeyState::Pressed);
            Assert::IsTrue(mouse.ButtonState(MouseButton::Right) == KeyState::NotTouched);

            ///////////////////////////////////////
            // Holding Left mouse button and pressing Right mouse button
            event.mouseButton.button = sf::Mouse::Button::Right;
            // Handle event
            mouse.HandleMouseEvent(event);
            mouse.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(mouse.ButtonState(MouseButton::Left) == KeyState::HeldDown);
            Assert::IsTrue(mouse.ButtonState(MouseButton::Right) == KeyState::Pressed);

            ///////////////////////////////////////
            // Holding Left and Right mouse buttons
            mouse.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(mouse.ButtonState(MouseButton::Left) == KeyState::HeldDown);
            Assert::IsTrue(mouse.ButtonState(MouseButton::Right) == KeyState::HeldDown);

            ///////////////////////////////////////
            // Releasing Left and Right mouse buttons
            event.type = sf::Event::EventType::MouseButtonReleased;
            event.mouseButton.button = sf::Mouse::Button::Left;
            // Handle event
            mouse.HandleMouseEvent(event);
            event.mouseButton.button = sf::Mouse::Button::Right;
            mouse.HandleMouseEvent(event);
            mouse.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(mouse.ButtonState(MouseButton::Left) == KeyState::Released);
            Assert::IsTrue(mouse.ButtonState(MouseButton::Right) == KeyState::Released);

            ///////////////////////////////////////
            // Do nothing
            mouse.UpdateNotTouchedButtons();
            // Check buttons
            Assert::IsTrue(mouse.ButtonState(MouseButton::Left) == KeyState::NotTouched);
            Assert::IsTrue(mouse.ButtonState(MouseButton::Right) == KeyState::NotTouched);
        }

        TEST_METHOD(WheelEvents)
        {
            MouseDevice mouse;
            sf::Event event;
            const float wheelDiff(20.0f);
            
            ///////////////////////////////////////
            // Mouse wheel scroll event for vertical wheel
            event.type = sf::Event::EventType::MouseWheelScrolled;
            event.mouseWheelScroll.wheel = sf::Mouse::VerticalWheel;
            event.mouseWheelScroll.delta = wheelDiff;
            // Handle event
            mouse.HandleMouseEvent(event);
            mouse.UpdateWheels();
            // Check wheel values
            Assert::IsTrue(mouse.VerticalWheelDiff() == wheelDiff);
            Assert::IsTrue(mouse.HorizontalWheelDiff() == 0.0f);

            ///////////////////////////////////////
            // Mouse wheel scroll event for horizontal wheel
            event.mouseWheelScroll.wheel = sf::Mouse::HorizontalWheel;
            // Handle event
            mouse.HandleMouseEvent(event);
            mouse.UpdateWheels();
            // Check wheel values
            Assert::IsTrue(mouse.VerticalWheelDiff() == 0.0f);
            Assert::IsTrue(mouse.HorizontalWheelDiff() == wheelDiff);

            ///////////////////////////////////////
            // Mouse wheel scroll event for none of the two wheels
            // Handle events
            mouse.UpdateWheels();
            // Check wheel values
            Assert::IsTrue(mouse.VerticalWheelDiff() == 0.0f);
            Assert::IsTrue(mouse.HorizontalWheelDiff() == 0.0f);
        }

        TEST_METHOD(PositionEvents)
        {
            MouseDevice mouse;
            sf::Event event;
            event.type = sf::Event::EventType::MouseMoved;
            int x = 100;
            int y = 100;
            
            ///////////////////////////////////////
            // Mouse move event
            event.mouseMove.x = x;
            event.mouseMove.y = y;
            // Handle event
            mouse.HandleMouseEvent(event);
            // Check mouse position
            Assert::IsTrue(mouse.PositionX() == x);
            Assert::IsTrue(mouse.PositionY() == y);

            ///////////////////////////////////////
            // Mouse move event
            event.mouseMove.x = x = 359;
            event.mouseMove.y = y = 165;
            // Handle event
            mouse.HandleMouseEvent(event);
            // Check mouse position
            Assert::IsTrue(mouse.PositionX() == x);
            Assert::IsTrue(mouse.PositionY() == y);
        }
    };
}