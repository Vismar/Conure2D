#pragma once
#include <typeinfo>

namespace C2D
{
    /*!
     * \brief Special handler that was created to make possible to compare AnyCallable instances.
     * 
     * Works in a tricky way. It has 2 variables:
     *   - First handler - plain size_t variable. 
     *   - Second handler - pointer to type info. \n
     *   
     * Both are used differently for two cases: 
     *   - AnyCallable that contains a pointer to a function. 
     *   - AnyCallable that contains a pointer to a class method. \n
     *   
     * Check variable descriptions to know more.
     */
    class AnyCallableHandler
    {
    public:
        /*!
         * \brief Default constructor.
         */
        AnyCallableHandler() noexcept;

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
        std::size_t _firstHandler;
        /*! 
         * Second handler contains pointer to type info of a function 
         * ONLY when AnyCallable contains a pointer to a class method.
         * Otherwise it will contains nullptr.
         */
        std::type_info* _secondHandler;

        template <class Ret>
        friend class AnyCallable;
    };

    static const AnyCallableHandler EmptyAnyCallableHandler;
}