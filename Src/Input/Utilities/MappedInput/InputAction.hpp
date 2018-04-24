#pragma once

namespace Input
{
    enum class ButtonState;
    enum class KeyboardButton;
    enum class MouseButton;
    enum class JoystickButton;
    class InputSystemInterface;

    /*!
     * \brief Simple enumeration of input types.
     */
    enum class InputType
    {
        Keyboard, /*!< Keyboard device. */
        Mouse,    /*!< Mouse device. */
        Joystick  /*!< Joystick device. */
    };

    /*!
     * \brief Simple union to store any possible input button.
     */
    union ButtonUnion
    {
        /*!
         * \brief Constructor to assign keyboard button as value.
         * \param keyboardButtonValue - keyboard button.
         */
        explicit ButtonUnion(KeyboardButton keyboardButtonValue);

        /*!
         * \brief Constructor to assign mouse button as value.
         * \param mouseButtonValue - mouse button.
         */
        explicit ButtonUnion(MouseButton mouseButtonValue);

        /*!
         * \brief Constructor to assign joystick button as value.
         * \param joystickButtonValue - joystick button.
         */
        explicit ButtonUnion(JoystickButton joystickButtonValue);

        /*!
         * \brief Relational operator to compare one ButtonUnion to another.
         */
        bool operator==(const ButtonUnion& other) const;

        /*! Keyboard button. */
        KeyboardButton keyboardButton;
        /*! Mouse button. */
        MouseButton mouseButton;
        /*! Joystick button. */
        JoystickButton joystickButton;
    };

    /*!
     * \brief Stores input type and button itself.
     */
    struct ActionButton
    {
        /*!
         * \brief Constructor to create action button from keyboard button.
         * \param keyboardButton - keyboard button that will be used to set input action and its type.
         */
        explicit ActionButton(KeyboardButton keyboardButton);

        /*!
         * \brief Constructor to create action button from mouse button.
         * \param mouseButton - mouse button that will be used to set input action and its type.
         */
        explicit ActionButton(MouseButton mouseButton);

        /*!
         * \brief Constructor to create action button from joystick button.
         * \param joystickButton - joystick button that will be used to set input action and its type.
         */
        explicit ActionButton(JoystickButton joystickButton);

        /*!
         * \brief Relational operator to compare one ActionButton to another.
         */
        bool operator==(const ActionButton& other) const;

        /*!
         * \brief Sets input type to keyboard and keyboard button as input action.
         * \param keyboardButton - keyboard button.
         */
        void SetButton(KeyboardButton keyboardButton);

        /*!
         * \brief Sets input type to mouse and mouse button as input action.
         * \param mouseButton - mouse button.
         */
        void SetButton(MouseButton mouseButton);

        /*!
         * \brief Sets input type to joystick and joystick button as input action.
         * \param joystickButton - joystick button.
         */
        void SetButton(JoystickButton joystickButton);

        /*! Type of input. */
        InputType type;
        /*! Input button. */
        ButtonUnion buttonUnion;
    };

    /*!
     * \brief Input action that represented as button and its required state which is needed to activate this action.
     */
    class InputAction
    {
    public:
        /*!
         * \brief Default constructor.
         */
        InputAction();

        /*!
         * \brief Constructor to create input action with required state and action button.
         * \param state - required state to activate input action.
         * \param joystickId - joystick id that will be used if input action is using joystick button. 
         *                     Can be set to anything if action button is not joystick button.
         * \param actionButton - actual button that will be checked to activate input action.
         */
        InputAction(ButtonState state, int joystickId, const ActionButton& actionButton);

        /*!
         * \brief Relational operator to compare one InputAction to another.
         */
        bool operator==(const InputAction& other) const;

        /*!
         * \brief Check if input action is currently active.
         * \param inputSystem - reference to the input system from which action will be checked.
         * \return True if specified button is in required state. Otherwise - false.
         */
        bool IsActive(const InputSystemInterface& inputSystem) const;

        /*!
         * \brief Sets required button state to specified one.
         * \param state - button state that will be set as required.
         */
        void SetRequiredState(ButtonState state);

        /*!
         * \brief Sets required button to check activation of input action.
         * \param joystickId - joystick id that will be used if input action is using joystick button. 
         *                     Can be set to anything if action button is not joystick button.
         * \param actionButton - actual button that will be checked to activate input action.
         */
        void SetRequriedButton(int joystickId, const ActionButton& actionButton);
                
    private:
        /*!
         * \brief Checks if stored button was pressed during the frame.
         * \param inputSystem - reference to the input system from which button will be checked.
         * \return True if stored button was pressed.
         */
        bool _IsButtonPressed(const InputSystemInterface& inputSystem) const;

        /*!
         * \brief Checks if stored button was held down during the frame.
         * \param inputSystem - reference to the input system from which button will be checked.
         * \return True if stored button was held down.
         */
        bool _IsButtonHeldDown(const InputSystemInterface& inputSystem) const;

        /*!
         * \brief Checks if stored button was released during the frame.
         * \param inputSystem - reference to the input system from which button will be checked.
         * \return True if stored button was released.
         */
        bool _IsButtonReleased(const InputSystemInterface& inputSystem) const;

        /*! Required state of button. */
        ButtonState _requiredState;
        /*! Button that will be checked to activate input action. */
        ActionButton _button;
        /*! Joystick id that will be used if button specified for joystick device. */
        int _joystickId;
    };
}