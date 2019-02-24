#pragma once
#include <queue>
#include <mutex>
#include <chrono>
#include <atomic>
#include <optional>
#include <type_traits>
#include <condition_variable>

using namespace std::chrono_literals;

namespace C2D
{
    struct UseMutex {};
    struct UseSpinlock {};

    /*!
     * \brief The queue which uses locks to provide safe access to stored items for multiple threads.
     * \tparam T Type of items that will be stored within the queue.
     */
    template <class T, class LockType = UseSpinlock>
    class LockedQueue final
    {
        /*!
         * \brief Standard mutex with condition variable to notify awaiting threads.
         */
        struct Mutex final
        {
            /*! Mutex to protect queue variable. */
            std::mutex mutex;
            /*! Condition variable to notify waiting consumers about new items in the queue. */
            std::condition_variable conditionVar;
        };

        /*!
         * \brief Atomic flag that "spins" to get access to queue.
         */
        struct Spinlock final
        {
            /*! Simple atomic flag. */
            std::atomic_flag spinlock = ATOMIC_FLAG_INIT;
        };

        /*! Lock type that will be used in queue. */
        using ActualLockType = typename std::conditional<std::is_same_v<LockType, UseMutex>,
                                                         LockedQueue::Mutex,
                                                         LockedQueue::Spinlock>::type;

        // Queue accepts only 2 possible locks
        static_assert(std::is_same_v<LockType, UseMutex> || std::is_same_v<LockType, UseSpinlock>,
                      "Wrong lock type. Must be UseMutex or UseSpinlock");
    public:
        LockedQueue() = default;
        ~LockedQueue() = default;
        LockedQueue(const LockedQueue&) = delete;
        LockedQueue(LockedQueue&&) = delete;
        LockedQueue& operator=(const LockedQueue&) = delete;
        LockedQueue& operator=(LockedQueue&&) noexcept = delete;

        /*!
         * \brief Pops item from the queue.
         * \return Item will be returned if the queue is not empty (for both type of locks).
         *         Nothing will be returned if the queue is deactivated (for both type of locks)
         *         or if queue is empty (only for spinlock type of lock).
         *
         * Locks itself in the wait state until new item will be available or queue deactivated.
         */
        std::optional<T> Pop();

        /*!
         * \brief (Exist only for mutex type of lock!) Tries to pop item from the queue.
         * \return Item will be returned if the queue is not empty.
         *         Nothing will be returned if the queue is deactivated or no items were added there during the wait.
         *
         * Lock itself in the wait state until new item will be available or queue deactivated or timeout (100ms).
         */
        template <class TempType = T, class TempLock = LockType>
        typename std::enable_if<std::is_same_v<TempLock, UseMutex>, std::optional<TempType>>::type TryPop();

        /*!
         * \brief Pushes new item to the queue.
         * \param item New item that will be added to the queue as a copy of provided one.
         */
        void Push(const T& item);

        /*!
         * \brief Pushes new item to the queue.
         * \param item new Item that will be moved to the queue.
         */
        void Push(T&& item);

        /*!
         * \brief Activates the queue.
         *
         * When the queue is activated consumers are able to acquire items from it.
         * Otherwise, nothing always will be returned.
         */
        void Activate();

        /*!
         * \brief Deactivates the queue.
         *
         * When the queue is activated consumers are able to acquire items from it.
         * Otherwise, nothing always will be returned.
         */
        void Deactivate();

    private:
        /*! Queue that stores items in it. */
        std::queue<T> _queue;
        /*! Flag that defines if queue will return item by any pop() operation. */
        std::atomic_bool _isActive = true;
        /*! Lock that will be used. */
        ActualLockType _lock;
    };

#include "LockedQueue.inl"

}
