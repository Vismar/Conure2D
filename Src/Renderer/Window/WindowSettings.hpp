#pragma once
#include <string>

namespace sf { class VideoMode; struct ContextSettings; }

namespace Renderer
{
    /*!
     * \brief Enumeration of styles that can be used by window.
     */
    enum class WindowStyle
    {
        FullScreen, /*!< Full-screen window style. No borders, no title bar. */
        Windowed,   /*!< Windowed window style. Borders, title bar with "close" button. */
        NoBorders   /*!< Windowed window style without borders and title bar. */
    };

    /*!
     * \brief All settings that can be applied to SFML window.
     */
    struct WindowSettings
    {
        /*!
         * \brief Returns current video mode.
         * \return SFML Video mode that contains window resolution and number of bits per pixel.
         */
        sf::VideoMode GetVideoMode() const;

        /*!
         * \brief Returns SFML window style.
         * \return Check what current window style is and then returns equivalent SFML style.
         */
        uint32_t GetSfmlStyle() const;

        /*!
         * \brief Returns context settings for SFML window.
         * \return Gathers currently stored parameters into ContextSettings and returns it.
         */
        sf::ContextSettings GetContextSettings() const;

        /*! Title of the window. */
        std::string title = "Conure2D game";
        /*! Window style. */
        WindowStyle style = WindowStyle::Windowed;
        /*! Window width. */
        uint32_t width = 1280;
        /*! Window height. */
        uint32_t height = 720;
        /*! Number of bits per pixel.. */
        uint32_t bitsPerPixel = 32;
        /*! Level of anti-aliasing. */
        uint32_t antialiasing = 0;
        /*! Bits of the depth buffer. */
        uint32_t depthBits = 0;
        /*! Bits of the stencil buffer.  */
        uint32_t stencilBits = 0;
        /*! Major number of the context version to create. */
        uint32_t majorContextVersion = 2;
        /*! Minor number of the context version to create. */
        uint32_t minorContaxtVersion = 0;
        /*! Flag which defines vertical synchronization. */
        bool verticalSync = false;
        /*! Limit of frames per second. 0 - turns limit off. */
        uint32_t frameLimit = 0;
        /*! Flag which defines visibility of cursor on the window. */
        bool cursorIsVisible = true;
        /*! Flag which defines if cursor can leave the window. */
        bool cursorIsGrabbed = false;
    };
}
