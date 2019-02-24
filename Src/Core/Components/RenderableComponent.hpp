#pragma once
#include "Core/Components/Base/BaseDataComponent.hpp"
#include "Utility/RenderablesCompare.hpp"
#include "Utility/EventSystem/EventManager.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <set>
#include <atomic>

namespace C2D
{
    class TransformComponent;
    class CameraComponent;

    /*!
     * \brief Base component for all renderable components.
     * 
     * - Defines relational operators to sort components to define rendering order.
     * - Stores layer number for the same reason. 
     * - Inherited components will have the same characteristics in comparison, 
     *   so scene object will not be able to store more than one renderable component.
     */
    class [[deprecated("Will be reimplemented")]] RenderableComponent : public BaseDataComponent, public EventManager, public sf::Drawable
    {
    public:
        RenderableComponent() = delete;
        RenderableComponent(const RenderableComponent& other) = delete;
        RenderableComponent(RenderableComponent&& other) = delete;
        RenderableComponent& operator=(const RenderableComponent& other) = delete;
        RenderableComponent& operator=(RenderableComponent&& other) = delete;
        ~RenderableComponent() override;

        /*!
         * \brief Default constructor.
         * \param sceneObject - weak pointer to the object which contains this component.
         */
        explicit RenderableComponent(std::weak_ptr<SceneObject>&& sceneObject);

        /*!
         * \brief Operator "lesser".
         * \param right - another renderable component to compare.
         * \return True if this component lesser than an operator on the right side of the operator.
         * 
         * Compares layer numbers of renderable components. Virtual function, can be overridden.
         */
        virtual bool operator<(const RenderableComponent& right) const;

        /*!
         * \brief Operator "greater".
         * \param right - another renderable component to compare.
         * \return True if this component greater than an operator on the right side of the operator.
         * 
         * Only uses "operator<", so no need to override this operator.
         */
        bool operator>(const RenderableComponent& right) const;

        /*!
         * \brief Operator "lesser or equal".
         * \param right - another renderable component to compare.
         * \return True if this component lesser or equal to an operator on the right side of the operator.
         *
         * Only uses "operator>", so no need to override this operator.
         */
        bool operator<=(const RenderableComponent& right) const;

        /*!
         * \brief Operator "greater or equal".
         * \param right - another renderable component to compare.
         * \return True if this component greater or equal to an operator on the right side of the operator.
         *
         * Only uses "operator<", so no need to override this operator.
         */
        bool operator>=(const RenderableComponent& right) const;

        /*!
         * \brief Sets layer number.
         * \param newLayerNumber - number of the layer.
         */
        void SetLayerNumber(int8_t newLayerNumber);

        /*!
         * \brief Return layer number.
         * \return Number of the layer.
         */
        int8_t GetLayerNumber() const;

        /*!
         * \brief Returns status of the visibility of this object in view of a specified camera component.
         * \param cameraComponent - weak pointer to a camera component.
         * \return True if object is visible for a specified camera component.
         * 
         * Virtual method, can be overridden.
         */
        virtual bool IsVisible(const std::weak_ptr<CameraComponent>& cameraComponent) const;

        /*!
         * \brief Sets texture for this component.
         * \param texture - shared pointer to a texture that will be used by this component.
         */
        void SetTexture(const std::shared_ptr<sf::Texture>& texture);

        /*!
         * \brief Returns texture that is used by this component.
         * \return Weak pointer to the texture that is used in render process.
         */
        std::weak_ptr<sf::Texture> GetTexture() const;

    protected:
        /*!
         * \brief Initializes component.
         * 
         * Initializes component in such way that any inherited components will have 
         * the same characteristics in comparison, 
         * so scene object will not be able to store more than one renderable component.
         */
        void Initialize() override;

        /*! Weak pointer to transform component of a scene object that contains this component. */
        std::weak_ptr<TransformComponent> _transformComponent;
        /*! Array of vertices. */
        sf::VertexArray _vertices;
        /*! Weak pointer to the texture that will be used in render. */
        std::weak_ptr<sf::Texture> _texture;

    private:
        /*!
         * \brief Callback that will be invoked upon changes in the transform component.
         */
        void _OnTransformComponentUpdated();

        /*!
         * \brief Utility function to update stored transform.
         * 
         * Called only when transform needs to be updated.
         */
        void _UpdateTransform() const;
        
        /*!
         * \brief Draws object to the specified render target.
         * \param target - render target to which object will be rendered.
         * \param states - states to which will be assigned vertices and texture.
         */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

        /*! Number of the layer. The higher the layer - later object should be rendered. */
        std::atomic_int8_t _layerNumber;
        /*! Simple atomic flag of the need of the update of the transform. */
        mutable std::atomic_bool _transformNeedUpdate;
        /*! Transform that will be used in render. */
        mutable sf::Transform _transform;
        /*! Handler of TransformUpdated event from transform component. */
        AnyCallableHandler _transformUpdatedHandler;
    };

    /*! Simple alias to shorten the name of the vector of weak pointers to renderable components. */
    using RenderableArray = std::vector<std::weak_ptr<RenderableComponent>>;
    /*! Simple alias to shorten the name of the set of weak pointers to renderable components. */
    using RenderableSet = std::set<std::weak_ptr<RenderableComponent>, RenderablesCompare>;
}
