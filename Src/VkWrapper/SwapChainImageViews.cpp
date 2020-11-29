#include "SwapChainImageViews.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

SwapChainImageViews::SwapChainImageViews(VkDevice lDevice, const SwapChain& swapChain)
: _lDevice(lDevice)
{
    TraceIt;

    const auto& swapChainImages = swapChain.GetImages();

    _imageViews.resize(swapChainImages.size());
    for (size_t i = 0; i < swapChainImages.size(); ++i)
    {
        VkImageViewCreateInfo createInfo =
        {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = swapChainImages[i],
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = swapChain.GetImageFormat(),
            .components =
            {
                .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                .a = VK_COMPONENT_SWIZZLE_IDENTITY,
            },
            .subresourceRange =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1
            }
        };

        Assert(vkCreateImageView(_lDevice, &createInfo, nullptr, &_imageViews[i]) == VK_SUCCESS,
               "Failed to create image view");
    }
}



// ---------------------------------------------------------------------------------------------------------------------

SwapChainImageViews::~SwapChainImageViews()
{
    for (auto imageView : _imageViews)
    {
        vkDestroyImageView(_lDevice, imageView, nullptr);
    }
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VkImageView>& SwapChainImageViews::GetImageViews() const
{
    return _imageViews;
}

// ---------------------------------------------------------------------------------------------------------------------