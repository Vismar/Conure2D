#pragma once
#include "Core/Components/RenderableComponent.hpp"
#include <list>
#include <memory>

namespace  Core
{
    /*!
     * \brief Interface for scene map that can be rendered by render system.
     */
    class RenderableSceneMapInterface
    {
    public:
        RenderableSceneMapInterface(const RenderableSceneMapInterface& other) = delete;
        RenderableSceneMapInterface(RenderableSceneMapInterface&& other) = delete;
        RenderableSceneMapInterface& operator=(const RenderableSceneMapInterface& other) = delete;
        RenderableSceneMapInterface& operator=(RenderableSceneMapInterface&& other) = delete;
        RenderableSceneMapInterface() = default;
        virtual ~RenderableSceneMapInterface() = default;

        /*!
         * \brief Returns list of scene names that should be interpreted as the render order.
         * \return Const reference to the list of the scene names.
         *
         * First item in the list should be rendered earlier than others.
         * And the last item in the list should be rendered later than others.
         */
        virtual const std::list<std::string>& GetRenderOrder() const = 0;

        /*!
         * \brief Grabs renderable components from the specified scene.
         * \param sceneName - name of the scene from which renderable components should be grabbed.
         * \return Shared pointer to the array of renderable components of the specified scene.
         *
         * Array of renderable components was not sorted or filtered in any way,
         * so render system should do required operations before rendering if it is necessary.
         */
        virtual std::shared_ptr<RenderableSet> GetRenderableComponentsFromScene(const std::string& sceneName) const = 0;
    };
}
