#pragma once
#include "Utility/EventSystem/DispatcherInterface.hpp"
#include "Utility/Containers/AnyCallable.hpp"
#include <vector>

namespace Utility
{
    /*!
     * \tparam Ret - returning type of stored functions.
     * 
     * Container that handles array of AnyCallable and provides next functionality: 
     *   - Add/Remove callables
     *   - Invoke them at once (to do so you should implement Invoke() method by yourself in the way you want).
     */
    template <class Ret>
    class Dispatcher : public DispatcherInterface
    {
    public:
        /*!
         * \brief Adds callable to the array and returns handle of added callable.
         * \tparam Args - list of arguments.
         * \param function - a pointer to a function that will be stored.
         * \return Handler of callable if it was stored. Otherwise - empty handler.
         */
        template <class ... Args>
        const AnyCallableHandler& AddCallable(Ret(*function)(Args...));

        /*!
         * \brief Adds callable to the array and returns handle of added callable.
         * \tparam UserClass - class type.
         * \tparam Args - list of arguments.
         * \param userClass - a pointer to a class whose function will be stored.
         * \param function - a pointer to a function that will be stored.
         * \return Handler of callable if it was stored. Otherwise - empty handler.
         */
        template <class UserClass, class ... Args>
        const AnyCallableHandler& AddCallable(UserClass* userClass, Ret(UserClass::*function)(Args...));

        /*!
         * \brief Simply removes callable from the list of callables.
         * \param callableHandler - handler of callable that should be removed.
         */
        void RemoveCallable(const AnyCallableHandler& callableHandler) final;

        /*!
         * \brief Returns number of stored callables.
         * \return Number of callables that was stored in dispatcher.
         */
        size_t GetNumberOfCallables() const final;

    protected:
        /*! Array of callables that can be invoked by Invoke() function that should be implemented by the inherited class.. */
        std::vector<AnyCallable<Ret>> _callables;

    private:
        /*!
         * \brief Check if specified callable was already added to this dispatcher.
         * \param newCallable - callable that should be checked.
         * \return True of specified callable was not added. Otherwise - false.
         */
        bool _NotAdded(const AnyCallable<Ret>& newCallable) const;
    };

#include "Dispatcher.inl"
}
