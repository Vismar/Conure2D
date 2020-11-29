#include "SwapChain.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

SwapChain::SwapChain(VkDevice lDevice,
                     VkSurfaceKHR surface,
                     const SuitablePDevice& pDevice,
                     const GLFWWrapper::Window& window)
: _lDevice(lDevice)
{
    TraceIt;

    // Get swap chain setting
    // TODO: This part must be rewritten later so it will be possible to determine best settings at the start
    //       or use already selected previously.
    auto swapChainDetail = pDevice.GetSwapChainDetails();
    const auto& surfaceFormat = ChooseSwapSurfaceFormat(swapChainDetail.GetFormats());
    _imageFormat = surfaceFormat.format;
    const auto presentMode = ChooseSwapPresentMode(swapChainDetail.GetPresentModes());
    _extent = ChooseSwapExtent(swapChainDetail.GetCapabilities(), window);

    // Get image counter
    uint32_t imageCount = swapChainDetail.GetCapabilities().minImageCount + 1;
    std::clamp(imageCount,
               swapChainDetail.GetCapabilities().minImageCount,
               swapChainDetail.GetCapabilities().maxImageCount);

    // Create createInfo for swap chain
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = _extent;
    createInfo.imageArrayLayers = 1; // Should always be 1 until this thing well be used for stereoscopic 3D application
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    const uint32_t indices[] =
    {
            pDevice.GetQueueFamilyIndices().GetGraphicsFamily().value(),
            pDevice.GetQueueFamilyIndices().GetPresentFamily().value()
    };
    if (pDevice.GetQueueFamilyIndices().GetGraphicsFamily() != pDevice.GetQueueFamilyIndices().GetPresentFamily())
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = static_cast<uint32_t>(std::size(indices));
        createInfo.pQueueFamilyIndices = indices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }
    createInfo.preTransform = swapChainDetail.GetCapabilities().currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE; // Turn it off if all pixels should be readable to create final image
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    Assert(vkCreateSwapchainKHR(_lDevice, &createInfo, nullptr, &_swapChain) == VK_SUCCESS,
           "Failed to create swap chain");

    // Obtain swap chain images
    vkGetSwapchainImagesKHR(_lDevice, _swapChain, &imageCount, nullptr);
    _images.resize(imageCount);
    vkGetSwapchainImagesKHR(_lDevice, _swapChain, &imageCount, _images.data());
}

// ---------------------------------------------------------------------------------------------------------------------

SwapChain::~SwapChain()
{
    vkDestroySwapchainKHR(_lDevice, _swapChain, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

VkFormat SwapChain::GetImageFormat() const
{
    return _imageFormat;
}

// ---------------------------------------------------------------------------------------------------------------------

const VkExtent2D& SwapChain::GetExtent() const
{
    return _extent;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VkImage>& SwapChain::GetImages() const
{
    return _images;
}

// ---------------------------------------------------------------------------------------------------------------------

VkSwapchainKHR SwapChain::GetHandle() const
{
    return _swapChain;
}

// ---------------------------------------------------------------------------------------------------------------------

const VkSurfaceFormatKHR& SwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats)
{
    for (const auto& format : formats)
    {
        if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return format;
        }
    }

    return formats.front();
}

// ---------------------------------------------------------------------------------------------------------------------

VkPresentModeKHR SwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& presentModes)
{
    for (const auto& presentMode : presentModes)
    {
        if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return presentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

// ---------------------------------------------------------------------------------------------------------------------

VkExtent2D SwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, const GLFWWrapper::Window& window)
{
    auto [width, height] = window.GetFrameBufferSize();
    VkExtent2D extent2D = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
    extent2D.width = std::max(capabilities.minImageExtent.width,
                              std::min(capabilities.maxImageExtent.width, extent2D.width));
    extent2D.height = std::max(capabilities.minImageExtent.height,
                               std::min(capabilities.maxImageExtent.height, extent2D.height));

    return extent2D;
}

// ---------------------------------------------------------------------------------------------------------------------