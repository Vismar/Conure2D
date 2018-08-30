#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
RingBuffer<T, A>::ReverseIterator::ReverseIterator(size_type index, RingBuffer<T, A>* ringBuffer)
: _index(index)
, _ringBuffer(ringBuffer)
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ReverseIterator& RingBuffer<T, A>::ReverseIterator::operator++()
{
    // If stored index is equal to the end index, that means that we should do nothing here
    if (_index != RingBuffer<T, A>::EndIndex)
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
                // Decrease index
                _ringBuffer->_ChangeIndex(_index, -1);
            }
        }
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ReverseIterator RingBuffer<T, A>::ReverseIterator::operator++(int)
{
    ReverseIterator newIter = *this;
    ++(*this);

    return newIter;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
bool RingBuffer<T, A>::ReverseIterator::operator==(const ReverseIterator& other) const
{
    return ((_ringBuffer == other._ringBuffer) && (_index == other._index));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
bool RingBuffer<T, A>::ReverseIterator::operator!=(const ReverseIterator& other) const
{
    return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ReverseIterator::reference RingBuffer<T, A>::ReverseIterator::operator*() const
{
    return _ringBuffer->_buffer[_index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ReverseIterator::pointer RingBuffer<T, A>::ReverseIterator::operator->() const
{
    return &(_ringBuffer->_buffer[_index]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////