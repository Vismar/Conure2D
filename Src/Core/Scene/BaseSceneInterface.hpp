#pragma once
#include <string_view>
#include <set>
#include <memory>

namespace Core
{
    class SceneObject;
    class RenderableComponent;
    struct RenderablesCompare;
    class CameraComponent;
    struct CamerasCompare;

    /*!
     * \brief An interface for a BaseScene class.
     * 
     * Used in SceneMap to store all scenes and have access to certain functions 
     * that should not be publicly visible for an end user.
     */
    class BaseSceneInterface
    {
    public:
        BaseSceneInterface(const BaseSceneInterface& other) = delete;
        BaseSceneInterface(BaseSceneInterface&& other) = delete;
        BaseSceneInterface& operator=(const BaseSceneInterface& other) = delete;
        BaseSceneInterface& operator=(BaseSceneInterface&& other) = delete;
        BaseSceneInterface() = default;
        virtual ~BaseSceneInterface() = default;

        /*!
         * \brief Creates empty scene object.
         * \return Weak pointer to created scene object.
         */
        virtual std::weak_ptr<SceneObject> CreateObject() = 0;

        /*!
         * \brief Sets activation flag to specified value.
         * \param activate - bool flag that will be applied to scene.
         */
        virtual void Activate(bool activate) = 0;
        
        /*!
         * \brief Returns flag value that indicates the state of the scene..
         * \return True if scene was activated previously.
         */
        virtual bool Activated() const = 0;
        
        /*!
         * \brief Marks the scene to be deleted when the time comes.
         */
        virtual void DeleteLater() = 0;
        
        /*!
         * \brief Gets name of the scene.
         * \return Name of the scene.
         */
        virtual const std::string& GetName() const = 0;

        /*!
         * \brief Grabs array of renderable components of the scene.
         * \return Shared pointer to the array of renderable components of the scene.
         *
         * Removes all weak pointers from the array if they are not "alive".
         * Then adds new renderable components that was added during the render phase.
         * Returns shared pointer to updated array of weak pointers to renderable components of the scene.
         */
        virtual std::shared_ptr<std::set<std::weak_ptr<RenderableComponent>, RenderablesCompare>> GetRenderableComponents() const = 0;

        /*!
         * \brief Grabs array of camera components of the scene.
         * \return Shared pointer to the array of camera components of the scene.
         *
         * Removes all weak pointers from the array if they are not "alive".
         * Then adds new camera components that was added during the render phase.
         * Returns shared pointer to updated array of weak pointers to camera components of the scene.
         */
        virtual std::shared_ptr<std::set<std::weak_ptr<CameraComponent>, CamerasCompare>> GetCameraComponents() const = 0;

        /*!
         * \brief Updates all scene objects one by one.
         *
         * Do next things in described order: \n
         * 1) Calls Update() for every scene object. \n
         * 2) Calls LateUpdate() for every scene object.
         */
        virtual void Update() = 0;
        
        /*!
         * \brief Checks if the scene was marked as to be deleted later.
         * \return True if it was marked as to be deleted later. Otherwise - false.
         */
        virtual bool MarkedAsDeleteLater() const = 0;
    };
}