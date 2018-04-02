#pragma once
#include <memory>
#include "Core/Scene/SceneObject.hpp"
#include "Core/Components/RenderableComponent.hpp"
#include <mutex>

namespace Core
{
    /*! Simple alias to shorten the name of the type. */
    using RenderableArray = std::vector<std::weak_ptr<RenderableComponent>>;

    /*!
     * \brief Base class for all scenes.
     * 
     * This base scene contains functionality to create scene objects 
     * and to aggregate renderable components that can be passed to a render system.
     */
    class BaseScene
    {
    public:
        BaseScene(const BaseScene& other) = delete;
        BaseScene(BaseScene&& other) = delete;
        BaseScene& operator=(const BaseScene& other) = delete;
        BaseScene& operator=(BaseScene&& other) = delete;
        ~BaseScene() = default;

        /*! 
         * \brief Default constructor.
         */
        BaseScene();

        /*!
         * \brief Creates empty scene object.
         * \return Weak pointer to created scene object.
         */
        std::weak_ptr<SceneObject> CreateObject();

        /*!
         * \brief Sets activation flag to specified value.
         * \param activate - bool flag that will be applied to scene.
         */
        void Activate(const bool activate);

        /*!
         * \brief Returns flag value that indicates the state of the scene..
         * \return True if scene was activated previously.
         */
        bool Activated() const;

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
        std::shared_ptr<RenderableArray> _GetRenderableComponents() const;

        /*!
         * \brief Updates all scene objects one by one.
         * 
         * Do next things in described order: \n
         * 1) Calls Update() for every scene object. \n
         * 2) Calls LateUpdate() for every scene object.
         */
        void _Update();

        /*!
         * \brief Callback that is used to add new renderable components to the renderable array 
         *        when a new component has been added to any scene object.
         * \param newComponent - weak pointer to the newly added component.
         * 
         * Callback that is bonded to every scene object and called when any of them has added a new component. 
         * Checks if the new component is a renderable component and then adds it to the array.
         */
        void _OnNewComponentAdded(std::weak_ptr<BaseComponent> newComponent);

        /*! Simple flag that defines if scene is activated or not. Used to know if scene should be rendered. */
        bool _activated;
        /*! Array of renderable components that should be used by render system. */
        std::shared_ptr<RenderableArray> _renderableComponents;
        /*! Array of renderable components that will be added to main array that goes to a render system. */
        mutable RenderableArray _renderableComponentsToAdd;
        /*! Mutex that used to update renderable arrays. */
        mutable std::mutex _renderableArrayMutex;

        friend class SceneMap;
    };
}
