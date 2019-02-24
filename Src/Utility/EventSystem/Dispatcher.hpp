#pragma once
#include "Utility/EventSystem/DispatcherInterface.hpp"
#include "Utility/Containers/AnyCallable/AnyCallable.hpp"
#include "Utility/Exception/ExceptionHandler.hpp"
#include <vector>

namespace C2D
{
    /*!
     * \brief Container that stores AnyCallables.
     * \tparam Ret - returning type of stored functions.
     * 
     * Container that handles array of AnyCallable and provides next functionality: 
     *   - Add/Remove callables
     *   - Invoke them at once (to do so you should implement Invoke() method by yourself in the way you want).
     */
    template <class Ret>
    class [[deprecated("Will be removed")]] Dispatcher : public DispatcherInterface
    {
    public:
        /*!
         * \brief Adds callable to the array and returns handle of added callable.
         * \tparam Args - list of arguments.
         * \param function - a pointer to a function that will be stored.
         * \return Handler of callable if it was stored. Otherwise - empty handler.
         */
        template <class ... Args>
        AnyCallableHandler AddCallable(Ret(*function)(Args...));

        /*!
         * \brief Adds callable to the array and returns handle of added callable.
         * \tparam UserClass - class type.
         * \tparam Args - list of arguments.
         * \param userClass - a pointer to a class whose function will be stored.
         * \param function - a pointer to a function that will be stored.
         * \return Handler of callable if it was stored. Otherwise - empty handler.
         */
        template <class UserClass, class ... Args>
        AnyCallableHandler AddCallable(UserClass* userClass, Ret(UserClass::*function)(Args...));

        /*!
         * \brief Invokes every stored callable in the dispatcher with specified parameters.
         * \tparam Args - list of arguments.
         * \param args - arguments that will be used in call of stored functions.
         *
         * Tries to call every stored function with specified parameters.
         * If call of the function was failed because of the bad_any_cast,
         * function will be removed from the array.
         */
        template <class ... Args>
        void Invoke(Args&& ... args);

        /*!
         * \brief Invokes every stored callable in the dispatcher.
         *
         * Tries to call every stored function without any parameter.
         * If call of the function was failed because of the bad_any_cast,
         * function will be removed from the array.
         */
        void Invoke() override;

        /*!
         * \brief Simply removes callable from the list of callables.
         * \param callableHandler - handler of callable that should be removed.
         */
        void RemoveCallable(const AnyCallableHandler& callableHandler) final;

        /*!
         * \brief Returns number of stored callables.
         * \return Number of callables that were stored in dispatcher.
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
