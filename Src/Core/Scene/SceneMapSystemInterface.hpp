#pragma once

namespace Core
{
    /*!
     * \brief Public interface for scene map system that should be used by game logic.
     */
    class SceneMapSystemInterface
    {
    public:
        SceneMapSystemInterface(const SceneMapSystemInterface& other) = delete;
        SceneMapSystemInterface(SceneMapSystemInterface&& other) = delete;
        SceneMapSystemInterface& operator=(const SceneMapSystemInterface& other) = delete;
        SceneMapSystemInterface& operator=(SceneMapSystemInterface&& other) = delete;
        SceneMapSystemInterface() = default;
        virtual ~SceneMapSystemInterface() = default;
    };
}