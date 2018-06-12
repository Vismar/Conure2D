#include "SpriteRenderComponent.hpp"
#include <SFML/Graphics/Texture.hpp>

using namespace Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SpriteRenderComponent::SpriteRenderComponent(std::weak_ptr<Core::SceneObject>&& sceneObject)
: RenderableComponent(std::move(sceneObject))
{
    _vertices.setPrimitiveType(sf::TriangleStrip);
    _vertices.resize(5);

    _vertices[0].position = { 0.0f, 0.0f };
    _vertices[1].position = { 0.0f, 100.0f };
    _vertices[2].position = { 100.0f, 100.0f };
    _vertices[3].position = { 100.0f, 0.0f };
    _vertices[4].position = { 0.0f, 0.0f };

    _vertices[0].color = sf::Color::White;
    _vertices[1].color = sf::Color::White;
    _vertices[2].color = sf::Color::White;
    _vertices[3].color = sf::Color::White;
    _vertices[4].color = sf::Color::White;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SpriteRenderComponent::SetTextureCoordinates(const sf::IntRect& rect)
{
    const auto left = static_cast<float>(rect.left);
    const auto right = left + rect.width;
    const auto top = static_cast<float>(rect.top);
    const auto bottom = top + rect.height;

    _vertices[0].texCoords = { left, top };
    _vertices[1].texCoords = { left, bottom };
    _vertices[2].texCoords = { right, bottom };
    _vertices[3].texCoords = { right, top };
    _vertices[4].texCoords = { left, top };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SpriteRenderComponent::Initialize()
{
    RenderableComponent::Initialize();

    BindToEvent("TextureUpdated", this, &SpriteRenderComponent::_OnTextureChanged);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SpriteRenderComponent::_OnTextureChanged()
{
    if (const auto texture = _texture.lock())
    {
        SetTextureCoordinates(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
