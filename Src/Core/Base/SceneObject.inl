#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Component>
std::weak_ptr<Component> SceneObject::GetComponent() const
{
    std::weak_ptr<Component> returningPointer;

    // Search for the component
    const auto component = _componentMap.find(std::type_index(typeid(Component)));
    // If we found a component, cast to required type and return
    if (component != _componentMap.end())
    {
        returningPointer = std::dynamic_pointer_cast<Component>(component->second);
    }

    return returningPointer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Component>
bool SceneObject::AddComponent()
{
    bool added(false);

    const std::type_index componentTypeIndex = std::type_index(typeid(Component));
    // If component with required type is not added to the map - add it
    if (_componentMap.find(componentTypeIndex) == _componentMap.end())
    {
        _componentMap.emplace(componentTypeIndex, std::make_shared<Component>());
        added = true;
    }

    return added;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Component>
void SceneObject::RemoveComponent()
{
    const std::type_index componentTypeIndex = std::type_index(typeid(Component));

    if (componentTypeIndex != std::type_index(typeid(TransformComponent)))
    {
        const auto componentIterator = _componentMap.find(componentTypeIndex);
        // If component with required type exist in the map, erase it
        if (componentIterator != _componentMap.end())
        {
            _componentMap.erase(componentIterator);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
