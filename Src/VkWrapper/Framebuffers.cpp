#include "Framebuffers.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Framebuffers::Framebuffers(VkDevice lDevice,
                           const SwapChainImageViews& swapChainImageViews,
                           VkRenderPass renderPass,
                           VkExtent2D swapChainExtent)
: _lDevice(lDevice)
{
    TraceIt;

    const auto& imageViews = swapChainImageViews.GetImageViews();
    _framebuffers.resize(imageViews.size());
    for (size_t i = 0; i < imageViews.size(); ++i)
    {
        VkImageView attachments[] =
        {
            imageViews[i]
        };

        VkFramebufferCreateInfo createInfo =
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = renderPass,
            .attachmentCount = static_cast<uint32_t>(std::size(attachments)),
            .pAttachments = attachments,
            .width = swapChainExtent.width,
            .height = swapChainExtent.height,
            .layers = 1
        };

        Assert(vkCreateFramebuffer(_lDevice, &createInfo, nullptr, &_framebuffers[i]) == VK_SUCCESS,
               "Failed to create framebuffer");
    }
}

// ---------------------------------------------------------------------------------------------------------------------

Framebuffers::~Framebuffers()
{
    for (auto frameBuffer : _framebuffers)
    {
        vkDestroyFramebuffer(_lDevice, frameBuffer, nullptr);
    }
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VkFramebuffer>& Framebuffers::GetFramebuffers() const
{
    return _framebuffers;
}

// ---------------------------------------------------------------------------------------------------------------------