#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
RingBuffer<T, A>::RingBuffer() : _headIndex(0), _tailIndex(0), _empty(true)
{
    _buffer.resize(10);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
void RingBuffer<T, A>::Resize(size_type newSize)
{
    // RingBuffer cannot have number of elements less than 1
    if (newSize >= 1 && newSize < EndIndex)
    {
        // If a new size is smaller than a current one, we must be sure that
        // only entries at the start of the buffer would be affected.
        if (newSize < _buffer.size())
        {
            // We should rotate vector in two cases:
            // - if tail index is bigger or equal to the new size
            // - head index is bigger than tail index (which means vector is rotated)
            // And we must be sure that new tail index will be equal to last index in the new vector
            if (_tailIndex >= newSize || _tailIndex < _headIndex)
            {
                // Get new tail index
                const auto newTailIndex = newSize - 1;

                // If new tail index not equal to current tail index, we should rotate vector
                if (newTailIndex != _tailIndex)
                {
                    size_type leftShift(0ll);
                    size_type rightShift(0ll);

                    // If tail index is bigger than new tail index,
                    // we should check in which direction rotation will be more efficient
                    if (_tailIndex > newTailIndex)
                    {
                        leftShift = _tailIndex - newTailIndex;
                        rightShift = _buffer.size() - _tailIndex + newTailIndex;
                    }
                    else if (_tailIndex < newTailIndex)
                    {
                        leftShift = _tailIndex + (_buffer.size() - newTailIndex);
                        rightShift = newTailIndex - _tailIndex;
                    }

                    // Use left rotation if left shift is lesser than right one
                    if (leftShift < rightShift)
                    {
                        std::rotate(_buffer.begin(), _buffer.begin() + leftShift, _buffer.end());
                    }
                    else
                    {
                        std::rotate(_buffer.rbegin(), _buffer.rbegin() + rightShift, _buffer.rend());
                    }
                }

                // Reset indexes
                _headIndex = 0;
                _tailIndex = newTailIndex;
            }

            // Resize buffer
            _buffer.resize(newSize);
        }
        // If a new size is bigger than a current one, we should rotate vector in such way
        // that head of the ring would be at the start of the vector
        else if (newSize > _buffer.size())
        {
            // If head of the ring is not at the start of the vector, we should rotate vector before resizing it
            if (_headIndex > 0)
            {
                // If head index is closer to the start of vector, use left rotation
                if (_headIndex < (_buffer.size() - _headIndex))
                {
                    std::rotate(_buffer.begin(), _buffer.begin() + _headIndex, _buffer.end());
                }
                // If head index is closer to the end of vector (or distance is equal), use right rotation
                else
                {
                    std::rotate(_buffer.rbegin(), _buffer.rbegin() + (_buffer.size() - _headIndex), _buffer.rend());
                }

                // Reset indexes
                _headIndex = 0;
                _tailIndex = _buffer.size() - 1;
            }

            // Resize buffer
            _buffer.resize(newSize);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::size_type RingBuffer<T, A>::GetSize() const
{
    return _buffer.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
void RingBuffer<T, A>::PushBack(const T& entry)
{
    // If empty flag is true and tail and head indexes are equal, that means buffer is empty
    // and we should just assign new value to the first buffer element
    if (_empty && (_tailIndex == _headIndex))
    {
        _buffer[_tailIndex] = entry;

        _empty = false;
    }
    // If tail and head indexes are different then just do a common indexes shifts and other operations
    else
    {
        _ChangeIndex(_tailIndex, 1);
        //_IncreaseIndex(_tailIndex);

        // If tail and head indexes are equal, increase head index
        if (_tailIndex == _headIndex)
        {
            _ChangeIndex(_headIndex, 1);
        }

        _buffer[_tailIndex] = entry;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
void RingBuffer<T, A>::EmplaceBack(T&& entry)
{
    // If empty flag is true and tail and head indexes are equal, that means buffer is empty
    // and we should just assign new value to the first buffer element
    if (_empty && (_tailIndex == _headIndex))
    {
        _buffer[_tailIndex] = entry;

        _empty = false;
    }
    // If tail and head indexes are different then just do a common indexes shifts and other operations
    else
    {
        _ChangeIndex(_tailIndex, 1);
        //_IncreaseIndex(_tailIndex);

        // If tail and head indexes are equal, increase head index
        if (_tailIndex == _headIndex)
        {
            _ChangeIndex(_headIndex, 1);
        }

        _buffer[_tailIndex] = entry;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::Iterator RingBuffer<T, A>::begin()
{
    size_type requiredIndex = _headIndex;

    // If buffer is still empty, we should return "end" iterator
    if (_empty)
    {
        requiredIndex = EndIndex;
    }

    return Iterator(requiredIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ReverseIterator RingBuffer<T, A>::rbegin()
{
    size_type requiredIndex = _tailIndex;

    // If buffer is still empty, we should return "end" iterator
    if (_empty)
    {
        requiredIndex = EndIndex;
    }

    return ReverseIterator(requiredIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::Iterator RingBuffer<T, A>::end()
{
    return Iterator(EndIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
typename RingBuffer<T, A>::ReverseIterator RingBuffer<T, A>::rend()
{
    return ReverseIterator(EndIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
bool RingBuffer<T, A>::_ValidateIndex(const size_type index)
{
    bool valid(true);

    // If index is bigger or equal to the buffer size, index is not valid
    if (index >= _buffer.size())
    {
        valid = false;
    }
    // If tail index is bigger than head index (not cycled yet) and tail index is not reached the end of a buffer,
    // we should check if specified index is in range between tail index and end of the buffer.
    // If so - index is not valid.
    else if ((_tailIndex > _headIndex) && (_tailIndex < (_buffer.size() - 1)))
    {
        valid = index <= _tailIndex;
    }

    return valid;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class A>
void RingBuffer<T, A>::_ChangeIndex(size_type &index, size_type diff) const
{
    index += diff;
    const auto bufferSize = _buffer.size();

    // If the new index value is bigger than buffer size
    // then we should continuously make it is smaller
    // until it will be in the range
    while (index >= bufferSize)
    {
        index -= bufferSize;
    }

    // If the new index value is lesser than buffer size
    // then we should continuously make it is bigger
    // until it will be in the range
    while (index < 0)
    {
        index += bufferSize;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
