#include "CppUnitTest.h"
#include "Utility/Containers/RingBuffer/RingBuffer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
    TEST_CLASS(RingBufferTests)
    {
    public:
        /*!
         * Testing functions Resize() and GetSize()
         */
        TEST_METHOD(Resize)
        {
            RingBuffer<uint64_t> ringBuffer;

            // Default size
            Assert::IsTrue(ringBuffer.GetSize() == 10, L"Wrong initial size. Should be == 10.");

            // Check size values that are not accepted by ring buffer
            ringBuffer.Resize(0ll);
            Assert::IsTrue(ringBuffer.GetSize() == 10, L"Resize goes wrong. New size value == 0 should be ignored.");
            ringBuffer.Resize(-1ll);
            Assert::IsTrue(ringBuffer.GetSize() == 10, L"Resize goes wrong. New size value == -1 should be ignored.");

            // Check resize to valid value
            ringBuffer.Resize(20);
            Assert::IsTrue(ringBuffer.GetSize() == 20, L"Resize goes wrong. New size should be == 20.");
            ringBuffer.Resize(1);
            Assert::IsTrue(ringBuffer.GetSize() == 1, L"Resize goes wrong. New size should be == 1.");

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
                Assert::IsTrue(entry == checkValue, L"Resize to bigger number goes wrong.");
                ++checkValue;
            }

            // Set smaller size of the ring buffer
            ringBuffer.Resize(5);
            // Check entry values
            checkValue = 5;
            for (auto& entry : ringBuffer)
            {
                Assert::IsTrue(entry == checkValue, L"Resize to lower number goes wrong.");
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
                Assert::IsTrue(entry == checkValue, L"Resize to bigger number with shifted ring buffer goes wrong.");
                ++checkValue;
            }
        }

        /*!
         * Testing function PushBack()
         */
        TEST_METHOD(PushBack)
        {
            RingBuffer<uint64_t> ringBuffer;

            // Add some values to ring buffer
            for (uint64_t i = 0; i < 5; ++i)
            {
                ringBuffer.PushBack(i);
            }

            // Check entries in ring buffer
            uint64_t count(0);
            for (auto& entry : ringBuffer)
            {
                Assert::IsTrue(entry == count, L"Wrong entry value #1");
                ++count;
            }
            // Check number of entries in ring buffer
            Assert::IsTrue(count == 5, L"Wrong number of entries #1");

            // Fill ring buffer with additional values that will overwrite already added entries
            for (uint64_t i = 990; i < 1000; ++i)
            {
                ringBuffer.PushBack(i);
            }

            count = 990;
            // Check entries in ring buffer
            for (auto& entry : ringBuffer)
            {
                Assert::IsTrue(entry == count, L"Wrong entry value #2");
                ++count;
            }
            // Check number of entries in ring buffer
            Assert::IsTrue((count - 990) == 10, L"Wrong number of entries #2");
        }

        /*!
         * Testing function EmplaceBack()
         */
        TEST_METHOD(EmplaceBack)
        {
            RingBuffer<uint64_t> ringBuffer;
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
                Assert::IsTrue(entry == count, L"Wrong entry value #1");
                ++count;
            }
            // Check number of entries in ring buffer
            Assert::IsTrue((count - addition) == 5, L"Wrong number of entries #1");

            // Fill ring buffer with additional values that will overwrite already added entries
            for (uint64_t i = 990; i < 1000; ++i)
            {
                ringBuffer.EmplaceBack(i + addition);
            }

            count = 990 + addition;
            // Check entries in ring buffer
            for (auto& entry : ringBuffer)
            {
                Assert::IsTrue(entry == count, L"Wrong entry value #2");
                ++count;
            }
            // Check number of entries in ring buffer
            Assert::IsTrue((count - addition - 990) == 10, L"Wrong number of entries #2");
        }

        /*!
         * Testing straight and reverse iterators
         */
        TEST_METHOD(Iterators)
        {
            RingBuffer<uint64_t> ringBuffer;

            // Add some entries to ring buffer
            for (uint64_t i = 0; i < 10; ++i)
            {
                ringBuffer.PushBack(i);
            }

            // Check entries in ring buffer with straight iterator
            uint64_t count(0);
            for (auto& entry : ringBuffer)
            {
                Assert::IsTrue(entry == count, L"Wrong entry value #1");
                ++count;
            }
            // Check number of entries in ring buffer
            Assert::IsTrue(count == 10, L"Wrong number of entries #1");

            // Check entries in ring buffer with reverse iterator
            --count;
            for (auto entry = ringBuffer.rbegin(); entry != ringBuffer.rend(); ++entry)
            {
                Assert::IsTrue(*entry == count, L"Wrong entry value #2");
                --count;
            }
            // Check number of entries in ring buffer
            Assert::IsTrue(++count == 0, L"Wrong number of entries #2");
        }
    };
}