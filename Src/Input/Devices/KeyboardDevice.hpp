#pragma once

namespace sf { class Event; }

namespace Input
{
    enum class KeyState;
    enum class KeyboardKey;
    class KeyStateHandler;

    /*!
     * \brief Device which handles all keyboard actions.
     */
    class KeyboardDevice
    {
    public:
        KeyboardDevice(const KeyboardDevice&) = delete;
        KeyboardDevice(KeyboardDevice&&) = delete;
        KeyboardDevice& operator=(const KeyboardDevice&) = delete;
        KeyboardDevice& operator=(KeyboardDevice&&) = delete;

        /*!
         * \brief Default constructor that initializes inner arrays of keys.
         */
        KeyboardDevice();

        /*!
         * \brief Default destructor that frees initialized inner arrays of keys.
         */
        ~KeyboardDevice();

        /*!
         * \brief Returns state of specified keyboard key.
         * \param key - specified keyboard key to return its state.
         * \return KeyState which defines in what state specified key is.
         */
        KeyState KeyState(KeyboardKey key) const;

        /*!
         * \brief Handles keyboard events.
         * \param event - keyboard event to handle.
         * 
         * Checks event type and updates state of specified key.
         */
        void HandleKeyboardEvent(const sf::Event& event);

        /*!
         * \brief Updates state of keys that was not touched during the normal update.
         * 
         * Keyboard device stores additional array of keys that was updated during the update phase.
         * So, when this function is called, it will updates all keys that was not updated and resets that additional array.
         * This function should be executed only after all events was handled during the update phase.
         */
        void UpdateNotTouchedKeys();

    private:
        /*! Key states. */
        KeyStateHandler* _keys;
        /*! Additional array to know what keys was updated. */
        bool* _touchedKeys;
    };
}