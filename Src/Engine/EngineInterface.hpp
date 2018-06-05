#pragma once

namespace Core
{
    class SceneMapSystemInterface;
}

namespace Input
{
    class InputSystemInterface;
}

namespace Renderer
{
    class RenderSystemInterface;
}

namespace Utility
{
    class TimeSpan;
    class IOSystemInterface;
    class LogSystem;
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
     * \brief Grabs input system.
     * \return Reference to the input system.
     */
    Input::InputSystemInterface& GetInputSystem();

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

    /*!
     * \brief Returns IO system.
     * \return Reference to the IO system.
     */
    Utility::IOSystemInterface& GetIOSystem();

    /*!
     * \brief Returns log system.
     * \return Reference to the log system.
     */
    Utility::LogSystem& GetLogSystem();
}
#include "EngineInterfaceDefinitions.inl"