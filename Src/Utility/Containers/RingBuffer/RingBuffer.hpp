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
    template <class T, class A = std::allocator<T> >
    class RingBuffer
    {
    public:
        using allocator_type = A;
        using value_type  = typename A::value_type;
        using reference = typename A::reference;
        using const_reference = typename A::const_reference;
        using difference_type = typename A::difference_type;
        using size_type = typename A::size_type;

        class ConstIterator;
        class ConstReverseIterator;

        /*!
         * \brief Iterator for RingBuffer.
         */
        class Iterator
        {
        public:
            Iterator() = delete;
            Iterator(const Iterator&) = default;
            ~Iterator() = default;

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
            Iterator operator++(int);

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

            friend ConstIterator;
        };
        using iterator = Iterator;

        /*!
         * \brief Const iterator for RingBuffer.
         */
        class ConstIterator
        {
        public:
            ConstIterator() = delete;
            ConstIterator(const ConstIterator&) = default;
            ~ConstIterator() = default;

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
            explicit ConstIterator(size_type index, const RingBuffer<T, A> *ringBuffer);

            /*!
             * \brief Copy constructor creates const iterator from non const iterator.
             * \param iterator - non const iterator.
             */
            ConstIterator(const Iterator& iterator);

            /*!
             * \brief The prefix increment operator.
             * \return Reference to updated iterator.
             */
            ConstIterator &operator++();

            /*!
             * \brief The postfix increment operator
             * \return Iterator without incrementation.
             */
            ConstIterator operator++(int);

            /*!
             * \brief Comparison of two iterators.
             * \param other - other iterator.
             * \return True if iterators are equal. Otherwise - false.
             */
            bool operator==(const ConstIterator& other) const;

            /*!
             * \brief Comparison of two iterators.
             * \param other - other iterator.
             * \return True if iterators are not equal. Otherwise - false.
             */
            bool operator!=(const ConstIterator& other) const;

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
            const RingBuffer<T, A>* _ringBuffer;
        };
        using const_iterator = ConstIterator;

        /*!
         * \brief Reverse iterator for RingBuffer.
         */
        class ReverseIterator
        {
        public:
            ReverseIterator() = delete;
            ReverseIterator(const ReverseIterator&) = default;
            ~ReverseIterator() = default;

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
            explicit ReverseIterator(size_type index, RingBuffer<T, A> *ringBuffer);

            /*!
             * \brief The prefix increment operator.
             * \return Reference to updated iterator.
             */
            ReverseIterator &operator++();

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

            friend ConstReverseIterator;
        };
        using reverse_iterator = ReverseIterator;

        /*!
         * \brief Const reverse iterator for RingBuffer.
         */
        class ConstReverseIterator
        {
        public:
            ConstReverseIterator() = delete;
            ConstReverseIterator(const ConstReverseIterator&) = default;
            ~ConstReverseIterator() = default;

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
            explicit ConstReverseIterator(size_type index, const RingBuffer<T, A> *ringBuffer);

            /*!
             * \brief Copy constructor creates const reverse iterator from non const reverse iterator.
             * \param iterator - non const reverse iterator.
             */
            ConstReverseIterator(const ReverseIterator& iterator);

            /*!
             * \brief The prefix increment operator.
             * \return Reference to updated iterator.
             */
            ConstReverseIterator &operator++();

            /*!
             * \brief The postfix increment operator
             * \return Iterator without incrementation.
             */
            ConstReverseIterator operator++(int);

            /*!
             * \brief Comparison of two iterators.
             * \param other - other iterator.
             * \return True if iterators are equal. Otherwise - false.
             */
            bool operator==(const ConstReverseIterator& other) const;

            /*!
             * \brief Comparison of two iterators.
             * \param other - other iterator.
             * \return True if iterators are not equal. Otherwise - false.
             */
            bool operator!=(const ConstReverseIterator& other) const;

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
            const RingBuffer<T, A> *_ringBuffer;
        };
        using const_reverse_iterator = ConstReverseIterator;

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
         * \brief Returns a const iterator to the beginning of the ring buffer.
         * \return A const iterator to the beginning of the ring buffer.
         */
        ConstIterator begin() const;

        /*!
         * \brief Returns a const iterator to the beginning of the ring buffer.
         * \return A const iterator to the beginning of the ring buffer.
         */
        ConstIterator cbegin() const;

        /*!
         * \brief Returns a reverse iterator to the beginning (actual end) of the ring buffer.
         * \return A reverse iterator to the beginning (actual end) of the ring buffer.
         */
        ReverseIterator rbegin();

        /*!
         * \brief Returns a const reverse iterator to the beginning (actual end) of the ring buffer.
         * \return A const reverse iterator to the beginning (actual end) of the ring buffer.
         */
        ConstReverseIterator rbegin() const;

        /*!
         * \brief Returns a const reverse iterator to the beginning (actual end) of the ring buffer.
         * \return A const reverse iterator to the beginning (actual end) of the ring buffer.
         */
        ConstReverseIterator crbegin() const;

        /*!
         * \brief Returns an iterator to the beginning of the ring buffer.
         * \return An iterator to the beginning of the ring buffer.
         */
        Iterator end();

        /*!
         * \brief Returns a const iterator to the beginning of the ring buffer.
         * \return A const iterator to the beginning of the ring buffer.
         */
        ConstIterator end() const;

        /*!
         * \brief Returns a const iterator to the beginning of the ring buffer.
         * \return A const iterator to the beginning of the ring buffer.
         */
        ConstIterator cend() const;

        /*!
         * \brief Returns a reverse iterator to the end (actual beginning) of the ring buffer.
         * \return A reverse iterator to the end (actual beginning) of the ring buffer.
         */
        ReverseIterator rend();

        /*!
         * \brief Returns a const reverse iterator to the end (actual beginning) of the ring buffer.
         * \return A const reverse iterator to the end (actual beginning) of the ring buffer.
         */
        ConstReverseIterator rend() const;

        /*!
         * \brief Returns a const reverse iterator to the end (actual beginning) of the ring buffer.
         * \return A const reverse iterator to the end (actual beginning) of the ring buffer.
         */
        ConstReverseIterator crend() const;

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
#include "RingBufferConstIterator.inl"
#include "RingBufferReverseIterator.inl"
#include "RingBufferConstReverseIterator.inl"
}