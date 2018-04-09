#pragma once

namespace Renderer
{
    class RenderSystemInterface;
}

namespace Core
{
    class SceneMapSystemInterface;
}

namespace Engine
{
    /*!
     * \brief Grabs render system.
     * \return Reference to the render system.
     */
    Renderer::RenderSystemInterface& GetRenderSystem();

    /*!
     * \brief Grabs scene map system.
     * \return Reference to the scene map system.
     */
    Core::SceneMapSystemInterface& GetSceneMapSystem();
}
