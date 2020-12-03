#pragma once
#include <vector>
#include <limits>
#include <algorithm>

namespace C2D
{
    /*!
     * \brief Container that uses a single, fixed-size buffer as if it were connected end-to-end.
     * \tparam T - type of used data.
     */
    template <class T, class A = std::allocator<T>>
    class RingBuffer
    {
    public:
        using value_type  = typename A::value_type;
        using size_type = typename A::size_type;

        /*!
         * \brief Iterator for RingBuffer.
         */
        class Iterator
        {
        public:
            Iterator() = delete;
            Iterator(const Iterator&) = default;
            ~Iterator() = default;

            using value_type = T;
            using pointer = const T*;
            using reference = const T&;

            /*!
             * \brief Constructor.
             * \param index - index of an entry.
             * \param ringBuffer - pointer to the ring buffer.
             */
            explicit Iterator(size_type index, RingBuffer<T, A> *ringBuffer);

            /*!
             * \brief The prefix increment operator.
             * \return Reference to updated iterator.
             */
            Iterator &operator++();

            /*!
             * \brief The postfix increment operator
             * \return Iterator without incrementation.
             */
            const Iterator operator++(int);

            /*!
             * \brief Comparison of two iterators.
             * \param other - other iterator.
             * \return True if iterators are equal. Otherwise - false.
             */
            bool operator==(const Iterator& other) const;

            /*!
             * \brief Comparison of two iterators.
             * \param other - other iterator.
             * \return True if iterators are not equal. Otherwise - false.
             */
            bool operator!=(const Iterator& other) const;

            /*!
             * \brief The member access operator.
             * \return Pointer to the value on which iterator is pointing.
             */
            reference operator*() const;

            /*!
             * \brief The member access operator.
             * \return Pointer to the value on which iterator is pointing.
             */
            pointer operator->() const;

        private:
            /*! Index of an entry two which iterator is pointing. */
            size_type _index;
            /*! Pointer to the ring buffer to which entries iterator is pointing. */
            RingBuffer<T, A>* _ringBuffer;
        };
        using iterator = Iterator;

        /*!
         * \brief Reverse iterator for RingBuffer.
         */
        class ReverseIterator
        {
        public:
            ReverseIterator() = delete;
            ReverseIterator(const ReverseIterator&) = default;
            ~ReverseIterator() = default;

            using value_type = T;
            using pointer = const T *;
            using reference = const T &;

            /*!
             * \brief Constructor.
             * \param index - index of an entry.
             * \param ringBuffer - pointer to the ring buffer.
             */
            explicit ReverseIterator(size_type index, RingBuffer<T, A> *ringBuffer);

            /*!
             * \brief The prefix increment operator.
             * \return Reference to updated iterator.
             */
            ReverseIterator& operator++();

            /*!
             * \brief The postfix increment operator
             * \return Iterator without incrementation.
             */
            const ReverseIterator operator++(int);

            /*!
             * \brief Comparison of two iterators.
             * \param other - other iterator.
             * \return True if iterators are equal. Otherwise - false.
             */
            bool operator==(const ReverseIterator& other) const;

            /*!
             * \brief Comparison of two iterators.
             * \param other - other iterator.
             * \return True if iterators are not equal. Otherwise - false.
             */
            bool operator!=(const ReverseIterator& other) const;

            /*!
             * \brief The member access operator.
             * \return Pointer to the value on which iterator is pointing.
             */
            reference operator*() const;

            /*!
             * \brief The member access operator.
             * \return Pointer to the value on which iterator is pointing.
             */
            pointer operator->() const;

        private:
            /*! Index of an entry two which iterator is pointing. */
            size_type _index;
            /*! Pointer to the ring buffer to which entries iterator is pointing. */
            RingBuffer<T, A> *_ringBuffer;
        };

        RingBuffer(const RingBuffer& other) = default;
        RingBuffer(RingBuffer&& other) noexcept = default;
        RingBuffer& operator=(const RingBuffer& other) = default;
        RingBuffer& operator=(RingBuffer&& other) noexcept = default;
        ~RingBuffer() = default;

        /*!
         * \brief Default constructor.
         */
        RingBuffer();

        /*!
         * \brief Resizes ring buffer.
         * \param newSize - new size of the ring buffer.
         *
         * newSize cannot be less than 1 and equal to the max size.
         */
        void Resize(size_type newSize);

        /*!
         * \brief Grabs number of allocated entries.
         * \return Number of allocated entries.
         */
        size_type GetSize() const;

        /*!
         * \brief Adds new entry to the end of ring buffer.
         * \param entry - new entry that will be copied to the ring buffer.
         *
         * If tail of the ring buffer overlaps its head upon adding new entry,
         * new entry will replace head entry and starting index will be moved to the next stored entry.
         */
        void PushBack(const T& entry);

        /*!
         * \brief Adds new entry to the end of ring buffer.
         * \param entry - new entry that will be moved to the ring buffer.
         *
         * If tail of the ring buffer overlaps its head upon adding new entry,
         * new entry will replace head entry and starting index will be moved to the next stored entry.
         */
        void EmplaceBack(T&& entry);

        /*!
         * \brief Returns an iterator to the beginning of the ring buffer.
         * \return An iterator to the beginning of the ring buffer.
         */
        Iterator begin();

        /*!
         * \brief Returns a reverse iterator to the beginning (actual end) of the ring buffer.
         * \return A reverse iterator to the beginning (actual end) of the ring buffer.
         */
        ReverseIterator rbegin();

        /*!
         * \brief Returns an iterator to the beginning of the ring buffer.
         * \return An iterator to the beginning of the ring buffer.
         */
        Iterator end();

        /*!
         * \brief Returns a reverse iterator to the end (actual beginning) of the ring buffer.
         * \return A reverse iterator to the end (actual beginning) of the ring buffer.
         */
        ReverseIterator rend();

    private:
        /*!
         * \brief Validates specified index.
         * \param index - index to check.
         * \return True if specified index is in range between head and tail of the ring. Otherwise - false.
         */
        bool _ValidateIndex(size_type index);

        /*!
         * \brief Changes specified index by specified value
         *        and make sure that new index value will be in the range of buffer indices.
         * \param index - index that will be changed.
         * \param diff - diff of value.
         */
        void _ChangeIndex(size_type& index, size_type diff) const;

        /*! Simple index that is used by "end" iterator. */
        static const size_type EndIndex = std::numeric_limits<size_type>::max();
        /*! Index of the first entry in the buffer. */
        size_type _headIndex;
        /*! Index of the last entry in the buffer. */
        size_type _tailIndex;
        /*! Simple inner flag that shows if ring buffer currently is empty or not. */
        bool _empty;
        /*! Buffer that stores data. */
        std::vector<T, A> _buffer;
    };

#include "RingBuffer.inl"
#include "RingBufferIterator.inl"
#include "RingBufferReverseIterator.inl"
}