#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
RingBuffer<T>::Iterator::Iterator(uint64_t index, RingBuffer<T>* ringBuffer) : _index(index), _ringBuffer(ringBuffer)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename RingBuffer<T>::Iterator& RingBuffer<T>::Iterator::operator++()
{
    // If stored index is equal to the end index, that means that we should do nothing here
    if (_index != EndIndex)
    {
        // Check pointer to the ring buffer
        if (_ringBuffer != nullptr)
        {
            // If stored index is equal to tail, then next iterator should point to the end
            if (_index == _ringBuffer->_tailIndex)
            {
                _index = EndIndex;
            }
            else
            {
                _ringBuffer->_IncreaseIndex(_index);
            }
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename RingBuffer<T>::Iterator RingBuffer<T>::Iterator::operator++(int)
{
    Iterator newIter = *this;
    ++(*this);

    return newIter;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool RingBuffer<T>::Iterator::operator==(Iterator other) const
{
    return ((_ringBuffer == other._ringBuffer) && (_index == other._index));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool RingBuffer<T>::Iterator::operator!=(Iterator other) const
{
    return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
T& RingBuffer<T>::Iterator::operator*() const
{
    return _ringBuffer->_buffer[_index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
const T* RingBuffer<T>::Iterator::operator->() const
{
    return &(_ringBuffer->_buffer[_index]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
