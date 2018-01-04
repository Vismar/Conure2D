#pragma once

namespace sf { class Event; }

namespace Input
{
    /*!
     * \brief Ñlass that helps to update input devices via SFML events and create/update/delete named actions and axises.
     */
    class InputHandler
    {
    public:
        /*****************************************/
        /*             DeviceManager             */
        /*****************************************/
        /*!
         * \brief Handles all input events.
         * \param event - input event to handle.
         */
        static void HandleInputEvent(const sf::Event& event);

        /*!
         * \brief Finishes update of input, so this function should be called after handling all events.
         */
        static void FinishHandle();
    };
}