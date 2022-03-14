#include "CommandBuffers.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

CommandBuffers::CommandBuffers(VkDevice lDevice, size_t size, VkCommandPool commandPool)
: _lDevice(lDevice)
, _commandPool(commandPool)
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
}

// ---------------------------------------------------------------------------------------------------------------------

CommandBuffers::~CommandBuffers()
{
    vkFreeCommandBuffers(_lDevice,
                         _commandPool,
                         static_cast<uint32_t>(_commandBuffers.size()),
                         _commandBuffers.data());
}

// ---------------------------------------------------------------------------------------------------------------------

void CommandBuffers::RecordCommandBuffer(uint32_t commandBufferIndex,
                                         VkRenderPass renderPass,
                                         const VkFramebuffer& frameBuffer,
                                         VkExtent2D swapChainExtent,
                                         const std::vector<std::unique_ptr<GraphicsPipeline>>& graphicsPipelines,
                                         std::reference_wrapper<std::unique_ptr<ShaderManager>> shaderManager,
                                         VkClearValue* clearValue)
{
    VkCommandBufferBeginInfo beginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        .pInheritanceInfo = nullptr
    };

    Assert(vkBeginCommandBuffer(_commandBuffers[commandBufferIndex], &beginInfo) == VK_SUCCESS,
           "Failed to begin recording command buffer");

    VkRenderPassBeginInfo renderPassBeginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = renderPass,
        .framebuffer = frameBuffer,
        .renderArea =
        {
            .offset = {0, 0},
            .extent = swapChainExtent,
        },
        .clearValueCount = clearValue == nullptr ? 0u : 1u,
        .pClearValues = clearValue
    };

    vkCmdBeginRenderPass(_commandBuffers[commandBufferIndex], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    for (auto& graphicsPipeline : graphicsPipelines)
    {
        vkCmdBindPipeline(_commandBuffers[commandBufferIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->GetHandle());
        shaderManager.get()->GetPipelineShader(graphicsPipeline->Name()).SubmitUserCommands(_commandBuffers[commandBufferIndex]);
    }

    vkCmdEndRenderPass(_commandBuffers[commandBufferIndex]);

    Assert(vkEndCommandBuffer(_commandBuffers[commandBufferIndex]) == VK_SUCCESS,
           "Failed to record command buffer");
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VkCommandBuffer>& CommandBuffers::GetCommandBuffers() const
{
    return _commandBuffers;
}

// ---------------------------------------------------------------------------------------------------------------------