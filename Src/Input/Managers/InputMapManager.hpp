#pragma once
#include <string>
#include <unordered_map>

namespace  Input
{
    enum class KeyState;
    enum class KeyboardKey;
    enum class MouseButton;
    enum class JoystickButton;
    enum class JoystickAxis;
    class InputAction;
    class InputAxis;

    /*!
     * \brief Manager that handles creating/updating/deleting of mapped input actions and axes.
     */
    class InputMapManager
    {
    public:
        InputMapManager(const InputMapManager&) = delete;
        InputMapManager(InputMapManager&&) = delete;
        InputMapManager& operator=(const InputMapManager&) = delete;
        InputMapManager& operator=(InputMapManager&&) = delete;

        /*!
         * \brief Default constructor that initializes maps of input actions and input axes.
         */
        InputMapManager();

        /*!
         * \brief Default destructor that deletes maps of input actions and input axes.
         */
        ~InputMapManager();

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used. 
         * \param state - key state to activate action.
         * \param key - keyboard key to check.
         * 
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        void MapAction(const std::string& actionName, const KeyState state, const KeyboardKey key);

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used. 
         * \param state - button state to activate action.
         * \param mouseButton - mouse button to check.
         * 
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        void MapAction(const std::string& actionName, const KeyState state, const MouseButton mouseButton);

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used. 
         * \param state - button state to activate action.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button to check.
         * 
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        void MapAction(const std::string& actionName, const KeyState state, const int joystickId, const JoystickButton joystickButton);

        /*!
         * \brief Map specified axis to a certain name.
         * \param axisName - name of axis that will be used. 
         * \param joystickId - id of joystick to check.
         * \param axis - axis to check.
         * 
         * Only one axis can be assigned to a certain name. If name was already used, its axis will be rewritten.
         */
        void MapAxis(const std::string& axisName, const int joystickId, const JoystickAxis axis);

        /*!
         * \brief Map specified axis to a certain name.
         * \param axisName - name of axis that will be used. 
         * \param negativeAction - name of the action that will be interpreted as the negative position of an axis.
         * \param positiveAction - name of the action that will be interpreted as the positive position of an axis.
         * 
         * Only one axis can be assigned to a certain name. If name was already used, its axis will be rewritten.
         */
        void MapAxis(const std::string& axisName, const std::string& negativeAction, const std::string& positiveAction);

        /*!
         * \brief Checks if any of associated with the named action input actions is active.
         * \param actionName -  name to associate with.
         * \return True if at least one input action is active.
         */
        bool IsActionActive(const std::string& actionName) const;

        /*!
         * \brief Returns the position of the biggest by absolute value input axis.
         * \param axisName -  name to associate with.
         * \return The position of the biggest by absolute value input axis.
         */
        float GetAxisPosition(const std::string& axisName) const;

    private:
        /*! Map of named actions that stores array of input actions. */
        std::unordered_map<std::string, InputAction>* _inputActionMap;
        /*! Map of named axes that stores array of input axes. */
        std::unordered_map<std::string, InputAxis>* _inputAxisMap;
    };
}
