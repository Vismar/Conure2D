#pragma once

namespace Renderer
{
    class RenderSystemInterface;
}

namespace Core
{
    class SceneMapSystemInterface;
}

namespace Utility
{
    class TimeSpan;
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

    /*!
     * \brief Grabs render loop time span.
     * \return Const reference to the time span of the render loop.
     */
    const Utility::TimeSpan& GetRenderLoopTimeSpan();

    /*!
     * \brief Grabs logic loop time span.
     * \return Const reference to the time span of the logic loop.
     */
    const Utility::TimeSpan& GetLogicLoopTimeSpan();
}
