#pragma once
#include <cstdint>
#include <vector>

namespace Utility
{
    /*!
     * \brief Container that uses a single, fixed-size buffer as if it were connected end-to-end.
     * \tparam T - type of used data.
     */
    template <class T>
    class RingBuffer
    {
    public:
        class Iterator;
        class ReverseIterator;

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
         * newSize cannot be less than 1 and equal to max size.
         */
        void Resize(typename std::vector<T>::size_type newSize);

        /*!
         * \brief Grabs number of allocated entries.
         * \return Number of allocated entries.
         */
        typename std::vector<T>::size_type GetSize() const;

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
        auto begin();
        
        /*!
         * \brief Returns an iterator to the end of the ring buffer.
         * \return An iterator to the end of the ring buffer.
         */
        auto end();

        /*!
         * \brief Returns an reverse iterator to the beginning (actual end) of the ring buffer.
         * \return A reverse iterator to the beginning (actual end) of the ring buffer.
         */
        auto rbegin();

        /*!
         * \brief Returns an reverse iterator to the end (actual beginning) of the ring buffer.
         * \return A reverse iterator to the end (actual beginning) of the ring buffer.
         */
        auto rend();

    private:
        /*!
         * \brief Validates specified index.
         * \param index - index to check.
         * \return True if specified index is in range between head and tail of the ring. Otherwise - false.
         */
        bool _ValidateIndex(uint64_t index);

        /*!
         * \brief Increases specified index by 1.
         * \param index - index that will be increased.
         *
         * If specified index equal to (_buffer.size()-1), it will cycle the value to 0.
         */
        void _IncreaseIndex(uint64_t& index);

        /*! 
         * \brief Decreases specified index by 1.
         * \param index - index that will be decreased.
         * 
         * If specified index equal to 0, it will cycle the value to (_buffer.size() - 1).
         */
        void _DecreaseIndex(uint64_t& index);

        /*! Simple index that is used by "end" iterator. */
        static const uint64_t EndIndex = INT64_MAX;
        /*! Index of the first entry in the buffer. */
        uint64_t _headIndex;
        /*! Index of the last entry in the buffer. */
        uint64_t _tailIndex;
        /*! Simple inner flag that shows if ring buffer currently is empty or not. */
        bool _empty;
        /*! Buffer that stores data. */
        std::vector<T> _buffer;
    };
}

#include "RingBufferIterator.hpp"
#include "RingBufferReverseIterator.hpp"
#include "RingBuffer.inl"
