#pragma once
#include "Core/Base/BaseComponent.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include "Utility/EventSystem/EventManager.hpp"

namespace Core
{
    class TransformComponent;

    /*!
     * \brief Base component for all renderable components.
     * 
     * - Defines relational operators to sort components to define rendering order.
     * - Stores layer number for the same reason. 
     * - Inherited components will have the same characteristics in comparison, 
     *   so scene object will not be able to store more than one renderable component.
     */
    class RenderableComponent : public BaseComponent, public Utility::EventManager, public sf::Drawable
    {
    public:
        RenderableComponent() = delete;
        RenderableComponent(const RenderableComponent& other) = delete;
        RenderableComponent(RenderableComponent&& other) = delete;
        RenderableComponent& operator=(const RenderableComponent& other) = delete;
        RenderableComponent& operator=(RenderableComponent&& other) = delete;
        virtual ~RenderableComponent() = default;

        /*!
         * \brief Default constructor.
         * \param sceneObject - shared pointer to the object which contains this component.
         */
        explicit RenderableComponent(const std::shared_ptr<SceneObject>& sceneObject);

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
         * \brief Return layer number.
         * \return Number of the layer.
         */
        int8_t GetLayerNumber() const;

        /*!
         * \brief Sets layer number.
         * \param newLayerNumber - number of the layer.
         */
        void SetLayerNumber(const int8_t newLayerNumber);

        /*!
         * \brief Returns status of the visibility of this object.
         * \return True if object is visible.
         * 
         * Virtual method, can be overridden.
         */
        virtual bool IsVisible() const;

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
        void _UpdateTransform();
        
        /*!
         * \brief Draws object to the specified render target.
         * \param target - render target to which object will be rendered.
         * \param states - states to which will be assigned vertices and texture.
         */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

        /*! Number of the layer. The higher the layer - later object should be rendered. */
        std::atomic<int8_t> _layerNumber;
        /*! Simple atomic flag of the need of the update of the transform. */
        std::atomic<bool> _transformNeedUpdate;
        /*! Transform that will be used in render. */
        sf::Transform _transform;
    };
}
