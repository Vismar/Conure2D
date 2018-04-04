#pragma once
#include "Core/Scene/RenderableSceneMapInterface.hpp"
#include "Window/Window.hpp"

namespace Renderer
{
    /*!
     * \brief System that handles render process.
     * 
     * Render system require SceneMap from which it will gather data to render.
     */
    class RenderSystem
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
         * \param sceneMap - shared pointer to the scene map that will be used in render process.
         */
        void Start(const std::shared_ptr<Core::RenderableSceneMapInterface>& sceneMap);

        /*!
         * \brief Stops render process.
         */
        void Stop();

        /*!
         * \brief Checks if render system is currently rendering.
         * \return True if render system was previously started.
         */
        bool Working() const;

    private:
        /*! Simple flag that defines if render system currently working. */
        std::atomic<bool> _working;
        /*! Window to which render system is drawing everything and from which polling events. */
        Window _window;
        /*! Shared pointer to the scene map that is used in render process. */
        std::shared_ptr<Core::RenderableSceneMapInterface> _sceneMap;
    };
}
