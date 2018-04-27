#include "TransformComponent.hpp"
#include "Utility/EventSystem/Dispatcher.hpp"
#include "Core/Scene/SceneObject.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TransformComponent::TransformComponent(const std::shared_ptr<SceneObject>& sceneObject)
: BaseComponent(sceneObject)
, _transformUpdated(true)
, _globalTransformationsNeedUpdate(true)
, _rotation(0.0f)
, _globalRotation(0.0f)
, _scale(1.0f, 1.0f)
, _globalScale(1.0f, 1.0f)
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

    _TransformNeedUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetOrigin(const sf::Vector2f& newOrigin)
{
    SetOrigin(newOrigin.x, newOrigin.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetOrigin(const Utility::AtomicVector2F& newOrigin)
{
    SetOrigin(newOrigin.x, newOrigin.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Utility::AtomicVector2F& TransformComponent::GetGlobalPosition() const
{
    _UpdateGlobalTransformations();

    return _globalPosition;
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

    _TransformNeedUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetPosition(const sf::Vector2f& newPosition)
{
    SetPosition(newPosition.x, newPosition.y);
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

float TransformComponent::GetGlobalRotation() const
{
    _UpdateGlobalTransformations();

    return _globalRotation;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float TransformComponent::GetRotation() const
{
    return _rotation;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetRotation(const float newRotation)
{
    _rotation = std::fmod(newRotation, 360.0f);

    if (_rotation < 0)
    {
        _rotation = _rotation + 360.0f;
    }

    _TransformNeedUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Rotate(const float angle)
{
    SetRotation(_rotation + angle);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Utility::AtomicVector2<float>& TransformComponent::GetGlobalScale() const
{
    _UpdateGlobalTransformations();

    return _globalScale;
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

    _TransformNeedUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetScale(const sf::Vector2f& newScale)
{
    SetScale(newScale.x, newScale.y);
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

sf::Transform TransformComponent::GetTransform() const
{
    const float scaleX(_scale.x), scaleY(_scale.y);
    const float originX(_origin.x), originY(_origin.y);

    const auto angle = -_rotation * 3.141592654f / 180.0f;
    const auto cos = std::cos(angle);
    const auto sin = std::sin(angle);
    const auto sxc = scaleX * cos;
    const auto syc = scaleY * cos;
    const auto sxs = scaleX * sin;
    const auto sys = scaleY * sin;
    const auto tx = -originX * sxc - originY * sys + _position.x;
    const auto ty =  originX * sxs - originY * syc + _position.y;

    sf::Transform transform = sf::Transform(sxc,  sys,  tx,
                                            -sxs, syc,  ty,
                                            0.0f, 0.0f, 1.0f);

    if (const auto object = GetSceneObject().lock())
    {
        if (const auto parent = object->GetParent().lock())
        {
            if (const auto parentTransform = parent->GetTransformComponent().lock())
            {
                transform = parentTransform->GetTransform() * transform;
            }
        }
    }

    return transform;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Transformations TransformComponent::GetTransformations() const
{
    Transformations transformations;

    // Position
    transformations.position.x = _position.x;
    transformations.position.y = _position.y;

    // Rotation
    transformations.rotation = _rotation;

    // Scale
    transformations.scale.x = _scale.x;
    transformations.scale.y = _scale.y;

    return transformations;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Transformations TransformComponent::GetGlobalTransformations() const
{
    Transformations transformations;

    // Position
    const auto globalPosition = GetGlobalPosition();
    transformations.position.x = globalPosition.x;
    transformations.position.y = globalPosition.y;

    // Rotation
    transformations.rotation = GetGlobalRotation();

    // Scale
    const auto globalScale = GetGlobalScale();
    transformations.scale.x = globalScale.x;
    transformations.scale.y = globalScale.y;

    return transformations;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Transformations TransformComponent::GetTransformationsRelativeTo(const std::shared_ptr<TransformComponent>& otherTransform) const
{
    Transformations relativeTransformations;
    const auto newTransform = otherTransform->GetTransform().getInverse() * GetTransform();
    const auto matrix = newTransform.getMatrix();

    // Rotation
    relativeTransformations.rotation = std::atan2(matrix[1], matrix[0]) * 180.0f / 3.141592654f;

    // Scale
    const auto angle = -relativeTransformations.rotation * 3.141592654f / 180.0f;
    const auto cos = std::cos(angle);
    relativeTransformations.scale.x = matrix[0] / cos;
    relativeTransformations.scale.y = matrix[5] / cos;

    // Position
    const auto sin = std::sin(angle);
    const auto sxc = relativeTransformations.scale.x * cos;
    const auto syc = relativeTransformations.scale.y * cos;
    const auto sxs = relativeTransformations.scale.x * sin;
    const auto sys = relativeTransformations.scale.y * sin;
    relativeTransformations.position.x = matrix[12] + _origin.x * sxc + _origin.y * sys;
    relativeTransformations.position.y = matrix[13] - _origin.x * sxs + _origin.y * syc;

    return relativeTransformations;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::SetTransformations(const Transformations& transformations)
{
    SetPosition(transformations.position);
    SetRotation(transformations.rotation);
    SetScale(transformations.scale);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::Initialize()
{
    AddEvent("TransformUpdated", new Utility::Dispatcher<void>());
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
        _UpdateGlobalTransformations();
        InvokeEvent("TransformUpdated");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::_TransformNeedUpdate() const
{
    _transformUpdated = true;
    _globalTransformationsNeedUpdate = true;

    if (const auto object = GetSceneObject().lock())
    {
        for (auto& child : object->GetChildrenList())
        {
            child->GetTransformComponent().lock()->_TransformNeedUpdate();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TransformComponent::_UpdateGlobalTransformations() const
{
    if (_globalTransformationsNeedUpdate)
    {
        _globalTransformationsNeedUpdate = false;
        const auto transformMatrix = GetTransform().getMatrix();

        // Rotation
        _globalRotation = std::atan2(transformMatrix[1], transformMatrix[0]) * 180.0f / 3.141592654f;

        // Scale
        const auto angle = -_globalRotation * 3.141592654f / 180.0f;
        const auto cos = std::cos(angle);
        _globalScale.x = transformMatrix[0] / cos;
        _globalScale.y = transformMatrix[5] / cos;

        // Position
        const auto sin = std::sin(angle);
        const auto sxc = _globalScale.x * cos;
        const auto syc = _globalScale.y * cos;
        const auto sxs = _globalScale.x * sin;
        const auto sys = _globalScale.y * sin;
        _globalPosition.x = transformMatrix[12] + _origin.x * sxc + _origin.y * sys;
        _globalPosition.y = transformMatrix[13] - _origin.x * sxs + _origin.y * syc;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
