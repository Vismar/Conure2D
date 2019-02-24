#pragma once

namespace C2D
{
    //Core
    class SceneMapSystemInterface;

    // Input
    class InputSystemInterface;

    // Render
    class RenderSystemInterface;

    // Utility
    class TimeSpan;
    //class IOSystemInterface;
    //class LogSystem;

    /*!
     * \brief Grabs render system.
     * \return Reference to the render system.
     */
    RenderSystemInterface& GetRenderSystem();

    /*!
     * \brief Grabs scene map system.
     * \return Reference to the scene map system.
     */
    SceneMapSystemInterface& GetSceneMapSystem();

    /*!
     * \brief Grabs input system.
     * \return Reference to the input system.
     */
    InputSystemInterface& GetInputSystem();

    /*!
     * \brief Grabs render loop time span.
     * \return Const reference to the time span of the render loop.
     */
    //const TimeSpan& GetRenderLoopTimeSpan();

    /*!
     * \brief Grabs logic loop time span.
     * \return Const reference to the time span of the logic loop.
     */
    //const TimeSpan& GetLogicLoopTimeSpan();

    /*!
     * \brief Returns IO system.
     * \return Reference to the IO system.
     */
    //IOSystemInterface& GetIOSystem();

    /*!
     * \brief Returns log system.
     * \return Reference to the log system.
     */
    //LogSystem& GetLogSystem();
}
#include "EngineInterfaceDefinitions.inl"