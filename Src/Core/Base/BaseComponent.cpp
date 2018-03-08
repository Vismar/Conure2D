#include "BaseComponent.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseComponent::BaseComponent(const std::shared_ptr<SceneObject>& sceneObject)
    : _sceneObject(sceneObject)
    , _turnedOn(true)
    , _typeIndex(typeid(BaseComponent))
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseComponent::operator==(const BaseComponent& other) const
{
    return (other._typeIndex == _typeIndex);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseComponent::operator==(const std::type_index& typeIndex) const
{
    return (typeIndex == _typeIndex);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<SceneObject> BaseComponent::GetSceneObject() const
{
    return _sceneObject;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseComponent::IsTurnedOn() const
{
    return _turnedOn;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::TurnOn(const bool turnOn)
{
    _turnedOn = turnOn;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::Initialize()
{
    if (_typeIndex == typeid(BaseComponent))
    {
        // There is no other way to store type of an object
        _typeIndex = typeid(*this);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
