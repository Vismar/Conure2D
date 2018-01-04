#include "InputAction.hpp"
#include "DirectInput.hpp"

using namespace Input;

/*****************************************/
/*              ButtonUnion              */
/*****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonUnion::ButtonUnion(const KeyboardKey keyValue) : key(keyValue) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonUnion::ButtonUnion(const MouseButton mouseButtonValue) : mouseButton(mouseButtonValue) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonUnion::ButtonUnion(const JoystickButton joystickButtonValue) : joystickButton(joystickButtonValue) { }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ButtonUnion::operator==(const ButtonUnion& other) const
{
    return key == other.key;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*****************************************/
/*              ActionButton             */
/*****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ActionButton::ActionButton(const KeyboardKey key) : type(InputType::Keyboard), buttonUnion(key) { }

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

void ActionButton::SetButton(const KeyboardKey key)
{
    type = InputType::Keyboard;
    buttonUnion.key = key;
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
    : _requiredState(KeyState::Pressed)
    , _button(KeyboardKey::Escape)
    , _joystickId(-1)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputAction::InputAction(const KeyState& state, const int joystickId, const ActionButton& actionButton)
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

bool InputAction::IsActive() const
{
    bool isActive(false);

    switch (_requiredState)
    {
    case KeyState::Pressed:
        isActive = _IsButtonPressed();
        break;
    case KeyState::HeldDown:
        isActive = _IsButtonHeldDown();
        break;
    case KeyState::Released:
        isActive = _IsButtonReleased();
        break;
    default:
        // Unexpected state
        break;
    }

    return isActive;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputAction::SetRequiresState(const KeyState& state)
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

bool InputAction::_IsButtonPressed() const
{
    bool isPressed(false);

    switch (_button.type)
    {
    case InputType::Keyboard:
        isPressed = DirectInput::IsKeyPressed(_button.buttonUnion.key);
        break;
    case InputType::Mouse:
        isPressed = DirectInput::IsMouseButtonPressed(_button.buttonUnion.mouseButton);
        break;
    case InputType::Joystick:
        isPressed = DirectInput::IsJoystickButtonPressed(_joystickId, _button.buttonUnion.joystickButton);
        break;
    }

    return isPressed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputAction::_IsButtonHeldDown() const
{
    bool isHelDown(false);

    switch (_button.type)
    {
    case InputType::Keyboard:
        isHelDown = DirectInput::IsKeyHeldDown(_button.buttonUnion.key);
        break;
    case InputType::Mouse:
        isHelDown = DirectInput::IsMouseButtonHeldDown(_button.buttonUnion.mouseButton);
        break;
    case InputType::Joystick:
        isHelDown = DirectInput::IsJoystickButtonHeldDown(_joystickId, _button.buttonUnion.joystickButton);
        break;
    }

    return isHelDown;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputAction::_IsButtonReleased() const
{
    bool isReleased(false);

    switch (_button.type)
    {
    case InputType::Keyboard:
        isReleased = DirectInput::IsKeyReleased(_button.buttonUnion.key);
        break;
    case InputType::Mouse:
        isReleased = DirectInput::IsMouseButtonReleased(_button.buttonUnion.mouseButton);
        break;
    case InputType::Joystick:
        isReleased = DirectInput::IsJoystickButtonReleased(_joystickId, _button.buttonUnion.joystickButton);
        break;
    }

    return isReleased;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
