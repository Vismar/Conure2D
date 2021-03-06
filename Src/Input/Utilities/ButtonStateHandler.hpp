#pragma once

namespace C2D
{
    /*!
     * \brief Simple enumeration to enumerate all possible button states.
     */
    enum class ButtonState
    {
        NotTouched, /*!< Button was not touched. */
        Pressed,    /*!< Button was pressed.     */
        HeldDown,   /*!< Button was held down.   */
        Released    /*!< Button was released.    */
    };

    /*!
     * \brief Thread-safe handler which helps to update and check button state.
     */
    class [[deprecated("Will be reimplemented")]] ButtonStateHandler
    {
    public:
        ButtonStateHandler& operator=(const ButtonStateHandler& other) = delete;
        ButtonStateHandler& operator=(ButtonStateHandler&& other) = delete;
        ButtonStateHandler() = default;
        ButtonStateHandler(const ButtonStateHandler& other) = default;
        ButtonStateHandler(ButtonStateHandler&& other) = default;
        ~ButtonStateHandler() = default;

        /*!
         * \brief Updates specified state time of a button.
         * \param state - state for which new time will be assigned.
         * \param time - new time that will be assigned to a specified state.
         */
        void UpdateState(ButtonState state/*, const Time& time*/);

        /*!
         * \brief Calculates state of a button in a specified time span.
         * \param timeSpan - time span in which button should be checked.
         * \return State of a button in specified time span.
         */
       // ButtonState GetState(const TimeSpan& timeSpan) const;

    private:
        /*!
         * \brief Checks if button was pressed during a specified time span.
         * \param timeSpan - time span in which button should be checked.
         * \return True if button was pressed during a specified time span. Otherwise - false.
         */
        //bool _IsPressed(const TimeSpan& timeSpan) const;
        
        /*!
         * \brief Checks if button was held down during a specified time span.
         * \param timeSpan - time span in which button should be checked.
         * \return True if button was held down during a specified time span. Otherwise - false.
         */
        //bool _IsHeldDown(const TimeSpan& timeSpan) const;
        
        /*!
         * \brief Checks if button was released during a specified time span.
         * \param timeSpan - time span in which button should be checked.
         * \return True if button was released during a specified time span. Otherwise - false.
         */
        //bool _IsReleased(const TimeSpan& timeSpan) const;

        /*! Timestamp of a moment when button was pressed. */
        //Time _pressTime;
        /*! Timestamp of a moment when button was released. */
        //Time _releaseTime;
    };
}
