#pragma once
#include "Utilities/InputUtilities.hpp"
#include "Utilities/Keys/KeyboardKeys.hpp"
#include "Utilities/Keys/MouseButtons.hpp"
#include "Utilities/Keys/JoystickButtons.hpp"
#include "Utilities/Keys/JoystickAxises.hpp"

namespace Input
{
    /*!
     * \brief Static class that helps to directly check user input.
     * 
     * That class helps to check direct input from keyboard, mouse, and joystick.
     * Moreover, user can check the state of actions and axises mapped to a certain name through InputUtility.
     */
    class DirectInput
    {
    public:
        /*****************************************/
        /*               Keyboard                */
        /*****************************************/

        /*!
         * \brief Checks if specified key was pressed during the current frame.
         * \param key - specific key to check.
         * \return True if key was pressed during the current frame. Otherwise - false.
         */
        static bool IsKeyPressed(const KeyboardKey key);

        /*!
         * \brief Checks if specified key was held down during the current frame.
         * \param key - specific key to check.
         * \return True if key was held down during the current frame. Otherwise - false.
         */

        static bool IsKeyHeldDown(const KeyboardKey key);
        /*!
         * \brief Checks if specified key was released during the current frame.
         * \param key - specific key to check.
         * \return True if key was released during the current frame. Otherwise - false.
         */
        static bool IsKeyReleased(const KeyboardKey key);

        /*****************************************/
        /*                 Mouse                 */
        /*****************************************/

        /*!
         * \brief Checks if specified mouse button was pressed during the current frame.
         * \param button - specific mouse button to check.
         * \return True if mouse button was pressed during the current frame. Otherwise - false.
         */
        static bool IsMouseButtonPressed(const MouseButton button);

        /*!
         * \brief Checks if specified mouse button was held down during the current frame.
         * \param button - specific mouse button to check.
         * \return True if mouse button was held down during the current frame. Otherwise - false.
         */
        static bool IsMouseButtonHeldDown(const MouseButton button);

        /*!
         * \brief Checks if specified mouse button was released during the current frame.
         * \param button - specific mouse button to check.
         * \return True if mouse button was released during the current frame. Otherwise - false.
         */
        static bool IsMouseButtonReleased(const MouseButton button);

        /*!
         * \brief Returns movement of vertical wheel during the current frame.
         * \return Value that defines how much vertical wheel was moved during the current frame.
         */
        static float GetMouseVerticalWheelDiff();

        /*!
         * \brief Returns movement of horizontal wheel during the current frame.
         * \return Value that defines how much horizontal wheel was moved during the current frame.
         */
        static float GetMouseHorizontalWheelDiff();

        /*!
         * \brief Returns current position of mouse on X axis (0 on left).
         * \return X coordinate.
         */
        static int GetMousePositionX();

        /*!
         * \brief Returns current position of mouse on Y axis (0 on top).
         * \return Y coordinate.
         */
        static int GetMousePositionY();

        /*****************************************/
        /*               Joystick                */
        /*****************************************/

        /*!
         * \brief Checks if specified joystick button was pressed during the current frame.
         * \param joystickId - inner identifier of joystick.
         * \param button - specific joystick button to check.
         * \return True if joystick button was pressed during the current frame. Otherwise - false.
         */
        static bool IsJoystickButtonPressed(const int joystickId, const JoystickButton button);

        /*!
         * \brief Checks if specified joystick button was held down during the current frame.
         * \param joystickId - inner identifier of joystick
         * \param button - specific joystick button to check.
         * \return True if joystick button was held down during the current frame. Otherwise - false.
         */
        static bool IsJoystickButtonHeldDown(const int joystickId, const JoystickButton button);

        /*!
         * \brief Checks if specified joystick button was released during the current frame.
         * \param joystickId - inner identifier of joystick
         * \param button - specific joystick button to check.
         * \return True if joystick button was released during the current frame. Otherwise - false.
         */
        static bool IsJoystickButtonReleased(const int joystickId, const JoystickButton button);

        /*!
         * \brief Returns position of specified joystick axis.
         * \param joystickId - inner identifier of joystick
         * \param axis - specific joystick axis to check.
         * \return Position of specified joystick axis.
         */
        static float GetJoystickAxisPosition(const int joystickId, const JoystickAxis axis);

        /*!
         * \brief Checks if specified joystick is connected.
         * \param joystickId - inner identifier of joystick
         * \return True of specified joystick is connected. Otherwise - false.
         */
        static bool IsJoystickConnected(const int joystickId);

        /*!
         * \brief Returns name of specified joystick.
         * \param joystickId - inner identifier of joystick
         * \return Name of specified joystick.
         */
        static std::string GetJoystickName(const int joystickId);

        /*!
         * \brief Returns vendor id of specified joystick.
         * \param joystickId - inner identifier of joystick
         * \return Vendor id of specified joystick.
         */
        static unsigned int GetJoystickVendorId(const int joystickId);

        /*!
         * \brief Returns product id of specified joystick.
         * \param joystickId - inner identifier of joystick
         * \return Product id of specified joystick.
         */
        static unsigned int GetJoystickProductId(const int joystickId);

        /*****************************************/
        /*                 Maps                  */
        /*****************************************/

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used.
         * \param state - key state to activate action.
         * \param key - keyboard key to check.
         *
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        static void MapAction(const std::string& actionName, const KeyState state, const KeyboardKey key);

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used.
         * \param state - button state to activate action.
         * \param mouseButton - mouse button to check.
         *
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        static void MapAction(const std::string& actionName, const KeyState state, const MouseButton mouseButton);

        /*!
         * \brief Map specified action to a certain name.
         * \param actionName - name of action that will be used.
         * \param state - button state to activate action.
         * \param joystickId - id of joystick to check.
         * \param joystickButton - joystick button to check.
         *
         * Only one action can be assigned to a certain name. If name was already used, its button will be rewritten.
         */
        static void MapAction(const std::string& actionName, const KeyState state, const int joystickId, const JoystickButton joystickButton);

        /*!
         * \brief Map specified axis to a certain name.
         * \param axisName - name of axis that will be used.
         * \param joystickId - id of joystick to check.
         * \param axis - axis to check.
         *
         * Only one axis can be assigned to a certain name. If name was already used, its axis will be rewritten.
         */
        static void MapAxis(const std::string& axisName, const int joystickId, const JoystickAxis axis);

        /*!
         * \brief Map specified axis to a certain name.
         * \param axisName - name of axis that will be used.
         * \param negativeAction - name of the action that will be interpreted as the negative position of an axis.
         * \param positiveAction - name of the action that will be interpreted as the positive position of an axis.
         *
         * Only one axis can be assigned to a certain name. If name was already used, its axis will be rewritten.
         */
        static void MapAxis(const std::string& axisName, const std::string& negativeAction, const std::string& positiveAction);

        /*!
         * \brief Checks if action is active.
         * \param actionName - name of the action to check.
         * \return True if created action is active during the frame. Otherwise - false.
         */
        static bool IsActionActive(const std::string& actionName);

        /*!
         * \brief Returns position of axis.
         * \param axisName - name of axis.
         * \return Position of specified axis.
         */
        static float GetAxisPosition(const std::string& axisName);
    };
}