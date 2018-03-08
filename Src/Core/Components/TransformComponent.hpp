#pragma once
#include "Core/Base/BaseComponent.hpp"
#include "Utility/EventSystem/EventManager.hpp"
#include "Utility/Math/AtomicVector2.hpp"

namespace Core
{
    /*!
     * \brief Transform component contains all required transform data such as origin point, position, rotation, and scale.
     * 
     * This component attached to every SceneObject and cannot be removed from it.
     * Transform is used to describe position and orientation of an object in a game space.
     * Every piece of data stored as atomic, so all changes to it is thread-safe.
     */
    class TransformComponent final : public BaseComponent, public Utility::EventManager
    {
    public:
        TransformComponent() = delete;
        TransformComponent(const TransformComponent& other) = delete;
        TransformComponent(TransformComponent&& other) = delete;
        TransformComponent& operator=(const TransformComponent& other) = delete;
        TransformComponent& operator=(TransformComponent&& other) = delete;
        ~TransformComponent() = default;

        /*! Default constructor. */
        explicit TransformComponent(const std::shared_ptr<SceneObject>& sceneObject);

        /*!
         * \brief Returns transform origin.
         * \return Const reference to a float atomic vector that contains transform origin.
         */
        const Utility::AtomicVector2F& GetOrigin() const;

        /*!
         * \brief Sets transform origin to specified values.
         * \param newOriginX - X value of new transform origin.
         * \param newOriginY - Y value of new transform origin.
         */
        void SetOrigin(const float newOriginX, const float newOriginY);

        /*!
         * \brief Sets transform origin to specified value.
         * \param newOrigin - const reference to a new transform origin.
         */
        void SetOrigin(const Utility::AtomicVector2F& newOrigin);

        /*!
         * \brief Returns transform position.
         * \return Const reference to a float atomic vector that contains transform position.
         */
        const Utility::AtomicVector2F& GetPosition() const;

        /*!
         * \brief Sets transform position to specified values.
         * \param newPositionX - X value of new transform position.
         * \param newPositionY - Y value of new transform position.
         */
        void SetPosition(const float newPositionX, const float newPositionY);

        /*!
         * \brief Sets transform position to specified value.
         * \param newPosition - const reference to a new transform position.
         */
        void SetPosition(const Utility::AtomicVector2F& newPosition);

        /*!
         * \brief Moves transform position by specified offset values.
         * \param offsetX - X value of offset.
         * \param offsetY - Y value of offset.
         */
        void Move(const float offsetX, const float offsetY);

        /*!
         * \brief Moves transform position by specified offset value.
         * \param offset - const reference to an atomic offset vector.
         */
        void Move(const Utility::AtomicVector2F& offset);

        /*!
         * \brief Returns transform rotation.
         * \return A float value of transform rotation.
         */
        float GetRotation() const;

        /*!
         * \brief Sets transform rotation to specified value.
         * \param newRotation - rotation that will be set as new transform rotation.
         */
        void SetRotation(const float newRotation);

        /*!
         * \brief Rotates transform rotation by specified degree.
         * \param angle - angle value that will add to transform rotation.
         */
        void Rotate(const float angle);

        /*!
         * \brief Returns transform scale.
         * \return Const reference to a float atomic vector that contains transform scale.
         */
        const Utility::AtomicVector2F& GetScale() const;

        /*!
         * \brief Sets transform scale to specified values.
         * \param newScaleX - X value of new transform scale.
         * \param newScaleY - Y value of new transform scale.
         */
        void SetScale(const float newScaleX, const float newScaleY);

        /*!
         * \brief Sets transform position to specified value.
         * \param newScale - const reference to a new transform scale.
         */
        void SetScale(const Utility::AtomicVector2F& newScale);

        /*!
         * \brief Scales(multiply) transform scale by specified factor values.
         * \param factorX - X value of factor.
         * \param factorY - Y value of factor.
         */
        void Scale(const float factorX, const float factorY);

        /*!
         * \brief Scales(multiply) transform scale by specified factor value.
         * \param factor - const reference to an atomic factor vector.
         */
        void Scale(const Utility::AtomicVector2F& factor);
        
    protected:
        /*!
         * \brief Creates necessary events.
         */
        void Initialize() final;
        /*!
         * \brief Empty function.
         */
        void Update() final;
        /*!
         * \brief Invokes events if necessary.
         */
        void LateUpdate() final;

    private:
        /*! Simple flag to identify if transform was updated and we should invoke "OnTransformUpdate" event. */
        std::atomic<bool> _transformUpdated;
        /*! Transform origin. */
        Utility::AtomicVector2F _origin;
        /*! Transform position. */
        Utility::AtomicVector2F _position;
        /*! Transform rotation. */
        std::atomic<float> _rotation;
        /*! Transform scale. */
        Utility::AtomicVector2F _scale;
    };
}
