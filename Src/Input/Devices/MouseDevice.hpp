#pragma once
#include "Input/Devices/MouseDeviceInterface.hpp"
#include "Input/Utilities/Buttons/MouseButtons.hpp"
#include "Input/Utilities/ButtonStateHandler.hpp"
#include <SFML/Window/Event.hpp>
#include <vector>
#include <atomic>

namespace C2D
{
    /*!
     * \brief Device which handles all mouse actions.
     */
    class MouseDevice final : public MouseDeviceInterface
    {
    public:
        MouseDevice(const MouseDevice&) = delete;
        MouseDevice(MouseDevice&&) = delete;
        MouseDevice& operator=(const MouseDevice&) = delete;
        MouseDevice& operator=(MouseDevice&&) = delete;
        ~MouseDevice() final = default;

        /*!
         * \brief Default constructor that initializes inner arrays of buttons.
         */
        MouseDevice();

         /*!
          * \brief Returns state of specified mouse button.
          * \param button - mouse button which should be checked.
          * \param timeSpan - time span in which button should be checked.
          * \return ButtonState which defines in what state specified button is.
          */
        ButtonState GetButtonState(MouseButton button, const TimeSpan& timeSpan) const;

        /*!
         * \brief Returns wheel offset (positive is up, negative is down).
         * \return Abstract value that defines how much vertical wheel was scrolled.
         */
        float VerticalWheelDiff(const TimeSpan& timeSpan) const final;

        /*!
         * \brief Returns wheel offset (positive is left, negative is right).
         * \return Abstract value that defines how much horizontal wheel was scrolled.
         */
        float HorizontalWheelDiff(const TimeSpan& timeSpan) const final;

        /*!
         * \brief Returns current x coordinate of the mouse cursor relative to the top left corner of the window.
         * \return Integer value of x coordinate of the mouse cursor.
         */
        int PositionX() const final;

        /*!
         * \brief Returns current y coordinate of the mouse cursor relative to the top left corner of the window.
         * \return Integer value of y coordinate of the mouse cursor.
         */
        int PositionY() const final;

        /*!
         * \brief Handles mouse events.
         * \param event - mouse event to handle.
         */
        void HandleMouseEvent(const sf::Event& event);

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
        std::vector<ButtonStateHandler> _buttons;
        /*! Timestamp of a moment when vertical wheel was moved. */
        Time _verticalWheelMovedTime;
        /*! Value of vertical wheel scroll. */
        std::atomic<float> _verticalWheelDiff;
        /*! Timestamp of a moment when horizontal wheel was moved. */
        Time _horizontalWheelMovedTime;
        /*! Value of horizontal wheel scroll. */
        std::atomic<float> _horizontalWheelDiff;
        /*! Current x coordinate of the mouse cursor relative to the top left corner of the window. */
        std::atomic<int> _posX;
        /*! Current y coordinate of the mouse cursor relative to the top left corner of the window. */
        std::atomic<int> _posY;
    };
}