#include "RenderSystem.hpp"

using namespace Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderSystem::RenderSystem() : _working(false), _noErrors(true), _window(WindowSettings())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::Start(const Core::RenderableSceneMapInterface& sceneMap,
                         Input::InputSystemHandlerInterface& inputSystem,
                         Utility::TimeSpan& renderLoopTimeSpan)
{
    if (!_working)
    {
        _working = true;
        renderLoopTimeSpan.SetNewEnd(Utility::Time::CurrentTime());
        renderLoopTimeSpan.SetNewEnd(Utility::Time::CurrentTime());

        // If render was started, window is open and scene map is not nullptr, render
        while (_working && _window.IsOpen())
        {
            // Poll events
            _window.PollEvents(inputSystem, renderLoopTimeSpan.Start());

            // Render
            _window.BeginDraw();

            // Grab scene order
            const auto& sceneOrder = sceneMap.GetRenderOrder();
            // Go through every mentioned scene
            for (auto& sceneName : sceneOrder)
            {
                // Try to get set of renderable components from certain scene
                if (const auto renderableSet = sceneMap.GetRenderableComponentsFromScene(sceneName))
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

            // Update time span
            renderLoopTimeSpan.SetNewEnd(Utility::Time::CurrentTime());
        }

        _working = false;
        _noErrors = false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::Stop()
{
    _working = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderSystem::NoErrors() const
{
    return _noErrors;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
