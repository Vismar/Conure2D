#pragma once
#include "Core/Components/RenderableComponent.hpp"

namespace C2D
{
    /*!
     * \brief Simple renderable component.
     * 
     * Contains 4 vertices that form square which will use stored texture.
     */
    class SpriteRenderComponent : public RenderableComponent
    {
    public:
        /*!
         * \brief Default constructor.
         * \param sceneObject - shared pointer to the object which contains this component.
         */
        explicit SpriteRenderComponent(std::weak_ptr<SceneObject>&& sceneObject);

        /*!
         * \brief Sets texture coordinates.
         * \param rect - rectangle from which texture coordinates will be assigned to vertices.
         */
        void SetTextureCoordinates(const sf::IntRect& rect);

    protected:
        /*!
         * \brief Initializes component and binds callbacks to certain events.
         */
        void Initialize() final;

    private:
        /*!
         * \brief Do nothing.
         */
        void Reset() final {}

        /*!
         * \brief Callback that is used to update texture coordinates when a new texture has been assigned to the component.
         */
        void _OnTextureChanged();
    };
}