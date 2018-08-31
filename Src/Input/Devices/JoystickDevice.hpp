#pragma once
#include "Input/Devices/JoystickDeviceInterface.hpp"
#include "Input/Utilities/Buttons/JoystickButtons.hpp"
#include "Input/Utilities/ButtonStateHandler.hpp"
#include <SFML/Window/Event.hpp>
#include <atomic>
#include <string>
#include <vector>

namespace Input
{
    /*!
     * \brief Device which handles all joystick actions.
     */
    class JoystickDevice : public JoystickDeviceInterface
    {
    public:
        JoystickDevice& operator=(const JoystickDevice&) = delete;
        JoystickDevice& operator=(JoystickDevice&&) = delete;
        JoystickDevice(JoystickDevice&& other) = delete;

        /*!
         * \brief Default constructor that initializes inner arrays of buttons.
         */
        JoystickDevice();

        /*!
         * \brief Copy constructor.
         * 
         * Copy constructor is required because we have several joysticks that can be connected and handled.
         */
        JoystickDevice(const JoystickDevice&);

        /*!
         * \brief Simple destructor.
         */
        ~JoystickDevice() final;

        /*!
         * \brief Sets inner id of current joystick.
         * \param joystickId - inner id of joystick that will be used by device to identify itself.
         */
        void SetJoystickId(unsigned int joystickId);

        /*!
         * \brief Sets connection state of current joystick.
         * \param connectionState - state of connection.
         */
        void SetJoystickConnectionState(bool connectionState);

         /*!
          * \brief Returns state of specified joystick button.
          * \param button - joystick button which should be checked.
          * \param timeSpan - time span in which button should be checked.
          * \return ButtonState which defines in what state specified button is.
          */
        ButtonState GetButtonState(JoystickButton button, const Conure::Utility::TimeSpan& timeSpan) const;

        /*!
         * \brief Returns position [range: -100.0f .. 100.0f] of specified joystick axis.
         * \param axis - axis, value of which is required.
         * \return Position of specified axis.
         */
        float JoystickAxisPosition(JoystickAxis axis) const final;

        /*!
         * \brief Returns name of current joystick.
         * \return Vendors name via string,
         */
        std::string Name() const final;

        /*!
         * \brief Returns vendor id of current joystick.
         * \return Id of vendor.
         */
        uint32_t VendorId() const final;

        /*!
         * \brief Returns product id of current joystick.
         * \return Id of product.
         */
        uint32_t ProductId() const final;

        /*!
         * \brief Check if current joystick is connected.
         * \return True if joystick connected. Otherwise - false.
         */
        bool IsConnected() const final;

        /*!
         * \brief Handles joystick events.
         * \param event - joystick event to handle.
         */
        void HandleJoystickEvents(const sf::Event& event);

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
        std::vector<ButtonStateHandler> _buttons;
        /*! Axis states. */
        std::atomic<float>* _axes;
        /*! Inner joystick id which is required to identify itself. */
        unsigned int _joystickId;
        /*! Flag that defines if current joystick is connected. */
        std::atomic<bool> _isConnected;

        friend class JoystickDeviceTests;
    };
}
