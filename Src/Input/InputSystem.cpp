#include "InputSystem.hpp"
#include <SFML/Window/Event.hpp>

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputSystem::InputSystem(const Utility::TimeSpan& logicLoopTimeSpan) 
    : _logicLoopTimeSpan(logicLoopTimeSpan)
    , _keyboard(std::make_unique<KeyboardDevice>())
    , _mouse(std::make_unique<MouseDevice>())
    , _lastJoystickId(-1)
    , _inputMap(std::make_unique<InputMap>(*this))
{
    _joystick.resize(sf::Joystick::Count);
    for (auto& joystick : _joystick)
    {
        joystick = std::make_unique<JoystickDevice>();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputSystem::HandleInputEvent(const sf::Event& inputEvent, const Utility::Time& time)
{
    switch (inputEvent.type)
    {
    case sf::Event::EventType::KeyPressed:
    case sf::Event::EventType::KeyReleased:
        _keyboard->HandleKeyboardEvent(inputEvent, time);
        break;
    case sf::Event::EventType::MouseButtonPressed:
    case sf::Event::EventType::MouseButtonReleased:
    case sf::Event::EventType::MouseWheelScrolled:
    case sf::Event::EventType::MouseMoved:
        _mouse->HandleMouseEvent(inputEvent, time);
        break;
    case sf::Event::EventType::JoystickConnected:
        _joystick[inputEvent.joystickConnect.joystickId]->SetJoystickConnectionState(true);
        break;
    case sf::Event::EventType::JoystickDisconnected:
        _joystick[inputEvent.joystickConnect.joystickId]->SetJoystickConnectionState(false);
        break;
    case sf::Event::EventType::JoystickButtonPressed:
    case sf::Event::EventType::JoystickButtonReleased:
        _joystick[inputEvent.joystickButton.joystickId]->HandleJoystickEvents(inputEvent, time);
        // Update joystick id which was used and time when it happened
        _lastTimeJoystickUsed = time;
        _lastJoystickId = inputEvent.joystickButton.joystickId;        
        break;
    case sf::Event::EventType::JoystickMoved:
        _joystick[inputEvent.joystickMove.joystickId]->HandleJoystickEvents(inputEvent, time);
        // Update joystick id which was used and time when it happened
        _lastTimeJoystickUsed = time;
        _lastJoystickId = inputEvent.joystickButton.joystickId;
        break;
    default:
        // Unexpected event
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonPressed(const KeyboardButton keyboardButton) const
{
    return (_keyboard->GetButtonState(keyboardButton, _logicLoopTimeSpan) == ButtonState::Pressed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonPressed(const MouseButton mouseButton) const
{
    return (_mouse->GetButtonState(mouseButton, _logicLoopTimeSpan) == ButtonState::Pressed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonPressed(const uint32_t joystickId, const JoystickButton joystickButton) const
{
    return (_joystick[joystickId]->GetButtonState(joystickButton, _logicLoopTimeSpan) == ButtonState::Pressed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonHeldDown(const KeyboardButton keyboardButton) const
{
    return (_keyboard->GetButtonState(keyboardButton, _logicLoopTimeSpan) == ButtonState::HeldDown);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonHeldDown(const MouseButton mouseButton) const
{
    return (_mouse->GetButtonState(mouseButton, _logicLoopTimeSpan) == ButtonState::HeldDown);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonHeldDown(const uint32_t joystickId, const JoystickButton joystickButton) const
{
    return (_joystick[joystickId]->GetButtonState(joystickButton, _logicLoopTimeSpan) == ButtonState::HeldDown);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonReleased(const KeyboardButton keyboardButton) const
{
    return (_keyboard->GetButtonState(keyboardButton, _logicLoopTimeSpan) == ButtonState::Released);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonReleased(const MouseButton mouseButton) const
{
    return (_mouse->GetButtonState(mouseButton, _logicLoopTimeSpan) == ButtonState::Released);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonReleased(const uint32_t joystickId, const JoystickButton joystickButton) const
{
    return (_joystick[joystickId]->GetButtonState(joystickButton, _logicLoopTimeSpan) == ButtonState::Released);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::AnyButtonPressed() const
{
    return _AnyButtonState(ButtonState::Pressed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::AnyButtonHeldDown() const
{
    return _AnyButtonState(ButtonState::HeldDown);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::AnyButtonReleased() const
{
    return _AnyButtonState(ButtonState::Released);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MouseDeviceInterface& InputSystem::Mouse() const
{
    return *_mouse;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JoystickDeviceInterface& InputSystem::Joystick(const uint32_t joystickId) const
{
    return *_joystick[joystickId];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int32_t InputSystem::LastJoystickUsed() const
{
    auto joystickId(-1);

    if (_logicLoopTimeSpan.Start() <= _lastTimeJoystickUsed)
    {
        joystickId = _lastJoystickId;
    }

    return joystickId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputMapInterface& InputSystem::Map() const
{
    return *_inputMap;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::_AnyButtonState(const ButtonState state) const
{
    bool anyButtonInState(false);

    // Check if any keyboard button was in specified state
    for (auto i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        if (_keyboard->GetButtonState(static_cast<KeyboardButton>(i), _logicLoopTimeSpan) == state)
        {
            anyButtonInState = true;
            break;
        }
    }

    // If keyboard button was not in specified state, check mouse buttons
    if (!anyButtonInState)
    {
        for (auto i = 0; i < sf::Mouse::ButtonCount; ++i)
        {
            if (_mouse->GetButtonState(static_cast<MouseButton>(i), _logicLoopTimeSpan) == state)
            {
                anyButtonInState = true;
                break;
            }
        }
    }

    return anyButtonInState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
