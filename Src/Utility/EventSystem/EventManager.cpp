#include "EventManager.hpp"

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EventManager::~EventManager()
{
    for (auto& event : _events)
    {
        delete event.second;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EventManager::UnbindFromEvent(const std::string& eventName, const AnyCallableHandler& callableHandler)
{
    const auto event = _events.find(eventName);
    if (event != _events.end())
    {
        event->second->RemoveCallable(callableHandler);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool EventManager::AddEvent(const std::string& eventName, DispatcherInterface* dispatcher)
{
    bool created(false);

    const auto event = _events.find(eventName);
    if (event == _events.end())
    {
        _events.insert({eventName, dispatcher});
        created = true;
    }

    return created;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EventManager::DeleteEvent(const std::string& eventName)
{
    const auto event = _events.find(eventName);
    if (event != _events.end())
    {
        delete event->second;
        _events.erase(eventName);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EventManager::InvokeEvent(const std::string& eventName)
{
    const auto event = _events.find(eventName);
    if (event != _events.end())
    {
        event->second->Invoke();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
