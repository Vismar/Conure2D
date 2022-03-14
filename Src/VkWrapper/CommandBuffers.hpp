#pragma once
#include <vector>
#include <memory>
#include <vulkan/vulkan.h>
#include <VkWrapper/Vertex/VertexBufferArray.hpp>
#include <VkWrapper/GraphicsPipeline.hpp>
#include <VkWrapper/Shader/ShaderManager.hpp>

namespace C2D::VkWrapper
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
        CommandBuffers(VkDevice lDevice, size_t size, VkCommandPool commandPool);
        ~CommandBuffers();

        void RecordCommandBuffer(uint32_t commandBufferIndex,
                                 VkRenderPass renderPass,
                                 const VkFramebuffer& frameBuffer,
                                 VkExtent2D swapChainExtent,
                                 const std::vector<std::unique_ptr<GraphicsPipeline>>& graphicsPipelines,
                                 std::reference_wrapper<std::unique_ptr<ShaderManager>> shaderManager,
                                 VkClearValue* clearValue);

        [[nodiscard]]
        const std::vector<VkCommandBuffer>& GetCommandBuffers() const;

    private:
        VkDevice _lDevice;
        VkCommandPool _commandPool;
        std::vector<VkCommandBuffer> _commandBuffers;
    };
}