#pragma once
#include <vulkan/vulkan.h>

namespace VkWrapper
{
    class Semaphore final
    {
    public:
        explicit Semaphore(VkDevice lDevice);
        ~Semaphore();

        [[nodiscard]]
        VkSemaphore GetHandle() const;

    private:
        VkDevice _lDevice;
        VkSemaphore _semaphore;
    };
}