#pragma once
#include <cstddef>
#include "Utility/Containers/AnyCallable/AnyCallableHandler.hpp"

namespace Utility
{
    /*!
     * \brief Interface for a Dispatcher.
     *
     * Interface that provides almost all required methods that should be in any dispatcher, 
     * exclude AddCallable(), because these functions are template based, so it cannot be 
     * placed here and made as virtual.
     */
    class DispatcherInterface
    {
    public:
        DispatcherInterface() = default;
        DispatcherInterface(const DispatcherInterface& other) = default;
        DispatcherInterface(DispatcherInterface&& other) = default;
        virtual ~DispatcherInterface() = default;
        DispatcherInterface& operator=(const DispatcherInterface& other) = default;
        DispatcherInterface& operator=(DispatcherInterface&& other) = default;

        /*!
         * \brief Invokes every stored callable in the dispatcher.
         * 
         * Should be implemented by the inherited class.
         */
        virtual void Invoke() = 0;

        /*!
         * \brief Simply removes callable from the list of callables.
         * \param callableHandler - handler of callable that should be removed.
         */
        virtual void RemoveCallable(const AnyCallableHandler& callableHandler) = 0;

        /*!
         * \brief Returns number of stored callables.
         * \return Number of callables that was stored in dispatcher.
         */
        virtual size_t GetNumberOfCallables() const = 0;
    };
}