#pragma once
#include <typeindex>
#include <atomic>
#include <memory>

namespace Core
{
    class SceneObject;

    /*!
     * \brief Base class for all components that can be attached to SceneObject.
     * 
     * This component contains basic functions that are required by all components 
     * and provides functionality to compare them by its type so only 1 component of 1 type can be attached to SceneObject.
     */
    class BaseLogicComponent : public std::enable_shared_from_this<BaseLogicComponent>
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
        explicit BaseLogicComponent(const std::shared_ptr<SceneObject>& sceneObject);
        
        /*!
         * \brief Comparison of two base components by their type info.
         * \return True if both components are the same type. Otherwise - false.
         */
        bool operator==(const BaseLogicComponent& other) const;

        /*!
         * \brief Comparison of component type info as left value and specified type info as right value.
         * \return True if component and type info are the same type. Otherwise - false.
         */
        bool operator==(const std::type_index& typeIndex) const;

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
        std::atomic<bool> _turnedOn;
        /*! Type id of component. This variable is used in to identify identical components by its type. */
        std::type_index _typeIndex;

        friend bool operator==(const std::type_index& typeIndex, const BaseLogicComponent& component);
        friend class SceneObject;
        friend class RenderableComponent;
    };

    /*!
     * \brief Comparison of specified type info as left value and component type info as right value.
     * \return True if type info and component are the same type. Otherwise - false.
     */
    inline bool operator==(const std::type_index& typeIndex, const BaseLogicComponent& component)
    {
        return (typeIndex == component._typeIndex);
    }
}
