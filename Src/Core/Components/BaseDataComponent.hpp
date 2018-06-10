#pragma once
#include "Core/Components/BaseComponent.hpp"

namespace Core
{
    /*!
     * \brief Base class for all components which should store only data and can be attached to SceneObject.
     */
    class BaseDataComponent : public BaseComponent
    {
    public:
        BaseDataComponent() = default;
        BaseDataComponent(const BaseDataComponent& other) = default;
        BaseDataComponent(BaseDataComponent&& other) = default;
        BaseDataComponent& operator=(const BaseDataComponent& other) = default;
        BaseDataComponent& operator=(BaseDataComponent&& other) = default;
        virtual ~BaseDataComponent() = default;

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
