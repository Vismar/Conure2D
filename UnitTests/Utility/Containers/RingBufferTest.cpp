#include "Utility/Containers/RingBuffer/RingBuffer.hpp"
#include <gtest/gtest.h>

/*!
 * Testing functions Resize() and GetSize()
 */
TEST(RingBuffer, Resize)
{
    Utility::RingBuffer<uint64_t> ringBuffer;

    // Default size
    EXPECT_EQ(10, ringBuffer.GetSize());

    // Check size values that are not accepted by ring buffer
    ringBuffer.Resize(0ll);
    EXPECT_EQ(10, ringBuffer.GetSize());
    ringBuffer.Resize(-1ll);
    EXPECT_EQ(10, ringBuffer.GetSize());

    // Check resize to valid value
    ringBuffer.Resize(20);
    EXPECT_EQ(20, ringBuffer.GetSize());
    ringBuffer.Resize(1);
    EXPECT_EQ(1, ringBuffer.GetSize());

    // Set new size
    ringBuffer.Resize(5);
    // Add entries to the ring buffer
    for (uint64_t i = 0; i < 5; ++i)
    {
        ringBuffer.PushBack(i);
    }
    // Resize ring buffer
    ringBuffer.Resize(10);
    // Add some new entries to the ring buffer
    for (uint64_t i = 5; i < 10; ++i)
    {
        ringBuffer.PushBack(i);
    }
    // Check entry values
    uint64_t checkValue(0);
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(checkValue, entry);
        ++checkValue;
    }

    // Set smaller size of the ring buffer
    ringBuffer.Resize(5);
    // Check entry values
    checkValue = 5;
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(checkValue, entry);
        ++checkValue;
    }
    for (uint64_t i = checkValue; i < checkValue + 2; ++i)
    {
        ringBuffer.PushBack(i);
    }
    checkValue += 2;
    ringBuffer.Resize(10);
    for (uint64_t i = checkValue; i < checkValue + 5; ++i)
    {
        ringBuffer.PushBack(i);
    }
    checkValue = 7;
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
    Utility::RingBuffer<uint64_t> ringBuffer;

    // Add some values to ring buffer
    for (uint64_t i = 0; i < 5; ++i)
    {
        ringBuffer.PushBack(i);
    }

    // Check entries in ring buffer
    uint64_t count(0);
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(5, count);

    // Fill ring buffer with additional values that will overwrite already added entries
    for (uint64_t i = 990; i < 1000; ++i)
    {
        ringBuffer.PushBack(i);
    }

    count = 990;
    // Check entries in ring buffer
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(10, (count - 990));
}

/*!
 * Testing function EmplaceBack()
 */
TEST(RingBuffer, EmplaceBack)
{
    Utility::RingBuffer<uint64_t> ringBuffer;
    const uint64_t addition(1000);

    // Add some values to ring buffer
    for (uint64_t i = 0; i < 5; ++i)
    {
        ringBuffer.EmplaceBack(i + addition);
    }

    // Check entries in ring buffer
    uint64_t count(0 + addition);
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(5, (count - addition));

    // Fill ring buffer with additional values that will overwrite already added entries
    for (uint64_t i = 990; i < 1000; ++i)
    {
        ringBuffer.EmplaceBack(i + addition);
    }

    count = 990 + addition;
    // Check entries in ring buffer
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(10, (count - addition - 990));
}

/*!
 * Testing straight and reverse iterators
 */
TEST(RingBuffer, Iterators)
{
    Utility::RingBuffer<uint64_t> ringBuffer;

    // Add some entries to ring buffer
    for (uint64_t i = 0; i < 10; ++i)
    {
        ringBuffer.PushBack(i);
    }

    // Check entries in ring buffer with straight iterator
    uint64_t count(0);
    for (auto& entry : ringBuffer)
    {
        EXPECT_EQ(count, entry);
        ++count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(10, count);

    // Check entries in ring buffer with reverse iterator
    --count;
    for (auto entry = ringBuffer.rbegin(); entry != ringBuffer.rend(); ++entry)
    {
        EXPECT_EQ(count, *entry );
        --count;
    }
    // Check number of entries in ring buffer
    EXPECT_EQ(0, ++count);
}