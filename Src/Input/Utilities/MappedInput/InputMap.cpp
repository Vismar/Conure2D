#include "InputMap.hpp"
#include "Input/Utilities/MappedInput/InputAction.hpp"
#include "Input/Utilities/MappedInput/InputAxis.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputMap::InputMap(const InputSystemInterface& inputSystem)
: _inputSystem(inputSystem)
, _inputActionMap(std::make_unique<std::unordered_map<std::string, InputAction>>())
, _inputAxisMap(std::make_unique<std::unordered_map<std::string, InputAxis>>())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMap::MapAction(const std::string& actionName, const ButtonState state, const KeyboardButton keyBoardButton)
{
    (*_inputActionMap)[actionName].SetRequiredState(state);
    (*_inputActionMap)[actionName].SetRequriedButton(-1, ActionButton(keyBoardButton));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMap::MapAction(const std::string& actionName, const ButtonState state, const MouseButton mouseButton)
{
    (*_inputActionMap)[actionName].SetRequiredState(state);
    (*_inputActionMap)[actionName].SetRequriedButton(-1, ActionButton(mouseButton));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMap::MapAction(const std::string& actionName, const ButtonState state, const int joystickId, const JoystickButton joystickButton)
{
    (*_inputActionMap)[actionName].SetRequiredState(state);
    (*_inputActionMap)[actionName].SetRequriedButton(joystickId, ActionButton(joystickButton));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMap::MapAxis(const std::string& axisName, const int joystickId, const JoystickAxis axis)
{
    (*_inputAxisMap)[axisName].SetAxis(joystickId, axis);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMap::MapAxis(const std::string& axisName, const std::string& negativeAction, const std::string& positiveAction)
{
    (*_inputAxisMap)[axisName].SetAxis(negativeAction, positiveAction);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputMap::IsActionActive(const std::string& actionName) const
{
    bool isActive(false);

    // Check if such action exist
    const auto action = _inputActionMap->find(actionName);
    if (action != _inputActionMap->end())
    {
        isActive = action->second.IsActive(_inputSystem);
    }

    return isActive;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float InputMap::GetAxisPosition(const std::string& axisName) const
{
    float axisPosition(0.0f);

    // Check if such axis exist
    const auto axis = _inputAxisMap->find(axisName);
    if (axis != _inputAxisMap->end())
    {
        axisPosition = axis->second.GetPosition(_inputSystem);
    }

    return axisPosition;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
