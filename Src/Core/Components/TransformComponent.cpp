#include "TransformComponent.hpp"
#include "Utility/EventSystem/SimplestDispatcher.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TransformComponent::TransformComponent(const std::shared_ptr<SceneObject>& sceneObject) 
    : BaseComponent(sceneObject)
    ,_transformUpdated(true)
    , _rotation(0.0f)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Utility::AtomicVector2F& TransformComponent::GetOrigin() const
{
    return _origin;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetOrigin(const float newOriginX, const float newOriginY)
{
    _origin.x = newOriginX;
    _origin.y = newOriginY;

    _transformUpdated = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetOrigin(const Utility::AtomicVector2<float>& newOrigin)
{
    SetOrigin(newOrigin.x, newOrigin.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Utility::AtomicVector2F& TransformComponent::GetPosition() const
{
    return _position;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetPosition(const float newPositionX, const float newPositionY)
{
    _position.x = newPositionX;
    _position.y = newPositionY;

    _transformUpdated = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetPosition(const Utility::AtomicVector2F& newPosition)
{
    SetPosition(newPosition.x, newPosition.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Move(const float offsetX, const float offsetY)
{
    SetPosition(_position.x + offsetX, _position.y + offsetY);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Move(const Utility::AtomicVector2F& offset)
{
    SetPosition(_position.x + offset.x, _position.y + offset.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float TransformComponent::GetRotation() const
{
    return _rotation;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetRotation(const float newRotation)
{
    _rotation = newRotation;

    _transformUpdated = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Rotate(const float angle)
{
    SetRotation(_rotation + angle);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Utility::AtomicVector2F& TransformComponent::GetScale() const
{
    return _scale;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetScale(const float newScaleX, const float newScaleY)
{
    _scale.x = newScaleX;
    _scale.y = newScaleY;

    _transformUpdated = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetScale(const Utility::AtomicVector2F& newScale)
{
    SetScale(newScale.x, newScale.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Scale(const float factorX, const float factorY)
{
    SetScale(_scale.x * factorX, _scale.y * factorY);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Scale(const Utility::AtomicVector2F& factor)
{
    SetScale(_scale.x * factor.x, _scale.y = _scale.y * factor.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Initialize()
{
    AddEvent("TransformUpdated", new Utility::SimplestDispatcher());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Update()
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::LateUpdate()
{
    if (_transformUpdated)
    {
        _transformUpdated = false;
        InvokeEvent("TransformUpdated");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
