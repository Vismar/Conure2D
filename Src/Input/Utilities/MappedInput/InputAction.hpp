#pragma once

namespace Input
{
    enum class KeyState;
    enum class KeyboardKey;
    enum class MouseButton;
    enum class JoystickButton;

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
         * \brief Constructor to assign keyboard key as value.
         * \param keyValue - keyboard key.
         */
        explicit ButtonUnion(const KeyboardKey keyValue);

        /*!
         * \brief Constructor to assign mouse button as value.
         * \param mouseButtonValue - mouse button.
         */
        explicit ButtonUnion(const MouseButton mouseButtonValue);

        /*!
         * \brief Constructor to assign joystick button as value.
         * \param joystickButtonValue - joystick button.
         */
        explicit ButtonUnion(const JoystickButton joystickButtonValue);

        /*!
         * \brief Relational operator to compare one ButtonUnion to another.
         */
        bool operator==(const ButtonUnion& other) const;

        /*! Keyboard key. */
        KeyboardKey key;
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
         * \brief Constructor to create action button from keyboard key.
         * \param key - keyboard key that will be used to set input action and its type.
         */
        explicit ActionButton(const KeyboardKey key);

        /*!
         * \brief Constructor to create action button from mouse button.
         * \param mouseButton - mouse button that will be used to set input action and its type.
         */
        explicit ActionButton(const MouseButton mouseButton);

        /*!
         * \brief Constructor to create action button from joystick button.
         * \param joystickButton - joystick button that will be used to set input action and its type.
         */
        explicit ActionButton(const JoystickButton joystickButton);

        /*!
         * \brief Relational operator to compare one ActionButton to another.
         */
        bool operator==(const ActionButton& other) const;

        /*!
         * \brief Sets input type to keyboard and keyboard key as input action.
         * \param key - keyboard key.
         */
        void SetButton(const KeyboardKey key);

        /*!
         * \brief Sets input type to mouse and mouse button as input action.
         * \param mouseButton - mouse button.
         */
        void SetButton(const MouseButton mouseButton);

        /*!
         * \brief Sets input type to joystick and joystick button as input action.
         * \param joystickButton - joystick button.
         */
        void SetButton(const JoystickButton joystickButton);

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
        InputAction();

        /*!
         * \brief Constructor to create input actin with required state and action button.
         * \param state - requried state to activate inputa action.
         * \param joystickId - joystick id that will be used if input action is using joystick button. 
         *                     Can be set to anything if action button is not joystick button.
         * \param actionButton - actual button that will be checked to activate input action.
         */
        InputAction(const KeyState& state, const int joystickId, const ActionButton& actionButton);

        /*!
         * \brief Relational operator to compare one InputAction to another.
         */
        bool operator==(const InputAction& other) const;

        /*!
         * \brief Check if input action is currently active.
         * \return True if specified button is in required state. Otherwise - false.
         */
        bool IsActive() const;

        /*!
         * \brief Sets required key state to specified one.
         * \param state - key state that will be set as requried.
         */
        void SetRequiresState(const KeyState& state);

        /*!
         * \brief Sets required button to check activation of input action.
         * \param joystickId - joystick id that will be used if input action is using joystick button. 
         *                     Can be set to anything if action button is not joystick button.
         * \param actionButton - actual button that will be checked to activate input action.
         */
        void SetRequriedButton(const int joystickId, const ActionButton& actionButton);
                
    private:
        /*!
         * \brief Checks if stored button was pressed during the frame.
         * \return True if stored button was pressed.
         */
        bool _IsButtonPressed() const;

        /*!
         * \brief Checks if stored button was held down during the frame.
         * \return True if stored button was held down.
         */
        bool _IsButtonHeldDown() const;

        /*!
         * \brief Checks if stored button was released during the frame.
         * \return True if stored button was released.
         */
        bool _IsButtonReleased() const;

        /*! Requried state of button. */
        KeyState _requiredState;
        /*! Button that will be checked to activate input action. */
        ActionButton _button;
        /*! Joystick id that will be used if button specified for joystick device. */
        int _joystickId;
    };
}