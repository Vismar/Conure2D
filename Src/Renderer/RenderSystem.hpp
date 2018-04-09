#pragma once
#include "Core/Scene/RenderableSceneMapInterface.hpp"
#include "Renderer/RenderSystemInterface.hpp"
#include "Renderer/Window/Window.hpp"
#include "Utility/Time/TimeSpan.hpp"

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
         * \param renderLoopTimeSpan - time span of render loop.
         */
        void Start(const Core::RenderableSceneMapInterface& sceneMap, Utility::TimeSpan& renderLoopTimeSpan);

        /*!
         * \brief Stops render process.
         */
        void Stop();

        /*!
         * \brief Checks if render system has no errors.
         * \return True if render system working as intended.
         */
        bool NoErrors() const;

    private:
        /*! Simple flag that defines if render system currently working. */
        std::atomic<bool> _working;
        /*! Simple flag that defines if render system works correctly. */
        std::atomic<bool> _noErrors;
        /*! Window to which render system is drawing everything and from which polling events. */
        Window _window;
    };
}
