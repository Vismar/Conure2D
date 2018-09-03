#include "SceneObject.hpp"
#include <algorithm>

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::atomic_uint64_t SceneObject::_globalIdCounter = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SceneObject::SceneObject() 
: _deleteLater(false)
, _objectId(++_globalIdCounter)
, _name("SceneObject")
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
    return std::dynamic_pointer_cast<TransformComponent>(_logicComponentMap.at(std::type_index(typeid(TransformComponent))));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<SceneObject> SceneObject::GetParent() const
{
    return _parent;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::SetParent(const std::shared_ptr<SceneObject>& newParent)
{
    if (auto transform = GetTransformComponent().lock())
    {
        // If we assigning new parent to an object, we should do next things:
        // - Add the object as a child to a new parent.
        // - Remove the object from parent list of children if the object previously has a parent.
        // - Update local transformations of the object relative to a new parent.
        if (newParent != nullptr)
        {
            // Add child to a new parent
            (void)newParent->_AddChild(this->shared_from_this());

            // If the object has a parent, we should remove it from the list of children of a parent
            if (auto parent = _parent.lock())
            {
                parent->RemoveChild(_objectId);
            }

            // Obtain new local transformations relative to the parent and assign them to the object
            if (const auto parentTransform = newParent->GetTransformComponent().lock())
            {
                const auto transformations = transform->GetTransformationsRelativeTo(parentTransform);
                transform->SetTransformations(transformations);
            }
        }
        // If we detaching the object from a parent, we should update local transformations to a global transformations
        else
        {
            // We should gather all transformations BEFORE assigning it 
            // because if we will assign a new value to any of transformations
            // and then tries to obtain next transformation value, 
            // it already will be recalculated based on recently assigned value.
            const auto& globalPosition = transform->GetGlobalPosition();
            const auto& globalRotation = transform->GetGlobalRotation();
            const auto& globalScale = transform->GetGlobalScale();

            // So at first, we obtain global transformations and only after it we assign it one by one.
            transform->SetPosition(globalPosition);
            transform->SetRotation(globalRotation);
            transform->SetScale(globalScale);
        }

        // Set a new parent
        _parent = newParent;
    }
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

std::vector<std::weak_ptr<SceneObject>>& SceneObject::GetChildrenList()
{
    return _children;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::DeleteLater()
{
    _deleteLater = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SceneObject::_AddChild(const std::shared_ptr<SceneObject>& newChild)
{
    bool added(false);

    // If the object doesn't have specified object as a child, we should add it to the list
    if (_FindChild(newChild->GetId()) == _children.end())
    {
        _children.push_back(newChild);
        added = true;
    }

    return added;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::_Initialize()
{
    // Every scene object ALWAYS must have transform component 
    if (AddComponent<TransformComponent>())
    {
        AddEvent("ComponentAdded", new Dispatcher<void>);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::_Update()
{
    // Update the components
    for (auto component : _logicComponentMap)
    {
        // Only if component is turned on we should call the function
        if (component.second->IsTurnedOn())
        {
            component.second->Update();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::_LateUpdate()
{
    // Late update the components
    for (auto component : _logicComponentMap)
    {
        // Only if component is turned on we should call the function
        if (component.second->IsTurnedOn())
        {
            component.second->LateUpdate();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SceneObject::ChildConstIterator SceneObject::_FindChild(const uint64_t childId) const
{
    auto returningIterator = _children.end();

    // Loop through the list of the children and try to find one with the same id that was specified
    for (auto child = _children.begin(); child != _children.end(); ++child)
    {
        if (const auto lockedChild = child->lock())
        {
            if (lockedChild->GetId() == childId)
            {
                returningIterator = child;
                break;
            }
        }
    }

    return returningIterator;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
