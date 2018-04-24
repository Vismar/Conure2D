#include "SpriteRenderComponent.hpp"
#include "SFML/Graphics/Texture.hpp"

using namespace Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SpriteRenderComponent::SpriteRenderComponent(const std::shared_ptr<Core::SceneObject>& sceneObject)
    : RenderableComponent(sceneObject)
{
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(4);

    _vertices[0].position = sf::Vector2f(0.0f, 0.0f);
    _vertices[1].position = sf::Vector2f(100.0f, 0.0f);
    _vertices[2].position = sf::Vector2f(100.0f, 100.0f);
    _vertices[3].position = sf::Vector2f(0.0f, 100.0f);

    _vertices[0].color = sf::Color::White;
    _vertices[1].color = sf::Color::White;
    _vertices[2].color = sf::Color::White;
    _vertices[3].color = sf::Color::White;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SpriteRenderComponent::SetTextureCoordinates(const sf::IntRect& rect)
{
    const auto left = static_cast<float>(rect.left);
    const auto right = left + rect.width;
    const auto top = static_cast<float>(rect.top);
    const auto bottom = top + rect.height;

    _vertices[0].texCoords = sf::Vector2f(left, top);
    _vertices[1].texCoords = sf::Vector2f(left, bottom);
    _vertices[2].texCoords = sf::Vector2f(right, top);
    _vertices[3].texCoords = sf::Vector2f(right, bottom);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SpriteRenderComponent::Update()
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SpriteRenderComponent::LateUpdate()
{ }

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
