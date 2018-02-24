#pragma once
#include "WindowSettings.hpp"
#include <atomic>

namespace sf { class RenderWindow; class Drawable; class Image; }

namespace Renderer
{
    /*!
     * Window for rendering that contains all basic video settings and handles user input.
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
         * \brief Applies specified settings to window before next frame.
         * \param settings - specified window settings.
         *
         * Overall, this function changes stored settings to specified and nothing more.
         * New settings will be applied only before rendering of a new frame if settings were changed.
         */
        void SetSettings(WindowSettings settings);
        
        /*!
         * \brief Returns const reference to stored window settings.
         * \return Stored window settings.
         */
        const WindowSettings& GetSettings() const;

        /*!
         * \brief Sets new icon to the window.
         * \param icon - new icon that will be applied to the window.
         * 
         * Actually saves specified icon and apply it before rendering a new frame.
         */
        void SetIcon(const sf::Image& icon);

        /*!
         * \brief Checks if window is currently opened.
         * \return True if window is opened, otherwise - false.
         */
        bool IsOpen() const;

        /*!
         * \brief Gather all window events and handles it via Input module.
         */
        void PollEvents() const;

        /*!
        * \brief Initiates drawing process: applies window settings and new icon if it required before rendering new frame.
        */
        void BeginDraw();

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
        /*!
        * \brief Applies window settings to the window.
        */
        void _ApplySettings();

        /*! Simple flag that defines if new settings should be applied to the window or not. */
        std::atomic<bool> _applyNewSettings;
        /*! Stored window settings. */
        WindowSettings _settings;
        /*! Simple flag that defines if new icon should be applied to the window or not. */
        std::atomic<bool> _applyNewIcon;
        /*! Stored icon of the window */
        sf::Image* _icon;
        /*! Actual SFML window that is used to render everything. */
        sf::RenderWindow* _renderWindow;
    };
}
