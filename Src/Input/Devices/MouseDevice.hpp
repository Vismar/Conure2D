#pragma once
#include <atomic>

namespace sf { class Event; }

namespace Input
{
    enum class KeyState;
    enum class MouseButton;
    class KeyStateHandler;

    /*!
     * \brief Device which handles all mouse actions.
     */
    class MouseDevice
    {
    public:
        MouseDevice(const MouseDevice&) = delete;
        MouseDevice(MouseDevice&&) = delete;
        MouseDevice& operator=(const MouseDevice&) = delete;
        MouseDevice& operator=(MouseDevice&&) = delete;

        /*!
         * \brief Default constructor that initializes inner arrays of buttons.
         */
        MouseDevice();

        /*!
         * \brief Default destructor that frees initialized inner arrays of buttons.
         */
        ~MouseDevice();

        /*!
         * \brief Returns state of specified mouse button.
         * \param button - specified mouse button to return its state.
         * \return KeyState which defines in what state specified button is.
         */
        KeyState ButtonState(MouseButton button) const;

        /*!
         * \brief Returns wheel offset (positive is up, negative is down).
         * \return Abstract value that defines how much vertical wheel was scrolled.
         */
        float VerticalWheelDiff() const;

        /*!
         * \brief Returns wheel offset (positive is left, negative is right).
         * \return Abstract value that defines how much horizontal wheel was scrolled.
         */
        float HorizontalWheelDiff() const;

        /*!
         * \brief Returns current x coordinate of the mouse cursor relative to the top left corner of the window.
         * \return Integer value of x coordinate of the mouse cursor.
         */
        int PositionX() const;

        /*!
         * \brief Returns current y coordinate of the mouse cursor relative to the top left corner of the window.
         * \return Integer value of y coordinate of the mouse cursor.
         */
        int PositionY() const;

        /*!
         * \brief Handles mouse events.
         * \param event - mouse event to handle.
         */
        void HandleMouseEvent(const sf::Event& event);

        /*!
         * \brief Updates state of buttons that was not touched during the normal update.
         * 
         * Mouse device stores additional array of buttons that was updated during the update phase.
         * So, when this function is called, it will updates all buttons that was not updated and resets that additional array.
         * This function should be executed only after all events was handled during the update phase.
         */
        void UpdateNotTouchedButtons();

        /*!
         * \brief Simply resets mouse wheel scroll value if necessary.
         */
        void UpdateWheels();

    private:
        /*!
         * \brief Handles mouse button events.
         * \param event - mouse button event.
         */
        void _HandleMouseButtonEvent(const sf::Event& event);

        /*!
         * \brief Handles mouse wheel events.
         * \param event - mouse wheel event.
         */
        void _HandleMouseWheelEvent(const sf::Event& event);

        /*!
         * \brief Handles mouse move event.
         * \param event - mouse move event.
         */
        void _HandleMouseMoveEvent(const sf::Event& event);

        /*! Buttons states. */
        KeyStateHandler* _buttons;
        /*! Additional array to know what buttons was updated. */
        bool* _touchedButtons;
        /*! Flag that defines if vertical wheel was updated during the update phase. */
        bool _verticalWheelUpdated;
        /*! Value of vertical wheel scroll. */
        std::atomic<float> _verticalWheelDiff;
        /*! Flag that defines if horizontal wheel was updated during the update phase. */
        bool _horizontalWheelUpdated;
        /*! Value of horizontal wheel scroll. */
        std::atomic<float> _horizontalWheelDiff;
        /*! Current x coordinate of the mouse cursor relative to the top left corner of the window. */
        std::atomic<int> _posX;
        /*! Current y coordinate of the mouse cursor relative to the top left corner of the window. */
        std::atomic<int> _posY;
    };
}