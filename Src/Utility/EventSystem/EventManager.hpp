#pragma once
#include "Utility/EventSystem/Dispatcher.hpp"
#include <unordered_map>

namespace Utility
{
    /*!
     * \brief Manager that provides functionality to create/delete named events and invoke them.
     * 
     * Class that provides functionality to do next things: 
     *   - Create/Delete named events with special dispatcher that can handle any possible function.
     *   - These events can be invoked whenever you want.
     *   - To these events can be bind any function that will be called when an event was invoked.
     *   - By a gained handler from binding a function to an event, the same function can be unbounded from that event. \n
     * 
     * Technically, this event manager designed to be a base class for entities that want to store and produce events,
     * to which any function can be attached. \n
     * 
     * P.S. If you will try to bind a function with different signature from what will be used by dispatcher,
     * it will do one of the two things: 
     *   - If a function returns different parameter than used in the dispatcher, 
     *     then it will not be added at all to a dispatcher.
     *   - If a function requires different parameters than used in the dispatcher, 
     *     then it will be removed from the dispatcher upon invoke.
     */
    class EventManager
    {
    public:
        EventManager() = default;
        EventManager(const EventManager&) = delete;
        EventManager(EventManager&&) = delete;
        EventManager& operator=(const EventManager&) = delete;
        EventManager& operator=(EventManager&&) = delete;

        /*!
         * \brief Destructor that deletes all stored dispatchers.
         */
        virtual ~EventManager();

        /*!
         * \brief Binds function to specified event.
         * \tparam Ret - returning type of a function.
         * \tparam Args - list of arguments.
         * \param eventName - name of the event to which function will be bounded.
         * \param function - a pointer to a function that will be bounded.
         * \return Handler of callable if it was bounded. Otherwise - empty handler.
         * 
         * Callable should NOT be const.
         */
        template <class Ret, class ... Args>
        const AnyCallableHandler& BindToEvent(const std::string& eventName, 
                                              Ret(*function)(Args...));

        /*!
         * \brief Binds class method to specified event.
         * \tparam Ret - returning type of a function.
         * \tparam UserClass - class type.
         * \tparam Args - list of arguments.
         * \param eventName - name of the event to which function will be bounded.
         * \param userClass - a pointer to a class whose function will be bounded.
         * \param function - a pointer to a function that will be bounded.
         * \return Handler of callable if it was bounded. Otherwise - empty handler.
         * 
         * Callable should NOT be const.
         */
        template <class Ret, class UserClass, class ... Args>
        const AnyCallableHandler& BindToEvent(const std::string& eventName, 
                                              UserClass* userClass, 
                                              Ret(UserClass::*function)(Args...));

        /*!
         * \brief Unbinds the callable that handled by handler from specified event.
         * \param eventName - name of the event from which function will be removed.
         * \param callableHandler - handler of callable that should be removed.
         */
        void UnbindFromEvent(const std::string& eventName, const AnyCallableHandler& callableHandler);

    protected:
        /*!
         * \brief Creates new named event with specified dispatcher.
         * \param eventName - name of the event.
         * \param dispatcher - dispatcher that will be used to store callables.
         * \return True if event was created. Otherwise - false.
         */
        bool AddEvent(const std::string& eventName, DispatcherInterface* dispatcher);

        /*!
         * \brief Deletes specified event.
         * \param eventName - name of the event that will be deleted.
         */
        void DeleteEvent(const std::string& eventName);

        /*!
         * \brief Invokes all bounded callables to specified event.
         * \param eventName - name of the event that will be invoked.
         */
        void InvokeEvent(const std::string& eventName);

        /*!
         * \brief Invokes all bounded callables to specified event.
         * \tparam Ret - returning type of stored functions.
         * \tparam Args - list of arguments.
         * \param eventName -  name of the event that will be invoked.
         * \param args - arguments that will be used in call of stored functions.
         * 
         * Tries to cast stored dispatcher to a specified type and invoke it with specified arguments.
         */
        template <class Ret, class ... Args>
        void InvokeEvent(const std::string& eventName, Args&& ... args);

    private:
        /*! Map of named events and it dispatchers. */
        std::unordered_map<std::string, DispatcherInterface*> _events;
    };

#include "EventManager.inl"
}