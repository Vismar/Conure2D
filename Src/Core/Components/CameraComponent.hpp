#pragma once
#include "Core/Components/Base/BaseDataComponent.hpp"
#include "Core/Components/Utility/CamerasCompare.hpp"
#include "Utility/EventSystem/EventManager.hpp"
#include "Utility/Math/Vector2.hpp"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <set>

namespace C2D
{
    class TransformComponent;

    /*!
     * \brief Base component for all camera components.
     *
     * Simple data component that stores parameters that are required to create sf::View
     * and provides basic functionality to change them. Creates sf::View in depends on data from TransformComponent.
     */
    class CameraComponent : public BaseDataComponent, public EventManager
    {
    public:
        CameraComponent() = delete;
        ~CameraComponent() override = default;
        CameraComponent(const CameraComponent& other) = delete;
        CameraComponent(CameraComponent&& other) = delete;
        CameraComponent& operator=(const CameraComponent& other) = delete;
        CameraComponent& operator=(CameraComponent&& other) = delete;

        /*!
         * \brief Default constructor.
         * \param sceneObject - weak pointer to the object which contains this component.
         */
        explicit CameraComponent(std::weak_ptr<SceneObject>&& sceneObject);

        /*!
         * \brief Operator "lesser".
         * \param right - another camera component to compare.
         * \return True if this component lesser than an operator on the right side of the operator.
         *
         * Compares priority numbers of camera components. Virtual function, can be overridden.
         */
        virtual bool operator<(const CameraComponent& right) const;

        /*!
         * \brief Operator "greater".
         * \param right - another camera component to compare.
         * \return True if this component greater than an operator on the right side of the operator.
         *
         * Only uses "operator<", so no need to override this operator.
         */
        bool operator>(const CameraComponent& right) const;

        /*!
         * \brief Operator "lesser or equal".
         * \param right - another camera component to compare.
         * \return True if this component lesser or equal to an operator on the right side of the operator.
         *
         * Only uses "operator>", so no need to override this operator.
         */
        bool operator<=(const CameraComponent& right) const;

        /*!
         * \brief Operator "greater or equal".
         * \param right - another camera component to compare.
         * \return True if this component greater or equal to an operator on the right side of the operator.
         *
         * Only uses "operator<", so no need to override this operator.
         */
        bool operator>=(const CameraComponent& right) const;

        /*!
         * \brief Conversion operator to sf::View.
         * \return Returns new sf::View variable that was generated from stored data in camera and transform components.
         */
        explicit operator sf::View() const;

        /*!
         * \brief Set new priority of a camera component.
         * \param newPriority - new priority that will be used by camera component.
         */
        void SetPriority(uint8_t newPriority);

        /*!
         * \brief Gets current priority of a camera component.
         * \return Current priority of a camera component.
         */
        uint8_t GetPriority() const;

        /*!
         * \brief Sets new size of a camera view.
         * \param newSize - new size of a camera view.
         */
        void SetSize(const Vector2f& newSize);

        /*!
         * \brief Gets current size of a camera view.
         * \return Current size of a camera view.
         */
        Vector2f GetSize() const;

        /*!
         * \brief Sets new viewport for a camera.
         * \param newViewport - rectangular shaped screen section which camera will represent.
         *                      Stores coordinates of the top-left and bottom-right corners.
         *                      Each value should be in range of [0.0f..1.0f].
         *                      0.0f - left/top of a screen, 1.0f - right/bottom of a screen.
         */
        void SetViewport(const sf::FloatRect& newViewport);

        /*!
         * \brief Gets current viewport rectangle.
         * \return Rectangle which stores coordinates of the top-left and bottom-right corners.
         */
        sf::FloatRect GetViewport() const;

    protected:
        /*!
         * \brief Initializes component.
         *
         * Initializes component in such way that any inherited components will have
         * the same characteristics in comparison,
         * so scene object will not be able to store more than one camera component.
         */
        void Initialize() override;

        /*! Weak pointer to a transform component which used by camera component to get its coordinates. */
        std::weak_ptr<TransformComponent> _transformComponent;

    private:
        /*! Priority of a camera. The lesser the number, the prior the camera. */
        std::atomic_uint8_t _priority;
        /*! Size of a view. */
        Vector2af _size;
        /*! Left coordinate of a viewport of a view. */
        std::atomic<float> _viewportLeftCoord;
        /*! Top coordinate of a viewport of a view. */
        std::atomic<float> _viewportTopCoord;
        /*! Width of a viewport of a view. */
        std::atomic<float> _viewportWidth;
        /*! Height of a viewport of a view. */
        std::atomic<float> _viewportHeight;
    };

    /*! Simple alias to shorten the name of the vector of weak pointers to camera components. */
    using CameraArray = std::vector<std::weak_ptr<CameraComponent>>;
    /*! Simple alias to shorten the name of the set of weak pointers to camera components. */
    using CameraSet = std::set<std::weak_ptr<CameraComponent>, CamerasCompare>;
}