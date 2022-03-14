#pragma once
#include <vulkan/vulkan.h>

namespace C2D::VkWrapper
{
    class CommandPool final
    {
    public:
        CommandPool(VkDevice lDevice, uint32_t graphicsFamilyIndex);
        ~CommandPool();

        void Reset();

        [[nodiscard]]
        VkCommandPool GetHandle() const;

    private:
        VkDevice _lDevice;
        VkCommandPool _commandPool;
    };
}