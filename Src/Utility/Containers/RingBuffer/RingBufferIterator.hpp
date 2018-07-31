#pragma once
#include "RingBuffer.hpp"

namespace Utility
{
    /*!
     * \brief Iterator for RingBuffer.
     * \tparam T - type of used data.
     */
    template<class T>
    class RingBuffer<T>::Iterator
    {
    public:
        using difference_type = T;
        using value_type = T;
        using pointer = const T *;
        using reference = const T &;
        using iterator_category = std::forward_iterator_tag;

        /*!
         * \brief Constructor.
         * \param index - index of an entry.
         * \param ringBuffer - pointer to the ring buffer.
         */
        explicit Iterator(uint64_t index, RingBuffer<T> *ringBuffer);

        /*!
         * \brief The prefix increment operator.
         * \return Reference to updated iterator.
         */
        Iterator &operator++();

        /*!
         * \brief The postfix increment operator
         * \return Iterator without incrementation.
         */
        Iterator operator++(int);

        /*!
         * \brief Comparison of two iterators.
         * \param other - other iterator.
         * \return True if iterators are equal. Otherwise - false.
         */
        bool operator==(Iterator other) const;

        /*!
         * \brief Comparison of two iterators.
         * \param other - other iterator.
         * \return True if iterators are not equal. Otherwise - false.
         */
        bool operator!=(Iterator other) const;

        /*!
         * \brief The member access operator.
         * \return Pointer to the value on which iterator is pointing.
         */
        T &operator*() const;

        /*!
         * \brief The member access operator.
         * \return Pointer to the value on which iterator is pointing.
         */
        const T *operator->() const;

    private:
        /*! Index of an entry two which iterator is pointing. */
        uint64_t _index;
        /*! Pointer to the ring buffer to which entries iterator is pointing. */
        RingBuffer<T> *_ringBuffer;
    };

}
#include "RingBufferIterator.inl"