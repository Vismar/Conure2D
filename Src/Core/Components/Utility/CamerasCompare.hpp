#pragma once
#include <memory>

namespace Core
{
    class CameraComponent;

    /*!
     * \brief Comparator for shared and weak pointers to CameraComponent.
     */
    struct CamerasCompare
    {
        using is_transparent = void;

        /*!
         * \brief Compares 2 shared pointers to CameraComponent.
         * \param first - first shared pointer to CameraComponent.
         * \param second - second shared pointer to CameraComponent.
         * \return True if first CameraComponent is lesser than second one.
         */
        bool operator() (const std::shared_ptr<CameraComponent>& first,
                         const std::shared_ptr<CameraComponent>& second) const;

        /*!
         * \brief Compares shared pointer to CameraComponent and actual CameraComponent.
         * \param first - shared pointer to CameraComponent.
         * \param second - actual CameraComponent.
         * \return True if first CameraComponent is lesser than second one.
         */
        bool operator() (const std::shared_ptr<CameraComponent>& first,
                         const CameraComponent& second) const;

        /*!
         * \brief Compares actual CameraComponent and shared pointer to CameraComponent.
         * \param first - actual CameraComponent.
         * \param second - shared pointer to CameraComponent.
         * \return True if first CameraComponent is lesser than second one.
         */
        bool operator() (const CameraComponent& first,
                         const std::shared_ptr<CameraComponent>& second) const;

        /*!
         * \brief Compares 2 weak pointers to CameraComponent.
         * \param first - first weak pointer to CameraComponent.
         * \param second - second weak pointer to CameraComponent.
         * \return True if first CameraComponent is lesser than second one.
         */
        bool operator() (const std::weak_ptr<CameraComponent>& first,
                         const std::weak_ptr<CameraComponent>& second) const;

        /*!
         * \brief Compares weak pointer to CameraComponent and actual CameraComponent.
         * \param first - weak pointer to CameraComponent.
         * \param second - actual CameraComponent.
         * \return True if first CameraComponent is lesser than second one.
         */
        bool operator() (const std::weak_ptr<CameraComponent>& first,
                         const CameraComponent& second) const;

        /*!
         * \brief Compares actual CameraComponent and weak pointer to CameraComponent.
         * \param first - actual CameraComponent.
         * \param second - shared pointer to CameraComponent.
         * \return True if first CameraComponent is lesser than second one.
         */
        bool operator() (const CameraComponent& first,
                         const std::weak_ptr<CameraComponent>& second) const;
    };
}