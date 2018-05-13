#include "CppUnitTest.h"
#include "Utility/Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.hpp"
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
    void Producer(LockFreeLinkedQueue<int64_t>& queue, const uint64_t numberOfElements)
    {
        // Use PushBack function
        for (uint64_t i = 0; i < numberOfElements; ++i)
        {
            queue.PushBack(i);
        }
    }
    
    void Consumer(LockFreeLinkedQueue<int64_t>& queue, std::atomic_int64_t& sum)
    {
        // Try to sum all things from queue
        while (const auto node = queue.PopFront())
        {
            sum += *node;
        }
    }

    TEST_CLASS(LockFreeLinkedQueueTests)
    {
    public:
        TEST_METHOD(SingleThreadTest)
        {
            LockFreeLinkedQueue<int64_t> queue;

            // Use PushBack function
            for (uint64_t i = 0; i < _halfOfElements; ++i)
            {
                queue.PushBack(i);
            }
            Assert::IsTrue(queue.GetSize() == _halfOfElements,
                           _ExpectedAndActual(_halfOfElements, queue.GetSize()).c_str());

            // Use EmplaceBack function
            for (uint64_t i = 0; i < _halfOfElements; ++i)
            {
                queue.EmplaceBack(10);
            }
            Assert::IsTrue(queue.GetSize() == (_halfOfElements * 2),
                           _ExpectedAndActual(_halfOfElements * 2, queue.GetSize()).c_str());

            // Check that all nodes were added in and popped out
            int64_t sum(0);
            while (const auto node = queue.PopFront())
            {
                sum += *node;
            }
            Assert::IsTrue(queue.GetSize() == 0, _ExpectedAndActual(0, queue.GetSize()).c_str());
            Assert::IsTrue(sum == 1725, _ExpectedAndActual(1725, sum).c_str());
        }

        TEST_METHOD(MultiThreadedTest)
        {
            LockFreeLinkedQueue<int64_t> queue;
            std::atomic_int64_t sum(0);

            // Producers
            std::thread threadProducer1(&Producer, std::ref(queue), _halfOfElements);
            std::thread threadProducer2(&Producer, std::ref(queue), _halfOfElements);

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

            // Check if everything was consumed and produced and summed up
            Assert::IsTrue(queue.GetSize() == 0, _ExpectedAndActual(0, queue.GetSize()).c_str());
            Assert::IsTrue(sum == 2450, _ExpectedAndActual(2450, sum).c_str());
        }

    private:
        static std::wstring _ExpectedAndActual(const int64_t expected, const int64_t actual)
        {
            std::wstringstream stream;
            stream << L"Expected - " << expected << L". Actual - " << actual << L".";

            return stream.str();
        }

        const uint64_t _halfOfElements = 50;
    };
}