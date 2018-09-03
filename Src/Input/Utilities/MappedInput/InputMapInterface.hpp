#pragma once
#include <string>

namespace C2D
{
    enum class JoystickAxis;
    enum class ButtonState;
    enum class KeyboardButton;
    enum class MouseButton;
    enum class JoystickButton;
    class InputAction;
    class InputAxis;

    /*!
     * \brief Public interface for input map.
     */
    class InputMapInterface
    {
    public:
        InputMapInterface(const InputMapInterface&) = delete;
        InputMapInterface(InputMapInterface&&) = delete;
        InputMapInterface& operator=(const InputMapInterface&) = delete;
        InputMapInterface& operator=(InputMapInterface&&) = delete;
        InputMapInterface() = default;
        virtual ~InputMapInterface() = default;

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used.
         * \param state - button state to activate action.
         * \param keyBoardButton - keyboard button to check.
         *
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        virtual void MapAction(const std::string& actionName, ButtonState state, KeyboardButton keyBoardButton) = 0;

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used.
         * \param state - button state to activate action.
         * \param mouseButton - mouse button to check.
         * 
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        virtual void MapAction(const std::string& actionName, ButtonState state, MouseButton mouseButton) = 0;

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used.
         * \param state - button state to activate action.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button to check.
         *
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        virtual void MapAction(const std::string& actionName, 
                               ButtonState state, 
                               int joystickId, 
                               JoystickButton joystickButton) = 0;

        /*!
         * \brief Map specified axis to a certain name.
         * \param axisName - name of axis that will be used.
         * \param joystickId - id of joystick to check.
         * \param axis - axis to check.
         *
         * Only one axis can be assigned to a certain name. If name was already used, its axis will be rewritten.
         */
        virtual void MapAxis(const std::string& axisName, int joystickId, JoystickAxis axis) = 0;

        /*!
         * \brief Map specified axis to a certain name.
         * \param axisName - name of axis that will be used.
         * \param negativeAction - name of the action that will be interpreted as the negative position of an axis.
         * \param positiveAction - name of the action that will be interpreted as the positive position of an axis.
         *
         * Only one axis can be assigned to a certain name. If name was already used, its axis will be rewritten.
         */
        virtual void MapAxis(const std::string& axisName, const std::string& negativeAction, const std::string& positiveAction) = 0;

        /*!
         * \brief Checks if any of associated with the named action input actions is active.
         * \param actionName -  name to associate with.
         * \return True if at least one input action is active.
         */
        virtual bool IsActionActive(const std::string& actionName) const = 0;

        /*!
         * \brief Returns the position of the biggest by absolute value input axis.
         * \param axisName -  name to associate with.
         * \return The position of the biggest by absolute value input axis.
         */
        virtual float GetAxisPosition(const std::string& axisName) const = 0;
    };
}
