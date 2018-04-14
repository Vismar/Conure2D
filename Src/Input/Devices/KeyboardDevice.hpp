#pragma once
#include "Input/Utilities/Buttons/KeyboardButtons.hpp"
#include "Input/Utilities/ButtonStateHandler.hpp"
#include "SFML/Window/Event.hpp"
#include <vector>

namespace Input
{
    /*!
     * \brief Device which handles all keyboard actions.
     */
    class KeyboardDevice
    {
    public:
        KeyboardDevice(const KeyboardDevice& other) = delete;
        KeyboardDevice(KeyboardDevice&& other) = delete;
        KeyboardDevice& operator=(const KeyboardDevice& other) = delete;
        KeyboardDevice& operator=(KeyboardDevice&& other) = delete;
        ~KeyboardDevice() = default;

        /*!
         * \brief Default constructor that initializes inner arrays of buttons.
         */
        KeyboardDevice();

        /*!
         * \brief Returns state of specified keyboard button.
         * \param button - keyboard button which should be checked.
         * \param timeSpan - time span in which button should be checked.
         * \return ButtonState which defines in what state specified button is.
         */
        ButtonState GetButtonState(KeyboardButton button, const Utility::TimeSpan& timeSpan) const;

        /*!
         * \brief Handles keyboard events.
         * \param event - keyboard event to handle.
         * \param time - new time that will be used by button.
         */
        void HandleKeyboardEvent(const sf::Event& event, const Utility::Time& time);

    private:
        /*! Buttons states. */
        std::vector<ButtonStateHandler> _buttons;
    };
}
