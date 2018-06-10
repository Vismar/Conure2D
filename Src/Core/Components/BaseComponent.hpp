#pragma once
#include <memory>
#include <typeindex>

namespace Core
{
    /*!
     * \brief Base class for all components.
     * 
     * Provides base functionality to compare components by its type index which is stored as protected member.
     */
    class BaseComponent : public std::enable_shared_from_this<BaseComponent>
    {
    public:
        BaseComponent(const BaseComponent& other) = default;
        BaseComponent(BaseComponent&& other) = default;
        BaseComponent& operator=(const BaseComponent& other) = default;
        BaseComponent& operator=(BaseComponent&& other) = default;
        virtual ~BaseComponent() = default;

        /*!
         * \brief Default constructor.
         */
        BaseComponent();

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

    protected:
        /*! Type id of component. This variable is used in to identify identical components by its type. */
        std::type_index _typeIndex;

    private:
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
