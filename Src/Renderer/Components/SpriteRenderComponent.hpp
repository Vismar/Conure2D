#pragma once
#include "Core/Components/RenderableComponent.hpp"

namespace Renderer
{
    /*!
     * \brief Simple renderable component.
     * 
     * Contains 4 vertices that form square which will use stored texture.
     */
    class SpriteRenderComponent : public Core::RenderableComponent
    {
    public:
        /*!
         * \brief Default constructor.
         * \param sceneObject - shared pointer to the object which contains this component.
         */
        explicit SpriteRenderComponent(std::weak_ptr<Core::SceneObject>&& sceneObject);

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
         * \brief Callback that is used to update texture coordinates when a new texture has been assigned to the component.
         */
        void _OnTextureChanged();
    };
}