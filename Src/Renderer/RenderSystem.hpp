#pragma once
#include "Core/Scene/RenderableSceneMapInterface.hpp"
#include "Input/InputSystemHandlerInterface.hpp"
#include "Renderer/RenderSystemInterface.hpp"
#include "Renderer/Window/Window.hpp"
#include "Utility/Time/TimeSpan.hpp"
#include <mutex>

namespace Renderer
{
    /*!
     * \brief System that handles render process.
     * 
     * Render system require SceneMap from which it will gather data to render.
     */
    class RenderSystem : public RenderSystemInterface
    {
    public:
        RenderSystem(const RenderSystem& other) = delete;
        RenderSystem(RenderSystem&& other) = delete;
        RenderSystem& operator=(const RenderSystem& other) = delete;
        RenderSystem& operator=(RenderSystem&& other) = delete;
        ~RenderSystem() = default;
        
        /*!
         * \brief Default constructor.
         */
        RenderSystem();        

        /*!
         * \brief Starts the rendering process with specified scene map.
         * \param sceneMap - const reference to a scene map that will be used in render process.
         * \param inputSystem - reference to input system which will handle input events from the window.
         * \param renderLoopTimeSpan - time span of render loop.
         */
        void Start(const Core::RenderableSceneMapInterface& sceneMap, 
                   Input::InputSystemHandlerInterface& inputSystem,
                   Utility::TimeSpan& renderLoopTimeSpan);

        /*!
         * \brief Stops render process.
         */
        void Stop();

        /*!
         * \brief Checks if render system has no errors.
         * \return True if render system working as intended.
         */
        bool NoErrors() const;

        /*!
         * \brief Applies new settings to window.
         * \param windowSettings - specified window settings.
         */
        void SetNewSettings(WindowSettings windowSettings) final;

        /*!
         * \brief Gets copy of window settings that are currently applied to the window.
         * \return Copy of window settings.
         */
        WindowSettings GetSettings() const final;

        /*!
         * \brief Sets new title to the window.
         * \param title - new title that will be used by window.
         */
        void SetWindowTitle(const std::string& title) final;

        /*!
         * \brief Resizes window to specified size.
         * \param width - new width of the window.
         * \param height - new height of the window.
         */
        void SetWindowSize(uint32_t width, uint32_t height) final;

        /*!
         * \brief Resizes window resolution to specified values.
         * \param width - new width of the window resolution.
         * \param height - new height of the window resolution.
         */
        void SetWindowResolution(uint32_t width, uint32_t height) final;

        /*!
         * \brief Sets new antialiasing level.
         * \param antialiasingLevel - new level of antialiasing.
         */
        void SetAntialiasing(uint32_t antialiasingLevel) final;

        /*!
         * \brief Turns vertical sync On/Off.
         * \param enabled - flag that defines if vertical sync should be turned on or off.
         */
        void SetVerticalSyncEnabled(bool enabled) final;

        /*!
         * \brief Sets framerate limit a maximum fixed frequency.
         * \param frameLimit - new framerate limit, in frames per seconds (use 0 to disable limit).
         */
        void SetFramerateLimit(uint32_t frameLimit) final;

        /*!
         * \brief Turns on or off visibility of the mouse cursor.
         * \param visible - flag that defines if mouse cursor should be visible or not.
         */
        void SetMouseCursorVisible(bool visible) final;

        /*!
         * \brief Grabs or releases the mouse cursor.
         * \param grabbed - flag that defines if mouse cursor should be grabbed or not.
         */
        void SetMouseCursorGrabbed(bool grabbed) final;

    private:
        /*!
         * \brief Updates window.
         * 
         * Checks flags and recreates or updates the window if is necessary. 
         */
        void _UpdateWindow();

        /*! Simple flag that defines if render system currently working. */
        std::atomic<bool> _working;
        /*! Simple flag that defines if render system works correctly. */
        std::atomic<bool> _noErrors;
        /*! Mutex that is used to lock window settings. */
        mutable std::mutex _settingsMutex;
        /*! Simple flag that defines if window should be recreated. */
        std::atomic<bool> _recreateWindow;
        /*! Simple flag that defines if window parameters was updated. */
        std::atomic<bool> _updateWindowParameters;
        /*! Current window settings that is used by window. */
        WindowSettings _settings;
        /*! Window to which render system is drawing everything and from which polling events. */
        Window _window;
    };
}
