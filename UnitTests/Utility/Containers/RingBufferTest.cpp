#include "Utility/Containers/RingBuffer/RingBuffer.hpp"
#include <gtest/gtest.h>

/*!
 * Testing functions Resize() and GetSize()
 */
TEST(RingBuffer, Resize)
{
    C2D::RingBuffer<uint64_t> ringBuffer;

    // Default size
    EXPECT_EQ(10ull, ringBuffer.GetSize());

    // Check size values that are not accepted by ring buffer
    ringBuffer.Resize(0);
    EXPECT_EQ(10ull, ringBuffer.GetSize());

    // Check resize to valid value
    ringBuffer.Resize(20ull);
    EXPECT_EQ(20ull, ringBuffer.GetSize());
    ringBuffer.Resize(1ull);
    EXPECT_EQ(1ull, ringBuffer.GetSize());

    // Set new size
    ringBuffer.Resize(5ull);
    // Add entries to the ring buffer
    for (uint64_t i = 0ull; i < 5ull; ++i)
    {
        ringBuffer.PushBack(i);
    }
    // Resize ring buffer
    ringBuffer.Resize(10ull);
    // Add some new entries to the ring buffer
    for (uint64_t i = 5ull; i < 10ull; ++i)
    {
        ringBuffer.PushBack(i);
    }
    // Check entry values
    uint64_t checkValue(0ull);
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(checkValue, entry);
        ++checkValue;
    }

    // Set smaller size of the ring buffer
    ringBuffer.Resize(5ull);
    // Check entry values
    checkValue = 5ull;
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(checkValue, entry);
        ++checkValue;
    }
    for (uint64_t i = checkValue; i < checkValue + 2ull; ++i)
    {
        ringBuffer.PushBack(i);
    }
    checkValue += 2ull;
    ringBuffer.Resize(10ull);
    for (uint64_t i = checkValue; i < checkValue + 5ull; ++i)
    {
        ringBuffer.PushBack(i);
    }
    checkValue = 7ull;
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(checkValue, entry);
        ++checkValue;
    }
}

/*!
 * Testing function PushBack()
 */
TEST(RingBuffer, PushBack)
{
    C2D::RingBuffer<uint64_t> ringBuffer;

    // Add some values to ring buffer
    for (uint64_t i = 0ull; i < 5ull; ++i)
    {
        ringBuffer.PushBack(i);
    }

    // Check entries in ring buffer
    uint64_t count(0ull);
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(5ull, count);

    // Fill ring buffer with additional values that will overwrite already added entries
    for (uint64_t i = 990ull; i < 1000ull; ++i)
    {
        ringBuffer.PushBack(i);
    }

    count = 990ull;
    // Check entries in ring buffer
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(10ull, (count - 990ull));
}

/*!
 * Testing function EmplaceBack()
 */
TEST(RingBuffer, EmplaceBack)
{
    C2D::RingBuffer<uint64_t> ringBuffer;
    const uint64_t addition(1000ull);

    // Add some values to ring buffer
    for (uint64_t i = 0ull; i < 5ull; ++i)
    {
        ringBuffer.EmplaceBack(i + addition);
    }

    // Check entries in ring buffer
    uint64_t count(0ull + addition);
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(5ull, (count - addition));

    // Fill ring buffer with additional values that will overwrite already added entries
    for (uint64_t i = 990ull; i < 1000ull; ++i)
    {
        ringBuffer.EmplaceBack(i + addition);
    }

    count = 990ull + addition;
    // Check entries in ring buffer
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(10ull, (count - addition - 990ull));
}

/*!
 * Testing straight and reverse iterators
 */
TEST(RingBuffer, Iterator)
{
    C2D::RingBuffer<uint64_t> ringBuffer;
    std::vector<uint64_t> vector;

    // Add some entries to ring buffer
    for (uint64_t i = 0ull; i < 10ull; ++i)
    {
        ringBuffer.PushBack(i);
        vector.push_back(i);
    }

    // Check entries in ring buffer with straight iterator
    uint64_t count(0ull);
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        EXPECT_EQ(vector[count], entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(10ull, count);
}

TEST(RingBuffer, ReverseIterator)
{
    C2D::RingBuffer<uint64_t> ringBuffer;
    std::vector<uint64_t> vector;

    // Add some entries to ring buffer
    for (uint64_t i = 0ull; i < 10ull; ++i)
    {
        ringBuffer.PushBack(i);
        vector.push_back(i);
    }

    // Check entries in ring buffer with reverse iterator
    uint64_t count = 9ull;
    for (auto entry = ringBuffer.rbegin(); entry != ringBuffer.rend(); ++entry)
    {
        EXPECT_EQ(count, *entry );
        EXPECT_EQ(vector[count], *entry);
        --count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(0ull, ++count);
}