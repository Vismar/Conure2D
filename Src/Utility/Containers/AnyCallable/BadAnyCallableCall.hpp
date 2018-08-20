#pragma once
#include <any>
#include <sstream>
#include <vector>

namespace Utility
{
    template <class Ret>
    class AnyCallable;

    class BadAnyCallableCall : public std::bad_any_cast
    {
    public:
        BadAnyCallableCall() = delete;
        ~BadAnyCallableCall() override = default;
        BadAnyCallableCall(const BadAnyCallableCall& other) = default;
        BadAnyCallableCall(BadAnyCallableCall&& other) noexcept = default;
        BadAnyCallableCall& operator=(const BadAnyCallableCall& other) = default;
        BadAnyCallableCall& operator=(BadAnyCallableCall&& other) = default;

        template <class Ret, class ... Args>
        explicit BadAnyCallableCall(const AnyCallable<Ret>& anyCallable, Args&& ... args);

        const char* what() const noexcept override;
    private:
        std::string _exceptionMessage;
    };
}

#include "BadAnyCallableCall.inl"