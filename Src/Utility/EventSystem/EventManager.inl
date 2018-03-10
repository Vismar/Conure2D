#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret, class ... Args>
const AnyCallableHandler& EventManager::BindToEvent(const std::string& eventName, Ret(*function)(Args...))
{
    const auto event = _events.find(eventName);
    if (event != _events.end())
    {
        if (Dispatcher<Ret>* dispatcher = dynamic_cast<Dispatcher<Ret>*>(event->second))
        {
            return dispatcher->AddCallable(function);
        }
    }

    return EmptyAnyCallableHandler;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret, class UserClass, class ... Args>
const AnyCallableHandler& EventManager::BindToEvent(const std::string& eventName,
                                                    UserClass* userClass, 
                                                    Ret(UserClass::*function)(Args...))
{
    const auto event = _events.find(eventName);
    if (event != _events.end())
    {
        if (Dispatcher<Ret>* dispatcher = dynamic_cast<Dispatcher<Ret>*>(event->second))
        {
            return dispatcher->AddCallable(userClass, function);
        }
    }

    return EmptyAnyCallableHandler;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret, class ... Args>
void EventManager::InvokeEvent(const std::string& eventName, Args&&... args)
{
    const auto event = _events.find(eventName);
    if (event != _events.end())
    {
        // Try to cast stored dispatcher to the specified type, 
        // because dispatcher interface do not have the function
        // that will be used if cast succeeded
        if (auto dispatcher = dynamic_cast<Dispatcher<Ret>*>(event->second))
        {
            dispatcher->Invoke(std::forward<Args>(args)...);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
