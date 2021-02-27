#include "GraphicsPipeline.hpp"
#include "VkWrapper/Vertex/Vertex.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

GraphicsPipeline::GraphicsPipeline(VkDevice lDevice,
                                   const PipelineShader& pipelineShader,
                                   VkExtent2D swapChainExtent,
                                   VkRenderPass renderPass)
: _lDevice(lDevice)
{
    TraceIt;

    auto vertexShaderCreationInfo = pipelineShader.GetVertexShaderCreationInfo(_lDevice);
    auto fragmentShaderCreationInfo = pipelineShader.GetFragmentShaderCreationInfo(_lDevice);
    VkPipelineShaderStageCreateInfo shaderStages[] =
    {
        vertexShaderCreationInfo.createInfo,
        fragmentShaderCreationInfo.createInfo
    };

    auto vertexInputInfo = CreateVertexInputStateInfo();
    auto inputAssemblyStateInfo = CreateInputAssemblyStateInfo();
    auto viewport = CreateViewport(swapChainExtent);
    auto scissor = CreateScissor(swapChainExtent);
    auto viewportStateInfo = CreateViewportStateInfo(viewport, scissor);
    auto rasterizationStateInfo = CreateRasterizationStateInfo();
    auto multisampleStateInfo = CreateMultisampleStateInfo();
    auto colorBlendAttachmentState = CreateColorBlendAttachmentState();
    auto colorBlendStateInfo = CreateColorBlendStateInfo(colorBlendAttachmentState);
   /* VkDynamicState dynamicStates[] =
    {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_LINE_WIDTH
    };
    auto dynamicStateInfo = CreateDynamicStateInfo(dynamicStates, static_cast<uint32_t>(std::size(dynamicStates)));*/

    CreatePipelineLayout();

    VkGraphicsPipelineCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = static_cast<uint32_t>(std::size(shaderStages)),
        .pStages = shaderStages,
        .pVertexInputState = &vertexInputInfo,
        .pInputAssemblyState = &inputAssemblyStateInfo,
        .pViewportState = &viewportStateInfo,
        .pRasterizationState = &rasterizationStateInfo,
        .pMultisampleState = &multisampleStateInfo,
        .pDepthStencilState = nullptr,
        .pColorBlendState = &colorBlendStateInfo,
        .pDynamicState = nullptr,//&dynamicStateInfo,
        .layout = _pipelineLayout,
        .renderPass = renderPass,
        .subpass = 0,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1
    };

    Assert(vkCreateGraphicsPipelines(_lDevice, VK_NULL_HANDLE, 1, &createInfo, nullptr, &_pipeline) == VK_SUCCESS,
           "Failed to create graphics pipeline");
}

// ---------------------------------------------------------------------------------------------------------------------

GraphicsPipeline::~GraphicsPipeline()
{
    vkDestroyPipeline(_lDevice, _pipeline, nullptr);
    vkDestroyPipelineLayout(_lDevice, _pipelineLayout, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipeline GraphicsPipeline::GetHandle() const
{
    return _pipeline;
}

// ---------------------------------------------------------------------------------------------------------------------

void GraphicsPipeline::CreatePipelineLayout()
{
    VkPipelineLayoutCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 0,
        .pSetLayouts = nullptr,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr
    };

    Assert(vkCreatePipelineLayout(_lDevice, &createInfo, nullptr, &_pipelineLayout) == VK_SUCCESS,
           "Failed to create pipeline layout");
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipelineVertexInputStateCreateInfo GraphicsPipeline::CreateVertexInputStateInfo()
{
    const auto& bindingDescription = Vertex::GetBindingDescription();
    const auto& attributeDescriptions = Vertex::GetAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &bindingDescription,
        .vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size()),
        .pVertexAttributeDescriptions = attributeDescriptions.data()
    };

    return createInfo;
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipelineInputAssemblyStateCreateInfo GraphicsPipeline::CreateInputAssemblyStateInfo()
{
    VkPipelineInputAssemblyStateCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE
    };

    return createInfo;
}

// ---------------------------------------------------------------------------------------------------------------------

VkViewport GraphicsPipeline::CreateViewport(const VkExtent2D& swapChainExtent)
{
    VkViewport viewport =
    {
        .x = 0.0f,
        .y = 0.0f,
        .width = static_cast<float>(swapChainExtent.width),
        .height = static_cast<float>(swapChainExtent.height),
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };

    return viewport;
}

// ---------------------------------------------------------------------------------------------------------------------

VkRect2D GraphicsPipeline::CreateScissor(const VkExtent2D& swapChainExtent)
{
    VkRect2D scissor =
    {
        .offset = {0, 0},
        .extent = swapChainExtent
    };

    return scissor;
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipelineViewportStateCreateInfo GraphicsPipeline::CreateViewportStateInfo(const VkViewport& viewport,
                                                                            const VkRect2D& scissor)
{
    VkPipelineViewportStateCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .pViewports = &viewport,
        .scissorCount = 1,
        .pScissors = &scissor
    };

    return createInfo;
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipelineRasterizationStateCreateInfo GraphicsPipeline::CreateRasterizationStateInfo()
{
    VkPipelineRasterizationStateCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_BACK_BIT,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f,
        .lineWidth = 1.0f
    };

    return createInfo;
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipelineMultisampleStateCreateInfo GraphicsPipeline::CreateMultisampleStateInfo()
{
    VkPipelineMultisampleStateCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable = VK_FALSE,
        .minSampleShading = 1.0f,
        .pSampleMask = nullptr,
        .alphaToCoverageEnable = VK_FALSE,
        .alphaToOneEnable = VK_FALSE
    };

    return createInfo;
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipelineColorBlendAttachmentState GraphicsPipeline::CreateColorBlendAttachmentState()
{
    VkPipelineColorBlendAttachmentState colorBlendAttachmentState =
    {
        // Pseudo code that demonstrates what happens with the next specified parameters
        // if (blendEnable)
        // {
        //     finalColor.rgb = (srcColorBlendFactor * newColor.rgb) <colorBlendOp> (dstColorBlendFactor * oldColor.rgb);
        //     finalColor.a = (srcAlphaBlendFactor * newColor.a) <alphaBlendOp> (dstAlphaBlendFactor * oldColor.a);
        // }
        // else
        // {
        //     finalColor = newColor;
        // }
        // finalColor = finalColor & colorWriteMask;
        .blendEnable = VK_FALSE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD,
        // Color mask that sets what colors are gonna be used in color blending
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
                          VK_COLOR_COMPONENT_G_BIT |
                          VK_COLOR_COMPONENT_B_BIT |
                          VK_COLOR_COMPONENT_A_BIT
    };

    return colorBlendAttachmentState;
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipelineColorBlendStateCreateInfo GraphicsPipeline::CreateColorBlendStateInfo(
        const VkPipelineColorBlendAttachmentState& colorBlendAttachment)
{
    VkPipelineColorBlendStateCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable = VK_FALSE,
        .logicOp = VK_LOGIC_OP_COPY,
        .attachmentCount = 1,
        .pAttachments = &colorBlendAttachment,
        .blendConstants = { 0.0f, 0.0f, 0.0f, 0.0f}
    };

    return createInfo;
}

// ---------------------------------------------------------------------------------------------------------------------

VkPipelineDynamicStateCreateInfo GraphicsPipeline::CreateDynamicStateInfo(VkDynamicState* dynamicStates,
                                                                          uint32_t size)
{
    VkPipelineDynamicStateCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = size,
        .pDynamicStates = dynamicStates
    };

    return createInfo;
}

// ---------------------------------------------------------------------------------------------------------------------