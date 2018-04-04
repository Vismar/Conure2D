#include "RenderSystem.hpp"
#include <thread>

using namespace Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderSystem::RenderSystem() : _working(false), _window(WindowSettings())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::Start(const std::shared_ptr<Core::RenderableSceneMapInterface>& sceneMap)
{
    if (!_working)
    {
        _working = true;
        _sceneMap = sceneMap;

        // If render was started, window is open and scene map is not nullptr, render
        while (_working && _window.IsOpen() && _sceneMap)
        {
            // Poll events
            _window.PollEvents();

            // Render
            _window.BeginDraw();

            // Grab scene order
            const auto& sceneOrder = _sceneMap->GetRenderOrder();
            // Go through every mentioned scene
            for (auto& sceneName : sceneOrder)
            {
                // Try to get set of renderable components from certain scene
                if (const auto renderableSet = _sceneMap->GetRenderableComponentsFromScene(sceneName))
                {
                    // Go through every renderable component in the obtained set
                    for (auto& renderableComponent : (*renderableSet))
                    {
                        if (const auto renderable = renderableComponent.lock())
                        {
                            // Renderable component should be turned on and be visible
                            if (renderable->IsTurnedOn() && renderable->IsVisible())
                            {
                                _window.Draw(*renderable);
                            }
                        }
                    }
                }
            }

            _window.EndDraw();
        }

        _working = false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::Stop()
{
    _working = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderSystem::Working() const
{
    return _working;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
