#include "EngineApp.hpp"

using namespace Engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EngineApp::EngineApp()
: _renderSystem(std::make_unique<Renderer::RenderSystem>())
, _logicThreadIsWorking(false)
, _sceneMap(std::make_unique<Core::SceneMap>())
, _inputSystem(std::make_unique<Input::InputSystem>(_logicLoopTimeSpan))
, _ioSystem(std::make_unique<Utility::IOSystem>())
, _logSystem(std::make_unique<Utility::LogSystem>(*_ioSystem))
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
    // Start IO thread
    _ioSystem->Start();

    // Start logic thread
    std::thread logicThread(&EngineApp::_LogicLoop, this);
    logicThread.detach();

    // Start render system
    _renderSystem->Start(*_sceneMap, *_inputSystem, _renderLoopTimeSpan);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EngineApp::End() const
{
    // If we come here, so render system already finished its work, no need to do anything with that.
    // But all other systems should be turned off manually

    // Finish work of logic thread
    while (_logicThreadIsWorking);  // wait until logic thread will end its work

    // Finish work of log system
    _logSystem->Flush();            // flush all log entries if any still in queue

    // Finish work of IO system
    _ioSystem->Stop();              // turn off IO system 
    while (_ioSystem->IsRunning()); // wait until IO thread will end its work
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

Utility::IOSystem& EngineApp::GetIOSystem() const
{
    return *_ioSystem;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Utility::LogSystem& EngineApp::GetLogSystem() const
{
    return *_logSystem;
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

            // Update time span
            _logicLoopTimeSpan.SetNewEnd(Utility::Time::CurrentTime());
        }

        // Mark that logic thread finished its work
        _logicThreadIsWorking = false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
