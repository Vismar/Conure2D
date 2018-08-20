#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
Utility::AnyCallable<Ret>::AnyCallable(Ret(*function)(Args...))
{
    _SetHandler(function);

    std::function<Ret(Args...)> temporary(function);
    _function = temporary;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class UserClass, class ... Args>
Utility::AnyCallable<Ret>::AnyCallable(UserClass* userClass, Ret(UserClass::*function)(Args...))
{
    _SetHandler(userClass, function);

    std::function<Ret(Args...)> internal =
        [userClass, function](Args... args)
        {
            return (*userClass.*function)(std::forward<Args>(args)...);
        };

    _function = internal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
bool Utility::AnyCallable<Ret>::operator==(const AnyCallable& other) const
{
    return (_handler == other._handler);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
Ret Utility::AnyCallable<Ret>::operator()(Args&& ... args)
{
    try
    {
        return std::any_cast<std::function<Ret(Args...)>> (_function)(std::forward<Args>(args)...);
    }
    catch (const std::bad_any_cast& exception)
    {
        throw BadAnyCallableCall(*this, std::forward<Args>(args)...);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
Utility::AnyCallableHandler Utility::AnyCallable<Ret>::GetHandler() const
{
    return _handler;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
std::type_index Utility::AnyCallable<Ret>::GetContainedType() const
{
    return _function.type();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
void Utility::AnyCallable<Ret>::_SetHandler(Ret(*function)(Args...))
{
    _handler._firstHandler = reinterpret_cast<std::size_t>(function);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class UserClass, class ... Args>
void Utility::AnyCallable<Ret>::_SetHandler(UserClass* userClass, Ret(UserClass::*function)(Args...))
{
    _handler._firstHandler = reinterpret_cast<std::size_t>(userClass);
    _handler._secondHandler = const_cast<std::type_info*>(&typeid(function));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
