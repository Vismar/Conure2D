#include "KeyboardDevice.hpp"
#include "Utilities/KeyStateHandler.hpp"
#include "Utilities//Keys/KeyboardKeys.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Event.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyboardDevice::KeyboardDevice()
    : _keys(new KeyStateHandler[sf::Keyboard::KeyCount]())
    , _touchedKeys(new bool[sf::Keyboard::KeyCount]())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyboardDevice::~KeyboardDevice()
{
    delete[] _keys;
    delete[] _touchedKeys;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyState KeyboardDevice::KeyState(KeyboardKey key) const
{
    return _keys[static_cast<int>(key)].State();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyboardDevice::HandleKeyboardEvent(const sf::Event& event)  
{
    // If key was pressed or released, get its code and update state
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        _keys[event.key.code].UpdateState(KeyState::Pressed);
        _touchedKeys[event.key.code] = true;

    }
    else if (event.type == sf::Event::EventType::KeyReleased)
    {
        _keys[event.key.code].UpdateState(KeyState::Released);
        _touchedKeys[event.key.code] = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyboardDevice::UpdateNotTouchedKeys()
{
    for (auto i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        if (_touchedKeys[i])
        {
            _touchedKeys[i] = false;
        }
        else
        {
            _keys[i].UpdateState(KeyState::NotTouched);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
