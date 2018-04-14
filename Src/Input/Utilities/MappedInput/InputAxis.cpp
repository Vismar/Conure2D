#include "InputAxis.hpp"
#include "Input/InputSystemInterface.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputAxis::InputAxis()
    : _axisType(AxisType::Axis)
    , _joystickAxis(JoystickAxis::PovX)
    , _joystickId(0)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputAxis::InputAxis(const int joystickId, const JoystickAxis axis)
    : _axisType(AxisType::Axis)
    , _joystickAxis(axis)
    , _joystickId(joystickId)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputAxis::InputAxis(std::string&& negativeAction, std::string&& positiveAction)
    : _axisType(AxisType::Buttons)
    , _joystickAxis()
    , _joystickId(-1)
    , _negativeAction(negativeAction)
    , _positiveAction(positiveAction)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputAxis::operator==(const InputAxis& other) const
{
    bool equal;

    if (_axisType == AxisType::Axis)
    {
        equal = (_joystickAxis == other._joystickAxis) && (_joystickId == other._joystickId);
    }
    else
    {
        equal = (_negativeAction == other._negativeAction) && (_positiveAction == other._positiveAction);
    }

    return equal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float InputAxis::GetPosition(const InputSystemInterface& inputSystem) const
{
    float position(0.0f);

    if (_axisType == AxisType::Axis)
    {
        position = inputSystem.Joystick(_joystickId).JoystickAxisPosition(_joystickAxis);
    }
    else
    {
        if (inputSystem.Map().IsActionActive(_negativeAction))
        {
            position -= 1.0f;
        }
        
        if (inputSystem.Map().IsActionActive(_positiveAction))
        {
            position += 1.0f;
        }
    }

    return position;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputAxis::SetAxis(const int joystickId, const JoystickAxis& axis)
{
    _axisType = AxisType::Axis;
    _joystickId = joystickId;
    _joystickAxis = axis;
    _negativeAction.clear();
    _positiveAction.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputAxis::SetAxis(const std::string& negativeAction, const std::string& positiveAction)
{
    _axisType = AxisType::Buttons;
    _joystickId = -1;
    _negativeAction = negativeAction;
    _positiveAction = positiveAction;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
