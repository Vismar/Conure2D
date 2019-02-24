#include "KeyboardDevice.hpp"

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyboardDevice::KeyboardDevice()
{
    _buttons.resize(sf::Keyboard::KeyCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
ButtonState KeyboardDevice::GetButtonState(KeyboardButton button, const TimeSpan& timeSpan) const
{
    return _buttons[static_cast<int>(button)].GetState(timeSpan);
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyboardDevice::HandleKeyboardEvent(const sf::Event& event)
{
    // If button was pressed or released, get its code and update state
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        //_buttons[event.key.code].UpdateState(ButtonState::Pressed, Time::CurrentTime());
    }
    else if (event.type == sf::Event::EventType::KeyReleased)
    {
        //_buttons[event.key.code].UpdateState(ButtonState::Released, Time::CurrentTime());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
