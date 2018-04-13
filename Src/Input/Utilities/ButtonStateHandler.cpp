#include "ButtonStateHandler.hpp"

using namespace Input;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ButtonStatehandler::UpdateState(const ButtonState state, const Utility::Time& time)
{
    switch (state)
    {
    case ButtonState::Pressed:
        _pressTime = time;
        break;
    case ButtonState::Released:
        _releaseTime = time;
        break;
    default:
        // Do nothing
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonState ButtonStatehandler::GetState(const Utility::TimeSpan& timeSpan) const
{
    ButtonState buttonState;

    // If a button was pressed, it can be:
    //   - Only pressed
    //   - Pressed and released in the same time (VERY rare or even impossible case)
    // Second case will be interpreted as "NotTouched".
    if (_IsPressed(timeSpan))
    {
        if (_IsReleased(timeSpan))
        {
            buttonState = ButtonState::NotTouched;
        }
        else
        {
            buttonState = ButtonState::Pressed;
        }
    }
    // If a button was not pressed, it might be held down in a specified time span
    else if (_IsHeldDown(timeSpan))
    {
        buttonState = ButtonState::HeldDown;
    }
    // If a button was not pressed/held down, it might be released in a specified time span
    else if (_IsReleased(timeSpan))
    {
        buttonState = ButtonState::Released;
    }
    // If a button was not pressed/released/held down - then it was not touched at all
    else
    {
        buttonState = ButtonState::NotTouched;
    }

    return buttonState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ButtonStatehandler::_IsPressed(const Utility::TimeSpan& timeSpan) const
{
    // Button is pressed when pressed time is IN specified time span
    return (timeSpan.Start() <= _pressTime) && (_pressTime <= timeSpan.End());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ButtonStatehandler::_IsHeldDown(const Utility::TimeSpan& timeSpan) const
{
    // Button is held down when it is not pressed and start of time span is bigger than press time
    return  (_pressTime < timeSpan.Start()) && !_IsReleased(timeSpan);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ButtonStatehandler::_IsReleased(const Utility::TimeSpan& timeSpan) const
{
    // Button is released when pressed time is IN specified time span
    return (timeSpan.Start() <= _releaseTime) && (_releaseTime <= timeSpan.End());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////