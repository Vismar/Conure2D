#pragma once
#include <vector>
#include <vulkan/vulkan.h>

namespace VkWrapper
{
    /*!
     *
     *
     * \note Command buffers will be automatically freed when their command pool is destroyed,
     *       so there is no need an explicit cleanup.
     */
    class CommandBuffers final
    {
    public:
        CommandBuffers(VkDevice lDevice,
                       size_t size,
                       VkCommandPool commandPool,
                       VkRenderPass renderPass,
                       const std::vector<VkFramebuffer>& frameBuffers,
                       VkExtent2D swapChainExtent,
                       VkPipeline pipeline);

        [[nodiscard]]
        const std::vector<VkCommandBuffer>& GetCommandBuffers() const;

    private:
        VkDevice _lDevice;
        std::vector<VkCommandBuffer> _commandBuffers;
    };
}