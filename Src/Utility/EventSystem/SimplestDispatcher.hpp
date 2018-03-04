#pragma once
#include "Utility/EventSystem/Dispatcher.hpp"

namespace Utility
{
    /*!
     * \brief Implementation of Dispatcher<void> that uses no parameters on function calls.
     */
    class SimplestDispatcher : public Dispatcher<void>
    {
    public:
        /*!
         * \brief Invokes every stored callable in the dispatcher.
         * 
         * Tries to call every stored function without any parameter.
         * If Call of the function was failed because of the bad_any_cast,
         * function will be removed from the array.
         */
        void Invoke() final;
    };
}