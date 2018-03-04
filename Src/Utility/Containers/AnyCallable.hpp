#pragma once
#include "Utility/Containers/AnyCallableHandler.hpp"
#include <any>
#include <functional>

namespace Utility
{
    /*!
     * \brief Container that provides the ability to store any kind of function despite its signature and then call it.
     * 
     * Heavy template oriented class that stores gotten function in std::any and then cast it back to make a function call.
     * Can store simple function or class method. Both can be with any parameters, 
     * but returning type must be defined upon creation of this container.
     */
    template <class Ret>
    class AnyCallable
    {
    public:
        AnyCallable() = default;
        AnyCallable(const AnyCallable& other) = default;
        AnyCallable(AnyCallable&& other) = default;
        ~AnyCallable() = default;
        AnyCallable& operator=(const AnyCallable& other) = default;
        AnyCallable& operator=(AnyCallable&& other) = default;

        /*!
         * \brief Constructor that creates AnyCallable from pointer to a function.
         * \param function - a pointer to a function.
         */
        template <class ... Args>
        explicit AnyCallable(Ret(*function)(Args...));

        /*!
         * \brief Constructor that creates AnyCallable from pointer to a class method.
         * \param userClass - a pointer to a class whose function can be called by operator().
         * \param function - a pointer to a function which can be called by operator().
         */
        template <class UserClass, class ... Args>
        explicit AnyCallable(UserClass* userClass, Ret(UserClass::*function)(Args...));

        /*!
         * \brief Equality operator.
         * \param other - const reference to other AnyCallable.
         * \return True if both AnyCallable have equal handlers. Otherwise - false.
         */
        bool operator==(const AnyCallable& other) const;

        /*!
         * \brief Function call operator.
         * \param args - arguments that will be used in call of stored function.
         * 
         * Should be used in try-catch section, because any_cast will throw exception if it failed.
         */
        template <class ... Args>
        Ret operator()(Args&& ... args);

        /*!
         * \brief Returns handler.
         * \return Handler of this particular instance of AnyCallable.
         */
        const AnyCallableHandler& GetHandler() const;

    private:
        /*!
         * \brief Sets data in handler from given function.
         * \param function - a pointer to function that will be stored.
         */
        template <class ... Args>
        void _SetHandler(Ret(*function)(Args...));
        
        /*
         * \brief Sets data in handler from given class and its function.
         * \param userClass - a pointer to a class whose function can be called by operator().
         * \param function - a pointer to a function which can be called by operator().
         */
        template <class UserClass, class ... Args>
        void _SetHandler(UserClass* userClass, Ret(UserClass::*function)(Args...));

        /*! Handler that used to compare two AnyCallable. */
        AnyCallableHandler _handler;
        /*! Container to store any kind of function despite its signature. */
        std::any _function;
    };

#include "AnyCallable.inl"
}