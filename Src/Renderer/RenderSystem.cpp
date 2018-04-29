#include "RenderSystem.hpp"

using namespace Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderSystem::RenderSystem() 
: _working(false)
, _noErrors(true)
, _recreateWindow(false)
, _updateWindowParameters(false)
, _window(WindowSettings())
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

            // Update window
            _UpdateWindow();

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

void RenderSystem::SetNewSettings(WindowSettings windowSettings)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    // These parameters require recreating the window
    if ((windowSettings.resolutionWidth != _settings.resolutionWidth) ||
        (windowSettings.resolutionHeight != _settings.resolutionHeight) ||
        (windowSettings.style != _settings.style) ||
        (windowSettings.bitsPerPixel != _settings.bitsPerPixel) ||
        (windowSettings.depthBits != _settings.depthBits) ||
        (windowSettings.stencilBits != _settings.stencilBits) ||
        (windowSettings.antialiasing != _settings.antialiasing) ||
        (windowSettings.majorContextVersion != _settings.majorContextVersion) ||
        (windowSettings.minorContaxtVersion != _settings.minorContaxtVersion))
    {
        _recreateWindow = true;
    }

    //These parameters not require to recreate window but new values anyway should be assigned
    if ((windowSettings.title != _settings.title) ||
        (windowSettings.width != _settings.width) ||
        (windowSettings.height != _settings.height) ||
        (windowSettings.verticalSync != _settings.verticalSync) ||
        (windowSettings.frameLimit != _settings.frameLimit) ||
        (windowSettings.cursorIsVisible != _settings.cursorIsVisible) ||
        (windowSettings.cursorIsGrabbed != _settings.cursorIsGrabbed))
    {
        _updateWindowParameters = true;
    }

    _settings = std::move(windowSettings);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WindowSettings RenderSystem::GetSettings() const
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    return _settings;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::SetWindowTitle(const std::string& title)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    if (title != _settings.title)
    {
        _settings.title = title;
        _updateWindowParameters = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::SetWindowSize(const uint32_t width, const uint32_t height)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    if (width != _settings.width || height != _settings.height)
    {
        _settings.width = width;
        _settings.height = height;
        _updateWindowParameters = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::SetWindowResolution(const uint32_t width, const uint32_t height)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    if (width != _settings.resolutionWidth || height != _settings.resolutionHeight)
    {
        _settings.resolutionWidth = width;
        _settings.resolutionHeight = height;
        _recreateWindow = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::SetAntialiasing(const uint32_t antialiasingLevel)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    if (antialiasingLevel != _settings.antialiasing)
    {
        _settings.antialiasing = antialiasingLevel;
        _recreateWindow = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::SetVerticalSyncEnabled(const bool enabled)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    if (enabled != _settings.verticalSync)
    {
        _settings.verticalSync = enabled;
        _updateWindowParameters = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::SetFramerateLimit(const uint32_t frameLimit)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    if (frameLimit != _settings.frameLimit)
    {
        _settings.frameLimit = frameLimit;
        _updateWindowParameters = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::SetMouseCursorVisible(const bool visible)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);
    
    if (visible != _settings.cursorIsVisible)
    {
        _settings.cursorIsVisible = visible;
        _updateWindowParameters = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::SetMouseCursorGrabbed(const bool grabbed)
{
    std::lock_guard<std::mutex> lock(_settingsMutex);

    if (grabbed != _settings.cursorIsGrabbed)
    {
        _settings.cursorIsGrabbed = grabbed;
        _updateWindowParameters = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderSystem::_UpdateWindow()
{
    if (_recreateWindow || _updateWindowParameters)
    {
        std::lock_guard<std::mutex> lock(_settingsMutex);

        // Recreate window if it is needed
        if (_recreateWindow)
        {
            _window.SetNewSettings(_settings);

            _recreateWindow = false;
            _updateWindowParameters = false;
        }
        else if (_updateWindowParameters)
        {
            // Update window title
            _window.SetTitle(_settings.title);

            // Update window parameters that is not require recreating the window
            _window.SetSize(_settings.width, _settings.height);
            _window.SetVerticalSyncEnabled(_settings.verticalSync);
            _window.SetFramerateLimit(_settings.frameLimit);
            _window.SetMouseCursorVisible(_settings.cursorIsVisible);
            _window.SetMouseCursorGrabbed(_settings.cursorIsGrabbed);

            _updateWindowParameters = false;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
