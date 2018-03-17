#pragma once
#include <atomic>
#include <string>

namespace sf { class Event; }

namespace Input
{
    enum class KeyState;
    enum class JoystickButton;
    enum class JoystickAxis;
    class KeyStateHandler;

    /*!
     * \brief Device which handles all joystick actions.
     */
    class JoystickDevice
    {
    public:
        JoystickDevice(const JoystickDevice&) = delete;
        JoystickDevice(JoystickDevice&&) = delete;
        JoystickDevice& operator=(const JoystickDevice&) = delete;
        JoystickDevice& operator=(JoystickDevice&&) = delete;

        /*!
         * \brief Default constructor that initializes inner arrays of buttons.
         */
        JoystickDevice();

        /*!
         * \brief Default destructor that frees initialized inner arrays of buttons.
         */
        ~JoystickDevice();

        /*!
         * \brief Sets inner id of current joystick.
         * \param joystickId - inner id of joystick that will be used by device to identify itself.
         */
        void SetJoystickId(const unsigned int joystickId);

        /*!
         * \brief Sets connection state of current joystick.
         * \param connectionState - state of connection.
         */
        void SetJoystickConnectionState(const bool connectionState);

        /*!
         * \brief Returns state of specified joystick button.
         * \param button - specified mouse joystick to return its state.
         * \return KeyState which defines in what state specified button is.
         */
        KeyState ButtonState(const JoystickButton button) const;

        /*!
         * \brief Returns position [range: -100.0 .. 100.0] of specified joystick axis.
         * \param axis - axis, value of which is required.
         * \return Position of specified axis.
         */
        float JoystickAxisPosition(const JoystickAxis axis) const;

        /*!
         * \brief Returns name of current joystick.
         * \return Vendors name via string,
         */
        std::string Name() const;

        /*!
         * \brief Returns vendor id of current joystick.
         * \return Id of vendor.
         */
        unsigned int VendorId() const;

        /*!
         * \brief Returns product id of current joystick.
         * \return Id of product.
         */
        unsigned int ProductId() const;

        /*!
         * \brief Check if current joystick is connected.
         * \return True if joystick connected. Otherwise - false.
         */
        bool IsConnected() const;

        /*!
         * \brief Handles joystick events.
         * \param event - joystick event to handle.
         */
        void HandleJoystickEvents(const sf::Event& event);

        /*!
         * \brief Updates state of buttons that was not touched during the normal update.
         * 
         * Joystick device stores additional array of buttons that was updated during the update phase.
         * So, when this function is called, it will updates all buttons that was not updated and resets that additional array.
         * This function should be executed only after all events was handled during the update phase.
         */
        void UpdateNotTouchedButtons();

    private:
        /*!
         * \brief Handles joystick button events.
         * \param event - joystick button event.
         */
        void _HandleJoystickButtonEvent(const sf::Event& event);

        /*!
         * \brief Handles joystick axis movement event.
         * \param event - joystick axis movement event.
         */
        void _HandleJoystickMoveEvent(const sf::Event& event);

        /*! Buttons states. */
        KeyStateHandler* _buttons;
        /*! Additional array to know what buttons was updated. */
        bool* _touchedButtons;
        /*! Axis states. */
        std::atomic<float>* _axes;
        /*! Inner joystick id which is required to identify itself. */
        unsigned int _joystickId;
        /*! Flag that defines if current joystick is connected. */
        std::atomic<bool> _isConnected;

        friend class JoystickDeviceTests;
        friend class InputDeviceManagerTests;
    };
}