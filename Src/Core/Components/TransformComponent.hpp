#pragma once
#include "Core/Components/BaseComponent.hpp"
#include "Utility/EventSystem/EventManager.hpp"
#include "Utility/Math/AtomicVector2.hpp"
#include <SFML/Graphics/Transform.hpp>

namespace Core
{
    /*!
     * \brief Simple container to store basic transformations of an object.
     * 
     * This container created specifically to gather basic transformations in one place and modify them.
     * It is used to obtain or assign transformations to transform component.
     */
    struct Transformations
    {
        /*! Position. */
        sf::Vector2f position;
        /*! Rotation. */
        float rotation = 0.0f;
        /*! Scale. */
        sf::Vector2f scale;
    };

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

        /*! \brief Default constructor. */
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
         * \param newOrigin - const reference to a new transform origin (sf::Vector2f).
         */
        void SetOrigin(const sf::Vector2f& newOrigin);

        /*!
         * \brief Sets transform origin to specified value.
         * \param newOrigin - const reference to a new transform origin (Utility::AtomicVector2F).
         */
        void SetOrigin(const Utility::AtomicVector2F& newOrigin);

        /*!
         * \brief Returns global transform position.
         * \return Const reference to a float atomic vector that contains global transform position.
         */
        const Utility::AtomicVector2F& GetGlobalPosition() const;

        /*!
         * \brief Returns local transform position.
         * \return Const reference to a float atomic vector that contains local transform position.
         */
        const Utility::AtomicVector2F& GetPosition() const;

        /*!
         * \brief Sets local transform position to specified values.
         * \param newPositionX - X value of new local transform position.
         * \param newPositionY - Y value of new local transform position.
         */
        void SetPosition(const float newPositionX, const float newPositionY);

        /*!
         * \brief Sets local transform position to specified value.
         * \param newPosition - const reference to a new local transform position (sf::Vector2f).
         */
        void SetPosition(const sf::Vector2f& newPosition);

        /*!
         * \brief Sets local transform position to specified value.
         * \param newPosition - const reference to a new local transform position (Utility::AtomicVector2F).
         */
        void SetPosition(const Utility::AtomicVector2F& newPosition);

        /*!
         * \brief Moves local transform position by specified offset values.
         * \param offsetX - X value of offset.
         * \param offsetY - Y value of offset.
         */
        void Move(const float offsetX, const float offsetY);

        /*!
         * \brief Moves local transform position by specified offset value.
         * \param offset - const reference to an atomic offset vector.
         */
        void Move(const Utility::AtomicVector2F& offset);

        /*!
         * \brief Returns global transform rotation.
         * \return A float value of global transform rotation.
         */
        float GetGlobalRotation() const;

        /*!
         * \brief Returns local transform rotation.
         * \return A float value of local transform rotation.
         */
        float GetRotation() const;

        /*!
         * \brief Sets local transform rotation to specified value.
         * \param newRotation - rotation that will be set as new local transform rotation.
         */
        void SetRotation(const float newRotation);

        /*!
         * \brief Rotates local transform rotation by specified degree.
         * \param angle - angle value that will add to local transform rotation.
         */
        void Rotate(const float angle);

        /*!
         * \brief Returns global transform scale.
         * \return Const reference to a float atomic vector that contains global transform scale.
         */
        const Utility::AtomicVector2F& GetGlobalScale() const;

        /*!
         * \brief Returns local transform scale.
         * \return Const reference to a float atomic vector that contains local transform scale.
         */
        const Utility::AtomicVector2F& GetScale() const;

        /*!
         * \brief Sets local transform scale to specified values.
         * \param newScaleX - X value of new local transform scale.
         * \param newScaleY - Y value of new local transform scale.
         */
        void SetScale(const float newScaleX, const float newScaleY);

        /*!
         * \brief Sets local transform scale to specified value.
         * \param newScale - const reference to a new local transform scale (sf::Vector2f).
         */
        void SetScale(const sf::Vector2f& newScale);

        /*!
         * \brief Sets local transform scale to specified value.
         * \param newScale - const reference to a new local transform scale (Utility::AtomicVector2F).
         */
        void SetScale(const Utility::AtomicVector2F& newScale);

        /*!
         * \brief Scales(multiply) local transform scale by specified factor values.
         * \param factorX - X value of factor.
         * \param factorY - Y value of factor.
         */
        void Scale(const float factorX, const float factorY);

        /*!
         * \brief Scales(multiply) local transform scale by specified factor value.
         * \param factor - const reference to an atomic factor vector.
         */
        void Scale(const Utility::AtomicVector2F& factor);

        /*!
         * \brief Calculates transform matrix of the object and returns it.
         * \return Transform matrix that contains all required data.
         */
        sf::Transform GetTransform() const;
        
        /*!
         * \brief Returns local transformations.
         * \return Local transformation values in one container (position, rotation, scale).
         */
        Transformations GetTransformations() const;

        /*!
         * \brief Returns global transformations.
         * \return Global transformation values in one container (position, rotation, scale).
         */
        Transformations GetGlobalTransformations() const;

        /*!
         * \brief Return transformations relative to the specified transform.
         * \param otherTransform - transform relative to which new transformations will be calculated.
         * \return Local transformation values (position, rotation, scale) relative to the specified transform.
         */
        Transformations GetTransformationsRelativeTo(const std::shared_ptr<TransformComponent>& otherTransform) const;

        /*!
         * \brief Sets new local transformations.
         * \param transformations - new local transformations in one container (position, rotation, scale).
         */
        void SetTransformations(const Transformations& transformations);

    private:
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

        /*!
         * \brief Marks the transform and all child transforms as required to be updated.
         */
        void _TransformNeedUpdate() const;
        
        /*!
         * \brief Updates global transformations (position, rotation, scale).
         */
        void _UpdateGlobalTransformations() const;

        /*! Simple flag to identify if transform was updated and we should invoke "OnTransformUpdate" event. */
        mutable std::atomic<bool> _transformUpdated;
        /*! Simple flag to identify if global transformations need to be updated. */
        mutable std::atomic<bool> _globalTransformationsNeedUpdate;
        /*! Transform origin. Stores origin point of an object. */
        mutable Utility::AtomicVector2F _origin;
        /*! Local transform position. Stores local position of an object. */
        mutable Utility::AtomicVector2F _position;
        /*! Global transform position. Stores global position of an object. */
        mutable Utility::AtomicVector2F _globalPosition;
        /*! Local transform rotation. Stores local rotation of an object. */
        mutable std::atomic<float> _rotation;
        /*! Global transform rotation. Stores global rotation of an object. */
        mutable std::atomic<float> _globalRotation;
        /*! Local transform scale. Stores local scale of an object. */
        mutable Utility::AtomicVector2F _scale;
        /*! Global transform scale. Stores global scale of an object. */
        mutable Utility::AtomicVector2F _globalScale;
    };
}
