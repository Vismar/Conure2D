#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Component>
bool SceneObject::AddComponent()
{
    bool added(false);

    const auto componentTypeIndex = std::type_index(typeid(Component));
    if constexpr (std::is_base_of<BaseDataComponent, Component>::value)
    {
        if (_dataComponentMap.find(componentTypeIndex) == _dataComponentMap.end())
        {
            _dataComponentMap.emplace(componentTypeIndex, std::make_shared<Component>());
            _dataComponentMap[componentTypeIndex]->BaseDataComponent::Initialize();
            _dataComponentMap[componentTypeIndex]->Initialize();
            added = true;
        }
    }
    else if constexpr (std::is_base_of<BaseLogicComponent, Component>::value)
    {
        // If component with required type is not added to the map - add it
        if (_logicComponentMap.find(componentTypeIndex) == _logicComponentMap.end())
        {
            _logicComponentMap.emplace(componentTypeIndex, std::make_shared<Component>(this->shared_from_this()));
            _logicComponentMap[componentTypeIndex]->BaseLogicComponent::Initialize();
            _logicComponentMap[componentTypeIndex]->Initialize();
            added = true;

            InvokeEvent<void, std::weak_ptr<BaseComponent>>("ComponentAdded", _logicComponentMap[componentTypeIndex]);
        }
    }    

    return added;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Component>
std::weak_ptr<Component> SceneObject::GetComponent() const
{
    std::weak_ptr<Component> returningPointer;

    // If requested component is derived from BaseDataComponent then we should search it in data component map
    if constexpr (std::is_base_of<BaseDataComponent, Component>::value)
    {
        // If requested component are stored in the map, return it
        if (const auto component = _dataComponentMap.find(std::type_index(typeid(Component))); 
            component != _dataComponentMap.end())
        {
            returningPointer = std::dynamic_pointer_cast<Component>(component->second);
        }
    }
    // If requested component is derived from BaseLogicComponent then we should search it in logic component map
    else if constexpr (std::is_base_of<BaseLogicComponent, Component>::value)
    {
        // If requested component are stored in the map, return it
        if (const auto component = _logicComponentMap.find(std::type_index(typeid(Component)));
            component != _logicComponentMap.end())
        {
            returningPointer = std::dynamic_pointer_cast<Component>(component->second);
        }
    }

    return returningPointer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Component>
void SceneObject::RemoveComponent()
{
    const std::type_index componentTypeIndex = std::type_index(typeid(Component));

    if (componentTypeIndex != std::type_index(typeid(TransformComponent)))
    {
        // Check if requested component is derived from BaseDataComponent
        if constexpr (std::is_base_of<BaseDataComponent, Component>::value)
        {
            // If component with required type exist in the map, erase it
            if (const auto component = _dataComponentMap.find(componentTypeIndex);
                component != _dataComponentMap.end())
            {
                _dataComponentMap.erase(component);
            }
        }
        // Check if requested component is derived from BaseLogicComponent
        else if constexpr (std::is_base_of<BaseLogicComponent, Component>::value)
        {
            // If component with required type exist in the map, erase it
            if (const auto component = _logicComponentMap.find(componentTypeIndex); 
                component != _logicComponentMap.end())
            {
                _logicComponentMap.erase(component);
            }
        }        
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
