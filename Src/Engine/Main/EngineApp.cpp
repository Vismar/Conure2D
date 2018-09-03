#include "EngineApp.hpp"
#include "Engine/EngineInterface.hpp"
#include <thread>

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EngineApp::EngineApp()
: _ioSystem(std::make_unique<IOSystem>())
, _logSystem(std::make_unique<LogSystem>(*_ioSystem))
, _renderSystem(std::make_unique<RenderSystem>())
, _logicThreadIsWorking(false)
, _sceneMap(std::make_unique<SceneMap>())
, _inputSystem(std::make_unique<InputSystem>(_logicLoopTimeSpan))
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
    std::thread(&EngineApp::_LogicLoop, this).detach();

    // Start render system
    _renderSystem->Start(*_sceneMap, *_inputSystem, _renderLoopTimeSpan);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EngineApp::End() const
{
    // If we come here, so render system already finished its work, no need to do anything with that.
    // But all other systems should be turned off manually.

    // Finish work of logic thread
    while (_logicThreadIsWorking.load());  // wait until logic thread will end its work
    
    // Finish work of log system
    _logSystem->Flush();                   // flush all log entries if any still in queue

    // Finish work of IO system
    _ioSystem->Stop();                     // turn off IO system 
    while (_ioSystem->IsRunning());        // wait until IO thread will end its work
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderSystem& EngineApp::GetRenderSystem() const
{
    return *_renderSystem;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SceneMap& EngineApp::GetSceneMap() const
{
    return *_sceneMap;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputSystem& EngineApp::GetInputSystem() const
{
    return *_inputSystem;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TimeSpan& EngineApp::GetRenderLoopTimeSpan() const
{
    return _renderLoopTimeSpan;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TimeSpan& EngineApp::GetLogicLoopTimeSpan() const
{
    return _logicLoopTimeSpan;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IOSystem& EngineApp::GetIOSystem() const
{
    return *_ioSystem;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LogSystem& EngineApp::GetLogSystem() const
{
    return *_logSystem;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EngineApp::_LogicLoop()
{
    DEV_LOG(LogLevel::Debug, "Logic loop has started");

    // Launch logic loop only if it was not started yet
    if (!_logicThreadIsWorking)
    {
        _logicThreadIsWorking = true;
        _logicLoopTimeSpan.SetNewEnd(Time::CurrentTime());
        _logicLoopTimeSpan.SetNewEnd(Time::CurrentTime());

        // If render system works properly, update scenes
        while (_renderSystem->NoErrors())
        {
            // Update scenes
            _sceneMap->UpdateScenes();

            // Update time span
            _logicLoopTimeSpan.SetNewEnd(Time::CurrentTime());
        }

        // Mark that logic thread finished its work
        _logicThreadIsWorking = false;
    }

    DEV_LOG(LogLevel::Debug, "Logic loop has stopped");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
