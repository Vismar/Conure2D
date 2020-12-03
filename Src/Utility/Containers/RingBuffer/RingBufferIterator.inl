#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
RingBuffer<T, A>::Iterator::Iterator(RingBuffer<T, A>::size_type index,
                                                      RingBuffer<T, A>* ringBuffer)
: _index(index)
, _ringBuffer(ringBuffer)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::Iterator& RingBuffer<T, A>::Iterator::operator++()
{
    // If stored index is equal to the end index, that means that we should do nothing here
    if (_index != RingBuffer<T>::EndIndex)
    {
        // Check pointer to the ring buffer
        if (_ringBuffer != nullptr)
        {
            // If stored index is equal to tail, then next iterator should point to the end
            if (_index == _ringBuffer->_tailIndex)
            {
                _index = RingBuffer<T>::EndIndex;
            }
            else
            {
                // Increase index
                _ringBuffer->_ChangeIndex(_index, 1);
            }
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
const typename RingBuffer<T, A>::Iterator RingBuffer<T, A>::Iterator::operator++(int)
{
    Iterator newIter = *this;
    ++(*this);

    return newIter;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
bool RingBuffer<T, A>::Iterator::operator==(const Iterator& other) const
{
    return ((_ringBuffer == other._ringBuffer) && (_index == other._index));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
bool RingBuffer<T, A>::Iterator::operator!=(const Iterator& other) const
{
    return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::Iterator::reference RingBuffer<T, A>::Iterator::operator*() const
{
    return _ringBuffer->_buffer[_index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::Iterator::pointer RingBuffer<T, A>::Iterator::operator->() const
{
    return &(_ringBuffer->_buffer[_index]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////