#include "InputDeviceManager.hpp"
#include "Devices/KeyboardDevice.hpp"
#include "Devices/MouseDevice.hpp"
#include "Devices/JoystickDevice.hpp"
#include "SFML/Window/Event.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputDeviceManager::InputDeviceManager()
    : _keyboard(std::make_shared<KeyboardDevice>())
    , _mouse(std::make_shared<MouseDevice>())
{   
    for (auto i = 0; i < sf::Joystick::Count; ++i)
    {
        _joysticks.emplace_back(std::make_shared<JoystickDevice>());
        _joysticks.back()->SetJoystickId(i);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputDeviceManager::HandleInputEvent(const sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::EventType::KeyPressed:
    case sf::Event::EventType::KeyReleased:
        _keyboard->HandleKeyboardEvent(event);
        break;
    case sf::Event::EventType::MouseButtonPressed:
    case sf::Event::EventType::MouseButtonReleased:
    case sf::Event::EventType::MouseWheelScrolled:
    case sf::Event::EventType::MouseMoved:
        _mouse->HandleMouseEvent(event);
        break;
    case sf::Event::EventType::JoystickConnected:
        _joysticks[event.joystickConnect.joystickId]->SetJoystickConnectionState(true);
        break;
    case sf::Event::EventType::JoystickDisconnected:
        _joysticks[event.joystickConnect.joystickId]->SetJoystickConnectionState(false);
        break;
    case sf::Event::EventType::JoystickButtonPressed:
    case sf::Event::EventType::JoystickButtonReleased:
        _joysticks[event.joystickButton.joystickId]->HandleJoystickEvents(event);
        break;
    case sf::Event::EventType::JoystickMoved:
        _joysticks[event.joystickMove.joystickId]->HandleJoystickEvents(event);
        break;
    default:
        // Unexpected event
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputDeviceManager::FinishUpdate()
{
    _keyboard->UpdateNotTouchedKeys();
    _mouse->UpdateNotTouchedButtons();
    _mouse->UpdateWheels();
    for (auto i = 0; i < sf::Joystick::Count; ++i)
    {
        _joysticks[i]->UpdateNotTouchedButtons();
    }
    sf::Joystick::update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::shared_ptr<KeyboardDevice>& InputDeviceManager::GetKeyboardDevice() const
{
    return _keyboard;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::shared_ptr<MouseDevice>& InputDeviceManager::GetMouseDevice() const
{
    return _mouse;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::shared_ptr<JoystickDevice>& InputDeviceManager::GetJoystickDevice(const int joystickId) const
{
    return _joysticks[joystickId];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
