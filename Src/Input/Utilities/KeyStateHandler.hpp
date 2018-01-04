#pragma once
#include "InputUtilities.hpp"
#include <atomic>

namespace Input
{
    /*!
     * \brief Thread-safe handler which helps to update key state. 
     */
    class KeyStateHandler
    {
    public:
        /*!
         * \brief Constructor that will set-up current state as KeyState::NotTouched.
         */
        KeyStateHandler();

        /*!
         * \brief Returns key state.
         * \return KeyState that currently stored in handler.
         */
        KeyState State() const;

        /*!
         * \brief Updates current state.
         * \param keyState - key state that was gained during the last update from event handler. Will be used to identify current key state.
         */
        void UpdateState(const KeyState keyState);

    private:
        /*! Current key state. */
        std::atomic<KeyState> _keyState;
    };
}