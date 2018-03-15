#include "InputMapManager.hpp"
#include "Utilities/MappedInput/InputAction.hpp"
#include "Utilities/MappedInput/InputAxis.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputMapManager::InputMapManager()
    : _inputActionMap(new std::unordered_map<std::string, InputAction>)
    , _inputAxisMap(new std::unordered_map<std::string, InputAxis>)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputMapManager::~InputMapManager()
{
    delete _inputActionMap;
    delete _inputAxisMap;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMapManager::MapAction(const std::string& actionName, const KeyState state, const KeyboardKey key)
{
    (*_inputActionMap)[actionName].SetRequiredState(state);
    (*_inputActionMap)[actionName].SetRequriedButton(-1, ActionButton(key));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMapManager::MapAction(const std::string& actionName, const KeyState state, const MouseButton mouseButton)
{
    (*_inputActionMap)[actionName].SetRequiredState(state);
    (*_inputActionMap)[actionName].SetRequriedButton(-1, ActionButton(mouseButton));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMapManager::MapAction(const std::string& actionName, const KeyState state, const int joystickId, const JoystickButton joystickButton)
{
    (*_inputActionMap)[actionName].SetRequiredState(state);
    (*_inputActionMap)[actionName].SetRequriedButton(joystickId, ActionButton(joystickButton));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMapManager::MapAxis(const std::string& axisName, const int joystickId, const JoystickAxis axis)
{
    (*_inputAxisMap)[axisName].SetAxis(joystickId, axis);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputMapManager::MapAxis(const std::string& axisName, const std::string& negativeAction, const std::string& positiveAction)
{
    (*_inputAxisMap)[axisName].SetAxis(negativeAction, positiveAction);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputMapManager::IsActionActive(const std::string& actionName) const
{
    bool isActive(false);

    const auto action = _inputActionMap->find(actionName);

    // Check if such action exist
    if (action != _inputActionMap->end())
    {
        isActive = action->second.IsActive();
    }

    return isActive;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float InputMapManager::GetAxisPosition(const std::string& axisName) const
{
    float axisPosition(0.0f);

    // Check if such axis exist
    const auto axis = _inputAxisMap->find(axisName);
    if (axis != _inputAxisMap->end())
    {
        axisPosition = axis->second.GetPosition();
    }

    return axisPosition;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
