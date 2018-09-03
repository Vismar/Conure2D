#pragma once
#include "BaseScene.hpp"

namespace C2D
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

        /*!
         * \brief Adds new specified scene to the scene map.
         * \param newScene - shared pointer to the new scene that should be added.
         * \return True if scene was added. Otherwise, if scene with such name already added, false.
         */
        virtual bool AddScene(std::shared_ptr<BaseScene>&& newScene) = 0;

        /*!
         * \brief Grabs specified scene if it exists in scene map.
         * \param sceneName - name of a scene that should be returned.
         * \return Weak pointer to a specified scene.
         */
        virtual std::weak_ptr<BaseScene> GetScene(const std::string& sceneName) const = 0;

        /*!
         * \brief Removes specified scene from the scene map.
         * \param sceneName - name of the scene that should be removed.
         * \return True if scene was removed. Otherwise, if scene with such name does not exist, false.
         */
        virtual bool RemoveScene(const std::string& sceneName) = 0;

        /*!
         * \brief Sets render order of the scenes.
         * \param renderOrder - list of scene names that will be used as render order.
         *
         * Render order is used as a queue.
         * So first item in the list will be rendered earlier than others.
         * And the last item in the list will be rendered later than others. \n
         *
         * P.S. If new render order will not contain all scenes that are already (or will) exist
         * in the list, then not mentioned scenes will be added to the front of the list.
         */
        virtual void SetRenderOrder(const std::list<std::string>& renderOrder) = 0;
    };
}
