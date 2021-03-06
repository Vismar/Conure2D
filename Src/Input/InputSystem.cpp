#include "InputSystem.hpp"
#include <SFML/Window/Event.hpp>

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
InputSystem::InputSystem(const TimeSpan& logicLoopTimeSpan)
: _logicLoopTimeSpan(logicLoopTimeSpan)
, _keyboard(std::make_unique<KeyboardDevice>())
, _mouse(std::make_unique<MouseDevice>())
, _lastJoystickId(-1)
, _joysticksThreshold(0.1f)
, _inputMap(std::make_unique<InputMap>(*this))
{
    _joystick.resize(sf::Joystick::Count);
    for (auto& joystick : _joystick)
    {
        joystick = std::make_unique<JoystickDevice>();
    }
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputSystem::HandleInputEvent(const sf::Event& inputEvent)
{
    switch (inputEvent.type)
    {
    case sf::Event::EventType::KeyPressed:
    case sf::Event::EventType::KeyReleased:
        _keyboard->HandleKeyboardEvent(inputEvent);
        break;
    case sf::Event::EventType::MouseButtonPressed:
    case sf::Event::EventType::MouseButtonReleased:
    case sf::Event::EventType::MouseWheelScrolled:
    case sf::Event::EventType::MouseMoved:
        _mouse->HandleMouseEvent(inputEvent);
        break;
    case sf::Event::EventType::JoystickConnected:
        _joystick[inputEvent.joystickConnect.joystickId]->SetJoystickConnectionState(true);
        break;
    case sf::Event::EventType::JoystickDisconnected:
        _joystick[inputEvent.joystickConnect.joystickId]->SetJoystickConnectionState(false);
        break;
    case sf::Event::EventType::JoystickButtonPressed:
    case sf::Event::EventType::JoystickButtonReleased:
        _joystick[inputEvent.joystickButton.joystickId]->HandleJoystickEvents(inputEvent);
        // Update joystick id which was used and time when it happened
        //_lastTimeJoystickUsed = Time::CurrentTime();
        _lastJoystickId = inputEvent.joystickButton.joystickId;        
        break;
    case sf::Event::EventType::JoystickMoved:
        // Check JoystickMove event values to fits the threshold        
        if (std::abs(inputEvent.joystickMove.position) >= _joysticksThreshold.load())
        {
            _joystick[inputEvent.joystickMove.joystickId]->HandleJoystickEvents(inputEvent);
            // Update joystick id which was used and time when it happened
            //_lastTimeJoystickUsed = Time::CurrentTime();
            _lastJoystickId = inputEvent.joystickButton.joystickId;
        }
        break;
    default:
        // Unexpected event
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonPressed(const KeyboardButton keyboardButton) const
{
    return false;
    //return (_keyboard->GetButtonState(keyboardButton, _logicLoopTimeSpan) == ButtonState::Pressed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonPressed(const MouseButton mouseButton) const
{
    return false;
    //return (_mouse->GetButtonState(mouseButton, _logicLoopTimeSpan) == ButtonState::Pressed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonPressed(const uint32_t joystickId, const JoystickButton joystickButton) const
{

    return false;
    //return (_joystick[joystickId]->GetButtonState(joystickButton, _logicLoopTimeSpan) == ButtonState::Pressed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonHeldDown(const KeyboardButton keyboardButton) const
{

    return false;
    //return (_keyboard->GetButtonState(keyboardButton, _logicLoopTimeSpan) == ButtonState::HeldDown);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonHeldDown(const MouseButton mouseButton) const
{

    return false;
    //return (_mouse->GetButtonState(mouseButton, _logicLoopTimeSpan) == ButtonState::HeldDown);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonHeldDown(const uint32_t joystickId, const JoystickButton joystickButton) const
{

    return false;
    //return (_joystick[joystickId]->GetButtonState(joystickButton, _logicLoopTimeSpan) == ButtonState::HeldDown);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonReleased(const KeyboardButton keyboardButton) const
{

    return false;
    //return (_keyboard->GetButtonState(keyboardButton, _logicLoopTimeSpan) == ButtonState::Released);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonReleased(const MouseButton mouseButton) const
{
    return false;
    //return (_mouse->GetButtonState(mouseButton, _logicLoopTimeSpan) == ButtonState::Released);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputSystem::ButtonReleased(const uint32_t joystickId, const JoystickButton joystickButton) const
{
    return false;
    //return (_joystick[joystickId]->GetButtonState(joystickButton, _logicLoopTimeSpan) == ButtonState::Released);
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

    /*if (_logicLoopTimeSpan.Start() <= _lastTimeJoystickUsed)
    {
        joystickId = _lastJoystickId.load();
    }*/

    return joystickId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputSystem::SetJoystickThreshold(const float newThreshold)
{
    if (0.0f <= newThreshold || newThreshold <= 100.0f)
    {
        _joysticksThreshold = newThreshold;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float InputSystem::GetJoystickThreshold() const
{
    return _joysticksThreshold.load();
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
        /*if (_keyboard->GetButtonState(static_cast<KeyboardButton>(i), _logicLoopTimeSpan) == state)
        {
            anyButtonInState = true;
            break;
        }*/
    }

    // If keyboard button was not in specified state, check mouse buttons
    if (!anyButtonInState)
    {
        for (auto i = 0; i < sf::Mouse::ButtonCount; ++i)
        {
            /*if (_mouse->GetButtonState(static_cast<MouseButton>(i), _logicLoopTimeSpan) == state)
            {
                anyButtonInState = true;
                break;
            }*/
        }
    }

    return anyButtonInState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
