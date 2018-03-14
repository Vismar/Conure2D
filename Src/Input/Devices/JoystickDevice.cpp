#include "JoystickDevice.hpp"
#include "Utilities/KeyStateHandler.hpp"
#include "Utilities/Keys/JoystickButtons.hpp"
#include "Utilities/Keys/JoystickAxes.hpp"
#include "SFML/Window/Joystick.hpp"
#include "SFML/Window/Event.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JoystickDevice::JoystickDevice() 
    : _buttons(new KeyStateHandler[sf::Joystick::ButtonCount]())
    , _touchedButtons(new bool[sf::Joystick::ButtonCount]())
    , _axes(new std::atomic<float>[sf::Joystick::AxisCount]())
    , _joystickId(-1)
    , _isConnected(false)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JoystickDevice::~JoystickDevice()
{
    delete[] _buttons;
    delete[] _touchedButtons;
    delete[] _axes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void JoystickDevice::SetJoystickId(const unsigned int joystickId)
{
    _joystickId = joystickId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void JoystickDevice::SetJoystickConnectionState(const bool connectionState)
{
    _isConnected = connectionState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyState JoystickDevice::ButtonState(const JoystickButton button) const
{
    return _buttons[static_cast<int>(button)].State();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float JoystickDevice::JoystickAxisPosition(const JoystickAxis axis) const
{
    return _axes[static_cast<int>(axis)];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string JoystickDevice::Name() const
{
    return sf::Joystick::getIdentification(_joystickId).name;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int JoystickDevice::VendorId() const
{
    return sf::Joystick::getIdentification(_joystickId).vendorId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int JoystickDevice::ProductId() const
{
    return sf::Joystick::getIdentification(_joystickId).productId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool JoystickDevice::IsConnected() const
{
    return _isConnected;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void JoystickDevice::HandleJoystickEvents(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::EventType::JoystickButtonPressed:
    case sf::Event::EventType::JoystickButtonReleased:
        _HandleJoystickButtonEvent(event);
        break;
    case sf::Event::EventType::JoystickMoved:
        _HandleJoystickMoveEvent(event);
        break;
    default:
        // Unexpected parameter
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void JoystickDevice::UpdateNotTouchedButtons()
{
    for (auto i = 0; i < sf::Joystick::ButtonCount; ++i)
    {
        if (_touchedButtons[i])
        {
            _touchedButtons[i] = false;
        }
        else
        {
            _buttons[i].UpdateState(KeyState::NotTouched);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void JoystickDevice::_HandleJoystickButtonEvent(const sf::Event& event)
{
    _isConnected = true;
    // If button was pressed or released, get its code and update state
    if (event.type == sf::Event::EventType::JoystickButtonPressed)
    {
        _buttons[event.joystickButton.button].UpdateState(KeyState::Pressed);
        _touchedButtons[event.joystickButton.button] = true;
    }
    else if (event.type == sf::Event::EventType::JoystickButtonReleased)
    {
        _buttons[event.joystickButton.button].UpdateState(KeyState::Released);
        _touchedButtons[event.joystickButton.button] = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void JoystickDevice::_HandleJoystickMoveEvent(const sf::Event& event)
{
    _isConnected = true;
    _axes[event.joystickMove.axis] = event.joystickMove.position / 100.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
