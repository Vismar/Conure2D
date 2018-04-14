#include "EngineApp.hpp"

using namespace Engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EngineApp::EngineApp()
    : _renderSystem(std::make_unique<Renderer::RenderSystem>())
    , _logicThreadIsWorking(false)
    , _sceneMap(std::make_unique<Core::SceneMap>())
    , _inputSystem(std::make_unique<Input::InputSystem>(_logicLoopTimeSpan))
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EngineApp& EngineApp::Instance()
{
    static EngineApp engineApp;
    return engineApp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EngineApp::Run()
{
    // Start logic thread
    std::thread logicThread(&EngineApp::_LogicLoop, this);
    logicThread.detach();

    // Start render system
    _renderSystem->Start(*_sceneMap, *_inputSystem, _renderLoopTimeSpan);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EngineApp::End()
{
    // Wait all systems to end its work
    while (_logicThreadIsWorking); // wait until logic thread will end its work
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Renderer::RenderSystem& EngineApp::GetRenderSystem() const
{
    return *_renderSystem;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::SceneMap& EngineApp::GetSceneMap() const
{
    return *_sceneMap;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Input::InputSystem& EngineApp::GetInputSystem() const
{
    return *_inputSystem;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Utility::TimeSpan& EngineApp::GetRenderLoopTimeSpan() const
{
    return _renderLoopTimeSpan;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Utility::TimeSpan& EngineApp::GetLogicLoopTimeSpan() const
{
    return _logicLoopTimeSpan;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EngineApp::_LogicLoop()
{
    // Launch logic loop only if it was not started yet
    if (!_logicThreadIsWorking)
    {
        _logicThreadIsWorking = true;
        _logicLoopTimeSpan.SetNewEnd(Utility::Time::CurrentTime());
        _logicLoopTimeSpan.SetNewEnd(Utility::Time::CurrentTime());

        // If render system works properly, update scenes
        while (_renderSystem->NoErrors())
        {
            // Update scenes
            _sceneMap->UpdateScenes();

            // Make sure that logic loop runs only <= 125 times per second.
            // If it will run faster, then a user input might be missed during some loops.
            // It will lead to possible bugs.
            while ((Utility::Time::CurrentTime() - _logicLoopTimeSpan.End()).ToMilliseconds() < 8) {}

            // Update time span
            _logicLoopTimeSpan.SetNewEnd(Utility::Time::CurrentTime());
        }

        // Mark that logic thread finished its work
        _logicThreadIsWorking = false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
