#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
AnyCallableHandler Dispatcher<Ret>::AddCallable(Ret(*function)(Args...))
{
    AnyCallable<Ret> callable(function);
    if (_NotAdded(callable))
    {
        _callables.emplace_back(std::move(callable));

        return _callables.back().GetHandler();
    }

    return EmptyAnyCallableHandler;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class UserClass, class ... Args>
AnyCallableHandler Dispatcher<Ret>::AddCallable(UserClass* userClass, Ret(UserClass::*function)(Args...))
{
    AnyCallable<Ret> callable(userClass, function);
    if (_NotAdded(callable))
    {
        _callables.emplace_back(std::move(callable));

        return _callables.back().GetHandler();
    }

    return EmptyAnyCallableHandler;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
void Dispatcher<Ret>::Invoke(Args&&... args)
{
    for (auto iter = _callables.begin(); iter != _callables.end(); )
    {
        try
        {
            (*iter)(std::forward<Args>(args)...);
            ++iter;
        }
        catch (const std::bad_any_cast& exception)
        {
            (void)exception.what();
            iter = _callables.erase(iter);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
void Dispatcher<Ret>::Invoke()
{
    for (auto iter = _callables.begin(); iter != _callables.end(); )
    {
        try
        {
            (*iter)();
            ++iter;
        }
        catch (const std::bad_any_cast& exception)
        {
            (void)exception.what();
            iter = _callables.erase(iter);
        }
    }
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
