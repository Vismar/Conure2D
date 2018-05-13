#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
LockFreeLinkedQueue<T>::Reference::Reference(std::shared_ptr<Node>& node) : _node(node)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
LockFreeLinkedQueue<T>::Reference::operator bool() const
{
    return _node ? true : false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
T& LockFreeLinkedQueue<T>::Reference::operator*() const
{
    return _node->data;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
T* LockFreeLinkedQueue<T>::Reference::operator->() const
{
    return &_node->data;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
LockFreeLinkedQueue<T>::LockFreeLinkedQueue() : _size(0)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void LockFreeLinkedQueue<T>::PushBack(const T& data)
{
    // Create new tail node
    auto newTailNode = std::make_shared<Node>();
    newTailNode->data = data;
    newTailNode->prevNode = std::atomic_load(&_tail);

    _AddToTheBack(newTailNode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void LockFreeLinkedQueue<T>::EmplaceBack(T&& data)
{
    // Create new tail node
    auto newTailNode = std::make_shared<Node>();
    newTailNode->data = std::move(data);    
    newTailNode->prevNode = std::atomic_load(&_tail);

    _AddToTheBack(newTailNode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
typename LockFreeLinkedQueue<T>::Reference LockFreeLinkedQueue<T>::PopFront()
{
    // Check if head node contain something
    auto headNode = std::atomic_load(&_head);
    if (headNode)
    {
        // Use next node of the current head node as a new head node
        //auto nextNodeOfHeadNode = std::atomic_load(&headNode->nextNode);
        while (!std::atomic_compare_exchange_weak(&_head, &headNode, headNode->nextNode)) {}

        // If head node still exist
        if (headNode)
        {
            // Check next node
            auto nextNodeOfHeadNode = std::atomic_load(&headNode->nextNode);
            // If next node was empty, set it as tail
            if (!nextNodeOfHeadNode)
            {
                auto currentTailNode = std::atomic_load(&_tail);
                while (!std::atomic_compare_exchange_weak(&_tail, &currentTailNode, headNode->nextNode)) {}
            }
            // If next node was not empty, reset the previous node which it stores
            else
            {
                auto prevNodeOfNextNode = std::atomic_load(&nextNodeOfHeadNode->prevNode);
                while (!std::atomic_compare_exchange_weak(&nextNodeOfHeadNode->prevNode, &prevNodeOfNextNode, headNode->nextNode)) {}
            }

            // Reset pointers of all stored nodes to prevent unnecessary use of them
            headNode->prevNode.reset();
            headNode->nextNode.reset();

            // Decrement a number of elements
            --_size;
        }
    }

    return Reference(headNode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
uint64_t LockFreeLinkedQueue<T>::GetSize() const
{
    return _size.load();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void LockFreeLinkedQueue<T>::_AddToTheBack(const std::shared_ptr<Node>& newTailNode)
{
    // Set new tail node
    while (!std::atomic_compare_exchange_weak(&_tail, &newTailNode->prevNode, newTailNode)) {}

    // Check previous node
    auto prevTailNode = std::atomic_load(&newTailNode->prevNode);
    // If previous node was empty, set new node as head
    if (!prevTailNode)
    {
        prevTailNode = std::atomic_load(&_head);
        while (!std::atomic_compare_exchange_weak(&_head, &prevTailNode, newTailNode)) {}
    }
    // If previous node was not empty, set new tail node as next node for previous node
    else
    {
        auto nextNodeOfPreviousNode = std::atomic_load(&prevTailNode->nextNode);
        while (!std::atomic_compare_exchange_weak(&prevTailNode->nextNode, &nextNodeOfPreviousNode, newTailNode)) {}
    }

    // Increment a number of elements
    ++_size;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
