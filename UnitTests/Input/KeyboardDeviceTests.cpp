#include "CppUnitTest.h"
#include "Input/Devices/KeyboardDevice.hpp"
#include "Input/Utilities/Keys/KeyboardKeys.hpp"
#include "Input/Utilities/InputUtilities.hpp"
#include "SFML/Window/Event.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
    TEST_CLASS(KeyboardDeviceTests)
    {
    public:
        TEST_METHOD(KeyEvents)
        {
            KeyboardDevice keyboard;
            sf::Event event;
            
            ///////////////////////////////////////
            // Pressing W key
            event.type = sf::Event::EventType::KeyPressed;
            event.key.code = sf::Keyboard::W;
            // Handle event
            keyboard.HandleKeyboardEvent(event);
            keyboard.UpdateNotTouchedKeys();
            // Check keys
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::W) == KeyState::Pressed);
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::S) == KeyState::NotTouched);

            ///////////////////////////////////////
            // Holding W key and pressing S key
            event.key.code = sf::Keyboard::S;
            // Handle event
            keyboard.HandleKeyboardEvent(event);
            keyboard.UpdateNotTouchedKeys();
            // Check keys
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::W) == KeyState::HeldDown);
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::S) == KeyState::Pressed);

            ///////////////////////////////////////
            // Holding W and S keys
            keyboard.UpdateNotTouchedKeys();
            // Check keys
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::W) == KeyState::HeldDown);
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::S) == KeyState::HeldDown);

            ///////////////////////////////////////
            // Releasing W and S keys
            event.type = sf::Event::EventType::KeyReleased;
            event.key.code = sf::Keyboard::W;
            // Handle events
            keyboard.HandleKeyboardEvent(event);
            event.key.code = sf::Keyboard::S;
            keyboard.HandleKeyboardEvent(event);
            keyboard.UpdateNotTouchedKeys();
            // Check keys
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::W) == KeyState::Released);
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::S) == KeyState::Released);

            ///////////////////////////////////////
            // Do nothing
            keyboard.UpdateNotTouchedKeys();
            // Check keys
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::W) == KeyState::NotTouched);
            Assert::IsTrue(keyboard.KeyState(KeyboardKey::S) == KeyState::NotTouched);
        }
    };
}