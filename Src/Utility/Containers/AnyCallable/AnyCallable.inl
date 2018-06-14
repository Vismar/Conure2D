#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
AnyCallable<Ret>::AnyCallable(Ret(*function)(Args...))
{
    _SetHandler(function);

    std::function<Ret(Args...)> temporary(function);
    _function = temporary;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class UserClass, class ... Args>
AnyCallable<Ret>::AnyCallable(UserClass* userClass, Ret(UserClass::*function)(Args...))
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
bool AnyCallable<Ret>::operator==(const AnyCallable& other) const
{
    return (_handler == other._handler);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
Ret AnyCallable<Ret>::operator()(Args&& ... args)
{
    return std::any_cast<std::function<Ret(Args...)>> (_function)(std::forward<Args>(args)...);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
AnyCallableHandler AnyCallable<Ret>::GetHandler() const
{
    return _handler;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class ... Args>
void AnyCallable<Ret>::_SetHandler(Ret(*function)(Args...))
{
    _handler._firstHandler = reinterpret_cast<std::size_t>(function);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret>
template <class UserClass, class ... Args>
void AnyCallable<Ret>::_SetHandler(UserClass* userClass, Ret(UserClass::*function)(Args...))
{
    _handler._firstHandler = reinterpret_cast<std::size_t>(userClass);
    _handler._secondHandler = const_cast<std::type_info*>(&typeid(function));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
