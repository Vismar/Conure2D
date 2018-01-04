#pragma once
#include "Utilities/Keys/JoystickAxises.hpp"
#include <string>

namespace Input
{
    /*!
     * \brief Axis type that is used in AxisUnion.
     */
    enum class AxisType
    {
        Axis,   /*!< Axis itself. */
        Buttons /*!< Any button. */
    };

    /*!
     * \brief Input axis that can be represented as actual joystick axis or pair of action buttons.
     */
    class InputAxis
    {
    public:
        /*!
         * \brief Default constructor.
         * 
         * Will assign AxisType::Axis, JoystickAxis::PovX, Joystick Id = 0.
         */
        InputAxis();

        /*!
         * \brief Constructor to create input axis from actual joystick axis.
         * \param joystickId - joystick id that will be used to check proper joystick device.
         * \param axis - joystick axis that will be used.
         */
        InputAxis(const int joystickId, const JoystickAxis axis);

        /*!
         * \brief Constructor to create input axis from two already mapped actions.
         * \param negativeAction - name of the action that will be interpreted as the negative position of an axis.
         * \param positiveAction - name of the action that will be interpreted as the positive position of an axis.
         */
        InputAxis(std::string&& negativeAction, std::string&& positiveAction);

        /*!
         * \brief Relational operator to compare one InputAxis to another.
         * \param other - InputAxis on the right side of the operator.
         * \return True of axis types of variables are equal and required params are too. Otherwise - false.
         */
        bool operator==(const InputAxis& other) const;

        /*!
         * \brief Returns axis position.
         * \return Current axis position.
         */
        float GetPosition() const;

        /*!
         * \brief Sets actual axis to check.
         * \param joystickId - joystick id that will be used to check proper joystick device.
         * \param axis - joystick axis that will be used.
         */
        void SetAxis(const int joystickId, const JoystickAxis& axis);

        /*!
         * \brief Sets two already mapped actions to be interpreted as input axis.
         * \param negativeAction - name of the action that will be interpreted as the negative position of an axis.
         * \param positiveAction - name of the action that will be interpreted as the positive position of an axis.
         */
        void SetAxis(const std::string& negativeAction, const std::string& positiveAction);

    private:
        /*! Type of axis. Can be actual joystick axis or pair of mapped actions. */
        AxisType _axisType;
        /*! Action axis. */
        JoystickAxis _joystickAxis;
        /*! Joystick id that will be used if button specified for joystick device.. */
        int _joystickId;
        /*! Name of the action that will be interpreted as the negative position of an axis. */
        std::string _negativeAction;
        /*! Name of the action that will be interpreted as the positive position of an axis. */
        std::string _positiveAction;
    };
}
