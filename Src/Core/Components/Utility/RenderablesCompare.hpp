#pragma once
#include <memory>

namespace Core
{
    class RenderableComponent;

    /*!
     * \brief Comparator for shared and weak pointers to RenderableComponent.
     */
    struct RenderablesCompare
    {
        using is_transparent = void;

        /*!
         * \brief Compares 2 shared pointers to RenderablComponent.
         * \param first - first shared pointer to RenderableComponent.
         * \param second - second shared pointer to RenderableComponent.
         * \return True if first RenderableComponent is lesser than second one.
         */
        bool operator() (const std::shared_ptr<RenderableComponent>& first,
                         const std::shared_ptr<RenderableComponent>& second) const;

        /*!
         * \brief Compares shared pointer to RenderablComponent and actual RenderableComponent.
         * \param first - shared pointer to RenderableComponent.
         * \param second - actual RenderableComponent.
         * \return True if first RenderableComponent is lesser than second one.
         */
        bool operator() (const std::shared_ptr<RenderableComponent>& first,
                         const RenderableComponent& second) const;
        
        /*!
         * \brief Compares actual RenderableComponent and shared pointer to RenderablComponent.
         * \param first - actual RenderableComponent.
         * \param second - shared pointer to RenderableComponent.
         * \return True if first RenderableComponent is lesser than second one.
         */
        bool operator() (const RenderableComponent& first,
                         const std::shared_ptr<RenderableComponent>& second) const;

        /*!
         * \brief Compares 2 weak pointers to RenderablComponent.
         * \param first - first weak pointer to RenderableComponent.
         * \param second - second weak pointer to RenderableComponent.
         * \return True if first RenderableComponent is lesser than second one.
         */
        bool operator() (const std::weak_ptr<RenderableComponent>& first,
                         const std::weak_ptr<RenderableComponent>& second) const;

        /*!
         * \brief Compares weak pointer to RenderablComponent and actual RenderableComponent.
         * \param first - weak pointer to RenderableComponent.
         * \param second - actual RenderableComponent.
         * \return True if first RenderableComponent is lesser than second one.
         */
        bool operator() (const std::weak_ptr<RenderableComponent>& first,
                         const RenderableComponent& second) const;

        /*!
         * \brief Compares actual RenderableComponent and weak pointer to RenderablComponent.
         * \param first - actual RenderableComponent.
         * \param second - shared pointer to RenderableComponent.
         * \return True if first RenderableComponent is lesser than second one.
         */
        bool operator() (const RenderableComponent& first,
                         const std::weak_ptr<RenderableComponent>& second) const;
    };
}
