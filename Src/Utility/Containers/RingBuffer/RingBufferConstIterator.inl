#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
RingBuffer<T, A>::ConstIterator::ConstIterator(RingBuffer<T, A>::size_type index, const RingBuffer<T, A>* ringBuffer)
: _index(index)
, _ringBuffer(ringBuffer)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
RingBuffer<T, A>::ConstIterator::ConstIterator(const Iterator& iterator)
: _index(iterator._index)
, _ringBuffer(iterator._ringBuffer)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ConstIterator& RingBuffer<T, A>::ConstIterator::operator++()
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
typename RingBuffer<T, A>::ConstIterator RingBuffer<T, A>::ConstIterator::operator++(int)
{
    ConstIterator newIter = *this;
    ++(*this);

    return newIter;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
bool RingBuffer<T, A>::ConstIterator::operator==(const ConstIterator& other) const
{
    return ((_ringBuffer == other._ringBuffer) && (_index == other._index));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
bool RingBuffer<T, A>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ConstIterator::reference RingBuffer<T, A>::ConstIterator::operator*() const
{
    return _ringBuffer->_buffer[_index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ConstIterator::pointer RingBuffer<T, A>::ConstIterator::operator->() const
{
    return &(_ringBuffer->_buffer[_index]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////