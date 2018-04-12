#pragma once

/*!
 * \brief Reverse iterator for RingBuffer.
 * \tparam T - type of used data.
 */
template <class T>
class RingBuffer<T>::ReverseIterator
{
public:
    using difference_type = T;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::forward_iterator_tag;

    /*!
     * \brief Constructor.
     * \param index - index of an entry.
     * \param ringBuffer - pointer to the ring buffer.
     */
    explicit ReverseIterator(uint64_t index, RingBuffer<T>* ringBuffer);

    /*!
     * \brief The prefix increment operator.
     * \return Reference to updated iterator.
     */
    ReverseIterator& operator++();

    /*!
     * \brief The postfix increment operator
     * \return Iterator without incrementation.
     */
    ReverseIterator operator++(int);

    /*!
     * \brief Comparison of two iterators.
     * \param other - other iterator.
     * \return True if iterators are equal. Otherwise - false.
     */
    bool operator==(ReverseIterator other) const;

    /*!
     * \brief Comparison of two iterators.
     * \param other - other iterator.
     * \return True if iterators are not equal. Otherwise - false.
     */
    bool operator!=(ReverseIterator other) const;

    /*!
     * \brief The member access operator.
     * \return Pointer to the value on which iterator is pointing.
     */
    T& operator*() const;

    /*!
     * \brief The member access operator.
     * \return Pointer to the value on which iterator is pointing.
     */
    const T* operator->() const;

private:
    /*! Index of an entry two which iterator is pointing. */
    uint64_t _index;
    /*! Pointer to the ring buffer to which entries iterator is pointing. */
    RingBuffer<T>* _ringBuffer;
};

#include "RingBufferReverseIterator.inl"