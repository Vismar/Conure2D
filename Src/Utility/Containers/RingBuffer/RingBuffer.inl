#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
RingBuffer<T>::RingBuffer() : _headIndex(0), _tailIndex(0), _empty(true)
{
    _buffer.resize(10);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void RingBuffer<T>::Resize(uint64_t newSize)
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
                    uint64_t leftShift(0ll);
                    uint64_t rightShift(0ll);

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

template <class T>
uint64_t RingBuffer<T>::GetSize() const
{
    return _buffer.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void RingBuffer<T>::PushBack(const T& entry)
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
        _IncreaseIndex(_tailIndex);

        // If tail and head indexes are equal, increase head index
        if (_tailIndex == _headIndex)
        {
            _IncreaseIndex(_headIndex);
        }

        _buffer[_tailIndex] = entry;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void RingBuffer<T>::EmplaceBack(T&& entry)
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
        _IncreaseIndex(_tailIndex);

        // If tail and head indexes are equal, increase head index
        if (_tailIndex == _headIndex)
        {
            _IncreaseIndex(_headIndex);
        }

        _buffer[_tailIndex] = entry;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename RingBuffer<T>::Iterator RingBuffer<T>::begin()
{
    uint64_t requiredIndex = _headIndex;
    
    // If buffer is still empty, we should return "end" iterator
    if (_empty)
    {
        requiredIndex = EndIndex;
    }

    return Iterator(requiredIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename RingBuffer<T>::Iterator RingBuffer<T>::end()
{
    return Iterator(EndIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename RingBuffer<T>::ReverseIterator RingBuffer<T>::rbegin()
{
    uint64_t requiredIndex = _tailIndex;

    // If buffer is still empty, we should return "end" iterator
    if (_empty)
    {
        requiredIndex = EndIndex;
    }

    return ReverseIterator(requiredIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename RingBuffer<T>::ReverseIterator RingBuffer<T>::rend()
{
    return ReverseIterator(EndIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool RingBuffer<T>::_ValidateIndex(const uint64_t index)
{
    bool valid(true);

    // if index is bigger or equal to the buffer size, index is not valid
    if (index >= _buffer.size())
    {
        valid = false;
    }
    // If tail index is bigger than head index (not cycled yet) and tail index is not reached the end of a buffer,
    // we should check if specified index is in range between tail index and end of the buffer.
    // If so - index is not valid.
    else if ((_tailIndex > _headIndex) && (_tailIndex < (_buffer.size() - 1)))
    {
        valid = index > _tailIndex ? false : true;
    }

    return valid;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void RingBuffer<T>::_IncreaseIndex(uint64_t& index)
{
    if (++index >= _buffer.size())
    {
        index = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void RingBuffer<T>::_DecreseIndex(uint64_t& index)
{
    if (index == 0)
    {
        index = _buffer.size() - 1;
    }
    else
    {
        --index;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
