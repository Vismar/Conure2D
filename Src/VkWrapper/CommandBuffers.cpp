#include "CommandBuffers.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

CommandBuffers::CommandBuffers(VkDevice lDevice,
                               size_t size,
                               VkCommandPool commandPool,
                               VkRenderPass renderPass,
                               const std::vector<VkFramebuffer>& frameBuffers,
                               VkExtent2D swapChainExtent,
                               VkPipeline pipeline)
: _lDevice(lDevice)
{
    TraceIt;

    _commandBuffers.resize(size);

    VkCommandBufferAllocateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = static_cast<uint32_t>(size)
    };

    Assert(vkAllocateCommandBuffers(_lDevice, &createInfo, _commandBuffers.data()) == VK_SUCCESS,
           "Failed to allocate command buffers");

    for (size_t i = 0; i < size; ++i)
    {
        VkCommandBufferBeginInfo beginInfo =
        {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .flags = 0,
            .pInheritanceInfo = nullptr
        };

        Assert(vkBeginCommandBuffer(_commandBuffers[i], &beginInfo) == VK_SUCCESS,
               "Failed to begin recording command buffer");

        VkClearValue clearValue = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        VkRenderPassBeginInfo renderPassBeginInfo =
        {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .renderPass = renderPass,
            .framebuffer = frameBuffers[i],
            .renderArea =
            {
                .offset = {0, 0},
                .extent = swapChainExtent,
            },
            .clearValueCount = 1,
            .pClearValues = &clearValue
        };

        vkCmdBeginRenderPass(_commandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
            vkCmdDraw(_commandBuffers[i], 3, 1, 0, 0);
        vkCmdEndRenderPass(_commandBuffers[i]);

        Assert(vkEndCommandBuffer(_commandBuffers[i]) == VK_SUCCESS, "Failed to record command buffer");
    }
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VkCommandBuffer>& CommandBuffers::GetCommandBuffers() const
{
    return _commandBuffers;
}

// ---------------------------------------------------------------------------------------------------------------------