#pragma once
#include "Core/Scene/RenderableSceneMapInterface.hpp"
#include "Core/Scene/SceneMapSystemInterface.hpp"
#include "Core/Scene/BaseSceneInterface.hpp"

namespace Core
{
    /*!
     * \brief Scene map contains all scenes and provides functionality to work with them.
     */
    class SceneMap : public RenderableSceneMapInterface, public SceneMapSystemInterface
    {
    public:
        SceneMap(const SceneMap& other) = delete;
        SceneMap(SceneMap&& other) = delete;
        SceneMap& operator=(const SceneMap& other) = delete;
        SceneMap& operator=(SceneMap&& other) = delete;
        SceneMap() = default;
        ~SceneMap() override = default;

        /*!
         * \brief Adds new specified scene to the scene map.
         * \param newScene - shared pointer to the new scene that should be added.
         * \return True if scene was added. Otherwise, if scene with such name already added, false.
         */
        bool AddScene(std::shared_ptr<BaseScene>&& newScene) final;

        /*!
         * \brief Grabs specified scene if it exists in scene map.
         * \param sceneName - name of a scene that should be returned.
         * \return Weak pointer to a specified scene.
         */
        std::weak_ptr<BaseScene> GetScene(const std::string& sceneName) const final;

        /*!
         * \brief Removes specified scene from the scene map.
         * \param sceneName - name of the scene that should be removed.
         * \return True if scene was removed. Otherwise, if scene with such name does not exist, false.
         */
        bool RemoveScene(const std::string& sceneName) final;

        /*!
         * \brief Updates all scenes that stored in the scene map.
         * 
         * Goes through all scenes and updates them one by one. Update applied to a scene only if it active.
         */
        void UpdateScenes();

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
        void SetRenderOrder(const std::list<std::string>& renderOrder) final;

        /*!
         * \brief Returns list of scene names that should be interpreted as the render order.
         * \return Const reference to the list of the scene names.
         * 
         * First item in the list should be rendered earlier than others.
         * And the last item in the list should be rendered later than others.
         */
        const std::list<std::string>& GetRenderOrder() const final;

        /*!
         * \brief Grabs renderable components from the specified scene.
         * \param sceneName - name of the scene from which renderable components should be grabbed.
         * \return Shared pointer to the array of renderable components of the specified scene.
         * 
         * Array of renderable components was not sorted or filtered in any way,
         * so render system should do required operations before rendering if it is necessary.
         */
        std::shared_ptr<RenderableSet> GetRenderableComponentsFromScene(const std::string& sceneName) const final;

    private:
        /*!
         * \brief Adds specified scene name to the render order list.
         * \param newSceneName - name of the scene that should be added.
         * 
         * If such scene was not added to the render order, that it will be added to the front of the list.
         */
        void _AddSceneNameToRenderList(const std::string& newSceneName);

        /*! 
         * Simple list of the scene names that interpreted as a render order.
         * First item in the list should be rendered earlier, last item later.
         */
        std::list<std::string> _renderOrder;
        /*! Map of the scenes. */
        std::unordered_map<std::string, std::shared_ptr<BaseSceneInterface>> _scenes;
    };
}