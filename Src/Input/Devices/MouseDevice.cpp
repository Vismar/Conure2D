#include "MouseDevice.hpp"
#include <SFML/Window/Mouse.hpp>

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MouseDevice::MouseDevice()
: _verticalWheelDiff(0.0f)
, _horizontalWheelDiff(0.0f)
, _posX(0)
, _posY(0)
{
    _buttons.resize(sf::Mouse::ButtonCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonState MouseDevice::GetButtonState(MouseButton button, const Utility::TimeSpan& timeSpan) const
{
    return _buttons[static_cast<int>(button)].GetState(timeSpan);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float MouseDevice::VerticalWheelDiff(const Utility::TimeSpan& timeSpan) const
{
    float wheelDiff(0.0f);

    if ((timeSpan.Start() <= _verticalWheelMovedTime) && (_verticalWheelMovedTime <= timeSpan.End()))
    {
        wheelDiff = _verticalWheelDiff;
    }

    return wheelDiff;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float MouseDevice::HorizontalWheelDiff(const Utility::TimeSpan& timeSpan) const
{
    float wheelDiff(0.0f);

    if ((timeSpan.Start() <= _horizontalWheelMovedTime) && (_horizontalWheelMovedTime <= timeSpan.End()))
    {
        wheelDiff = _horizontalWheelDiff;
    }

    return wheelDiff;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int MouseDevice::PositionX() const
{
    return _posX;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int MouseDevice::PositionY() const
{
    return _posY;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MouseDevice::HandleMouseEvent(const sf::Event& event, const Utility::Time& time)
{
    switch (event.type)
    {
    case sf::Event::EventType::MouseButtonPressed:
    case sf::Event::EventType::MouseButtonReleased:
        _HandleMouseButtonEvent(event, time);
        break;
    case sf::Event::EventType::MouseWheelScrolled:
        _HandleMouseWheelEvent(event, time);
        break;
    case sf::Event::EventType::MouseMoved:
        _HandleMouseMoveEvent(event);
        break;
    default:
        // Unexpected parameter
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MouseDevice::_HandleMouseButtonEvent(const sf::Event& event, const Utility::Time& time)
{
    // If button was pressed or released, get its code and update state
    if (event.type == sf::Event::EventType::MouseButtonPressed)
    {
        _buttons[event.mouseButton.button].UpdateState(ButtonState::Pressed, time);
    }
    else if (event.type == sf::Event::EventType::MouseButtonReleased)
    {
        _buttons[event.mouseButton.button].UpdateState(ButtonState::Released, time);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MouseDevice::_HandleMouseWheelEvent(const sf::Event& event, const Utility::Time& time)
{
    if (event.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel)
    {
        _verticalWheelDiff = event.mouseWheelScroll.delta;
        _verticalWheelMovedTime = time;
    }
    else
    {
        _horizontalWheelDiff = event.mouseWheelScroll.delta;
        _horizontalWheelMovedTime = time;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MouseDevice::_HandleMouseMoveEvent(const sf::Event& event)
{
    _posX = event.mouseMove.x;
    _posY = event.mouseMove.y;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
