#include "KeyStateHandler.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyStateHandler::KeyStateHandler() : _keyState(KeyState::NotTouched) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyState KeyStateHandler::State() const
{
    return _keyState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KeyStateHandler::UpdateState(const KeyState keyState)
{
    switch (keyState)
    {
    case KeyState::Pressed:
        // If key was pressed currently but previously was released or not even touched then change state to KeyState::Pressed
        if (_keyState == KeyState::NotTouched || _keyState == KeyState::Released)
        {
            _keyState = KeyState::Pressed;
        }
        break;
    case KeyState::Released:
        _keyState = KeyState::Released;
        break;
    case KeyState::NotTouched:
        // If key was not touched currently but previously was pressed then change state to KeyState::HeldDown
        if (_keyState == KeyState::Pressed)
        {
            _keyState = KeyState::HeldDown;
        }
        // If key was not touched currently but previously was released then change state to KeyState::NotTouched
        else if (_keyState == KeyState::Released)
        {
            _keyState = KeyState::NotTouched;
        }
        break;
    default:
        // Unexpected parameter
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////