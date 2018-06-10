#pragma once
#include "Core/Components/BaseComponent.hpp"
#include <atomic>
#include <memory>

namespace Core
{
    class SceneObject;

    /*!
     * \brief Base class for all components which should have some logic in it and can be attached to SceneObject.
     * 
     * This component contains basic functions that are required by all logic components.
     */
    class BaseLogicComponent : public BaseComponent
    {
    public:
        BaseLogicComponent() = delete;
        BaseLogicComponent(const BaseLogicComponent& other) = delete;
        BaseLogicComponent(BaseLogicComponent&& other) = delete;
        BaseLogicComponent& operator=(const BaseLogicComponent& other) = delete;
        BaseLogicComponent& operator=(BaseLogicComponent&& other) = delete;
        virtual ~BaseLogicComponent() = default;

        /*! 
         * \brief Default constructor.
         * \param sceneObject - shared pointer to the object which contains this component.
         * 
         * After creating a component, we MUST initialize it with Initialize() method of base class. 
         */
        explicit BaseLogicComponent(std::weak_ptr<SceneObject>&& sceneObject);

        /*!
         * \brief Return weak pointer to the scene object that contain this component.
         * \return Weak pointer to the scene object.
         */
        std::weak_ptr<SceneObject> GetSceneObject() const;

        /*!
         * \brief Check if component is turned on.
         * \return True if component is turned on. Otherwise - false.
         */
        bool IsTurnedOn() const;

        /*!
        * \brief Turns component on/off.
        * \param turnOn - flag that defines if component should be turned on or off.
        */
        void TurnOn(bool turnOn = true);

    protected:
        /*!
         * \brief Initializes component.
         *
         * This is a virtual method with base implementation that is must be called after creating a component.
         * But it will be called by SceneObject upon creation.
         */
        virtual void Initialize();

        /*!
         * \brief Function that is called in every game loop.
         */
        virtual void Update() = 0;

        /*!
         * \brief Function that is called in every game loop when all "Update" functions were already called.
         */
        virtual void LateUpdate() = 0;

    private:
        /*! Weak pointer to the scene object that store this component. */
        std::weak_ptr<SceneObject> _sceneObject;
        /*! Flag that identifies if component is turned on or not. */
        std::atomic_bool _turnedOn;

        friend class SceneObject;
    };
}
