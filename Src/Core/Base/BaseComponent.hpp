#pragma once
#include <typeinfo>
#include <atomic>
#include <memory>

namespace Core
{
    //class SceneObject;

    /*!
     * \brief Base for all components that can be attached to SceneObject.
     * 
     * This component contains basic functions that are required by all components 
     * and provides functionality to compare them by its type so only 1 component of 1 type can be attached to SceneObject.
     */
    class BaseComponent : public std::enable_shared_from_this<BaseComponent>
    {
    public:
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;

        /*! 
         * \brief Default constructor.
         * 
         * After creating a component, we MUST initialize it with Initialize() method of base class. 
         */
        BaseComponent();
        
        /*!
         * \brief Default destructor.
         */
        virtual ~BaseComponent() = default;
        
        /*!
         * \brief Comparison of two base components by their type info.
         */
        bool operator==(const BaseComponent& other) const;

        /*!
         * \brief Comparison of component type info as left value and specified type info as right value.
         */
        bool operator==(const std::type_info& typeInfo) const;

        //shared_ptr<SceneObject> GetSceneObject() const;

        /*!
         * \brief Check if component is turned on.
         * \return True if component is turned on. Otherwise - false.
         */
        bool IsTurnedOn() const;

        /*!
         * \brief Turns component on/off.
         * \param turnOn - flag that defines if component should be turned on or off.
         */
        void TurnOn(const bool turnOn = true);
                
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
        //shared_ptr<SceneObject> _sceneObject;
        /*! Flag that identifies if component is turned on or not. */
        std::atomic<bool> _turnedOn;
        /*! 
         * \brief Type id of component. 
         * 
         * This variable is used in to identify identical components by its type.
         */
        std::type_info* _typeInfo;

        friend bool operator==(const std::type_info& typeInfo, const BaseComponent& component);
    };

    /*!
     * \brief Comparison of specified type info as left value and component type info as right value.
     */
    inline bool operator==(const std::type_info& typeInfo, const BaseComponent& component)
    {
        return (typeInfo == *component._typeInfo);
    }
}
