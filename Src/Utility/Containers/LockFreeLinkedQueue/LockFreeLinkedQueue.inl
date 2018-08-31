#pragma once

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

template <class T>
uint64_t LockFreeLinkedQueue<T>::GetSize() const
{
    return _size.load();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool LockFreeLinkedQueue<T>::IsEmpty() const
{
    return _size.load() == 0;
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
