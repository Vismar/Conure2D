#include "SceneMap.hpp"
#include "Engine/EngineInterface.hpp"
#include "Utility/LogSystem/LogSystem.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SceneMap::AddScene(std::shared_ptr<BaseScene>&& newScene)
{
    bool added(false);

    // If scene map do not already store any scene with such name, then add it
    const auto scene = _scenes.find(newScene->GetName());
    if (scene == _scenes.end())
    {
        DEV_LOG(Utility::LogLevel::Debug, "New scene was added - " + newScene->GetName());

        _scenes.emplace(newScene->GetName(), newScene);
        added = true;

        // Update render order list with new scene name
        _AddSceneNameToRenderList(newScene->GetName());
    }

    return added;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<BaseScene> SceneMap::GetScene(const std::string& sceneName) const
{
    std::weak_ptr<BaseScene> scenePointer;

    // If specified scene exist, return it
    const auto scene = _scenes.find(sceneName);
    if (scene != _scenes.end())
    {
        scenePointer = std::dynamic_pointer_cast<BaseScene>(scene->second);
    }

    return scenePointer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SceneMap::RemoveScene(const std::string& sceneName)
{
    bool removed(false);

    // If specified scene exist, remove it
    const auto scene = _scenes.find(sceneName);
    if (scene != _scenes.end())
    {
        DEV_LOG(Utility::LogLevel::Debug, sceneName + " scene was marked to be deleted later");

        // Mark a scene so it will be deleted later
        scene->second->DeleteLater();
        removed = true;
    }

    return removed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneMap::UpdateScenes()
{
    // Deleted scenes that were marked as "delete later"
    for (auto scene = _scenes.begin(); scene != _scenes.end(); ++scene)
    {
        if (scene->second->MarkedAsDeleteLater())
        {
            DEV_LOG(Utility::LogLevel::Debug, scene->first + " scene was deleted");

            scene = _scenes.erase(scene);
        }
    }

    // Update remained scenes
    for (auto& scene : _scenes)
    {
        // Update scene only if was activated
        if (scene.second->Activated())
        {
            scene.second->Update();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneMap::SetRenderOrder(const std::list<std::string>& renderOrder)
{
    _renderOrder = renderOrder;

    // Check if all scene names are in the list
    for (const auto& scene : _scenes)
    {
        _AddSceneNameToRenderList(scene.first);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::list<std::string>& SceneMap::GetRenderOrder() const
{
    return _renderOrder;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<RenderableSet> SceneMap::GetRenderableComponentsFromScene(const std::string& sceneName) const
{
    std::shared_ptr<RenderableSet> renderableComponents;

    // If specified scene exist and it is active, return array of renderable components
    const auto scene = _scenes.find(sceneName);
    if ((scene != _scenes.end()) && (scene->second->Activated()))
    {
        renderableComponents = scene->second->GetRenderableComponents();
    }

    return renderableComponents;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<CameraSet> SceneMap::GetCameraComponentsFromScene(const std::string& sceneName) const
{
    std::shared_ptr<CameraSet> cameraComponents;

    // If specified scene exist and it is active, return array of camera components
    const auto scene = _scenes.find(sceneName);
    if ((scene != _scenes.end()) && (scene->second->Activated()))
    {
        cameraComponents = scene->second->GetCameraComponents();
    }

    return cameraComponents;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneMap::_AddSceneNameToRenderList(const std::string& newSceneName)
{
    bool notAdded(true);

    // Try to find scene name in render order list
    for (auto& sceneName : _renderOrder)
    {
        if (sceneName == newSceneName)
        {
            notAdded = false;
        }
    }

    // If scene name was not added, then add it to the start of the list
    if (notAdded)
    {
        _renderOrder.push_front(newSceneName);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
