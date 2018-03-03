#pragma once
#include <typeinfo>

namespace Utility
{
    /*!
     * \brief Special handler that was created to make possible to compare AnyCallable instances.
     * 
     * Works in a tricky way. It have 2 variables: \n
     *   1) First handler - plain size_t variable. \n
     *   2) Second handler - pointer to type info. \n
     *   
     * Both are used differently for two cases: \n
     *   1) AnyCallable that contains a pointer to a function. \n
     *   2) AnyCallable that contains a pointer to a class method. \n
     *   
     * Check variable descriptions to know more.
     */
    class AnyCallableHandler
    {
    public:
        /*!
         * \brief Equality operator.
         * \param other - const reference to other handler.
         * \return True if both handlers have same handlers that are equals. Otherwise - false.
         */
        bool operator==(const AnyCallableHandler& other) const;

        /*!
         * \brief Check if handler currently handles something.
         * \return True if handler currently handles something. Otherwise - false.
         */
        bool IsHandling() const;

    private:
        /*!
         * First handler contains address to an object in next cases: \n
         *   1) If AnyCallable contains a pointer to a function, 
         *      then the first handler stores address of that function.
         *      Second handler stores nullptr. \n
         *   2) If AnyCallable contains a pointer to a class method, 
         *      then the first handler stores address of that class.
         *      Second handler stores pointer to type info that method. \n
         * 
         * If handler do not handle any AnyCallable, then first handler will be equal to 0.
         */
        std::size_t _firstHandler = 0;
        /*! 
         * Second handler contains pointer to type info of a function 
         * ONLY when AnyCallable contains a pointer to a class method.
         * Otherwise it will contains nullptr.
         */
        std::type_info* _secondHandler = nullptr;

        template <class Ret>
        friend class AnyCallable;
    };
}