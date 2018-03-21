#include "SceneObject.hpp"
#include <algorithm>

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::atomic_uint64_t SceneObject::_globalIdCounter = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SceneObject::SceneObject() : _objectId(++_globalIdCounter), _name("SceneObject")
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t SceneObject::GetId() const
{
    return _objectId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string& SceneObject::GetName() const
{
    return _name;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::SetName(const std::string& newName)
{
    _name = newName;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::SetName(std::string&& newName)
{
    _name = std::move(newName);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<TransformComponent> SceneObject::GetTransformComponent() const
{
    // Every scene object ALWAYS have transform component
    return std::dynamic_pointer_cast<TransformComponent>(_componentMap.at(std::type_index(typeid(TransformComponent))));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<SceneObject> SceneObject::GetParent() const
{
    return _parent;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::SetParent(const std::shared_ptr<SceneObject>& newParent)
{
    // We MUST add the object as a child to a new parent because if we didn't do it,
    // the counter of shared_ptr will become 0 and object will be deleted
    (void) newParent->AddChild(this->shared_from_this());

    // If the object has a parent, we should remove an object from the list of children of a parent
    if (auto parent = _parent.lock())
    {
        parent->RemoveChild(_objectId);
    }

    // Set a new parent
    _parent = newParent;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SceneObject::AddChild(std::shared_ptr<SceneObject>&& newChild)
{
    bool added(false);

    // If the object doesn't have specified object as a child, we should add it to the list
    if (_FindChild(newChild->GetId()) == _children.end())
    {
        _children.emplace_back(newChild);
        added = true;
    }

    return added;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::RemoveChild(const uint64_t childId)
{
    // If the object has specified object as a child, we should remove it from the list
    const auto child = _FindChild(childId);
    if (child != _children.end())
    {
        _children.erase(child);        
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::shared_ptr<SceneObject>>& SceneObject::GetChildrenList()
{
    return _children;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::_Initialize()
{
    // Every scene object ALWAYS must have transform component 
    AddComponent<TransformComponent>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::_Update()
{
    // Update the components
    for (auto component : _componentMap)
    {
        // Only if component is turned on we should call the function
        if (component.second->IsTurnedOn())
        {
            component.second->Update();
        }
    }

    // Update the children
    for (auto& child : _children)
    {
        child->_Update();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::_LateUpdate()
{
    // Late update the components
    for (auto component : _componentMap)
    {
        // Only if component is turned on we should call the function
        if (component.second->IsTurnedOn())
        {
            component.second->LateUpdate();
        }
    }

    // Late update of the children
    for (auto& child : _children)
    {
        child->_LateUpdate();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SceneObject::ChildConstIterator SceneObject::_FindChild(const uint64_t childId) const
{
    auto returningIterator = _children.end();

    // Loop through the list of the children and try to find one with the same id that was specified
    for (auto child = _children.begin(); child != _children.end(); ++child)
    {
        if ((*child)->GetId() == childId)
        {
            returningIterator = child;
            break;
        }
    }

    return returningIterator;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
