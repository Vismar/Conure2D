#include "Utility/Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.hpp"
#include <thread>
#include <gtest/gtest.h>

/*!
 * \brief Utility function that produces specified number of elements to specific queue.
 * \param queue - queue to which function should add some elements.
 * \param numberOfElements - number of lements that will be added to queue.
 */
void Producer(Conure::Utility::LockFreeLinkedQueue<int64_t>& queue, const uint64_t numberOfElements)
{
    // Use PushBack function
    for (uint64_t i = 0; i < numberOfElements; ++i)
    {
        queue.PushBack(i);
    }
}

/*!
 * \brief Utility function that consumes to specified variable all elements from specific queue.
 * \param queue - queue from which elements will be consumed.
 * \param sum - variable which will accumulate consumed values form queue.
 */
void Consumer(Conure::Utility::LockFreeLinkedQueue<int64_t>& queue, std::atomic_int64_t& sum)
{
    // Try to sum all things from queue
    while (const auto node = queue.PopFront())
    {
        sum += *node;
    }
}

/*! Number of elements that is used in tests. */
constexpr uint64_t NumberOfElements = 50;

/*!
 * Tests PushBack, PopFront and IsEmpty methods.
 */
TEST(LockFreeLinkedQueue, PushBack)
{
    Conure::Utility::LockFreeLinkedQueue<int64_t> queue;

    // Use PushBack function
    for (uint64_t i = 0; i < NumberOfElements; ++i)
    {
        queue.PushBack(i);
    }
    // Check number of elements
    EXPECT_EQ(NumberOfElements, queue.GetSize());

    // Use PopFront function
    for (uint64_t i = 0; i < NumberOfElements; ++i)
    {
        (void)queue.PopFront();
    }
    // Check number of elements
    EXPECT_EQ(0, queue.GetSize());
    EXPECT_TRUE(queue.IsEmpty());
}

/*!
 * Tests EmplaceBack, PopFront and IsEmpty methods.
 */
TEST(LockFreeLinkedQueue, EmplaceBack)
{
    Conure::Utility::LockFreeLinkedQueue<int64_t> queue;

    // Use PushBack function
    for (uint64_t i = 0; i < NumberOfElements; ++i)
    {
        queue.EmplaceBack(i + NumberOfElements);
    }
    // Check number of elements
    EXPECT_EQ(NumberOfElements, queue.GetSize());

    // Use PopFront function
    for (uint64_t i = 0; i < NumberOfElements; ++i)
    {
        (void)queue.PopFront();
    }
    // Check number of elements
    EXPECT_EQ(0, queue.GetSize());
    EXPECT_TRUE(queue.IsEmpty());
}

/*!
 * Tests PushBack, EmplaceBack, PopFront and IsEmpty methods in single thread.
 */
TEST(LockFreeLinkedQueue, ProdAndConsInSingleThread)
{
    Conure::Utility::LockFreeLinkedQueue<int64_t> queue;

    uint64_t expectedSumOfElements(0);
    // Use PushBack function
    for (uint64_t i = 0; i < NumberOfElements; ++i)
    {
        queue.PushBack(i);
        expectedSumOfElements += i;
    }
    EXPECT_EQ(NumberOfElements, queue.GetSize());

    // Use EmplaceBack function
    for (uint64_t i = 0; i < NumberOfElements; ++i)
    {
        queue.EmplaceBack(expectedSumOfElements + i);
        expectedSumOfElements += expectedSumOfElements + i;
    }
    EXPECT_EQ((NumberOfElements * 2), queue.GetSize());

    // Check that all nodes were added in and popped out
    int64_t sum(0);
    while (const auto node = queue.PopFront())
    {
        sum += *node;
    }
    EXPECT_EQ(0, queue.GetSize());
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_EQ(expectedSumOfElements, sum);
}

/*!
 * Tests PushBack, EmplaceBack, PopFront and IsEmpty methods in multiple threads.
 */
TEST(LockFreeLinkedQueue, ProdAndConsInMultipleThreads)
{
    Conure::Utility::LockFreeLinkedQueue<int64_t> queue;
    std::atomic_int64_t sum(0);

    // Producers
    std::thread threadProducer1(&Producer, std::ref(queue), NumberOfElements);
    std::thread threadProducer2(&Producer, std::ref(queue), NumberOfElements);

    // Consumers
    std::thread threadConsumer1(&Consumer, std::ref(queue), std::ref(sum));
    std::thread threadConsumer2(&Consumer, std::ref(queue), std::ref(sum));

    // Join threads
    threadProducer1.join();
    threadProducer2.join();
    threadConsumer1.join();
    threadConsumer2.join();

    // Just be sure that everything was consumed from queue
    Consumer(queue, sum);

    // Calc expected sum ef elements
    uint64_t expectedSumOfElements(0);
    for (auto i = 0; i < NumberOfElements; ++i)
    {
        expectedSumOfElements += i + i;
    }

    // Check if everything was consumed and produced and summed up
    EXPECT_EQ(0, queue.GetSize());
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_EQ(expectedSumOfElements, sum);
}