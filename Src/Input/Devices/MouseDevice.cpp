#include "MouseDevice.hpp"
#include "Utilities/KeyStateHandler.hpp"
#include "Utilities/Keys/MouseButtons.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Event.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MouseDevice::MouseDevice()
    : _buttons(new KeyStateHandler[sf::Mouse::ButtonCount]())
    , _touchedButtons(new bool[sf::Mouse::ButtonCount]())
    , _verticalWheelUpdated(false)
    , _verticalWheelDiff(0.0f)
    , _horizontalWheelUpdated(false)
    , _horizontalWheelDiff(0.0f)
    , _posX(0)
    , _posY(0)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MouseDevice::~MouseDevice()
{
    delete[] _buttons;
    delete[] _touchedButtons;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyState MouseDevice::ButtonState(MouseButton button) const
{
    return _buttons[static_cast<int>(button)].State();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float MouseDevice::VerticalWheelDiff() const
{
    return _verticalWheelDiff;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float MouseDevice::HorizontalWheelDiff() const
{
    return _horizontalWheelDiff;
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

void MouseDevice::HandleMouseEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::EventType::MouseButtonPressed:
    case sf::Event::EventType::MouseButtonReleased:
        _HandleMouseButtonEvent(event);
        break;
    case sf::Event::EventType::MouseWheelScrolled:
        _HandleMouseWheelEvent(event);
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

void MouseDevice::UpdateNotTouchedButtons()
{
    for (auto i = 0; i < sf::Mouse::ButtonCount; ++i)
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

void MouseDevice::UpdateWheels()
{
    // Update vertical wheel
    if (_verticalWheelUpdated)
    {
        _verticalWheelUpdated = false;
    }
    // If wheel was not updated during the update phase, reset wheel difference value
    else
    {
        _verticalWheelDiff = 0.0f;
    }

    //Update horizontal wheel
    if (_horizontalWheelUpdated)
    {
        _horizontalWheelUpdated = false;
    }
    // If wheel was not updated during the update phase, reset wheel difference value
    else
    {
        _horizontalWheelDiff = 0.0f;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MouseDevice::_HandleMouseButtonEvent(const sf::Event& event)
{
    // If button was pressed or released, get its code and update state
    if (event.type == sf::Event::EventType::MouseButtonPressed)
    {
        _buttons[event.mouseButton.button].UpdateState(KeyState::Pressed);
        _touchedButtons[event.mouseButton.button] = true;
    }
    else if (event.type == sf::Event::EventType::MouseButtonReleased)
    {
        _buttons[event.mouseButton.button].UpdateState(KeyState::Released);
        _touchedButtons[event.mouseButton.button] = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MouseDevice::_HandleMouseWheelEvent(const sf::Event& event)
{
    if (event.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel)
    {
        _verticalWheelDiff = event.mouseWheelScroll.delta;
        _verticalWheelUpdated = true;
    }
    else
    {
        _horizontalWheelDiff = event.mouseWheelScroll.delta;
        _horizontalWheelUpdated = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MouseDevice::_HandleMouseMoveEvent(const sf::Event& event)
{
    _posX = event.mouseMove.x;
    _posY = event.mouseMove.y;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
