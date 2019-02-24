#pragma once
#include <memory>
#include <typeindex>

namespace C2D
{
    class SceneObject;

    /*!
     * \brief Base class for all components.
     * 
     * Provides base functionality to compare components by its type index which is stored as protected member.
     */
    class [[deprecated("Will be reimplemented")]] BaseComponent : public std::enable_shared_from_this<BaseComponent>
    {
    public:
        BaseComponent() = delete;
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
        virtual ~BaseComponent() = default;

        /*!
         * \brief Constructor.
         */
        explicit BaseComponent(std::weak_ptr<SceneObject>&& sceneObject);

        /*!
         * \brief Comparison of two base components by their type info.
         * \return True if both components are the same type. Otherwise - false.
         */
        bool operator==(const BaseComponent& other) const;

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

    protected:
        /*! Type id of component. This variable is used in to identify identical components by its type. */
        std::type_index _typeIndex;

    private:
        /*! Weak pointer to the scene object that store this component. */
        std::weak_ptr<SceneObject> _sceneObject;

        friend bool operator==(const std::type_index& typeIndex, const BaseComponent& component);
    };

    /*!
     * \brief Comparison of specified type info as left value and component type info as right value.
     * \return True if type info and component are the same type. Otherwise - false.
     */
    inline bool operator==(const std::type_index& typeIndex, const BaseComponent& component)
    {
        return (typeIndex == component._typeIndex);
    }
}
