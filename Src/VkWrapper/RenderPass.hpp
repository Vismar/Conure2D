#pragma once
#include <vulkan/vulkan.h>

namespace C2D::VkWrapper
{
    class RenderPass final
    {
    public:
        RenderPass(VkDevice lDevice, VkFormat swapChainImageFormat);
        ~RenderPass();

        [[nodiscard]]
        VkRenderPass GetHandle() const;

    private:
        VkDevice _lDevice;
        VkRenderPass _renderPass{};
    };
}