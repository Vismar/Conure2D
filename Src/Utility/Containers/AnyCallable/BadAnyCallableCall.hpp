#pragma once
#include <any>
#include <sstream>
#include <vector>

namespace Utility
{
    template <class Ret>
    class AnyCallable;

    /*!
     * \brief Exception that will be thrown by AnyCallable upon std::bad_any_cast within the class.
     */
    class BadAnyCallableCall : public std::bad_any_cast
    {
    public:
        BadAnyCallableCall() = delete;
        ~BadAnyCallableCall() override = default;
        BadAnyCallableCall(const BadAnyCallableCall& other) = default;
        BadAnyCallableCall(BadAnyCallableCall&& other) noexcept = default;
        BadAnyCallableCall& operator=(const BadAnyCallableCall& other) = default;
        BadAnyCallableCall& operator=(BadAnyCallableCall&& other) = default;

        /*!
         * \brief Creates new exception upon bad call of AnyCallable.
         * \tparam Ret - returning parameter type,
         * \tparam Args - argument types that were used to call AnyCallable.
         * \param anyCallable - AnyCallable that were failed upon calling.
         * \param args - actual arguments that were used to call AnyCallable.
         */
        template <class Ret, class ... Args>
        explicit BadAnyCallableCall(const AnyCallable<Ret>& anyCallable, Args&& ... args);

        /*!
         * \brief Grabs message that contains information about exception
         * \return Returns message that contains what happend when exception was thrown.
         */
        const char* what() const noexcept override;

    private:
        /*! Message of an exception. */
        std::string _exceptionMessage;
    };
}

#include "BadAnyCallableCall.inl"