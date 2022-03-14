#pragma once
#include <VkWrapper/Shader/PipelineShader.hpp>
#include <VkWrapper/SwapChain.hpp>

namespace C2D::VkWrapper
{
    class GraphicsPipeline final
    {
    public:
        GraphicsPipeline(VkDevice lDevice,
                         const PipelineShader& pipelineShader,
                         VkExtent2D swapChainExtent,
                         VkRenderPass renderPass);
        ~GraphicsPipeline();

        [[nodiscard]]
        const std::string& Name() const;

        [[nodiscard]]
        VkPipeline GetHandle() const;

    private:
        void CreatePipelineLayout();

        static VkPipelineVertexInputStateCreateInfo CreateVertexInputStateInfo();
        static VkPipelineInputAssemblyStateCreateInfo CreateInputAssemblyStateInfo();
        static VkViewport CreateViewport(const VkExtent2D& swapChainExtent);
        static VkRect2D CreateScissor(const VkExtent2D& swapChainExtent);
        static VkPipelineViewportStateCreateInfo CreateViewportStateInfo(const VkViewport& viewport,
                                                                         const VkRect2D& scissor);
        static VkPipelineRasterizationStateCreateInfo CreateRasterizationStateInfo();
        static VkPipelineMultisampleStateCreateInfo CreateMultisampleStateInfo();
        static VkPipelineColorBlendAttachmentState CreateColorBlendAttachmentState();
        static VkPipelineColorBlendStateCreateInfo CreateColorBlendStateInfo(
                const VkPipelineColorBlendAttachmentState& colorBlendAttachment);
        static VkPipelineDynamicStateCreateInfo CreateDynamicStateInfo(VkDynamicState* dynamicStates, uint32_t size);

        std::string _name;
        VkDevice _lDevice;
        VkPipelineLayout _pipelineLayout{};
        VkPipeline _pipeline{};
    };
}