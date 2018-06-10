#pragma once
#include "BaseSceneInterface.hpp"
#include "Core/Scene/SceneObject.hpp"
#include "Core/Components/RenderableComponent.hpp"
#include <memory>
#include <mutex>

namespace Core
{
    /*!
     * \brief Base class for all scenes.
     * 
     * This base scene contains functionality to create scene objects 
     * and to aggregate renderable components that can be passed to a render system.
     */
    class BaseScene : public BaseSceneInterface
    {
    public:
        BaseScene() = delete;
        BaseScene(const BaseScene& other) = delete;
        BaseScene(BaseScene&& other) = delete;
        BaseScene& operator=(const BaseScene& other) = delete;
        BaseScene& operator=(BaseScene&& other) = delete;
        virtual ~BaseScene() = default;

        /*! 
         * \brief Default constructor.
         */
        explicit BaseScene(std::string_view sceneName);

        /*!
         * \brief Creates empty scene object.
         * \return Weak pointer to created scene object.
         */
        std::weak_ptr<SceneObject> CreateObject() final;

        /*!
         * \brief Sets activation flag to specified value.
         * \param activate - bool flag that will be applied to scene.
         */
        void Activate(bool activate) final;

        /*!
         * \brief Returns flag value that indicates the state of the scene..
         * \return True if scene was activated previously.
         */
        bool Activated() const final;

        /*!
         * \brief Marks the scene to be deleted when the time comes.
         */
        void DeleteLater() final;

        /*!
         * \brief Gets name of the scene.
         * \return Name of the scene.
         */
        const std::string& GetName() const final;

    protected:
        /*! Array of shared pointers to scene objects. */
        std::vector<std::shared_ptr<SceneObject>> _sceneObjects;

    private:
        /*!
         * \brief Grabs array of renderable components of the scene.
         * \return Shared pointer to the array of renderable components of the scene.
         * 
         * Removes all weak pointers from the array if they are not "alive".
         * Then adds new renderable components that was added during the render phase.
         * Returns shared pointer to updated array of weak pointers to renderable components of the scene.
         */
        std::shared_ptr<RenderableSet> GetRenderableComponents() const final;

        /*!
         * \brief Updates all scene objects one by one.
         * 
         * Do next things in described order: \n
         * 1) Calls Update() for every scene object. \n
         * 2) Calls LateUpdate() for every scene object.
         */
        void Update() final;

        /*!
         * \brief Checks if the scene was marked as to be deleted later.
         * \return True if it was marked as to be deleted later. Otherwise - false.
         */
        bool MarkedAsDeleteLater() const final;

        /*!
         * \brief Deletes all scene objects that were marked as "delete later".
         */
        void _DeleteMarkedObjects();

        /*!
         * \brief Callback that is used to add new renderable components to the renderable array 
         *        when a new component has been added to any scene object.
         * \param newComponent - weak pointer to the newly added component.
         * 
         * Callback that is bonded to every scene object and called when any of them has added a new component. 
         * Checks if the new component is a renderable component and then adds it to the array.
         */
        void _OnNewComponentAdded(std::weak_ptr<BaseComponent> newComponent);

        /*!
         * \brief Callback that is used to update renderable components in the set when they change their layer.
         * \param renderabelComponent - weak pointer to the renderable component that should be updated.
         * \param layer - new layer value. Not used.
         */
        void _OnRenderableComponentLayerChanged(std::weak_ptr<RenderableComponent> renderabelComponent, int8_t layer);

        const std::string _sceneName;
        /*! Flag that defines if scene should be deleted or not. */
        bool _deleteLater;
        /*! Simple flag that defines if scene is activated or not. Used to know if scene should be rendered. */
        std::atomic_bool _activated;
        /*! Set of renderable components that should be used by render system. */
        mutable std::shared_ptr<RenderableSet> _renderableComponents;
        /*! Array of renderable components that will be added to main array that goes to a render system. */
        mutable RenderableArray _renderableComponentsToAdd;
        /*! Mutex that used to update renderable arrays. */
        mutable std::mutex _renderableArrayMutex;
        /*! Array of shared pointers to scene objects that were created and should be added to main array before update phase. */
        std::vector<std::shared_ptr<SceneObject>> _newSceneObjects;
    };
}
