#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
const AnyCallableHandler& Dispatcher<Ret>::AddCallable(Ret(*function)(Args...))
{
    AnyCallable<Ret> callable(function);
    if (_NotAdded(callable))
    {
        _callables.emplace_back(std::move(callable));

        return _callables.back().GetHandler();
    }

    return _defaultAnyCallableHandler;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class UserClass, class ... Args>
const AnyCallableHandler& Dispatcher<Ret>::AddCallable(UserClass* userClass, Ret(UserClass::*function)(Args...))
{
    AnyCallable<Ret> callable(userClass, function);
    if (_NotAdded(callable))
    {
        _callables.emplace_back(std::move(callable));

        return _callables.back().GetHandler();
    }

    return _defaultAnyCallableHandler;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
void Dispatcher<Ret>::RemoveCallable(const AnyCallableHandler& callableHandler)
{
    for (auto iter = _callables.begin(); iter != _callables.end(); ++iter)
    {
        if (callableHandler == iter->GetHandler())
        {
            (void)_callables.erase(iter);
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
size_t Dispatcher<Ret>::GetNumberOfCallables() const
{
    return _callables.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
bool Dispatcher<Ret>::_NotAdded(const AnyCallable<Ret>& newCallable) const
{
    bool notAdded = true;

    for (const auto& callable : _callables)
    {
        if (newCallable == callable)
        {
            notAdded = false;
            break;
        }
    }

    return notAdded;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////