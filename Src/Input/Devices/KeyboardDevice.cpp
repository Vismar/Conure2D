#include "KeyboardDevice.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyboardDevice::KeyboardDevice()
{
    _buttons.resize(sf::Keyboard::KeyCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonState KeyboardDevice::GetButtonState(KeyboardButton button, const Utility::TimeSpan& timeSpan) const
{
    return _buttons[static_cast<int>(button)].GetState(timeSpan);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyboardDevice::HandleKeyboardEvent(const sf::Event& event, const Utility::Time& time)
{
    // If button was pressed or released, get its code and update state
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        _buttons[event.key.code].UpdateState(ButtonState::Pressed, time);
    }
    else if (event.type == sf::Event::EventType::KeyReleased)
    {
        _buttons[event.key.code].UpdateState(ButtonState::Released, time);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
