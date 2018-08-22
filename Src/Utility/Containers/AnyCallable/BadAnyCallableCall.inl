#pragma once
#include "Utility/LogSystem/LogUtilities.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Ret, class ... Args>
Utility::BadAnyCallableCall::BadAnyCallableCall(const AnyCallable<Ret>& anyCallable, Args&& ... args)
: std::bad_any_cast()
{
    std::basic_ostringstream<char> exceptionMessage;
    exceptionMessage << "Bad any cast upon call of a AnyCallable<>\n"
                     << "AnyCallable<> stored type: "
                     << Utility::PrettyTypeName(anyCallable.GetContainedType())
                     << "\nActual arguments that where used: ";

    std::vector<std::any> arguments{std::forward<Args>(args)...};
    for (auto& argument : arguments)
    {
        exceptionMessage << Utility::PrettyTypeName(argument.type()) << ", ";
    }
    exceptionMessage << "\n";

    _exceptionMessage = exceptionMessage.str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
