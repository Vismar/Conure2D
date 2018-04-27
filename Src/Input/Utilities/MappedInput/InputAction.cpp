#include "InputAction.hpp"
#include "Input/Utilities/ButtonStateHandler.hpp"
#include "Input/InputSystemInterface.hpp"

using namespace Input;

/*****************************************/
/*              ButtonUnion              */
/*****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonUnion::ButtonUnion(const KeyboardButton keyboardButtonValue) : keyboardButton(keyboardButtonValue) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonUnion::ButtonUnion(const MouseButton mouseButtonValue) : mouseButton(mouseButtonValue) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonUnion::ButtonUnion(const JoystickButton joystickButtonValue) : joystickButton(joystickButtonValue) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ButtonUnion::operator==(const ButtonUnion& other) const
{
    return keyboardButton == other.keyboardButton;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*****************************************/
/*              ActionButton             */
/*****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ActionButton::ActionButton(const KeyboardButton keyboardButton) : type(InputType::Keyboard), buttonUnion(keyboardButton) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ActionButton::ActionButton(const MouseButton mouseButton) : type(InputType::Mouse), buttonUnion(mouseButton) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ActionButton::ActionButton(const JoystickButton joystickButton) : type(InputType::Joystick), buttonUnion(joystickButton) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ActionButton::operator==(const ActionButton& other) const
{
    return (type == other.type) && (buttonUnion == other.buttonUnion);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ActionButton::SetButton(const KeyboardButton keyboardButton)
{
    type = InputType::Keyboard;
    buttonUnion.keyboardButton = keyboardButton;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ActionButton::SetButton(const MouseButton mouseButton)
{
    type = InputType::Mouse;
    buttonUnion.mouseButton = mouseButton;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ActionButton::SetButton(const JoystickButton joystickButton)
{
    type = InputType::Joystick;
    buttonUnion.joystickButton = joystickButton;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*****************************************/
/*              InputAction              */
/*****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputAction::InputAction()
: _requiredState(ButtonState::Pressed)
, _button(KeyboardButton::Escape)
, _joystickId(-1)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputAction::InputAction(const ButtonState state, const int joystickId, const ActionButton& actionButton)
: _requiredState(state)
, _button(actionButton)
, _joystickId(joystickId)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputAction::operator==(const InputAction& other) const
{
    return (_requiredState == other._requiredState) && 
           (_button == other._button) && 
           (_joystickId == other._joystickId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputAction::IsActive(const InputSystemInterface& inputSystem) const
{
    bool isActive(false);

    switch (_requiredState)
    {
    case ButtonState::Pressed:
        isActive = _IsButtonPressed(inputSystem);
        break;
    case ButtonState::HeldDown:
        isActive = _IsButtonHeldDown(inputSystem);
        break;
    case ButtonState::Released:
        isActive = _IsButtonReleased(inputSystem);
        break;
    default:
        // Unexpected state
        break;
    }

    return isActive;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputAction::SetRequiredState(const ButtonState state)
{
    _requiredState = state;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputAction::SetRequriedButton(const int joystickId, const ActionButton& actionButton)
{
    _button = actionButton;
    _joystickId = joystickId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputAction::_IsButtonPressed(const InputSystemInterface& inputSystem) const
{
    bool isPressed(false);

    switch (_button.type)
    {
    case InputType::Keyboard:
        isPressed = inputSystem.ButtonPressed(_button.buttonUnion.keyboardButton);
        break;
    case InputType::Mouse:
        isPressed = inputSystem.ButtonPressed(_button.buttonUnion.mouseButton);
        break;
    case InputType::Joystick:
        isPressed = inputSystem.ButtonPressed(_joystickId, _button.buttonUnion.joystickButton);
        break;
    }

    return isPressed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputAction::_IsButtonHeldDown(const InputSystemInterface& inputSystem) const
{
    bool isHelDown(false);

    switch (_button.type)
    {
    case InputType::Keyboard:
        isHelDown = inputSystem.ButtonHeldDown(_button.buttonUnion.keyboardButton);
        break;
    case InputType::Mouse:
        isHelDown = inputSystem.ButtonHeldDown(_button.buttonUnion.mouseButton);
        break;
    case InputType::Joystick:
        isHelDown = inputSystem.ButtonHeldDown(_joystickId, _button.buttonUnion.joystickButton);
        break;
    }

    return isHelDown;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputAction::_IsButtonReleased(const InputSystemInterface& inputSystem) const
{
    bool isReleased(false);

    switch (_button.type)
    {
    case InputType::Keyboard:
        isReleased = inputSystem.ButtonReleased(_button.buttonUnion.keyboardButton);
        break;
    case InputType::Mouse:
        isReleased = inputSystem.ButtonReleased(_button.buttonUnion.mouseButton);
        break;
    case InputType::Joystick:
        isReleased = inputSystem.ButtonReleased(_joystickId, _button.buttonUnion.joystickButton);
        break;
    }

    return isReleased;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
