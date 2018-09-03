#pragma once

namespace sf { class Event; }

namespace C2D
{
    class Time;

    /*!
     * \brief Public handler interface for input system.
     * 
     * Provides functionality to handle input events. Should be used by entity that poll events.
     */
    class InputSystemHandlerInterface
    {
    public:
        InputSystemHandlerInterface(const InputSystemHandlerInterface& other) = delete;
        InputSystemHandlerInterface(InputSystemHandlerInterface&& other) = delete;
        InputSystemHandlerInterface& operator=(const InputSystemHandlerInterface& other) = delete;
        InputSystemHandlerInterface& operator=(InputSystemHandlerInterface&& other) = delete;
        InputSystemHandlerInterface() = default;
        virtual ~InputSystemHandlerInterface() = default;

        /*!
         * \brief Handles input events.
         * \param inputEvent - SFML event which will be handled by input system.
         */
        virtual void HandleInputEvent(const sf::Event& inputEvent) = 0;
    };
}
