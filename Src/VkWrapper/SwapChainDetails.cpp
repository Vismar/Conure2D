#include "SwapChainDetails.hpp"

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

SwapChainDetails::SwapChainDetails(VkPhysicalDevice pDevice, VkSurfaceKHR surface)
{
    // Get capabilities
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pDevice, surface, &_capabilities);

    // Get formats
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(pDevice, surface, &formatCount, nullptr);
    if (formatCount != 0)
    {
        _formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(pDevice, surface, &formatCount, _formats.data());
    }

    // Get present modes
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(pDevice, surface, &presentModeCount, nullptr);
    if (presentModeCount != 0)
    {
        _presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(pDevice, surface, &presentModeCount, _presentModes.data());
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bool SwapChainDetails::IsAdequate() const
{
    return !_formats.empty() && !_presentModes.empty();
}

// ---------------------------------------------------------------------------------------------------------------------

const VkSurfaceCapabilitiesKHR& SwapChainDetails::GetCapabilities() const
{
    return _capabilities;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VkSurfaceFormatKHR>& SwapChainDetails::GetFormats() const
{
    return _formats;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VkPresentModeKHR>& SwapChainDetails::GetPresentModes() const
{
    return _presentModes;
}

// ---------------------------------------------------------------------------------------------------------------------