#include "RenderableComponent.hpp"
#include "Core/Components/TransformComponent.hpp"
#include "Core/Scene/SceneObject.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Utility/EventSystem/Dispatcher.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderableComponent::RenderableComponent(const std::shared_ptr<SceneObject>& sceneObject) 
    : BaseComponent(sceneObject)
    , _layerNumber(0)
    , _transformNeedUpdate(true)
{
    if (const auto object = GetSceneObject().lock())
    {
        _transformComponent = object->GetTransformComponent();
        if (const auto transform = _transformComponent.lock())
        {
            transform->BindToEvent("TransformUpdated", this, &RenderableComponent::_OnTransformComponentUpdated);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderableComponent::operator<(const RenderableComponent& right) const
{
    return (_layerNumber < right._layerNumber);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderableComponent::operator>(const RenderableComponent& right) const
{
    return (right < (*this));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderableComponent::operator<=(const RenderableComponent& right) const
{
    return !((*this) > right);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderableComponent::operator>=(const RenderableComponent& right) const
{
    return !(right < (*this));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int8_t RenderableComponent::GetLayerNumber() const
{
    return _layerNumber;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::SetLayerNumber(const int8_t newLayerNumber)
{
    _layerNumber = newLayerNumber;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderableComponent::IsVisible() const
{
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::SetTexture(const std::shared_ptr<sf::Texture>& texture)
{
    _texture = texture;

    InvokeEvent("TextureUpdated");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<sf::Texture> RenderableComponent::GetTexture() const
{
    return _texture;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::Initialize()
{
    _typeIndex = typeid(RenderableComponent);

    AddEvent("TextureUpdated", new Utility::Dispatcher<void>());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::_OnTransformComponentUpdated()
{
    _transformNeedUpdate = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::_UpdateTransform() const
{
    if (_transformNeedUpdate)
    {
        _transformNeedUpdate = false;
        if (const auto transform = _transformComponent.lock())
        {
            _transform = transform->GetTransform();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    _UpdateTransform();

    states.transform *= _transform;

    if (const auto texture = _texture.lock())
    {
        states.texture = texture.get();
    }

    target.draw(_vertices, states);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////