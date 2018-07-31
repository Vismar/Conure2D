#pragma once
#include "InputMapInterface.hpp"
#include "Input/Utilities/MappedInput/InputAction.hpp"
#include "Input/Utilities/MappedInput/InputAxis.hpp"
#include <string>
#include <unordered_map>
#include <memory>

namespace  Input
{
    class InputSystemInterface;

    /*!
     * \brief Manager that handles creating/updating/deleting of mapped input actions and axes.
     */
    class InputMap final : public InputMapInterface
    {
    public:
        InputMap(const InputMap&) = delete;
        InputMap(InputMap&&) = delete;
        InputMap& operator=(const InputMap&) = delete;
        InputMap& operator=(InputMap&&) = delete;
        InputMap() = delete;
        ~InputMap() final = default;

        /*!
         * \brief Default constructor that initializes maps of input actions and input axes.
         * \param inputSystem - const reference to input system which will be used by inner actions and axes.
         */
        explicit InputMap(const InputSystemInterface& inputSystem);

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used. 
         * \param state - button state to activate action.
         * \param keyBoardButton - keyboard button to check.
         * 
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        void MapAction(const std::string& actionName, ButtonState state, KeyboardButton keyBoardButton) final;

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used. 
         * \param state - button state to activate action.
         * \param mouseButton - mouse button to check.
         * 
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        void MapAction(const std::string& actionName, ButtonState state, MouseButton mouseButton) final;

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used. 
         * \param state - button state to activate action.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button to check.
         * 
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        void MapAction(const std::string& actionName, 
                       ButtonState state, 
                       int joystickId, 
                       JoystickButton joystickButton) final;

        /*!
         * \brief Map specified axis to a certain name.
         * \param axisName - name of axis that will be used. 
         * \param joystickId - id of joystick to check.
         * \param axis - axis to check.
         * 
         * Only one axis can be assigned to a certain name. If name was already used, its axis will be rewritten.
         */
        void MapAxis(const std::string& axisName, int joystickId, JoystickAxis axis) final;

        /*!
         * \brief Map specified axis to a certain name.
         * \param axisName - name of axis that will be used. 
         * \param negativeAction - name of the action that will be interpreted as the negative position of an axis.
         * \param positiveAction - name of the action that will be interpreted as the positive position of an axis.
         * 
         * Only one axis can be assigned to a certain name. If name was already used, its axis will be rewritten.
         */
        void MapAxis(const std::string& axisName, const std::string& negativeAction, const std::string& positiveAction) final;

        /*!
         * \brief Checks if any of associated with the named action input actions is active.
         * \param actionName -  name to associate with.
         * \return True if at least one input action is active.
         */
        bool IsActionActive(const std::string& actionName) const final;

        /*!
         * \brief Returns the position of the biggest by absolute value input axis.
         * \param axisName -  name to associate with.
         * \return The position of the biggest by absolute value input axis.
         */
        float GetAxisPosition(const std::string& axisName) const final;

    private:
        const InputSystemInterface& _inputSystem;
        /*! Map of named actions that stores array of input actions. */
        std::unique_ptr<std::unordered_map<std::string, InputAction>> _inputActionMap;
        /*! Map of named axes that stores array of input axes. */
        std::unique_ptr<std::unordered_map<std::string, InputAxis>> _inputAxisMap;
    };
}
