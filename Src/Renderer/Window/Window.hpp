#pragma once
#include "WindowSettings.hpp"
#include "Input/InputSystemHandlerInterface.hpp"
#include <atomic>
#include <memory>

namespace sf { class RenderWindow; class Drawable; class Image; }

namespace Renderer
{
    /*!
     * \brief Window for rendering that contains all basic video settings and handles user input.
     */
    class Window
    {
    public:
        Window() = delete;
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        /*!
         * \brief Constructor to create window with certain settings.
         * \param settings - settings that will be applied to window.
         */
        explicit Window(WindowSettings settings); 

        /*!
         * \brief Destructor that closes window and deletes it.
         */
        virtual ~Window();
   
        /*!
         * \brief Applies new settings to window.
         * \param windowSettings - specified window settings.
         */
        void SetNewSettings(WindowSettings windowSettings);
        
        /*!
         * \brief Returns const reference to stored window settings.
         * \return Stored window settings.
         */
        const WindowSettings& GetSettings() const;

        /*!
         * \brief Sets new title to the window.
         * \param title - new title that will be used by window.
         */
        void SetTitle(const std::string& title);

        /*!
         * \brief Resizes window to specified size.
         * \param width - new width of the window.
         * \param height - new height of the window.
         */
        void SetSize(uint32_t width, uint32_t height);

        /*!
         * \brief Resizes window resolution to specified values.
         * \param width - new width of the window resolution.
         * \param height - new height of the window resolution.
         */
        void SetResolution(uint32_t width, uint32_t height);

        /*!
         * \brief Sets new icon to the window.
         * \param icon - new icon that will be applied to the window.
         * 
         * Actually saves specified icon and apply it before rendering a new frame.
         */
        void SetIcon(const sf::Image& icon);

        /*!
         * \brief Sets new antialiasing level.
         * \param antialiasingLevel - new level of antialiasing.
         */
        void SetAntialiasing(uint32_t antialiasingLevel);

        /*!
         * \brief Turns vertical sync On/Off.
         * \param enabled - flag that defines if vertical sync should be turned on or off.
         */
        void SetVerticalSyncEnabled(bool enabled);

        /*!
         * \brief Sets framerate limit a maximum fixed frequency.
         * \param frameLimit - new framerate limit, in frames per seconds (use 0 to disable limit).
         */
        void SetFramerateLimit(uint32_t frameLimit);
        
        /*!
         * \brief Turns on or off visibility of the mouse cursor.
         * \param visible - flag that defines if mouse cursor should be visible or not.
         */
        void SetMouseCursorVisible(bool visible);

        /*!
         * \brief Grabs or releases the mouse cursor.
         * \param grabbed - flag that defines if mouse cursor should be grabbed or not.
         */
        void SetMouseCursorGrabbed(bool grabbed);

        /*!
         * \brief Checks if window is currently opened.
         * \return True if window is opened, otherwise - false.
         */
        bool IsOpen() const;

        /*!
         * \brief Gather all window events and handles it via Input module.
         * \param inputSystem - reference to input system which will handle input events from the window.
         * \param time - time which will be used along with events.
         */
        void PollEvents(Input::InputSystemHandlerInterface& inputSystem, const Utility::Time& time) const;

        /*!
         * \brief Initiates drawing process: applies window settings and new icon if it required before rendering new frame.
         */
        void BeginDraw() const;

        /*!
         * \brief Draws a specified drawable thing.
         * \param drawable - drawable entity.
         */
        void Draw(const sf::Drawable& drawable) const;

        /*!
         * \brief Finalizes drawing process.
         */
        void EndDraw() const;

    private:
        /*! Stored window settings. */
        WindowSettings _settings;
        /*! Stored icon of the window */
        sf::Image* _icon;
        /*! Actual SFML window that is used to render everything. */
        std::unique_ptr<sf::RenderWindow> _renderWindow;
    };
}
