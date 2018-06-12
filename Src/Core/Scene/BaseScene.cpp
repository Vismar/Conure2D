#include "BaseScene.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseScene::BaseScene(const std::string_view sceneName)
: _sceneName(sceneName)
, _deleteLater(false)
, _activated(false)
, _renderableComponents(std::make_shared<RenderableSet>())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<SceneObject> BaseScene::CreateObject()
{
    _newSceneObjects.emplace_back(std::make_shared<SceneObject>())->_Initialize();
    _newSceneObjects.back()->BindToEvent("ComponentAdded", this, &BaseScene::_OnNewComponentAdded);

    return _newSceneObjects.back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::Activate(const bool activate)
{
    _activated = activate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseScene::Activated() const
{
    return _activated;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string& BaseScene::GetName() const
{
    return _sceneName;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::DeleteLater()
{
    _deleteLater = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<RenderableSet> BaseScene::GetRenderableComponents() const
{
    // Remove "dead" pointers 
    for (auto iter = _renderableComponents->begin(); iter != _renderableComponents->end(); )
    {
        if ((*iter).lock())
        {
            ++iter;
        }
        else
        {
            iter = _renderableComponents->erase(iter);
        }
    }
    
    // Add new pointers to the list
    std::lock_guard lock(_renderableArrayMutex);
    for (auto& renderableComponent : _renderableComponentsToAdd)
    {
        const auto result = _renderableComponents->insert(renderableComponent);

        // If such component already in the set, replace it with a new one
        if (!result.second)
        {
            _renderableComponents->erase(result.first);
            _renderableComponents->insert(renderableComponent);
        }
    }

    // Clear to prevent copying
    _renderableComponentsToAdd.clear();

    return _renderableComponents;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::Update()
{
    // Delete objects that were marked as "delete later"
    _DeleteMarkedObjects();

    // Move all new scene objects to actual array
    for (auto sceneObject : _newSceneObjects)
    {
        _sceneObjects.emplace_back(sceneObject);
    }
    // Clear temporary array
    _newSceneObjects.clear();

    // Update
    for (auto& sceneObject : _sceneObjects)
    {
        sceneObject->_Update();
    }

    // LateUpdate
    for (auto& sceneObject : _sceneObjects)
    {
        sceneObject->_LateUpdate();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BaseScene::MarkedAsDeleteLater() const
{
    return _deleteLater;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::_DeleteMarkedObjects()
{
    _sceneObjects.erase(std::remove_if(_sceneObjects.begin(), 
                                       _sceneObjects.end(),
                                       [](const std::shared_ptr<SceneObject> object) { return object->_deleteLater; }),
                        _sceneObjects.end());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::_OnNewComponentAdded(std::weak_ptr<BaseComponent> newComponent)
{
    if (const auto component = newComponent.lock())
    {
        // Check if new component is renderable and then add it to the array
        if ((*component) == std::type_index(typeid(RenderableComponent)))
        {
            std::lock_guard lock(_renderableArrayMutex);

            if (const auto renderableComponent = std::dynamic_pointer_cast<RenderableComponent>(component))
            {
                _renderableComponentsToAdd.push_back(renderableComponent);
                renderableComponent->BindToEvent("LayerUpdated", this, &BaseScene::_OnRenderableComponentLayerChanged);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::_OnRenderableComponentLayerChanged(std::weak_ptr<RenderableComponent> renderabelComponent, int8_t)
{
    std::lock_guard lock(_renderableArrayMutex);
    _renderableComponentsToAdd.push_back(renderabelComponent);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
