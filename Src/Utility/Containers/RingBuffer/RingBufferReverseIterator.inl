#pragma once
#include "RingBufferReverseIterator.hpp"

namespace Utility
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
RingBuffer<T>::ReverseIterator::ReverseIterator(uint64_t index, RingBuffer<T>* ringBuffer)
: _index(index)
, _ringBuffer(ringBuffer)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename RingBuffer<T>::ReverseIterator& RingBuffer<T>::ReverseIterator::operator++()
{
    // If stored index is equal to the end index, that means that we should do nothing here
    if (_index != RingBuffer<T>::EndIndex)
    {
        // Check pointer to the ring buffer
        if (_ringBuffer != nullptr)
        {
            // If stored index is equal to tail, then next iterator should point to the end
            if (_index == _ringBuffer->_headIndex)
            {
                _index = RingBuffer<T>::EndIndex;
            }
            else
            {
                _ringBuffer->_DecreaseIndex(_index);
            }
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename RingBuffer<T>::ReverseIterator RingBuffer<T>::ReverseIterator::operator++(int)
{
    ReverseIterator newIter = *this;
    ++(*this);

    return newIter;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool RingBuffer<T>::ReverseIterator::operator==(ReverseIterator other) const
{
    return ((_ringBuffer == other._ringBuffer) && (_index == other._index));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool RingBuffer<T>::ReverseIterator::operator!=(ReverseIterator other) const
{
    return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
T& RingBuffer<T>::ReverseIterator::operator*() const
{
    return _ringBuffer->_buffer[_index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
const T* RingBuffer<T>::ReverseIterator::operator->() const
{
    return &(_ringBuffer->_buffer[_index]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}