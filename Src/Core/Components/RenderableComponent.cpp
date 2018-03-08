#include "RenderableComponent.hpp"
#include "Core/Components/TransformComponent.hpp"
#include "Core/Base/SceneObject.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

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
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::Initialize()
{
    _typeIndex = typeid(RenderableComponent);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::_OnTransformComponentUpdated()
{
    _transformNeedUpdate = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::_UpdateTransform()
{
    if (_transformNeedUpdate)
    {
        _transformNeedUpdate = false;
        if (const auto transform = _transformComponent.lock())
        {
            const float scaleX(transform->GetScale().x), scaleY(transform->GetScale().y);
            const float originX(transform->GetOrigin().x), originY(transform->GetOrigin().y);

            const float angle = -transform->GetRotation() * 3.141592654f / 180.0f;
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);
            const float sxc = scaleX * cos;
            const float syc = scaleY * cos;
            const float sxs = scaleX * sin;
            const float sys = scaleY * sin;
            const float tx = -originX * sxc - originY * sys + transform->GetPosition().x;
            const float ty = -originX * sxs - originY * syc + transform->GetPosition().y;

            _transform = sf::Transform(sxc,  sys,  tx,
                                       -sxs, syc,  ty,
                                       0.0f, 0.0f, 1.0f);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= _transform;
    if (const auto texture = _texture.lock())
    {
        states.texture = texture.get();
    }

    target.draw(_vertices, states);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
