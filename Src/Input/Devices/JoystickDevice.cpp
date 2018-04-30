#include "JoystickDevice.hpp"
#include <SFML/Window/Joystick.hpp>

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JoystickDevice::JoystickDevice() 
: _axes(new std::atomic<float>[sf::Joystick::AxisCount]())
, _joystickId(-1)
, _isConnected(false)
{
    _buttons.resize(sf::Joystick::ButtonCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JoystickDevice::JoystickDevice(const JoystickDevice& other)
: _axes(new std::atomic<float>[sf::Joystick::AxisCount]())
, _joystickId(-1)
, _isConnected(false)
{
    _buttons.resize(sf::Joystick::ButtonCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JoystickDevice::~JoystickDevice()
{
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

ButtonState JoystickDevice::GetButtonState(const JoystickButton button, const Utility::TimeSpan& timeSpan) const
{
    return _buttons[static_cast<int>(button)].GetState(timeSpan);
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

uint32_t JoystickDevice::VendorId() const
{
    return sf::Joystick::getIdentification(_joystickId).vendorId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t JoystickDevice::ProductId() const
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

void JoystickDevice::_HandleJoystickButtonEvent(const sf::Event& event)
{
    _isConnected = true;

    // If button was pressed or released, get its code and update state
    if (event.type == sf::Event::EventType::JoystickButtonPressed)
    {
        _buttons[event.joystickButton.button].UpdateState(ButtonState::Pressed, Utility::Time::CurrentTime());
    }
    else if (event.type == sf::Event::EventType::JoystickButtonReleased)
    {
        _buttons[event.joystickButton.button].UpdateState(ButtonState::Released, Utility::Time::CurrentTime());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void JoystickDevice::_HandleJoystickMoveEvent(const sf::Event& event)
{
    _isConnected = true;
    _axes[event.joystickMove.axis] = event.joystickMove.position / 100.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
