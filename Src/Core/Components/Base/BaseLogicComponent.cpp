#include "BaseLogicComponent.hpp"

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseLogicComponent::BaseLogicComponent(std::weak_ptr<SceneObject>&& sceneObject) 
: BaseComponent(std::move(sceneObject))
,_turnedOn(true)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseLogicComponent::IsTurnedOn() const
{
    return _turnedOn;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseLogicComponent::TurnOn(const bool turnOn)
{
    _turnedOn = turnOn;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseLogicComponent::Initialize()
{
    if (_typeIndex == typeid(BaseComponent))
    {
        _typeIndex = typeid(*this);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
