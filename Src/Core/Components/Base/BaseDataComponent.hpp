#pragma once
#include "Core/Components/Base/BaseComponent.hpp"

namespace Core
{
    /*!
     * \brief Base class for all components which should store only data and can be attached to SceneObject.
     */
    class BaseDataComponent : public BaseComponent
    {
    public:
        BaseDataComponent() = delete;
        BaseDataComponent(const BaseDataComponent& other) = delete;
        BaseDataComponent(BaseDataComponent&& other) = delete;
        BaseDataComponent& operator=(const BaseDataComponent& other) = delete;
        BaseDataComponent& operator=(BaseDataComponent&& other) = delete;
        ~BaseDataComponent() override = default;

        /*!
         * \brief Constructor.
         */
        explicit BaseDataComponent(std::weak_ptr<SceneObject>&& sceneObject);

        /*!
         * \brief Initializes component.
         *
         * This is a virtual method with base implementation that is must be called after creating a component.
         * But it will be called by SceneObject upon creation. 
         */
        virtual void Initialize();

        /*!
         * \brief Resets component to a certain state.
         */
        virtual void Reset() = 0;
    };
}
