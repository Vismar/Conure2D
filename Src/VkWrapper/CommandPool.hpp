#pragma once
#include <vulkan/vulkan.h>

namespace VkWrapper
{
    class CommandPool final
    {
    public:
        CommandPool(VkDevice lDevice, uint32_t graphicsFamilyIndex);
        ~CommandPool();

        [[nodiscard]]
        VkCommandPool GetHandle() const;

    private:
        VkDevice _lDevice;
        VkCommandPool _commandPool;
    };
}