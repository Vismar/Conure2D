#pragma once
#include <memory>
#include <atomic>

namespace Utility
{
    /*!
     * \brief A lock-free linked queue.
     * \tparam T - Type that will be stored in queue.
     * 
     * Pretty simple lock-free linked queue which designed to guarantee push/pop operations
     * to be executed simultaneously without any synchronization via mutexes or similar things.
     */
    template <class T>
    class LockFreeLinkedQueue
    {
        /*!
         * \brief Simple node that contains data and pointers to the next and previous nodes.
         */
        struct Node
        {
            /*! Data of the node. */
            T data;
            /*! Pointer to a new node. */
            std::shared_ptr<Node> nextNode;
            /*! Pointer to a previous node. */
            std::shared_ptr<Node> prevNode;
        };

    public:
        LockFreeLinkedQueue(const LockFreeLinkedQueue& other) = delete;
        LockFreeLinkedQueue(LockFreeLinkedQueue&& other) = delete;
        LockFreeLinkedQueue& operator=(const LockFreeLinkedQueue& other) = delete;
        LockFreeLinkedQueue& operator=(LockFreeLinkedQueue&& other) = delete;
        ~LockFreeLinkedQueue() = default;

        /*!
         * \brief Helper class which is used to return stored data in the LockFreeLinkedQueue.
         * 
         * Provides functionality to check if any data exist in the stored node 
         * and obtain it via operators *() and ->().
         */
        class Reference
        {
        public:
            Reference() = delete;
            Reference(const Reference& other) = default;
            Reference(Reference&& other) noexcept = default;
            Reference& operator=(const Reference& other) = default;
            Reference& operator=(Reference&& other) noexcept = default;
            ~Reference() = default;

            /*!
             * \brief Constructor with parameter.
             * \param node - node that will be stored inside the Reference.
             */
            explicit Reference(std::shared_ptr<Node>& node);

            /*!
             * \brief Explicit conversation to bool to check if reference stores something.
             */
            explicit operator bool() const;

            /*!
             * \brief Returns stored data in a node.
             * \return A reference to a data which is stored in a node.
             */
            T& operator*() const;

            /*!
             * \brief Returns stored data in a node.
             * \return Pointer to a data which is stored in a node.
             */
            T* operator->() const;

        private:
            /*! Pointer to a node which contains data. */
            std::shared_ptr<Node> _node;
        };

        /*!
         * \brief Default constructor.
         */
        LockFreeLinkedQueue();

        /*!
         * \brief Adds a new element to the end of the queue.
         * \param data - const reference to a new element.
         */
        void PushBack(const T& data);

        /*!
         * \brief Adds a new element to the end of the queue.
         * \param data - new element that will be moved to the queue.
         */
        void EmplaceBack(T&& data);

        /*!
         * \brief Removes first element in the queue and returns it.
         * \return An element which was removed from the queue.
         */
        Reference PopFront();

        /*!
         * \brief Gets number of elements in the linked queue.
         * \return Number of elements in the linked queue.
         */
        uint64_t GetSize() const;

        /*!
         * \brief Check if queue has not entries.
         * \return True size of queue is 0. Otherwise - false.
         */
        bool IsEmpty() const;

    private:
        /*!
         * \brief Add new node to the end of the queue.
         * \param newTailNode - new node which will become a new tail of the queue.
         */
        void _AddToTheBack(const std::shared_ptr<Node>& newTailNode);

        /*! The head of the linked queue. */
        std::shared_ptr<Node> _head;
        /*! The tail of the linked queue. */
        std::shared_ptr<Node> _tail;
        /*! Number of elements in the linked queue. */
        std::atomic_uint64_t _size;
    };

#include "LockFreeLinkedQueue.inl"
}
