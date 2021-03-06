#pragma once
#include <vulkan/vulkan.h>

namespace VkWrapper
{
    class Fence final
    {
    public:
        explicit Fence(VkDevice lDevice);
        ~Fence();

        [[nodiscard]]
        const VkFence& GetHandle() const;

    private:
        VkDevice _lDevice;
        VkFence _fence;
    };
}