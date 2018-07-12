#pragma once
#include "Render/Window/WindowSettings.hpp"

namespace Render
{
    /*!
     * \brief Public interface for render system that should be used by game logic.
     */
    class RenderSystemInterface
    {
    public:
        RenderSystemInterface(const RenderSystemInterface& other) = delete;
        RenderSystemInterface(RenderSystemInterface&& other) = delete;
        RenderSystemInterface& operator=(const RenderSystemInterface& other) = delete;
        RenderSystemInterface& operator=(RenderSystemInterface&& other) = delete;
        RenderSystemInterface() = default;
        virtual ~RenderSystemInterface() = default;

        /*!
         * \brief Applies new settings to window.
         * \param windowSettings - specified window settings.
         */
        virtual void SetNewSettings(WindowSettings windowSettings) = 0;

        /*!
         * \brief Gets copy of window settings that are currently applied to the window.
         * \return Copy of window settings.
         */
        virtual WindowSettings GetSettings() const = 0;

        /*!
         * \brief Sets new title to the window.
         * \param title - new title that will be used by window.
         */
        virtual void SetWindowTitle(const std::string& title) = 0;

        /*!
         * \brief Resizes window to specified size.
         * \param width - new width of the window.
         * \param height - new height of the window.
         */
        virtual void SetWindowSize(uint32_t width, uint32_t height) = 0;

        /*!
         * \brief Resizes window resolution to specified values.
         * \param width - new width of the window resolution.
         * \param height - new height of the window resolution.
         */
        virtual void SetWindowResolution(uint32_t width, uint32_t height) = 0;

        /*!
         * \brief Sets new antialiasing level.
         * \param antialiasingLevel - new level of antialiasing.
         */
        virtual void SetAntialiasing(uint32_t antialiasingLevel) = 0;

        /*!
         * \brief Turns vertical sync On/Off.
         * \param enabled - flag that defines if vertical sync should be turned on or off.
         */
        virtual void SetVerticalSyncEnabled(bool enabled) = 0;

        /*!
         * \brief Sets framerate limit a maximum fixed frequency.
         * \param frameLimit - new framerate limit, in frames per seconds (use 0 to disable limit).
         */
        virtual void SetFramerateLimit(uint32_t frameLimit) = 0;

        /*!
         * \brief Turns on or off visibility of the mouse cursor.
         * \param visible - flag that defines if mouse cursor should be visible or not.
         */
        virtual void SetMouseCursorVisible(bool visible) = 0;

        /*!
         * \brief Grabs or releases the mouse cursor.
         * \param grabbed - flag that defines if mouse cursor should be grabbed or not.
         */
        virtual void SetMouseCursorGrabbed(bool grabbed) = 0;
    };
}