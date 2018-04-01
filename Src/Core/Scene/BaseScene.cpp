#include "BaseScene.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseScene::BaseScene() : _activated(false)
{
    _renderableComponents = std::make_shared<RenderableArray>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<SceneObject> BaseScene::CreateObject()
{
    _sceneObjects.emplace_back(std::make_shared<SceneObject>())->_Initialize();

    return _sceneObjects.back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::Activate(const bool activate)
{
    _activated = activate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<RenderableArray> BaseScene::_GetRenderableComponents() const
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
            iter = (*_renderableComponents).erase(iter);
        }
    }

    // Add new pointers to the list
    std::lock_guard<std::mutex> lock(_renderableArrayMutex);
    for (auto& renderableComponent : _renderableComponentsToAdd)
    {
        _renderableComponents->push_back(renderableComponent);
    }

    // Clear to prevent copying
    _renderableComponentsToAdd.clear();

    return _renderableComponents;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BaseScene::_Loop()
{
    for (auto& sceneObject : _sceneObjects)
    {
        sceneObject->_Update();
    }

    for (auto& sceneObject : _sceneObjects)
    {
        sceneObject->_LateUpdate();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
